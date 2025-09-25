/***************************************************************************
 * @file     modules_delay.h
 * @version  V1.0.0
 * @author   
 * @date     2021-01-25 AM
 * @brief    
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 ****************************************************************************/

#ifndef __MODULES_DELAY_H__
#define __MODULES_DELAY_H__

// Include external header file.
#include "cbmx56x_conf.h"


#ifdef __cplusplus
extern "C" {
#endif


/**@brief ��ʱ��ʼ��  
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */  
void delay_init(void);

/**@brief us����ʱ  
 * 
 * @param[in]  nus:��ʱ��us��.
 * @param[out] None.
 * 
 * @return  None
 */  
void delay_us(uint32_t nus);

/**@brief ms����ʱ  
 * 
 * @param[in]  nms:��ʱ��ms��.
 * @param[out] None.
 * 
 * @return  None
 */  
void delay_ms(uint16_t nms);



#ifdef __cplusplus
}
#endif

#endif  //__MODULES_DELAY_H__


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/

