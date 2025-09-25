/***************************************************************************
 * @file     modules_init.h
 * @version  V1.0.0
 * @author   
 * @date     2021-01-25 AM
 * @brief    
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 ****************************************************************************/
#ifndef __MODULES_INIT_H__
#define __MODULES_INIT_H__

// Include external header file.
#include "cbmx56x_conf.h"
#include "i2c_coms.h"
#include "modules_fmc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @fn void modules_init(void)
* @brief 模块初始化
* @param None
* @return 0:success  1:error
*/

#define IIC_ADDR 0x16
#define IICDELAY  20



void clear_dog(void);
void block_delay_ms(uint32_t count);
void modules_init(void);
void app_iic_init(void);
void address_gpio_disable_irq(void);
void user_app_init(void);
void gpio_disable_irq(void);
void gpio_enable_irq(void);
void pmu_deepsleep2_enter(void);
void IIC_timeout_process(void);
void HDIV_init(void);
void SHA256_init(void);
void Flash_init(void);
void CRC_init(void);
void CC_lowpower_init(void);
void CC_normal_init(void);
void sleep(void);
void I2C_busy_judge(void);
void set_I2C_TimeOut_Count(uint16_t cnt);



#ifdef __cplusplus
}
#endif

#endif  //__MODULES_INIT_H__


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
