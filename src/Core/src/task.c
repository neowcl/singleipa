// Include header file.
#include "task.h"
#include "cbmx56x_i2c.h"

#include "modules_temp.h"
#include "utility.h"
#include "app_inc.h"
#include "bi2cs_interface.h"
#include "modules_pmu.h"
#include "life_time_collect.h"
#include "user_config.h"
#include "bit_register.h"
#include "calibration_handle.h"
#include "block_command.h"
#include "algorithm_api.h"
#include "Cell.h"
#include "Ram.h"
#include "datcalc_spl.h"
//#include "CBMX56X_Algorithm.h"
#include "Calc_CVT.h"
#include "standard_data_cmd.h"
#include "Mode.h"

//volatile uint16_t tempIPACnt=0;

volatile uint8_t timer_inc_cnt = 0;
uint32_t sys_run_time_cnt = 0; //
////////////////////////////
///////////////////////////////
uint16_t t_com86cnt=0;

uint8_t  readIPAFrist=1;
uint8_t  readIPAmes_flag=0;


//uint8_t READIPATEMPLATE = 0; //0x18
uint16_t open_IPA=0;
uint8_t  readIPAmesCnt=1;
uint16_t t_com66_FC_cnt=0;
uint16_t t_com62cnt=0;
CC_Vadc_value_t CC_Vadc_value;  //cc 电流值和Vadc电压 温度值
Calibration_t   cali_param;
uint8_t sys_run_mode = NORMAL;  //系统工作模式
uint8_t writeflg=0;
uint8_t nowriteflg=0;
uint16_t currlimit;
uint8_t readCommErr=0;
uint16_t readCommErrCnt=0;



cc_value_valid_t cc_value_valid;

power_mode_t     power_mode;
cell_parameter_t cell_parameter;

uint32_t Temp_SOCFlagConfig_bit;

//uint8_t sleep_wake = 0;
//uint8_t deep_sleep_wake = 0;

//const int16_t deep_sleep_current_thr = 10; //10mA 休眠阈值 待取消
//const int16_t sleep_current_thr      = 15; //15mA

float last_soc_val = 0; // 记录上一次SOC值
float EEP_soc_val = 0;

float last_cycle_count = 0; // 记录上一次

uint16_t alg_run_time_tick = 0;

/**
  * @brief  获取系统运行时间
  * @param  None
  * @retval None
  */
uint32_t get_sys_run_time(void)
{
    return sys_run_time_cnt ;
}


/**
  * @brief  算法运行的周期间隔
  * @param  None
  * @retval None
  */
uint16_t get_alg_run_time_tick(void)
{
    return alg_run_time_tick;
}
/**
  * @brief  获取存储在flash的阈值
  * @param  None
  * @retval None
  */
int16_t get_BMS_Status_memory(uint8_t type)
{
    int16_t ret = 0;
    
    return ret;
}


/***电池包状态 1 Init 初始化, 2 IDLE空闲,3 DSG 放电, 4 CHG 充电, 5 WARNING告警, 6 SHUTDOWN关机***/
/**
  * @brief  battery_mode_state
  * @param  current ,last bat state
  * @retval new bat state
  */
uint8_t battery_mode_state(float current, uint8_t bat_state)
{
    static uint8_t bat_state_bak = BAT_MODE_IDLE;
    static uint8_t cnt = 0;
    int16_t intput_current;
    uint8_t ret ;
    ret = bat_state;

    intput_current = (int16_t)(current*1000); //输入float current 单位是A

    /*jump into chg*/
    if(intput_current > get_BMS_Status_memory(CHG_CURRENT_THRESHOLD)){
        cnt = 0;
        return BAT_MODE_CHG; //0x04
    }
    /*jump into dsg*/
    if(intput_current < (0 - get_BMS_Status_memory(DSG_CURRENT_THRESHOLD))){
        cnt = 0;
        return BAT_MODE_DSG;//0x03
    }
    /* chg mode*/
    if(bat_state == BAT_MODE_CHG){
        if(intput_current < get_BMS_Status_memory(QUIT_CURRENT_THRESHOLD)){
            if(cnt++ > get_BMS_Status_memory(CHG_RELAX_TIME)){
                ret = BAT_MODE_IDLE;
                cnt = 0;
            }
        }
    }else if(bat_state == BAT_MODE_DSG){
        if(intput_current > (0 - get_BMS_Status_memory(QUIT_CURRENT_THRESHOLD))){
            if(cnt++ > get_BMS_Status_memory(DSG_RELAX_TIME)){
                ret = BAT_MODE_IDLE;
                cnt = 0;
            }
        }
    }
    return ret;
}




//#define CURRENT_SIZE 10
/**
  * @brief  cal_average_current
  * @param  input current
  * @retval average current
  */
#if 0
int16_t cal_average_current(int16_t in_current)//计算平均电流
{
    static uint8_t first_flag = 1;
    static uint8_t time_cnt = 0;
    static uint8_t current_cnt = 0;
    //static int16_t current_buf[CURRENT_SIZE];
    static int32_t current_sum = 0;
    static int16_t average_current = 0;

    if(first_flag){
        average_current = in_current;
        first_flag = 0;
    }

    time_cnt += get_pmu_period_time();
    current_sum += in_current;
    current_cnt++;
    if(time_cnt >= 60){ //one minute average current，应该按时间间隔累加待修改
        time_cnt = 0;
        average_current = current_sum/current_cnt;
        current_cnt = 0;
        current_sum = 0;
    }
    return average_current;
}
#endif
#define CUR_BUF_SIZE 60

int16_t cal_average_current(int16_t in_current)//, uint8_t interval_sec计算平均电流
{
    static int16_t current_buf[CUR_BUF_SIZE];//max_buf
    int16_t buf_out_val;
    
    static uint8_t buf_index = 0;
    static uint8_t full_flag = 0;
    static uint8_t first_flag = 1;
    static int32_t current_sum = 0;
    
    static int16_t average_current = 0;
    
    if(Fabs(average_current) < 50)
    {
        if(Fabs(in_current) > 50)
        {
            buf_index = 0;
            full_flag = 0;
            first_flag = 1;
            current_sum = 0;

            average_current = in_current;
            return average_current;
        }
    }

    if( full_flag )//buf is full
    {
        if(buf_index >= CUR_BUF_SIZE)
        {
            buf_index = 0;
        }
        buf_out_val = current_buf[buf_index];
        current_buf[buf_index++] = in_current;
        current_sum += (in_current - buf_out_val);

        average_current = (current_sum)/CUR_BUF_SIZE;
    }else{
        if(buf_index < CUR_BUF_SIZE)
        {
            current_buf[buf_index++] = in_current;
            current_sum += in_current;
            average_current = current_sum / buf_index;
        }
        if(buf_index >= CUR_BUF_SIZE)
        {
            full_flag = 1;
        }
    }
    return average_current;
}

/**
  * @brief  get_chip_uid
  * @param  None
  * @retval None
  */
void get_chip_uid(void)
{
    uint8_t uID[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    gcr_reg_unlock();
    flash_get_ChipUID_value(uID, 12);
    gcr_reg_lock();
    //set_reg_value(REGTYPE_REGISTER , regCS_CPUID, 0, uID, 12);
}

int16_t get_voltage(void)
{
    //return voltage_val_mV;
    return CC_Vadc_value.voltage;
}

int16_t get_current(void)
{
    //return current_val_mA;
    return CC_Vadc_value.hs_current;
}

int16_t get_high_speed_current(void)
{
    //return hs_current_val_mA;
    return CC_Vadc_value.hs_current;
}

int16_t get_average_current(void)
{
    //return hs_current_val_mA;
    return CC_Vadc_value.avg_current;
}

int16_t get_temperatureIn(void)
{
    //return temperature_in;
    return CC_Vadc_value.temprature_in;
}

int16_t get_temperatureEx(void)
{
    //return temperature_in;
    return CC_Vadc_value.temprature_ex;
}


unsigned char cali_timeout_cnt = 0;
void clear_cali_timeout_cnt(void)
{
    cali_timeout_cnt = 0;
}
/**
  * @brief  update_soc_input_param
  * @param  None
  * @retval None
  */
void update_soc_input_param(void)
{
    static uint16_t inc_count = 0; //test cnt
    static uint8_t cc_invalid_cnt = 0;
    int32_t vbat_val = 0;
    int16_t oldTemp;
    int16_t temperature_inner;
    int16_t temperature_ex;
    int32_t current_highPrecision; //高精度模式
    int32_t current_highSpeed;     //高速模式
    int16_t average_current;
    int32_t temprature_r;
    float temp_val;

    cc_value_valid.byte = 0; //clear valid bit

    //operation_status_SEC_bit_reg(get_sys_seal_type()); //block = 0x54


    /***电流获取***/
    if(modules_cc_hp_updata_value() == 0)
    {
        cc_enable_ctrl(ENABLE);
        //gpio_bit_write(GPIO_PIN_0, BIT_SET);
        if(f_CAL_EN)
        {            //校准状态 不乘系数
            //current_highPrecision = modules_cc_hp_get_value();
            current_highSpeed = modules_cc_hs_get_value();
            cali_timeout_cnt += get_pmu_period_time();
            if(cali_timeout_cnt > 120)
            { //校准超时
                f_CAL_EN= 0;
                cali_timeout_cnt = 0;
            }
        }
        else
        { 
            // 去掉偏移 乘校准系数  大电流系数
            //current_highPrecision = (modules_cc_hp_get_value() - Calibdata._HP_CCOffset) * Calibdata._CChighGain/CALIBRATION_AMP ;  //高精度 
            current_highSpeed = (modules_cc_hs_get_value()-CCOFFSET)* CCGAIN/CALIBRATION_AMP ;             //高速
            tabsc = (uint16_t)Fabs(current_highSpeed);
            if (tabsc <= D_DEADBAND) //
            {
               
                current_highSpeed = 0;
                tabsc = 0;
            }
           
        }

        if((current_highSpeed > -30000)&&(current_highSpeed < 30000))
        { //+-30A limit
            cc_value_valid.bit.current_valid = 1;
            // average_current = cal_average_current(current_highSpeed);
            CC_Vadc_value.avg_current = average_current;
            
            if ((t_com0d > 99) && (current_highSpeed < D_CURRENTLIMIT) && (current_highSpeed > 0) && (!f_CAL_EN))
            {
                currlimit++;
                if (currlimit >= D_CURRENTLIMITTIME)
                {
                    currlimit = D_CURRENTLIMITTIME;
                    t_com0a = 0x0000;
                }
                else
                {
                    t_com0a = current_highSpeed;
                }
            }
            else
            {
                currlimit = 0;
                t_com0a = current_highSpeed;
            }

            // t_com89 = average_current;
        }
        /*电流A*/
        temp_val = (float)current_highSpeed/1000;
        cc_invalid_cnt = 0;
    }
    else{
        cc_invalid_cnt++;
        if(cc_invalid_cnt > 1) 
        {
            cc_invalid_cnt = 0;
            cc_enable_ctrl(ENABLE);
        }
    }
  
    /***电压和内外温度值***/
    if(vadc_intetrrupt_status_get(VADC_INTR_VADCIF) == SET)
    {
        vadc_intetrrupt_flag_clear(VADC_INTR_VADCIF);
        if (!readIPAmes_flag)
        {
            temperature_inner = vadc_get_temperature(VADC_CHANNEL_2, VADC_VADCHS_INSIDE_SENSOR, 1) / 10;
            //READIPATEMPLATE=1;
            if (!f_CAL_EN)
            {
                temperature_inner += (int16_t)INTTEMPOFFSET * 10;
            }
#if NTC_TEMPERATURE_REDUCE
            if (temperature_inner > 400)
            {
                temperature_inner = 400 + ((temperature_inner - 400) >> 1);
            }
#endif
            // set_temperatureIn(temperature_inner);
            if ((temperature_inner > -500) && (temperature_inner < 1200))
            { // 温度限制-40至120
                t_com75 = temperature_inner + 2731;
                IntTemp = temperature_inner / 10;
            }
            //        if(GET_SOCFlagConfig_TempEnable_TSInt())//用内温
            //        {
            //            temperature_ex = temperature_inner;
            //        }else{ //用外温
            // temprature_r = vadc_get_temperature(VADC_CHANNEL_3, VADC_VADCHS_EXTERNAL_SENSOR, 2);
            // temperature_ex = Lookup_T(temprature_r); // 0.1 degc
            // if(!f_CAL_EN)
            // {
            // temperature_ex += (int16_t)CELLTEMPOFFSET * 10;
            // }

            //        }
            temperature_ex = temperature_inner;
#if NTC_TEMPERATURE_REDUCE
            if (temperature_ex > 400)
            {
                temperature_ex = 400 + ((temperature_ex - 400) >> 1);
            }
#endif
            if ((temperature_ex > -500) && (temperature_ex < 1200))
            { // 温度限制-40至120
                cc_value_valid.bit.tempratureEx_valid = 1;
                t_com08 = temperature_ex + 2731;
                CellTemp = temperature_ex / 10;
            }
        }
        else
        {

            if (!f_CAL_EN)
            {
                if (open_IPA>3)
                {
                    oldTemp = t_com08;
                    IIC_ReadReg(0x75, &temperature_ex);
                    if ((temperature_ex < 2200) || (temperature_ex > 3131))
                    {
                        IIC_ReadReg(0x75, &temperature_ex);
                        if ((temperature_ex < 2200) || (temperature_ex > 3131))
                        {
                            readCommErrCnt++;
                            if (readCommErrCnt > 5)
                            {
                                readCommErr = 1;
                                readCommErrCnt = 6;
                            }
                            else
                            {
                                temperature_ex = oldTemp - ((int16_t)CELLTEMPOFFSET * 10);
                            }
                        }
                        else
                        {
                            readCommErrCnt = 0;
                        }
                    }
                    else
                    {
                        readCommErrCnt = 0;
                    }
                }
                else
                {
                    readCommErr = 1;
                }

                if (!readCommErr)
                {
                    t_com08 = temperature_ex + ((int16_t)CELLTEMPOFFSET * 10);
                    // if (t_com08 == 2921)
                    // {
                    //     t_com08 = 2923;
                    // }

                    // if (t_com08 >= 3081 && (!f_discharge))
                    // {
                    //     t_com08 -= 50;
                    // }

                    t_com75 = temperature_ex;
                    CellTemp = (t_com08 - 2731) / 10;//(t_com08 - 2731 + ((int16_t)D_SPL_TEMP * 10)) / 10;
                    IntTemp = CellTemp;
                    //CellTemp_use_rsoc = (t_com08 - 2731) / 10;
                    temperature_inner = temperature_ex - 2731;
                }
                else
                {

                    temperature_inner = t_com08 - 2731;
                    t_com75 = temperature_inner + 2731;
                    IntTemp = temperature_inner / 10;
                    temperature_ex = temperature_inner;
                    t_com08 = temperature_ex + 2731;
                    CellTemp = temperature_ex / 10;

                    readCommErr = 0;
                }
            }
            else
            {
                IIC_ReadReg(0x75, &temperature_ex);
                t_com08 = temperature_ex;
                t_com75 = temperature_ex;
            }
        }
        CellTemp_use_rsoc=CellTemp;
        vbat_val = f_CAL_EN? vadc_get_voltage(VADC_CHANNEL_0) : vadc_get_voltage(VADC_CHANNEL_0) * CELLGAIN/CALIBRATION_AMP;

        if (!f_CAL_EN)
        {
            /* BA版本大于校准温度 正温度系数 0.025mv/摄氏度，小于校准温度 0.018mv/摄氏度  AA版本为0.014mv/摄氏度 adjust by ligx at 2022.12.14*/
            if (temperature_inner <= 650)
            { // 小于65摄氏度，进行补偿
                if (temperature_inner < 250)
                {
                    vbat_val += (int64_t)vbat_val * (temperature_inner - 250) * 27 / 10000000; // 2023-07-15
                }
                else
                {
                    vbat_val += (int64_t)vbat_val * (temperature_inner - 250) * 18 / 10000000;
                }
            }
        }

        if((vbat_val > 8000)&&(vbat_val < 50000)){    //电压限制 0.8~5.0V

            cc_value_valid.bit.vbat_valid = 1;
            vbat_val = A_Div_B(vbat_val + 5, 10);
            //set_voltage(vbat_val);                    //存储电压值
            if(vbat_val<3210&&  (!f_CAL_EN) &&t_com0a>0)
            {
                t_com09 = 3210;
            }
            else
            {
            t_com09 = vbat_val;
            }
//            interrupt_status_of_vol(vbat_val);
        }
        vadc_enable_ctrl(ENABLE);

        temp_val =  (float)vbat_val/1000;// 转换成浮点，单位V
        /*单节电池电压V*/
        
    }
     //bms_algorithm_U.InpStateBusTotal.soc_tmBase_ODS_ms = get_alg_run_time_tick()*1000; //算法运行周期单位ms
    /*均衡开关状态*/
    //bms_algorithm_U.InpBusSub1.inp_BalSwitchStatusSub_vb = 0;
    if(cc_value_valid.bit.current_valid){
        //CC_Vadc_value.hp_current = current_highPrecision;
        CC_Vadc_value.hs_current = current_highSpeed;
    }
    if(cc_value_valid.bit.vbat_valid){
        CC_Vadc_value.temprature_ex = temperature_ex;
        CC_Vadc_value.temprature_in = temperature_inner;
        CC_Vadc_value.voltage = vbat_val;
    }
    DCR_Mode();
}

/**
  * @brief  init_soc_input_state
  * @param  None
  * @retval None
  */
void init_soc_input_state(void)
{
 if (DF_FCC == 0) // FCC is not initialized with Flexible data
	{
		DF_MAXLOADCUR = D_INITMAXLOADCUR;
		DF_QMAX = D_DCAP;
		DF_SOH = 100;
		t_com10 = INIT_FCC; // set initial FCC
		IdealFcc = INIT_IDRFCC;
		
		Del_lrc = 0;
		Chargefactor = 1000;
		Dischargefactor = 1000;
		if (F_INITCAP == ON)
		{
			Init_Cap(); // Calc init RC
		}
		else
		{
			lrc_w = (long)t_com10 * INIT_RSOC * 36; // set initial RSOC
			Ilrc_w = (long)IdealFcc * INIT_RSOC * 36;
			t_com0d = INIT_RSOC;
		}
	}
    else
	{
		t_com10 = DF_FCC;
		// t_com0d = DF_RSOC;
		if (F_INITCAP == ON)
		{
			Init_Cap(); // Calc init RC
		}
	}
}

/**
  * @brief  update_soc_input_state
  * @param  None
  * @retval None
  */
void update_soc_input_state(void)
{
    static unsigned char init_flag = 0;
    /***电池包状态 1 Init 初始化, 2 IDLE空闲,3 DSG 放电, 4 CHG 充电, 5 WARNING告警, 6 SHUTDOWN关机***/
    if(init_flag != 0){
        //bms_algorithm_U.InpStateBusTotal.bsc_StBMSMode_ou8 = battery_mode_state(bms_algorithm_U.InpBusSub1.inp_IBatSub_os_A, \
                                                                        bms_algorithm_U.InpStateBusTotal.bsc_StBMSMode_ou8);
    }else{
        //bms_algorithm_U.InpStateBusTotal.bsc_StBMSMode_ou8 = BAT_MODE_IDLE;
        init_flag = 1;
    }
}

/**
  * @brief  init_EEP_data
  * @param  None
  * @retval None
  */
//void init_EEP_data(void)
//{
//    bms_algorithm_U.InpEEPBusSub1.inp_FlgEEPReadFinSub_ob = 1;//FlgEEPReadFinSub;
//    bms_algorithm_U.InpEEPBusSub1.soh_QDisChgEEPSub_os_Ah = QDisChgEEPSub;
//    bms_algorithm_U.InpEEPBusSub1.soh_QChgEEPSub_os_Ah = QChgEEPSub;
//    bms_algorithm_U.InpEEPBusSub1.soh_CntCCEEPSub_os = CntCCEEPSub;
//    bms_algorithm_U.InpEEPBusSub1.inp_SOCBatDispEEPSub_os_pct = SOCBatDispEEPSub;
//    bms_algorithm_U.InpEEPBusSub1.inp_SOHBatEEPSub_os_pct = SOHBatEEPSub;
//    bms_algorithm_U.InpEEPBusSub1.inp_SOCCellEEPSub_vs_pct = SOCCellEEPSub;
//    last_soc_val = SOCCellEEPSub;
//}

/**
  * @brief  sys_run_conuter
  * @param  None
  * @retval None
  */
//void sys_run_conuter(void)
//{
//    static uint16_t run_cnt = 0;
//    set_reg_value_u16(REGTYPE_REGISTER, regSerialNumber, 0, run_cnt); //0x1C for test
//    run_cnt++;
//}
#if 0
typedef struct{
    float _CntCCEEPSub; //存储CC上回值
    float _SOHBatEEPSub; //存储SOH上回值
    float _SOCBatDispEEPSub; //存储SOCDisp上回值
    float _SOCCellEEPSub; //存储SOCCell上回值
    float _QDisChgEEPSub; //存储QDsg上回值
    float _QChgEEPSub; //存储QChg上回值
}BatteryConfig_EEP_t;
#endif



/**
  * @brief  get_soc_output_param
  * @param  None
  * @retval None
  */



/**
* @fn void task_isr_process(void)
* @brief 定时器1中断处理函数(由TASK APP负责)
* @param None
* @return None.
*/
void app_task_isr_process(void)
{
    if (tim1_interrupt_status_get() == SET)
    {   
        if(t_com62Flg)
        {
            if(t_com62cnt>65500)
            {
                t_com62cnt=0;
            }
            t_com62cnt++;
        }
        if(t_com0d>99)
        {
            t_com66_FC_cnt++;
        }
        else
        {
            t_com66_FC_cnt=0;
        }
        if((!readIPAFrist) && (readIPAmesCnt<18))
        {
            readIPAmesCnt++;
        }
        t_com86cnt++;
        timer_inc_cnt++ ;

        if(readIPAmes_flag)
        {
            open_IPA++;
            if(open_IPA > COLSEIPA)
            {
                readIPAmes_flag = 0;
                open_IPA = 0;
                ts_W_L();
            }
        }
        
        // if( (tabsc>(0.3*D_DCAP)) && readIPAmes_flag)
        // {
        //     tempIPACnt++;
        // }
        // else
        // {
        //     tempIPACnt=0;
        // }
        //sys_run_time_cnt++ ;
        tim1_interrupt_status_clear();
       // I2C_busy_judge(); 
    }
}


/**
* @fn void app_task_loop(void)
* @brief 任务循环
* @param None
* @return None.
*/
void app_task_loop(void)
{
    static uint8_t pre_timer_inc_cnt = 0;

    if(pre_timer_inc_cnt != timer_inc_cnt)
    {
        if(timer_inc_cnt >= get_pmu_period_time())
        {
            alg_run_time_tick = timer_inc_cnt;
            timer_inc_cnt = 0;
            if(readIPAFrist)
            {
                readIPAFrist=0;
                readIPAmes_flag = 1;
                open_IPA=0;
                ts_W_H();
            }
            update_soc_input_param(); //电压电流采样

            //IIC_ReadReg(0x72, &t_com06);
            if (f_GAUGE_EN)           // 大部分函数功能
            {
                Calc_FullCharge(); // soc算法一些功能   不用动
                Calc_CC();
                Calc_RC();
                Calc_RSOC();
                Calc_iRSOC();
                Calc_QMax();
                Calc_AvgCur();
                Calc_ATTE();
                Calc_ATTF();
                
            }
            LifeTime_Calc();
			TemperatureRangeJudge();
			VoltageRangeJudge();
			TFStatus();
			Set_CCCV();
			Timestamp();
			FlagStatus(); // 加功能
			//FlagStatus1();
            if(readIPAmesCnt%5==0 && !f_CAL_EN && !f_SLEEP && !f_DP_SLP)
            {
                readIPAmessage();
            }
            fw_pmu_proc();              // 功耗控制处理  判读是否休眠
        }
        pre_timer_inc_cnt = timer_inc_cnt;
    }
    sleep_timeout_decrease();
}

char fristsample(void)
{
    if (modules_cc_hp_updata_value() == 0)
    {
        update_soc_input_param(); // 电压电流采样
        return 0;
    }
    return 1;
}


void cc_start_connection(void)
{
    update_soc_input_param(); // 电压电流采样
}