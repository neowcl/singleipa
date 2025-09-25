/***************************************************************************//**
 * @file     bms_register_command_handle.c
 * @version  V1.0.0
 * @author   sz414
 * @date     2022-08-09 PM
 * @brief    
 *
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

#include "app_inc.h"
#include "comm_protocol.h"
#include "user_config.h"
#include "standard_data_cmd.h"
#include "block_command.h"
#include "bit_register.h"
#include "utility.h"
#include "life_time_collect.h"
#include "bi2cs_interface.h"
#include "Protect.h"

extern void handle_debug_mode(uint8_t * data);
void handle_block_write();
//void handle_block_read();

// 定时扫描并处理寄存器命令.
void timer_reg_command(void)
{

    if(get_iic_rx_handle_type() & IIC_RX_DEBUG_MODE_BIT)  //debug mode private 
    {
        handle_debug_mode(debug_mode_buf);
        set_iic_rx_handle_type(IIC_RX_DEBUG_MODE_BIT, REMOVE_BIT);
    }

    if(get_iic_rx_handle_type()&IIC_RX_MACDATA_LEN_BIT)  //write block 
    {
        handle_block_write();
        set_iic_rx_handle_type(IIC_RX_MACDATA_LEN_BIT, REMOVE_BIT);
    }

    if(get_iic_rx_handle_type()&IIC_RX_ALT_MANU_ACCESS_BIT)
    {
        handle_block_read();
        set_iic_rx_handle_type(IIC_RX_ALT_MANU_ACCESS_BIT, REMOVE_BIT);
    }
    //ProtectProcess();
    bi2cs_dataCmd_Save(); // 给一些命令参数初始化赋值
    DFUdata_Chk();
    
    
    if (f_lt_W)
    {
        f_lt_W = OFF;
        LifeTime_Write(); // 写lifetime参数
    }

    if (f_dfreq)
    {
        f_dfreq = OFF;
        if (F_USEDFDAT)
        {
            DF_Write(); //  容量累计写df参数
        }
    }

    if (f_df_erase)
    {

        f_df_erase = OFF;
        DF_Erase_A(); // df参数擦除
        DF_Erase_B();
        ts_W_L(); 
        run_task_event(); // 重置
    }
    if (f_lt_erase) // lifetime参数擦除
    {
        f_lt_erase = OFF;
        LT_Erase_A();
        LT_Erase_B();
        ts_W_L(); 
        run_task_event(); // 重置
    }
    if (f_reset_mcu)
    {
        f_reset_mcu = OFF;
        if (F_USEDFDAT)
        {
            DF_Write(); //  复位写df参数
        }
        ts_W_L(); 
        run_task_event(); // 重置
    }
    //run_task_event(); // 重置
}


uint8_t checksum(uint8_t *Data, uint16_t Length)
{
    uint8_t sum = 0;
    uint16_t i;
    for(i = 0; i < Length; i++)
    {
        sum += Data[i];
    }
    sum = 0xFF - sum;
    return sum;
}


void filled_block_data(const void *pdata, uint8_t len)
{
    uint8_t i = 0;
    const uint8_t *p = (const uint8_t *)pdata;
    for(i = 0; i < 32; i++)
    {
        std_data.MACData[i] = 0;
    }
    if(len > 32)
    {
        return;
    }
    for(i = 0; i < len; i++)
    {
        std_data.MACData[i] = *p;
        //std_data.MACData[i] = (const uint8_t *)pdata;
        p++;
    }
    std_data.MAC_Length = len + 4;//include 0x3E 3F cs len
    std_data.MAC_ChkSum = checksum((uint8_t*)&std_data.AltMfAccess.Byte.LO, len + 2);
}

//const char DEVICE_TYPE[4] = {'x','5','6','x'};
const char CHEM_ID[2] = {0x05,0x06};

extern const uint8_t unseal_password[4];
extern const uint8_t full_unseal_password[4];
extern const uint32_t DEVICE_TYPE;

uint8_t unseal_state = 0;
uint8_t full_unseal_state = 0;
static uint32_t unseal_count = 0;
//get_sys_run_time() 

//  void handle_block_read()
// {
    
// }

void handle_block_write( )
{
    uint8_t hmac_sha256_key[32] ;//= HMAC_SHA256_KEY_BUF;
    uint8_t buf_calc_summary[32];
    uint8_t random_buf[32];
    uint8_t i,j, sum = 0;
    uint8_t mac_len;
    uint8_t key_update_flag = 0;
    
    

//    if(get_iic_rx_handle_type()&IIC_RX_MACDATA_LEN_BIT) //
   
        //cal  check sum
//        for(i = 0; i < 32; i++){
//            sum += std_data.MACData[i];
//        }
//        if((sum + std_data.MAC_ChkSum) != 0xFF){
//            return ;
//        }
        
//        set_iic_rx_handle_type(IIC_RX_MACDATA_LEN_BIT, REMOVE_BIT);


#if 0
    switch(data_type)
    {
        case SLAVE_IO_STATE_ALT_MANU:
//            if((AltManufacturerAccess[0] == 0)&&(AltManufacturerAccess[1] == 0))
            if(std_data.AltMfAccess.Word == 00)
            {
                authen_flow = 1;
            }
            break;
        case SLAVE_IO_STATE_MACDATA:
            if(authen_flow == 1){
                authen_flow = 2;
            }else{
                authen_flow = 0;
            }
            break;
        case SLAVE_IO_STATE_MACDATAH:
            if(authen_flow == 2){
                authen_flow = 3;
            }else{
                authen_flow = 0;
            }
            break;
        case SLAVE_IO_STATE_CSUM:
            if(authen_flow == 3){
                for(i = 0; i < 29; i++){
//                    random_buf[i] = MACData[i];
                }
                for(i = 0; i < 3; i++){
//                    random_buf[29+i] = MACDataH[i];
                }
                sum = 0;
                for(i = 0; i < 32; i++){
                    sum += random_buf[i];
                }
//                if((sum + MACDataCheckSum[0]) == 0xFF)
                {//检验通过
                    sha256_hmac_calc(&random_buf[0],
                                    32,
                                    &hmac_sha256_key[0],
                                    sizeof(hmac_sha256_key),
                                    &buf_calc_summary[0]);
                    //memcpy(MACData, &buf_calc_summary[0], 29);
                    for(i = 0; i < 29; i++){
//                        MACData[i] = buf_calc_summary[i];
                    }
                    //memcpy(MACDataH, &buf_calc_summary[29], 3);
                    for(i = 0; i < 3; i++){
//                        MACDataH[i] = buf_calc_summary[29+i];
                    }

                }
            }
            authen_flow = 0;
            break;
    }
#endif
}




