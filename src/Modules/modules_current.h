/***************************************************************************
 * @file     modules_current.h
 * @version  V1.0.0
 * @author   
 * @date     2021-01-25 AM
 * @brief    电流模块头文件
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 ****************************************************************************/
#ifndef __MODULES_CURRENT_H__
#define __MODULES_CURRENT_H__

// Include external header file.
#include "cbmx56x_conf.h"
#include "modules_delay.h"
#include "modules_fmc.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// Your code.
#define CC_CURR_VREF                  1217 * 1000     /*!< CC reference voltage */
#define CC_CURR_PGA                   10              /*!< CC gain */

#define CC_CALIBT_CLASSIS             1000            //电流校准参考经典值 1000mA

/**@brief CC模块中断处理函数  
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */  
void modules_cc_isr_process(void);

/**@brief 更新电池高精度电流
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  0:success  1:error
 */
char modules_cc_hp_updata_value(void);


/**@brief 获取电池高精度电流.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  高精度电流
 */
int32_t modules_cc_hp_get_value(void);

/**@brief 获取电池高精度电流.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  高精度电流
 */
 
 /**@brief 获取电池高速模式电流.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  高速模式电流
 */
int32_t modules_cc_hs_get_value(void);

/**@brief 获取电池高速模式电流.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  高速模式电流
 */
 
 
 
 
void modules_cc_hp_calibration(void);

/**@brief 电流模块设置校准参数.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
void modules_cc_hp_set_param(int16_t short_vol, int16_t coefficient);

/**@brief 电流模块获取校准offset参数.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
int16_t modules_cc_hp_get_short_vol(void);

/**@brief 电流模块设置进入内短模式.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
int16_t modules_cc_hp_get_coefficient(void);

/**@brief 获取电流换算完成标志位.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */

int8_t modules_cc_get_soc_calc_flag(void);



#ifdef __cplusplus
}
#endif

#endif  //__MODULES_CURRENT_H__


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
