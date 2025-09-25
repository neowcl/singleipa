/**************************************************************************//**
 * @file     .c
 * @version  
 * @author   
 * @date     
 * @brief    
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

// Include header file.
#include "modules_pmu.h"
#include "cbmx56x_conf.h"
#include "calibration_handle.h"
#include "task.h"
#include "modules_init.h"
#include "bit_register.h"
#include "user_config.h"
#include "bi2cs_interface.h"
#include "Cell.h"
#include "task.h"

volatile static uint8_t pmu_period_time = 1;
uint8_t pmu_sleep_timeout = 0;
static uint8_t sleep_mode_cnt = 0;
//uint8_t ResetIPA_flag=0;
//uint8_t resetCnt=0;
static fw_pmu_run_mode_t pmu_run_mode = PMU_ACTIVE_MODE;
/**
* @fn void fw_pmu_set_run_mode(fw_pmu_run_mode_t mode)
* @brief set run mode
* @param [in]mode: run mode
* @return None.
*/
void fw_pmu_set_run_mode(fw_pmu_run_mode_t mode)        //active/sleep/deep_sleep
{
    pmu_run_mode = mode;
    sleep_mode_cnt = 0;
    f_SLEEP = OFF;
    f_DP_SLP=OFF;
}

/**
* @fn uint8_t fw_pmu_get_run_mode(void)
* @brief get run mode
* @param None
* @return run mode
*/
fw_pmu_run_mode_t fw_pmu_get_run_mode(void)             // get run mode
{
    return pmu_run_mode;
}

uint8_t get_pmu_period_time(void)
{
    return pmu_period_time;
}

/**
* @fn void fw_pmu_proc(void)
* @brief pmu system proc
* @param None
* @return None.
*/
void fw_pmu_proc(void)
{
    int16_t bat_current;
   //static uint8_t sleep_mode_cnt = 0;

   if (f_CAL_EN)
   {
       pmu_run_mode = PMU_ACTIVE_MODE;
   }
   else
   {
       bat_current = get_high_speed_current();
       bat_current = ABS(bat_current) ;
       if ((bat_current < D_SLPCURR)&&f_SleepEn&& !f_DPSLEEPM)
       {
            sleep_mode_cnt++; 
           if (sleep_mode_cnt>20)
           {
               sleep_mode_cnt = 0;
               pmu_run_mode = PMU_SLEEP_MODE;
           }
       }
       else
       {
           sleep_mode_cnt = 0;
           pmu_run_mode = PMU_ACTIVE_MODE;
       }
   }

   if (f_SLEEP)
   {
       if (f_DP_SLP)
       {
           if ((!f_DP_SleepEn && !f_DPSLEEPM) || bat_current > D_DSLPCURR)
           {

               f_DP_SLP = OFF;
               f_SLEEP = ON;
               pmu_run_mode = PMU_SLEEP_MODE;
           }
       }
       else
       {

           if ((f_DP_SleepEn || f_DPSLEEPM) && bat_current <= D_DSLPCURR)
           {
               pmu_run_mode = PMU_DEEP_SLEEP_MODE;
               f_DP_SLP = ON;
           }
       }
   }

    switch(pmu_run_mode)
    {
        case PMU_ACTIVE_MODE:
            f_SLEEP = OFF;
            f_DP_SLP=OFF;
            break;
        case PMU_SLEEP_MODE:
            f_SLEEP = ON;
            f_DP_SLP=OFF;
            break;
        case PMU_DEEP_SLEEP_MODE:
            f_DP_SLP=ON;
            break;
    }

}


void sleep_timeout_decrease(void)
{
    switch(pmu_run_mode)        
    {
    case PMU_ACTIVE_MODE:
        pmu_period_time = PMU_ACTIVE_MODE_PERIOD_TIME;
        break;
    case PMU_SLEEP_MODE:
        pmu_period_time = PMU_SLEEP_MODE_PERIOD_TIME;
        break;
    case PMU_DEEP_SLEEP_MODE:
        pmu_period_time = PMU_DEEP_SLEEP_MODE_PERIOD_TIME;
        break;
    default:
        break;
    }

    if(pmu_sleep_timeout > 0){
        pmu_sleep_timeout --;
    }
    if(pmu_sleep_timeout == 0){
        #if SLEEP_ENABLE
            sleep();
        #endif
    }
}
