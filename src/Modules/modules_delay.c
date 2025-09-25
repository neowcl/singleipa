/**************************************************************************//**
 * @file     modules_vbat.c
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    ��ʱģ��
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

// Include header file.
#include "modules_delay.h"

static uint8_t  fac_us=0;			                    //us��ʱ������			   
static uint16_t fac_ms=0;			                    //ms��ʱ������,��os��,����ÿ�����ĵ�ms��
static uint16_t xms_max=0;                              //��¼delay_xms����������������ֵ

/**
* @fn void delay_init(uint8_t SYSCLK)
* @brief ��ʱ��ʼ��
* @param None
* @return ��ѹֵ
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
* @brief us����ʱ
* @param None
* @return ��ѹֵ
*/
void delay_us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL =0x00;  //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;            //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	            //�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;            //�رռ�����
	SysTick->VAL =0X00;       				            //��ռ����� 
}

/**
* @fn void delay_xms(uint16_t nms)
* @brief xms��ʱ
* @param None
* @return ��ѹֵ
*/
static void delay_xms(uint16_t nms)
{
    uint32_t temp;
    SysTick->LOAD=(uint32_t)nms*fac_ms;	                //ʱ�����(SysTick->LOADΪ24bit)
    SysTick->VAL =0x00;                                 //��ռ�����
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;            //��ʼ���� 
    do
    {
        temp=SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));               //�ȴ�ʱ�䵽��
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;            //�رռ�����
    SysTick->VAL =0X00;                                 //��ռ�����
} 

/**
* @fn void delay_ms(uint16_t nms)
* @brief ms����ʱ
* @param None
* @return ��ѹֵ
*/
void delay_ms(uint16_t nms)
{
    uint8_t repeat = nms/xms_max;   //������Ҫѭ�����ٴ�delay_xms
    uint16_t remain = nms%xms_max;
    while(repeat)
    {
        delay_xms(xms_max);
        repeat--;
    }
    if(remain)
        delay_xms(remain);
}
