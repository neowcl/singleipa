/***************************************************************************//**
 * @file     Algorithm.h
 * @version  V1.0.0
 * @author   lizhi
 * @date     2022-11-5 AM
 * @brief    BMS算法模块头文件
 * 
 * @copyright Copyright (C) 2022 Chipsea Technologies Corp. All rights reserved.
 ****************************************************************************
 * @attention
 *  硬件平台: xxxx \n
 *  SDK版本：SDK_1.0.0
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/11/5   <td>1.0      <td>lizhi       <td>创建初始版本
 * </table>
 *
 *****************************************************************************/

#include "rtwtypes.h"


/**@brief 算法模块初始化函数.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
extern void bms_algorithm_initialize(void);



/**@brief 算法模块运行计算函数（运行周期1S）.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
extern void bms_algorithm_step(void);


/**@brief 取算法模块输出SOC值.
 * 
 * @param[in]  None.
 * @param[out] 电池SOC值(int16) 值8910代表SOC=89.10%.
 * 
 * @return  None
 */
 
extern int16_T get_soc_output(void);


/*** (C) COPYRIGHT 2022 Chipsea Technologies (Shenzhen) Corp. ***/
