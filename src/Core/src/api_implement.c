/***************************************************************************//**
 * @file     api_inplement.c
 * @version  V1.0.0
 * @author   sz414
 * @date     2022-06-06 PM
 * @brief    该文件实现了Core层对APP层导出的接口函数
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/
 
#include "main_interface.h"
#include "app_interface.h"
#include "cbmx56x_i2c.h"
#include "modules_fmc.h"

void os_i2c_data_send(uint8_t u)
{
    i2c_data_send(u);
}

void os_sleep(uint16_t millisecond)
{
}

int os_read_reg_block(uint16_t addr, uint8_t* data, uint16_t len)
{
    return 0;
}

int os_write_reg_block(uint16_t addr, const uint8_t* data, uint16_t len)
{
    return 0;
}

int _CSX_CALL os_read_flash(uint16_t addr, uint8_t* data, uint16_t len)
{
    fmc_read_flash(addr, data, len);
    return 0;
}

int _CSX_CALL os_write_flash(uint16_t addr, const uint8_t* data, uint16_t len)
{
    fmc_write_flash(addr, data, len);
    return 0;
}

void os_enable_interrupt(bool enable)
{
    if(enable){
        __enable_irq();
    }else{
        __disable_irq();
    }
}

void os_reset_system(void) 
{
     __NVIC_SystemReset();    //reset system
}
