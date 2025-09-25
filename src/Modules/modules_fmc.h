/***************************************************************************
 * @file     modules_fmc.h
 * @version  V0.0.14
 * @author   
 * @date     2022-11-02 AM
 * @brief    flash读写模块头文件
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 ****************************************************************************/
#ifndef __MODULES_FMC_H__
#define __MODULES_FMC_H__

// Include external header file.
#include "cbmx56x_conf.h"
#include "modules_current.h" 
#include "modules_vbat.h" 


#ifdef __cplusplus
extern "C" {
#endif


/**@brief 储存在FLASH中的数据取出  
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */ 

/**@brief 校准参数写入flash  
 * 
 * @param[in]  short_vol:内短值.
 * @param[in]  coefficient:增益系数.
 * @param[in]  modules:要写入的模块.
 * 
 * @return  None
 */ 

//extern cal_data_t cal_data;

int fmc_read_flash(uint16_t addr,  uint8_t* data, uint16_t len);
int fmc_write_flash(uint16_t addr, const uint8_t* data, uint16_t len);
int fmc_page_erase(uint16_t start_addr);

uint16_t get_fmc_tick_cnt();

#ifdef __cplusplus
}
#endif

#endif  //__MODULES_FMC_H__

/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
