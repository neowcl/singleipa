/**************************************************************************//**
 * @file     modules_vbat.c
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    延时模块
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

// Include header file.
#include "modules_delay.h"

static uint8_t  fac_us=0;			                    //us延时倍乘数			   
static uint16_t fac_ms=0;			                    //ms延时倍乘数,在os下,代表每个节拍的ms数
static uint16_t xms_max=0;                              //记录delay_xms函数输入参数的最大值

/**
* @fn void delay_init(uint8_t SYSCLK)
* @brief 延时初始化
* @param None
* @return 电压值
*/
void delay_init(void)
{
    SysTick->CTRL |=SysTick_CTRL_CLKSOURCE_Msk; 
    fac_us = 16;
    fac_ms = (uint16_t)fac_us*1000;
    xms_max = 0x00ffffff/fac_us/1000;
}

/**
* @fn void delay_us(uint32_t nus)
* @brief us级延时
* @param None
* @return 电压值
*/
void delay_us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL =0x00;  //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;            //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	            //等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;            //关闭计数器
	SysTick->VAL =0X00;       				            //清空计数器 
}

/**
* @fn void delay_xms(uint16_t nms)
* @brief xms延时
* @param None
* @return 电压值
*/
static void delay_xms(uint16_t nms)
{
    uint32_t temp;
    SysTick->LOAD=(uint32_t)nms*fac_ms;	                //时间加载(SysTick->LOAD为24bit)
    SysTick->VAL =0x00;                                 //清空计数器
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;            //开始倒数 
    do
    {
        temp=SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));               //等待时间到达
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;            //关闭计数器
    SysTick->VAL =0X00;                                 //清空计数器
} 

/**
* @fn void delay_ms(uint16_t nms)
* @brief ms级延时
* @param None
* @return 电压值
*/
void delay_ms(uint16_t nms)
{
    uint8_t repeat = nms/xms_max;   //计算需要循环多少次delay_xms
    uint16_t remain = nms%xms_max;
    while(repeat)
    {
        delay_xms(xms_max);
        repeat--;
    }
    if(remain)
        delay_xms(remain);
}
