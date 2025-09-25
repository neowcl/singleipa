/***************************************************************************//**
 * @file     isr.h
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    中断模块头文件
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 ****************************************************************************
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/01/25  <td>1.0      <td>chensj0621  <td>创建初始版本
 * </table>
 *
 *****************************************************************************/


#ifndef __ISR_H__
#define __ISR_H__

// Include external header file.
#include "modules_vbat.h"
#include "task.h"
#include "i2c_coms.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief  This function handles NMI exception.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return 	None.
 */
void NMI_Handler(void);

/**@brief  This function handles Hard Fault exception.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return 	None.
 */
void HardFault_Handler(void);

/**@brief  This function handles SVCall exception.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return 	None.
 */
void SVC_Handler(void);

/**@brief  This function handles PendSVC exception.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return 	None.
 */
void PendSV_Handler(void);

/**@brief  This function handles SysTick Handler.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return 	None.
 */
void SysTick_Handler(void);

/**@brief  This function handles I2C Handler.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None.
 */
void I2C_IRQHandler(void);

/**@brief  This function handles TMR1 Handler.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None.
 */
void TMR1_IRQHandler(void);

/**@brief  This function handles WDT Handler.
* 
* @param[in]  None.
* @param[out] None.
* 
* @return  None.
*/
void WDT_IRQHandler(void);

void i2c_restart(void);

#ifdef __cplusplus
}
#endif

#endif  //__ISR_H__


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
