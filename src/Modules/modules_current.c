/****************************************************************************
 * @file     modules_current.c
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    电流模块
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

// Include header file.
#include "modules_current.h"


static int32_t  current_hp_value = 0;              //hp:HIGH PRECISION  小电流模式采用高精度电流
static int32_t  current_hs_value = 0;              //hs:HIGH_SPEED      正常模式采用快速响应电流 
static int16_t current_short_vol = 0;              //电流内短值
static float current_coefficient =1;               //电流增益系数
static uint8_t current_soc_calc_flag = 0;          //用于计算soc的标志位
static int32_t modules_cc_hp_calc_value(int32_t reg_data);
static void modules_cc_hp_short_mode(void);
static void modules_cc_hp_normal_mode(void);

/**
* @fn void modules_cc_isr_process(void)
* @brief CC模块中断处理函数  
* @param None
* @return None.
*/
void modules_cc_isr_process(void)
{
  
}

/**
* @fn char modules_cc_hp_updata_value(void)
* @brief 更新高精度电流值
* @param None
* @return 0:success  1:error
*/
char modules_cc_hp_updata_value(void)
{ 
    if(cc_intetrrupt_status_get(CC_INTR_CCIF) == SET)//240529
    {
        cc_intetrrupt_flag_clear(CC_INTR_CCIF);
        current_hp_value = cc_get_current(CC_HIGH_PRECISION_MODE)/1000;
        current_hs_value = cc_get_current(CC_HIGH_SPEED_MODE)/1000;
        return 0;
    }
    return 1;
}

/**
* @fn void modules_cc_hp_get_value(void)
* @brief 从电流检测模块获得电流值
* @param None
* @return 高精度电流值
*/
int32_t modules_cc_hp_get_value(void)
{
    return current_hp_value;
}

/**
* @fn void modules_cc_hp_get_value(void)
* @brief 从电流检测模块获得电流值
* @param None
* @return 高精度电流值
*/
int32_t modules_cc_hs_get_value(void)
{
    return current_hs_value;
}


/**
* @fn static int32_t modules_cc_hp_calc_value(int32_t reg_data)
* @brief 计算高精度电流值
* @param[out]  从寄存器取得的值
* @return 高精度电流
*/
static int32_t modules_cc_hp_calc_value(int32_t reg_data)   
{  
 
    int32_t dividend[2];
    int32_t divisor;
    int32_t quotient[2];
    int32_t remainder;
    int64_t value_curr;
    int32_t down_sampling_rate;
    uint8_t i= 0;
   
    int32_t cc_offset = cc_offset_get();
    
    down_sampling_rate = (int32_t)cc_down_sampling_rate_get();
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_HDIV, ENABLE);
    dividend[0] = ((reg_data >> 8)& 0x00FFFFFF);
    dividend[1] = reg_data << 24;
    
    divisor = down_sampling_rate;
    hdiv_quotient_read(dividend, divisor, quotient, &remainder);  
    
    dividend[1] = quotient[0];
    dividend[0] = quotient[1];
    hdiv_quotient_read(dividend, divisor+ 1, quotient, &remainder);

    if(quotient[0] > 0x800000)
    {
        value_curr = quotient[0] - 0x800000;
        i = 1;
    }
    else
    {
        value_curr= (0x800000 - quotient[0]); 
        i= 0;
    }
    value_curr -= cc_offset;
    value_curr = (value_curr* 2* CC_CURR_VREF* 1000/ CC_CURR_PGA)>> 24;

    if(!i)
    {
        value_curr = -value_curr;
    }
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_HDIV, DISABLE);
    
    value_curr = value_curr/1000;                            //丢弃后3个小数位，和TI同步
    //debug_printf("2value_curr %lld\n",value_curr);
    value_curr = (value_curr - current_short_vol) * current_coefficient;
    //debug_printf("3value_curr %lld\n",value_curr);
    //debug_printf(" short %d coe :%f\n",current_short_vol,current_coefficient);

    return (int16_t)value_curr;
}
#if 0
/**
* @fn void modules_cc_hs_calc_value(void)
* @brief 计算高精度电流值
* @param[out]  从寄存器取得的值
* @return 高速电流
*/
static int32_t modules_cc_hs_calc_value(int32_t reg_data)  
{     
    int32_t dividend[2];
    int32_t divisor;
    int32_t quotient[2];
    int32_t remainder;
    int64_t value_curr;
    int32_t down_sampling_rate;
    uint8_t i= 0;

    int32_t cc_offset = cc_offset_get();

    cc_value = cc_ccidr_get();

    down_sampling_rate = (int32_t)cc_down_sampling_rate_get();
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_HDIV, ENABLE);
    dividend[0] = ((reg_data >> 8)& 0x00FFFFFF);
    dividend[1] = reg_data << 24;

    divisor = down_sampling_rate* 2;
    hdiv_quotient_read(dividend, divisor, quotient, &remainder);  

    if (quotient[0]> 0x800000)
    {
       value_curr= quotient[0] - 0x800000;
       i= 1;
    }else
    {
       value_curr= (0x800000 - quotient[0]); 
       i= 0;
    }
    value_curr -= cc_offset;
    value_curr= (value_curr* 2* CC_CURR_VREF* 1000/ CC_CURR_PGA)>> 24;
           
    if(!i)
    {
       value_curr= -value_curr;
    }
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_HDIV, DISABLE);

    value_curr = value_curr/1000;                            //丢弃后3个小数位，和TI同步

    value_curr = (value_curr - current_short_vol) * current_coefficient;

    return (int16_t)value_curr;

}
#endif
/**
* @fn void modules_vbat_calibration(void)
* @brief 电压模块校准函数
* @param None
* @return None.
*/
/*
void modules_cc_hp_calibration(void)
{
     
    modules_cc_hp_set_param(0,1);                       //每次校准要初始化之前的内短值和系数，要不然会积累上次误差，越校越不准
  
    cc_enable_ctrl(DISABLE);                            //加这句是为了保证上一次CC转换彻底结束，以保证求内短值不会出错
    
    delay_ms(1200);
    
    modules_cc_hp_short_mode();                         //设置成内短模式

    delay_ms(1200);                                     //给硬件时间，正常模式下，CC模块1秒转换一次

    modules_cc_hp_updata_value();                       //采集数据 

    delay_ms(1200);

    current_short_vol = modules_cc_hp_get_value();   

    modules_cc_hp_normal_mode();                        //恢复成正常模式
 
    delay_ms(1100);                                     //给硬件时间
  
    modules_cc_hp_updata_value();                       //采集数据。

    delay_ms(1);

}
*/
/**
* @fn void modules_cc_hp_set_param(int16_t short_vol,int16_t coefficient)
* @brief 电流模块设置校准参数
* @param short_vol:offset参数
* @param coefficient:增益系数
* @return None.
*/
void modules_cc_hp_set_param(int16_t short_vol,int16_t coefficient)
{
    current_short_vol = short_vol ;
    current_coefficient = coefficient;

}

/**
* @fn int16_t modules_cc_hp_get_short_vol(void)
* @brief 电流模块获取校准offset参数
* @param None
* @return None.
*/
int16_t modules_cc_hp_get_short_vol(void)
{
    return current_short_vol;
}

/**
* @fn int16_t modules_cc_hp_get_coefficient(void)
* @brief 电流模块获取校准增益系数
* @param None
* @return None.
*/
int16_t modules_cc_hp_get_coefficient(void)
{
    return current_coefficient;
}

/**
* @fn int8_t modules_cc_get_soc_calc_flag(void) 
* @brief 从电流检测模块获得电流值
* @param None
* @return 高精度电流值
*/
int8_t modules_cc_get_soc_calc_flag(void)                                 
{
    return current_soc_calc_flag;
}

/**
* @fn static void modules_cc_hp_short_mode(void)
* @brief 电流模块设置进入内短模式
* @param None
* @return None.
*/
static void modules_cc_hp_short_mode(void)
{
    cc_config_t cc_config;

    cc_enable_ctrl(DISABLE);
    delay_ms(1);
    cc_config.cc_fclk = CC_FS_SEL_65538;
    cc_config.cc_gain = CC_GAIN_10;
    cc_config.cc_sinl = CC_SINL_SHORT;;
    cc_config.cc_fchop = CC_FCHOP_2;
    cc_config.cc_imod = CC_IMOD_NOLMAL;

//    cc_config.cc_fclk = CC_FS_SEL_32768;
//    cc_config.cc_gain = CC_GAIN_20;
//    cc_config.cc_sinl = CC_SINL_SHORT;;
//    cc_config.cc_fchop = CC_FCHOP_2;
//    cc_config.cc_imod = CC_IMOD_LOW_POWER;
    cc_init(&cc_config);
    cc_stop_mode_set(CC_STOP_INIT);
    cc_enable_ctrl(ENABLE);
}

/**
* @fn static void modules_cc_hp_normal_mode(void)
* @brief 电流模块设置进入正常模式
* @param None
* @return None.
*/
static void modules_cc_hp_normal_mode(void)
{
    cc_config_t cc_config;
    cc_enable_ctrl(DISABLE);
    delay_ms(1);
    cc_config.cc_fclk = CC_FS_SEL_65538;
    cc_config.cc_gain = CC_GAIN_10;
    cc_config.cc_sinl = CC_SINL_SRP_SRN;
    cc_config.cc_fchop = CC_FCHOP_2;
    cc_config.cc_imod = CC_IMOD_NOLMAL; 
    cc_init(&cc_config);
    cc_stop_mode_set(CC_STOP_INIT);
    cc_enable_ctrl(ENABLE);
}
