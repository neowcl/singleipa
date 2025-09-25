/***************************************************************************
 * @file     modules_vbat.h
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    电压检测模块头文件
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 ****************************************************************************/

#ifndef __MODULES_VBAT_H__
#define __MODULES_VBAT_H__

// Include external header file.
#include "cbmx56x_conf.h"
#include "task.h"
#include "modules_delay.h"
#include "modules_fmc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define	VADC_VBAT_VREF			1217                            /*!< VADC reference voltage */
#define	VADC_VBAT_PGA_GAIN		5                               /*!< VADC gain */
    
#define VBAT_CALIBT_CLASSIS     3800                            //校准使用的经典值 3800mV

/**@brief 电压模块中断处理函数  
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */  
void modules_vbat_isr_process(void);

/**@brief 更新电池电压值
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  0:success  1:error
 */
char modules_vbat_updata_value(void);

/**@brief 获取电池电压值.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  电压值
 */
int16_t modules_vbat_get_value(void);

/**@brief 打开Vadc采集.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  电压值
 */
void modules_vbat_ctrl_enable(void);

    
/**@brief 关闭Vadc采集.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  电压值
 */
void modules_vbat_ctrl_disable(void);

/**@brief 电压模块启动校准.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
void modules_vbat_calibration(void);

/**@brief 电压模块设置校准参数.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
void modules_vbat_set_param(int16_t short_vol, int16_t coefficient);

/**@brief 电压模块设置offset参数.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
int16_t modules_vbat_get_short_vol(void);

/**@brief 电压模块设置校准增益系数.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
int16_t modules_vbat_get_coefficient(void);


#ifdef __cplusplus
}
#endif

#endif  //__MODULES_VBAT_H__


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
