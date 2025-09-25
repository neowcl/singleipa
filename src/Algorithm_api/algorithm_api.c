/**
  * @brief   api transform to X58X
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#include "string.h"


#include "algorithm_api.h"
#include "task.h"
#include "block_command.h"
#include "standard_data_cmd.h"
#include "life_time_collect.h"

#define SOH_ALGORITHM_ENABLE 0

#if SOH_ALGORITHM_ENABLE
#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "soh_model.h"          /* Model's header file */
#include "rtwtypes.h"
#endif

void init_EEP_data(void);

/**
  * @brief  算法参数初始化
  * @param  None
  * @retval None
  */
void algorithm_init(void)
{
    #if SOH_ALGORITHM_ENABLE
        soh_model_initialize();
    #endif
    bms_algorithm_initialize();      //算法参数初始化
    init_EEP_data();                 //读取flash里面的参数，作为算法的输入
    init_soc_input_state();          //SOC输入状态初始化
}

/**
  * @brief  算法执行
  * @param  None
  * @retval None
  */
void algorithm_run(void)
{
    //bms_algorithm_step();
    #if SOH_ALGORITHM_ENABLE
        update_soc_val_to_SOH_alg();
        soh_model_step(); // 循环调用SOH主体函数
    #endif
}


#define SOC_PARA_FLASH_ADDR 0x0000EC00
#define SOC_PARA_FLASH_SIZE 32
#define SOC_PARA_FLASH_NUM  (64/SOC_PARA_FLASH_SIZE)

int8_t check_buf_0xFF(uint8_t *buf, uint8_t size)
{
    uint8_t i;
    for(i = 0; i < size; i++)
    {
        if(buf[i] != 0xFF)
        {
            return -1;
        }
    }
    return 0;
}

extern uint16_t fmc_tick_cnt;

#if 0
//0xD000 是SOC参数区域
#define SOC_PARA_FLASH_ADDR 0x0000CE00
#define SOC_PARA_FLASH_SIZE 32
#define SOC_PARA_FLASH_NUM  (512/SOC_PARA_FLASH_SIZE)


uint8_t cal_crc8_check(unsigned char *data, unsigned char len);

/**
  * @brief  校验参数格式是否正确
  * @param  None
  * @retval None
  */
int8_t check_soc_EEP_param(uint8_t *buf)
{
    soc_para_t *soc_para;
    uint8_t crc8_val = 0;
    soc_para = (soc_para_t*) buf;
    if(soc_para->flag != 0xAA)
    {
        return -1;
    }
    crc8_val = cal_crc8_check(&buf[2], sizeof(soc_para_t) - 2);//扣去flag crc 2bytes
    if(crc8_val != soc_para->crc8)
    {
        return -2;
    }
    return 0;
}



/**
  * @brief  读取SOC 从flash
  * @param  None
  * @retval None
  */
int8_t read_soc_EEP_param_flash(uint8_t page_num, soc_para_t *soc_para)
{
    uint8_t read_buf[SOC_PARA_FLASH_SIZE];
    soc_para_t *temp_soc_para;
    uint8_t crc8_val = 0;

    if(page_num >= SOC_PARA_FLASH_NUM){
        return -1;
    }

    gcr_reg_unlock(); //unlock flash
    flash_page_read(SOC_PARA_FLASH_ADDR + page_num*SOC_PARA_FLASH_SIZE, SOC_PARA_FLASH_SIZE, read_buf);
    gcr_reg_lock(); //lock flash
    if(check_soc_EEP_param(read_buf) == 0) // flash 0k
    {
        temp_soc_para = (soc_para_t*) read_buf;
        soc_para->_CntCCEEPSub = temp_soc_para->_CntCCEEPSub;
        soc_para->_SOHBatEEPSub = temp_soc_para->_SOHBatEEPSub;
        soc_para->_SOCBatDispEEPSub = temp_soc_para->_SOCBatDispEEPSub;
        soc_para->_SOCCellEEPSub = temp_soc_para->_SOCCellEEPSub;
        soc_para->_QDisChgEEPSub = temp_soc_para->_QDisChgEEPSub;
        soc_para->_QChgEEPSub = temp_soc_para->_QChgEEPSub;
        return 0;
    }
    if(check_buf_0xFF(read_buf,SOC_PARA_FLASH_SIZE) == 0) //all is 0xFF
    {
        return 1;
    }
    return -2;
}



/**
  * @brief  写参数入flash
  * @param  None
  * @retval None
  */
void write_soc_EEP_param_flash(soc_para_t soc_para)
{
    soc_para_t read_soc_param;

    uint8_t i;
    int8_t res;
    /*遍历存储*/
    for(i = 0; i < SOC_PARA_FLASH_NUM; i++)
    {
        res = read_soc_EEP_param_flash(i, &read_soc_param);
        if(res != 0) //read fail
        {
            break;
        }
    }
    /*遍历都没有全FF 或校验失败，从头开始*/
    if((i >= SOC_PARA_FLASH_NUM)||(res < 0))
    {
        i = 0;
    }

    soc_para.flag = 0xAA;
    soc_para.index = 0;
    soc_para.crc8 = cal_crc8_check((uint8_t *)&soc_para.index, sizeof(soc_para_t) - 2); //扣去flag crc 2bytes

    gcr_reg_unlock();
    if(res != 1)    // 如果是全FF不用erase
    {
        flash_page_erase(SOC_PARA_FLASH_ADDR);
        fmc_tick_cnt++;
    }
    flash_page_write(SOC_PARA_FLASH_ADDR+i*SOC_PARA_FLASH_SIZE, SOC_PARA_FLASH_SIZE, (uint8_t *)&soc_para);
    gcr_reg_lock();
}

/**
  * @brief  init_EEP_data
  * @param  None
  * @retval None
  */
void init_EEP_data(void)
{
    int8_t i;
    soc_para_t soc_para;

    bms_algorithm_U.InpEEPBusSub1.inp_FlgEEPReadFinSub_ob = 0;
    bms_algorithm_U.InpEEPBusSub1.inp_SOHBatEEPSub_os_pct = 100;
    //if(check_soc_para(read_buf) == 0) // flash 0k
    for(i = SOC_PARA_FLASH_NUM-1; i >= 0; i--)
    {
        if(read_soc_EEP_param_flash(i, &soc_para) == 0)
        {
            bms_algorithm_U.InpEEPBusSub1.inp_SOCBatDispEEPSub_os_pct = soc_para._SOCBatDispEEPSub;
            bms_algorithm_U.InpEEPBusSub1.inp_SOCCellEEPSub_vs_pct = soc_para._SOCCellEEPSub;//SOCCellEEPSub; //no array
            bms_algorithm_U.InpEEPBusSub1.inp_SOHBatEEPSub_os_pct = soc_para._SOHBatEEPSub;
            bms_algorithm_U.InpEEPBusSub1.soh_CntCCEEPSub_os = soc_para._CntCCEEPSub;
            bms_algorithm_U.InpEEPBusSub1.soh_QChgEEPSub_os_Ah = soc_para._QChgEEPSub;
            bms_algorithm_U.InpEEPBusSub1.soh_QDisChgEEPSub_os_Ah = soc_para._QDisChgEEPSub;
            bms_algorithm_U.InpEEPBusSub1.inp_FlgEEPReadFinSub_ob = 1;
            last_soc_val = soc_para._SOCBatDispEEPSub;
            EEP_soc_val = soc_para._SOCBatDispEEPSub;
            //set_reg_value_u16(REGTYPE_REGISTER, regRemainingCapacityAlarm, 0, (int16_t)(EEP_soc_val+0.5));
            break;
        }
    }

    if(SafetyConfig._Signature[0] == 0x55)
    {
        sys_seal_type = SYS_SEALED;
    }else{
        sys_seal_type = SYS_FULL_ACCESS;
    }
}
#endif


/****************
* 检查值的有效范围
*
****************/
int8_t check_soc_EEP_param(EEPdata_t *soc_para)
{
    if(soc_para->_FlgEEPReadFinSub != 1)
    {
        return -1;
    }

    if(soc_para->_SOHBatEEPSub > 100)   //50-100
    {
        return -2;
    }else if(soc_para->_SOHBatEEPSub < 50) {
        return -12;
    }

    if(soc_para->_SOCBatDispEEPSub > 100) //0-100
    {
        return -3;
    }else if(soc_para->_SOCBatDispEEPSub < 0) {
        return -13;
    }

    if(soc_para->_SOCCellEEPSub > 100) //0-100
    {
        return -4;
    }else if(soc_para->_SOCCellEEPSub < 0) {
        return -14;
    }

    if(soc_para->_CntCCEEPSub > 10000) //0-10000
    {
        return -5;
    }else if(soc_para->_CntCCEEPSub < 0) {
        return -15;
    }

    return 0;
}

/**************
* 存储地址 0xEC00
* 存储为两块，一块32个字节
* 注意后面还有lifetime数据
*0 - ok
***************/
//void read_SOC_EEP_data()
int8_t read_soc_EEP_param_flash(uint8_t page_num, EEPdata_t *soc_para)
{
    //EEPdata_t  EEPdata;
    uint8_t read_buf[SOC_PARA_FLASH_SIZE];
    EEPdata_t *temp_soc_para;

    if(page_num >= SOC_PARA_FLASH_NUM){
        return -1;
    }

    gcr_reg_unlock(); // unlock flash
    flash_page_read((uint32_t)&EEPdata + page_num * SOC_PARA_FLASH_SIZE, SOC_PARA_FLASH_SIZE, read_buf);
    gcr_reg_lock();   // lock flash
    temp_soc_para = (EEPdata_t *)read_buf;

    if(check_soc_EEP_param(temp_soc_para) == 0) //检查有效位
    {
        soc_para->_CntCCEEPSub = temp_soc_para->_CntCCEEPSub;
        soc_para->_SOHBatEEPSub = temp_soc_para->_SOHBatEEPSub;
        soc_para->_SOCBatDispEEPSub = temp_soc_para->_SOCBatDispEEPSub;
        soc_para->_SOCCellEEPSub = temp_soc_para->_SOCCellEEPSub;
        soc_para->_QDisChgEEPSub = temp_soc_para->_QDisChgEEPSub;
        soc_para->_QChgEEPSub = temp_soc_para->_QChgEEPSub;
        return 0;
    }
    if(check_buf_0xFF(read_buf, SOC_PARA_FLASH_SIZE) == 0) //all is 0xFF
    {
        return 1;
    }
    return -2;
}

/**
  * @brief  写参数入flash
  * @param  None
  * @retval None
  */
void write_soc_EEP_param_flash(EEPdata_t soc_para)
{
    EEPdata_t read_soc_param;
    uint8_t read_flash_buf[sizeof(VectorTable_t) + sizeof(LifeTime_t)];

    uint8_t i;
    int8_t res;

    /*遍历存储*/
    for(i = 0; i < SOC_PARA_FLASH_NUM; i++)
    {
        res = read_soc_EEP_param_flash(i, &read_soc_param);
        if(res != 0) //read fail
        {
            break;
        }
    }
    /*遍历都没有全FF 或校验失败，从头开始*/
    if((i >= SOC_PARA_FLASH_NUM)||(res < 0))
    {
        i = 0;
    }

//    soc_para.flag = 0xAA;
//    soc_para.index = 0;
//    soc_para.crc8 = cal_crc8_check((uint8_t *)&soc_para.index, sizeof(soc_para_t) - 2); //扣去flag crc 2bytes

    gcr_reg_unlock();
    if(res != 1)    // 如果是全FF不用erase
    {
        //擦除之前读取后面的数据 Vector,LifeTime
        flash_page_read((uint32_t)&VectorTable, sizeof(VectorTable_t) + sizeof(LifeTime_t), read_flash_buf);

        flash_page_erase(SOC_PARA_FLASH_ADDR);//擦一整页
        flash_page_write((uint32_t)&VectorTable, sizeof(VectorTable_t) + sizeof(LifeTime_t), read_flash_buf); //还原写入
        fmc_tick_cnt++;
    }
    soc_para._EEP_INDEX = fmc_tick_cnt;
    flash_page_write(SOC_PARA_FLASH_ADDR + i*SOC_PARA_FLASH_SIZE, SOC_PARA_FLASH_SIZE, (uint8_t *)&soc_para);

    gcr_reg_lock();
}

/**
  * @brief  init_EEP_data
  * @param  None
  * @retval None
  */
void init_EEP_data(void)
{
    int8_t i;
    EEPdata_t soc_para;

    bms_algorithm_U.InpEEPBusSub1.inp_SOCBatDispEEPSub_os_pct = 0;
    bms_algorithm_U.InpEEPBusSub1.inp_SOCCellEEPSub_vs_pct = 0;
    bms_algorithm_U.InpEEPBusSub1.inp_SOHBatEEPSub_os_pct = 100;
    bms_algorithm_U.InpEEPBusSub1.soh_CntCCEEPSub_os = 0;
    bms_algorithm_U.InpEEPBusSub1.soh_QChgEEPSub_os_Ah = 0;
    bms_algorithm_U.InpEEPBusSub1.soh_QDisChgEEPSub_os_Ah = 0;
    bms_algorithm_U.InpEEPBusSub1.inp_FlgEEPReadFinSub_ob = 1;
    //if(check_soc_para(read_buf) == 0) // flash 0k
    for(i = SOC_PARA_FLASH_NUM-1; i >= 0; i--)
    {
        if(read_soc_EEP_param_flash(i, &soc_para) == 0)
        {
            bms_algorithm_U.InpEEPBusSub1.inp_SOCBatDispEEPSub_os_pct = soc_para._SOCBatDispEEPSub;
            bms_algorithm_U.InpEEPBusSub1.inp_SOCCellEEPSub_vs_pct = soc_para._SOCCellEEPSub;//SOCCellEEPSub; //no array
            bms_algorithm_U.InpEEPBusSub1.inp_SOHBatEEPSub_os_pct = soc_para._SOHBatEEPSub;
            bms_algorithm_U.InpEEPBusSub1.soh_CntCCEEPSub_os = soc_para._CntCCEEPSub;
            bms_algorithm_U.InpEEPBusSub1.soh_QChgEEPSub_os_Ah = soc_para._QChgEEPSub;
            bms_algorithm_U.InpEEPBusSub1.soh_QDisChgEEPSub_os_Ah = soc_para._QDisChgEEPSub;
            bms_algorithm_U.InpEEPBusSub1.inp_FlgEEPReadFinSub_ob = 1;

            last_soc_val = soc_para._SOCBatDispEEPSub;
            EEP_soc_val = soc_para._SOCBatDispEEPSub;

            last_cycle_count = soc_para._CntCCEEPSub;

            //set_reg_value_u16(REGTYPE_REGISTER, regRemainingCapacityAlarm, 0, (int16_t)(EEP_soc_val+0.5));
            break;
        }
    }

    if(SafetyConfig._Signature[0] == 0x55)
    {
        sys_seal_type = SYS_SEALED;
    }else{
        sys_seal_type = SYS_FULL_ACCESS;
    }

    // SOCFlagConfig = BitConfig._SOCFlagConfig_FLASH;  //
    // std_data.SOCFlagConfig_bit = SOCFlagConfig;

    // std_bit_register.ManufacturingStatus.Byte = BitConfig._ManufacturingStatus_FLASH;

    //memcpy((uint8_t*)&life_time_data, (uint8_t*)&LifeTime, sizeof(LifeTime_t));
}



/**
  * @brief  设置算法的单体电压输入值 unit V和有效位
  * @param  None
  * @retval None
  */
void set_alg_cell_voltage(uint8_t ch, float vol_val, uint8_t valid)
{
    if(ch < SYS_CELL_NUM_MAX){
        bms_algorithm_U.InpBusSub1.inp_UCellSub_vs_V = vol_val;
        bms_algorithm_U.InpBusSub1.inp_qfUCellSub_vu8 = valid;
        #if SOH_ALGORITHM_ENABLE
            rtU_soh.input.inp_voltage_V[ch] = vol_val;
        #endif
    }
}

/**
  * @brief  设置算法的总电压输入值 unit V
  * @param  None
  * @retval None
  */
void set_alg_pack_voltage(float vol_val)
{
    bms_algorithm_U.InpBusSub1.inp_UPackSub_os_V = vol_val;
}


/**
  * @brief  设置算法的电流输入值 unit A
  * @param  None
  * @retval None
  */
void set_alg_pack_current( float cur_val, uint8_t valid)
{
    bms_algorithm_U.InpBusSub1.inp_IBatSub_os_A = cur_val;
    bms_algorithm_U.InpBusSub1.inp_qfIBatSub_ou8 = valid;
    #if SOH_ALGORITHM_ENABLE
        rtU_soh.input.inp_current_A = cur_val;
    #endif
}

/**
  * @brief  设置算法的温度输入值 unit degc
  * @param  None
  * @retval None
  */
void set_alg_pack_temprature( float temp_val, uint8_t valid)
{
    uint8_t i;
    bms_algorithm_U.InpBusSub1.btm_TModuSub_vs_degC = temp_val;
    bms_algorithm_U.InpBusSub1.btm_qfTModuSub_vu8 = valid;
    #if SOH_ALGORITHM_ENABLE
    for(i = 0; i< SYS_CELL_NUM_MAX; i++){
        rtU_soh.input.inp_temp_degree[i] = temp_val;
    }
    #endif
}

void update_soc_val_to_SOH_alg( void )
{
  uint8_t i;
    #if SOH_ALGORITHM_ENABLE
        for(i = 0; i < SYS_CELL_NUM_MAX; i++){
           // rtU_soh.input.inp_SOC_pct[i] = get_alg_cell_SOC_value[i];
        }
    #endif
}



/**
  * @brief  设置算法的单体均衡开关
  * @param  None
  * @retval None
  */
void set_alg_cell_balance_switch(uint8_t ch, uint8_t val)
{
    if(ch < SYS_CELL_NUM_MAX){
        bms_algorithm_U.InpBusSub1.inp_BalSwitchStatusSub_vb = val;
    }
}


/**
  * @brief  设置电池包BMS状态1-7
  * @param  1-init 2-IDEL 3-DSG 4-CHG 5-warning 6-shutdown 7-selfdischg
  * @retval None
  */
void set_alg_BMS_state(uint8_t val)
{
    bms_algorithm_U.InpStateBusTotal.bsc_StBMSMode_ou8 = val;
}

/**
  * @brief  获取电池包BMS状态1-7
  * @param  None
  * @retval None
  */
uint8_t get_alg_BMS_state(void)
{
    return (uint8_t)bms_algorithm_U.InpStateBusTotal.bsc_StBMSMode_ou8;
}

/**
  * @brief  均衡功能开关
  * @param  None
  * @retval None
  */
void set_alg_BMS_balance_switch(uint8_t val)
{
    bms_algorithm_U.InpStateBusTotal.bal_FlgBalState_ob = val;
}

/**
  * @brief  电池电量窗口上限
  * @param  None
  * @retval None
  */
void set_alg_SOC_window_H(float val)
{
    bms_algorithm_U.InpStateBusTotal.soh_SOCWinH_os_pct = val;
}

/**
  * @brief  电池电量窗口下限
  * @param  None
  * @retval None
  */
void set_alg_SOC_window_L(float val)
{
    bms_algorithm_U.InpStateBusTotal.soh_SOCWinL_os_pct = val;
}

/**
  * @brief  放空模式指令
  * @param  None
  * @retval None
  */
void set_alg_SOC_run_out_cmd(uint8_t val)
{
    bms_algorithm_U.InpStateBusTotal.inp_RunOutCmd_ob = val;
}

/**
  * @brief  获取总包SOC
  * @param  None
  * @retval None
  */
uint16_t get_alg_pack_SOC_value(void)
{
    return (uint16_t)bms_algorithm_Y.SOCSub1.soc_SOCDispCANSub_os_pct;
}

/**
  * @brief  获取单体SOC
  * @param  None
  * @retval None
  */
uint16_t get_alg_cell_SOC_value(uint8_t ch)
{
    if(ch >= SYS_CELL_NUM_MAX){
        ch = SYS_CELL_NUM_MAX-1;
    }
    return (uint16_t)bms_algorithm_Y.SOCSub1.soc_SOCCellSub_vs_pct;
}


/**
  * @brief  上电设置pack SOC设置值
  * @param  None
  * @retval None
  */
void set_alg_pack_SOC_init_val(uint16_t val)
{
    bms_algorithm_U.InpEEPBusSub1.inp_SOCBatDispEEPSub_os_pct = val;//SOCBatDispEEPSub;
}

/**
  * @brief  上电设置cell SOC设置值
  * @param  None
  * @retval None
  */
void set_alg_cell_SOC_init_val(uint8_t ch, uint16_t val)
{
    if(ch < SYS_CELL_NUM_MAX){
        bms_algorithm_U.InpEEPBusSub1.inp_SOCCellEEPSub_vs_pct = val;//SOCCellEEPSub
    }
}

/**
  * @brief  上电设置pack SOH设置值
  * @param  None
  * @retval None
  */
void set_alg_pack_SOH_init_val(uint16_t val)
{
    bms_algorithm_U.InpEEPBusSub1.inp_SOHBatEEPSub_os_pct = val;//SOHBatEEPSub;
}

/**
  * @brief  上电设置pack CntCC设置值
  * @param  None
  * @retval None
  */
void set_alg_pack_CntCC_init_val(uint16_t val)
{
    bms_algorithm_U.InpEEPBusSub1.soh_CntCCEEPSub_os = val;//CntCCEEPSub;
}


/**
  * @brief  上电设置周期内充电电量
  * @param  None
  * @retval None
  */
void set_alg_pack_Qchg_init_val(uint16_t val)
{
    bms_algorithm_U.InpEEPBusSub1.soh_QChgEEPSub_os_Ah = val;//QChgEEPSub;
}

/**
  * @brief  上电设置周期内放电电量
  * @param  None
  * @retval None
  */
void set_alg_pack_QDischg_init_val(uint16_t val)
{
    bms_algorithm_U.InpEEPBusSub1.soh_QDisChgEEPSub_os_Ah = val;//QDisChgEEPSub;
}

/**
  * @brief  上电读取EE有效位
  * @param  None
  * @retval None
  */
void set_alg_FlgEEPpack_val(uint16_t val)
{
    bms_algorithm_U.InpEEPBusSub1.inp_FlgEEPReadFinSub_ob = val;//FlgEEPReadFinSub;
}

/**
  * @brief  上电读取EE有效位
  * @param  None
  * @retval None
  */
void set_SOH_algorithm_dtime(float second)
{
    #if SOH_ALGORITHM_ENABLE
        rtU_soh.input.inp_dtime_s = second;
    #endif
}



/**
  * @brief  
  * @param  None
  * @retval  1 Init , 2 IDLE,3 DSG, 4 CHG, 5 WARNING, 6 SHUTDOWN
  */
uint8_t get_battery_state(void)
{
    return bms_algorithm_U.InpStateBusTotal.bsc_StBMSMode_ou8;//获取电芯的状态
}

/**
  * @brief  get_bat_soc_val
  * @param  None
  * @retval soc, float
  */
float get_bat_soc_val(void)
{
    return bms_algorithm_Y.SOCSub1.soc_SOCDispCANSub_os_pct;//获取SOC值
}

/**
  * @brief  get cycle_count
  * @param  None
  * @retval CC, float
  */
float get_soh_cycle_count(void)
{
    return bms_algorithm_Y.SOHSub1.soh_CntCC_os;
}

/**
  * @brief  get FCC,unit AH
  * @param  None
  * @retval FCC, float
  */
float get_full_charge_capacity(void)
{
    return bms_algorithm_Y.SOHSub1.soh_QminCapSub_os_Ah;
}

/**
  * @brief  get RemainingCapacity ,unit AH
  * @param  None
  * @retval RC, float
  */
float get_remaining_capacity(void)
{
    return bms_algorithm_Y.SOHSub1.soh_RMSub_os_Ah;
}

