/***************************************************************************//**
 * @file     
 * @version  V1.0.0
 * @author   
 * @date     2021-01-25 AM
 * @brief    
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

#ifndef __CALIBRATION_HANDLE_H__
#define __CALIBRATION_HANDLE_H__

#include "stdint.h"


#ifdef __cplusplus
extern "C" {
#endif

#define FMC_MODULES_VBAT          1
#define FMC_MODULES_CC            2
//#define FMC_CALIBRATION_DATA      0xEE00

#define CALIBRATION_AMP           16384
#define CELL_GAIN_DEFAULT         16384
#define CC_GAIN_DEFAULT           16384
#define CC_OFFSET_DEFAULT         0

#define DEADBAND_DEFAULT          4
#define CC_DEADBAND_DEFAULT       9

typedef struct
{
    int16_t fmc_magic;                //用来判断是否为首次写该flash
    int16_t fmc_vbat_gain;            //电压增益系数
    int16_t fmc_cc_gain;              //电流增益系数
    int16_t fmc_vbat_offset;          //电压offset值
    int16_t fmc_cc_offset;            //电流offset值
    int16_t fmc_voltage_calibra_temp; //校准时的电压值 1 = 0.1摄氏度
} cal_data_t;




void fmc_calibration_data_init(void);

uint8_t get_calibration_enable_flag(void);
void write_calibration_enable_flag(uint8_t flag);

#ifdef __cplusplus
}
#endif

#endif


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
