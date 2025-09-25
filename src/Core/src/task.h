/***************************************************************************//**
 * @file     task.h
 * @version  V1.0.0
 * @author   
 * @date     
 * @brief    
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/


#ifndef __TASK_H__
#define __TASK_H__

// Include external header file.
#include "cbmx56x_conf.h"
#include "i2c_coms.h"
#include "modules_vbat.h"


#ifdef __cplusplus
extern "C" {
#endif

#define COLSEIPA     300

#define DSG_CURRENT_THRESHOLD   0x01
#define CHG_CURRENT_THRESHOLD   0x02
#define QUIT_CURRENT_THRESHOLD  0x03
#define DSG_RELAX_TIME          0x04
#define CHG_RELAX_TIME          0x05

#define BAT_MODE_INIT           0x01
#define BAT_MODE_IDLE           0x02
#define BAT_MODE_DSG            0x03
#define BAT_MODE_CHG            0x04
#define BAT_MODE_WARNING        0x05
#define BAT_MODE_SHUTDOWN       0x06

#define TEMPRATURE_MAX_LIMIT    1200
#define TEMPRATURE_MIN_LIMIT    -400

#define SYS_CELL_NUM             1
#define SYS_CELL_NUM_MAX         1

typedef enum
{
    NORMAL = 0,
    SLEEP,
    DEEP_SLEEP

}sys_state_t;


typedef struct
{
    volatile int16_t voltage;       //mv
    volatile int16_t hp_current;    //mA
    volatile int16_t hs_current;    //mA
    volatile int16_t avg_current;    //mA
    volatile int16_t temprature_in; // x10
    volatile int16_t temprature_ex; // x10
}CC_Vadc_value_t;

/****************************************************
* Calibration related parameters
****************************************************/
typedef struct
{
    struct
    {
        uint32_t Cell_Gain;
        uint32_t Board_Offset;
    }voltage;
    struct
    {
        uint32_t CC_Gain;
        int32_t  CC_Offset;
        int32_t  LP_CC_Offset;
        uint16_t Dead_Band;
        uint16_t CC_Deadband;
    }current;
    struct
    {
        int16_t Inter_Temp_Offset;
        int16_t Exter_Temp_Offset;
        int16_t Voltage_Calibra_Temp;
        int16_t RSV;
    }temperature;
    uint8_t cali_en;
}Calibration_t;


//typedef union 
//{
//    struct
//    {
//        unsigned int low_accuracy_cc_cnvrsn                 :1;
//        unsigned int dymcocv_cellv_cnvrsn                   :1;
//        unsigned int ad_cnvrsn_disable                      :1;
//        unsigned int cc_cnvrsn_end                          :1;
//        unsigned int av_cnvrsn_end                          :1;
//        unsigned int at_cnvrsn_end                          :1;
//        unsigned int avg_current_jump_chg                   :1;
//        unsigned int avg_current_jump_dsg                   :1;
//        unsigned int avg_current_chg                        :1;
//        unsigned int avg_current_dsg                        :1;
//        unsigned int current_updated                        :1;
//        unsigned int voltage_updated                        :1;
//        unsigned int temperature_updated                    :1;
//        unsigned int rsv                                    :3;
//    }Bit;
//    unsigned int Byte;
//}Process_AD_t;

typedef struct
{
    int16_t voltage;
    int16_t curent;
    int16_t avg_voltage;
    int16_t avg_curent;
    int16_t wake_curent;
    int16_t temperature_ex;
    int16_t temperature_inner;
}cell_parameter_t;

 typedef union 
{
    struct
    {
        uint8_t sleep_mode                             :1;
        uint8_t deep_sleep_mode                        :1;
        uint8_t shut_mode                              :1;   
        uint8_t run_mode                               :1;
        uint8_t Sleep_Check                            :1;
        uint8_t low_accuracy_cc                        :1;
        uint8_t RSV                                    :2;
    }bit;
    uint8_t byte;
}power_mode_t;

 typedef union 
{
    struct
    {
        uint8_t vbat_valid                           :1;
        uint8_t current_valid                        :1;
        uint8_t tempratureEx_valid                   :1;
        uint8_t RSV                                  :5;
    }bit;
    uint8_t byte;
}cc_value_valid_t;

/**@brief 定时器1中断处理函数(由TASK APP负责)  
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */  
void app_task_isr_process(void);
   
/**@brief 任务循环
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */  
void app_task_loop(void);

/**@brief 获取系统时间
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  系统时间
 */  
void init_soc_input_state(void);
//void init_EEP_data(void);
void get_chip_uid(void);
void clear_cali_timeout_cnt(void);
uint32_t get_sys_run_time(void);

extern Calibration_t cali_param;
extern float last_soc_val;
extern float EEP_soc_val;
extern float last_cycle_count;
extern char fristsample(void);
extern void cc_start_connection(void);


extern uint32_t Temp_SOCFlagConfig_bit;

#ifdef __cplusplus
}
#endif

#endif

/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
