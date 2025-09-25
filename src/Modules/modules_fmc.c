/**************************************************************************//**
 * @file     modules_fmc.c
 * @version  V0.2.10
 * @author   jacklee
 * @date     2022-10-19 AM
 * @brief    fmc模块
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

// Include header file.
#include "ic_config.h"  //Configure about IC.
#include "modules_fmc.h"
#include "task.h"
#include "bms_register_inc.h"

uint16_t fmc_tick_cnt = 0;

uint16_t get_fmc_tick_cnt()
{
    return fmc_tick_cnt;
}
// #define  cal_data_FLASH_BASE_ADDR 0xD000, see ic_config.h

/**
* @fn calibration_data_write
* @brief 校准参数写进flash
* @param None
* @return None
*/
int fmc_read_flash(uint16_t addr,  uint8_t* data, uint16_t len)
{
    uint8_t redundant_bytes = 0;
    uint8_t redundant_data_buf[4];
    uint16_t i;

    redundant_bytes = 4 - (addr % 4);//起始地址里

    gcr_reg_unlock();
    flash_page_read(FMC_DATA_FLASH_BASE_ADDR + addr - (addr%4), 4, redundant_data_buf);

    if(len <= redundant_bytes){
        for(i = 0; i < len; i++){
            data[i] = redundant_data_buf[(addr % 4)+i];
        }
    }else{
        for(i = 0; i < redundant_bytes; i++){
            data[i] = redundant_data_buf[(addr % 4)+i];
        }
        flash_page_read(FMC_DATA_FLASH_BASE_ADDR + addr - (addr%4) + 4, len - redundant_bytes, &data[redundant_bytes]);
    }

    gcr_reg_lock();
    return 0;
}

#define PAGE_SIZE 512

#if 0
int fmc_write_flash(uint16_t addr, const uint8_t* data, uint16_t len)
{
	uint16_t srcPos;
	uint16_t destPos;
	uint16_t start_addr;
	uint8_t page_buf[PAGE_SIZE];
	
	srcPos = 0;  //在data中的位置.
	destPos = addr % PAGE_SIZE;  //在page_buf中的位置
	start_addr = addr - destPos; // 计算起始的地址
os_enable_interrupt(0);
	gcr_reg_unlock();

	while(srcPos < len)
	{
		flash_page_read(FMC_DATA_FLASH_BASE_ADDR + start_addr, PAGE_SIZE, page_buf); // 读取整页
		
		while(destPos < PAGE_SIZE && srcPos < len)
		{
			page_buf[destPos++] = data[srcPos++];
		}
		flash_page_erase(FMC_DATA_FLASH_BASE_ADDR + start_addr);
		flash_page_write(FMC_DATA_FLASH_BASE_ADDR + start_addr, PAGE_SIZE, page_buf);// 保存页
		
		// NEXT PAGE.
		start_addr += PAGE_SIZE;
		destPos = 0;
	}
	
    gcr_reg_lock();
os_enable_interrupt(1);
    return 0;
}
#endif

int fmc_page_erase(uint16_t start_addr)
{
    uint16_t addr;
    uint16_t initlen=0;
    addr=start_addr*PAGE_SIZE;
    os_enable_interrupt(0);
    gcr_reg_unlock();
    flash_page_erase(addr);
    gcr_reg_lock();
    os_enable_interrupt(1);
    return 1;
}



int fmc_write_flash(uint16_t addr, const uint8_t* data, uint16_t len)
{
    uint16_t srcPos;
    uint16_t destPos;
    uint16_t start_addr;
    uint8_t page_buf[PAGE_SIZE];

    addr += FMC_DATA_FLASH_BASE_ADDR;//设置为绝对地址

    srcPos = 0;  //在data中的位置.
    destPos = addr % PAGE_SIZE;  //在page_buf中的位置
    start_addr = addr - destPos; // 计算起始的地址
    os_enable_interrupt(0);
    gcr_reg_unlock();

    while(srcPos < len)
    {
        flash_page_read( start_addr, PAGE_SIZE, page_buf); // 读取整页
        
        while(destPos < PAGE_SIZE && srcPos < len)
        {
            page_buf[destPos++] = data[srcPos++];
        }
        fmc_tick_cnt++;
        flash_page_erase( start_addr);
        flash_page_write(start_addr, PAGE_SIZE, page_buf);// 保存页
        
        // NEXT PAGE.
        start_addr += PAGE_SIZE;
        destPos = 0;
    }

    gcr_reg_lock();
    os_enable_interrupt(1);
    return 0;
}
