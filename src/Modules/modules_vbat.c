/**************************************************************************//**
 * @file     modules_vbat.c
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    电压检测模块
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

// Include header file.
#include "modules_vbat.h"

static int16_t vbat_value = 0;

volatile static int16_t value_short_vol = 0;

volatile static float value_coefficient =1;

static int32_t modules_vbat_calc_value(int32_t reg_data);

/**
* @fn void modules_vbat_isr_process(void)
* @brief 电压模块中断处理函数  
* @param None
* @return None.
*/
void modules_vbat_isr_process(void)
{

}

/**
* @fn void modules_vbat_get_value(void)
* @brief 更新电压值
* @param None
* @return 0:success  1:error
*/
char modules_vbat_updata_value(void)
{ 
    int32_t vbat_value_temp = 0 ;

    if(vadc_flag_status_get(VADC_FLAG_CHANNEL0_ADCDVF) != SET)
    {
        return 1;
    }

    //modules_vbat_ctrl_disable();

    vbat_value_temp = vadc_conversion_value_get(VADC_CHANNEL_0);

    vbat_value = modules_vbat_calc_value(vbat_value_temp);                    //换算

    //modules_vbat_ctrl_enable();

    return 0;
}

/**
* @fn void modules_vbat_updata_task(void)
* @brief 从电压检测模块获得电压值
* @param None
* @return 电压值
*/
int16_t modules_vbat_get_value()
{
    return vbat_value;
}

/**
* @fn void modules_vbat_calc_value(void)
* @brief 计算电压值
* @param[out]  电压滤波后的值
* @return 电压值.
*/
static int32_t modules_vbat_calc_value(int32_t reg_data)
{
    int32_t dividend[2];
    int32_t divisor;
    int32_t quotient[2];
    int32_t remainder;
    int64_t value_vol;
    int32_t down_sampling_rate;
    int32_t vadc_offset;
    uint8_t i= 0;
       
  //  vadc_offset = vadc_vadc_offset_get();
   
    down_sampling_rate= (int32_t)vadc_down_sampling_rate_get();              //归一化值计算
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_HDIV, ENABLE);
    
    dividend[0]= ((reg_data>> 8)& 0x00FFFFFF);
    dividend[1]= reg_data<< 24;

    divisor= down_sampling_rate;
    hdiv_quotient_read(dividend, divisor, quotient, &remainder);  
    
    dividend[1]= quotient[0];
    dividend[0]= quotient[1];
    hdiv_quotient_read(dividend, divisor- 1, quotient, &remainder);
    
    if(quotient[0]> 0x800000)
    {
        value_vol= quotient[0]- 0x800000;
        i= 1;
    }
    else
    {
        value_vol= (0x800000- quotient[0]); 
        i= 0;
    }
    
    if (vadc_offset != 0)                                                   //偏移值处理
    {
        if (vadc_offset > 0x8000)
        {
            vadc_offset = vadc_offset - 0x8000;
        }
        else 
        {
            vadc_offset = -(0x8000 - vadc_offset);
        }
        vadc_offset= (2 * vadc_offset * 2 * VADC_VBAT_VREF * 10) >> 16; 
    }
    else 
    {
        vadc_offset = 0;
    }
    value_vol= ((VADC_VBAT_PGA_GAIN * value_vol * 2 * VADC_VBAT_VREF * 10) >> 24); 
    
    if(!i)
    {
        value_vol = -value_vol;
    }

    value_vol -= vadc_offset;
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_HDIV, DISABLE);

    value_vol = value_vol/10;                                               //不要最后一位，和TI同步

    value_vol = (value_vol-value_short_vol) * value_coefficient ;

    return (int16_t)value_vol;
}

#if 1

void modules_vbat_short_mode(void)
{
    vadc_channel_config_t vadc_channel_config;

    modules_vbat_ctrl_disable();  

    vadc_channel_config.channels = VADC_CHANNEL_0;
    vadc_channel_config.vadc_vadinchs = VADC_VADINCHS_NORMAL;
    vadc_channel_config.vadc_vadvbats = VADC_VADVBATS_SNS;
    vadc_channel_config.vadc_vadchs = VADC_VADCHS_INSIDE_SHORT;
    vadc_channel_config.vadc_gain = VADC_GAIN_0;
    vadc_channel_init(&vadc_channel_config);

    vadc_down_sampling_rate_set(750);

    //hal_vadc_stop_to_int();
    vadc_channel_enable_ctrl(VADC_CHANNEL_0, ENABLE);

    vadc_enable_ctrl(ENABLE);

}

void modules_vbat_normal_mode(void)
{
    vadc_channel_config_t vadc_channel_config;
        
    modules_vbat_ctrl_disable();  

    vadc_channel_config.channels = VADC_CHANNEL_0;
    vadc_channel_config.vadc_vadinchs = VADC_VADINCHS_VBAT;
    vadc_channel_config.vadc_vadvbats = VADC_VADVBATS_SNS;
    vadc_channel_config.vadc_vadchs = VADC_VADCHS_INSIDE_SHORT;
    vadc_channel_config.vadc_gain = VADC_GAIN_0;
    vadc_channel_init(&vadc_channel_config);

    vadc_down_sampling_rate_set(750);

    //hal_vadc_stop_to_int();
    vadc_channel_enable_ctrl(VADC_CHANNEL_0, ENABLE);

    vadc_enable_ctrl(ENABLE);
}

/**
* @fn void modules_vbat_calibration(void)
* @brief 电压模块校准函数
* @param None
* @return None.
*/
/*
void modules_vbat_calibration(void)                                         //使用此函数需要外部输入参考值(VBAT_CALIBT_CLASSIS)的电压
{
    modules_vbat_set_param(0,1);                                            //每次校准要初始化之前的内短值和系数，要不然会积累上误差，越校越不准

    modules_vbat_short_mode();                                              //设置成内短模式并启动

    delay_ms(40);                                                           //给硬件采集的时间
    
    modules_vbat_updata_value();                                            //采集数据 
     
    value_short_vol = modules_vbat_get_value();                             //取得内短模式下的offset值
    
    modules_vbat_normal_mode();                                             //恢复成正常模式
    
    delay_ms(40);
    
    modules_vbat_updata_value();                                            //更新正常模式下的值

    value_coefficient = ((float)VBAT_CALIBT_CLASSIS /(float)(modules_vbat_get_value() - value_short_vol));//理论电压(3800)除以实际采集电压减去offset电压就是电压增益系数
    //PS:这里采样硬件除法器应该可以优化计算速度，可以思考是否优化

    //modules_fmc_calibration_data_write(value_short_vol,value_coefficient,FMC_MODULES_VBAT);
}
*/
#endif

/**
* @fn void modules_vbat_ctrl_enable(void)
* @brief 启动AFE采样
* @param None
* @return None.
*/
void modules_vbat_ctrl_enable(void)
{
    vadc_enable_ctrl(ENABLE);
}

/**
* @fn void modules_vbat_ctrl_disable(void)
* @brief 关闭AFE采样
* @param None
* @return None.
*/
void modules_vbat_ctrl_disable(void)
{
    vadc_enable_ctrl(DISABLE);
}

/**
* @fn void modules_vbat_set_param(int16_t short_vol, int16_t coefficient)
* @brief 电压模块设置校准参数
* @param short_vol:offset参数
* @param coefficient:增益系数
* @return None.
*/
void modules_vbat_set_param(int16_t short_vol, int16_t coefficient)
{
    value_short_vol = short_vol;
    value_coefficient = coefficient;
  
}

/**
* @fn 
* @brief 电压模块设置offset参数
* @param None
* @return None.
*/
int16_t modules_vbat_get_short_vol(void)
{
    return value_short_vol;
}

/**
* @fn 
* @brief 电压模块设置校准增益系数
* @param None
* @return None.
*/
int16_t modules_vbat_get_coefficient(void)
{
    return value_coefficient;
}



