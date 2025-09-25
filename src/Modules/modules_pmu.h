/***************************************************************************//**
 * @file     .h
 * @version  
 * @author   
 * @date    
 * @brief    
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/


#ifndef __MODULES_PMU_H__
#define __MODULES_PMU_H__

// Include external header file.
#include "cbmx56x_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

/* PMU config ----------------------------------------------------------------*/
#define PMU_INTO_SLEEP_TIME                      1      //

#define PMU_INTO_DEEP_SLEEP_TIME                 1      //sleep mode into deepsleep mode

#define PMU_ACTIVE_MODE_PERIOD_TIME              1      //1*1s     active
#define PMU_SLEEP_MODE_PERIOD_TIME               10      //5*1s     slepp
#define PMU_DEEP_SLEEP_MODE_PERIOD_TIME          40     //20*1s    deep sleep

typedef enum
{
    PMU_ACTIVE_MODE = 0,
    PMU_SLEEP_MODE = 1,
    PMU_DEEP_SLEEP_MODE = 2,
} fw_pmu_run_mode_t;

uint8_t get_pmu_period_time(void);
void fw_pmu_proc(void);
extern uint8_t pmu_sleep_timeout;
//extern uint8_t ResetIPA_flag;
extern uint8_t resetCnt;
void sleep_timeout_decrease(void);
void fw_pmu_set_run_mode(fw_pmu_run_mode_t mode);
#ifdef __cplusplus
}
#endif

#endif  //__MODULES_TEMP_H__


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
