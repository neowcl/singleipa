/**************************************************************************//**
 * @file     i2c_coms.c
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    I2C模块
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

// Include header file.
#include "i2c_coms.h"
#include "modules_reg.h"
#include "cbmx56x_i2c.h"

#include "app_interface.h"
#include "main_interface.h"

#if 1
void app_iic_isr_process(void)
{
    // 进入中断时，获取ISR中断相关状态，并存入缓存。
    volatile uint32_t i2c_isr_buffer = *(volatile uint32_t *)0x40005418;  

    if(i2c_isr_buffer & I2C_ISR_ADDR)
    {
        i2c_flag_clear(I2C_ISR_ADDR);        //软件清标志位
        on_slave_io_event(SLAVE_IO_EVENT_START, 0);
    }
    else if(i2c_isr_buffer & I2C_ISR_RXNE)  //主机写数据请求
    {
        on_slave_io_event(SLAVE_IO_EVENT_DATA, i2c_data_receive());
    }
    else if(i2c_isr_buffer & I2C_ISR_TXIS)  //主机读数据请求
    {
        on_slave_io_event(SLAVE_IO_EVENT_TRANSMIT, 0);
    }
    else if(i2c_isr_buffer & I2C_ISR_STOPF)  //主机收到stop信号
    {
        i2c_flag_clear(I2C_ISR_STOPF);
        on_slave_io_event(SLAVE_IO_EVENT_STOP, 0);
    }
    else if(i2c_isr_buffer & I2C_ISR_OVR)    // NACK TIMEOUT
    {
        i2c_interrupt_bit_clear(I2C_ISR_OVR);
        i2c_software_reset();
    }

    i2c_flag_clear(I2C_ISR_NACKF); //软件清标志位
}
#endif

#if 0
uint8_t rx_data;
uint8_t tx_data;
/**
  * @brief  app_iic_isr_process
  * @param  None
  * @retval None
  */
void app_iic_isr_process(void)
{
    // 进入中断时，获取ISR中断相关状态，并存入缓存。
    volatile uint32_t i2c_isr_buffer = *(volatile uint32_t *)0x40005418;  

    if(i2c_isr_buffer & I2C_ISR_ADDR)
    {
        i2c_flag_clear(I2C_ISR_ADDR);       //软件清标志位
    }
    else if(i2c_isr_buffer & I2C_ISR_RXNE)	//主机写数据请求
    {
         rx_data = i2c_data_receive();       //接收一个字节数据
    }
    else if(i2c_isr_buffer & I2C_ISR_TXIS)  //主机读数据请求
    {
        i2c_data_send(tx_data);             //发送一个字节数据
    }
    else if(i2c_isr_buffer & I2C_ISR_STOPF) //主机收到stop信号
    {
        i2c_flag_clear(I2C_ISR_STOPF);
    }
    else if(i2c_isr_buffer & I2C_ISR_OVR)  // NACK TIMEOUT
    {    
        i2c_interrupt_bit_clear(I2C_ISR_OVR);
        i2c_software_reset();
    }
    i2c_flag_clear(I2C_ISR_NACKF); //软件清标志位
}
#endif
