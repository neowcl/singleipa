/***************************************************************************
 * @file     modules_temp.h
 * @version  V1.0.0
 * @author   
 * @date     2021-01-25 AM
 * @brief    温度检测模块头文件
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 ****************************************************************************/

#ifndef __MODULES_TEMP_H__
#define __MODULES_TEMP_H__

// Include external header file.
#include "cbmx56x_conf.h"
#include "modules_vbat.h"


#ifdef __cplusplus
extern "C" {
#endif

/**@brief 温度模块中断处理函数  
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */  
//void modules_temp_isr_process(void);

/**@brief 更新电池内部温度值
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  0:success  1:error
 */
//char modules_temp_in_updata_value(void);

/**@brief 更新电池外部温度值
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  0:success  1:error
 */
//char modules_temp_ex_updata_value(void);


/**@brief 从温度检测模块获得内部温度值.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  电压值
 */
//int16_t modules_temp_in_get_value(void);

/**@brief 从温度检测模块获得内部温度值.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  电压值
 */
//int16_t modules_temp_ex_get_value(void);

//int16_t modules_check_table(int table_data);

int16_t Lookup_T(int32_t Rt);

#ifdef __cplusplus
}
#endif

#endif  //__MODULES_TEMP_H__


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
