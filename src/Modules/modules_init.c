/**************************************************************************//**
 * @file     modules_init.c
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    初始化模块头文件
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

// Include header file.
#include "modules_init.h"
#include "modules_delay.h"
#include "modules_init.h"
#include "modules_delay.h"
#include "modules_reg.h"
#include "calibration_handle.h"
#include "bit_register.h"
//#include "cbmx56x_reg.h"

void block_delay_us(uint32_t count)
{
    volatile uint32_t cnt = count;
    while(cnt--)
    {
         cnt++;
         cnt--;
    }
}

void block_delay_ms(uint32_t count)
{
    while(count--)
    {
        block_delay_us(900);
    }
}


/**
  * @brief  iwdg_init 2s clk = 65.536kHz
  * @param  None
  * @retval None
  */
void iwdg_init(void)
{
    iwdg_write_access_enable_ctrl(IWDG_WRITE_ACCESS_ENABLE);
    iwdg_prescaler_set(IWDG_PRESCALER_64);
    iwdg_reload_set(0x800);
    iwdg_enable();
    iwdg_write_access_enable_ctrl(IWDG_WRITE_ACCESS_DISABLE);
}

/**
  * @brief  clear_dog
  * @param  None
  * @retval None
  */
void clear_dog(void)
{
    iwdg_write_access_enable_ctrl(IWDG_WRITE_ACCESS_ENABLE);
    iwdg_reload_counter();
    iwdg_write_access_enable_ctrl(IWDG_WRITE_ACCESS_DISABLE);
}

/**
* @fn  void modules_iic_init(void)
* @brief I2C初始化t
* @param None
* @return None.
*/
void app_iic_init(void)                                                                // IIC模块初始化
{
    i2c_config_t i2c_initstruct;
    rcc_apb_periph_clock_enable_ctrl(RCC_APB_PERI_I2C, ENABLE);                        //打开iic 时钟 
    i2c_stretch_clock_enable_ctrl(ENABLE);
    
    i2c_interrupt_config(I2C_ISR_TXIS | I2C_ISR_RXNE | I2C_ISR_ADDR | I2C_ISR_NACKF | I2C_ISR_STOPF, ENABLE);//打开iic 主机读请求中断 / 据接收中断 / STOP中断
      //0x00420F13  100k    0x0042C3C7  10k  0x00100306 500k
    i2c_initstruct.tmr_value =  0x00310309;//0x00310309;                               //!< 在主从模式中必须配置时序，以保证正确的数据保持和建立时间
    i2c_initstruct.analog_flag = I2C_ANALOG_FILTER_ENABLE;                             //!< 配置噪声滤波器
    i2c_initstruct.digital_value = 0x00;                                               //!< 设置数字噪声滤波器。范围为0x00 ~ 0x0F。
    i2c_initstruct.mode = I2C_BUS_MODE_I2C;                                            //!< set the I2C mode.
    i2c_initstruct.slave_addr1 = 0x16;  //slave IIC device address                     //!< set slave address 1.It can be a 7bits or 10bits address.
    i2c_initstruct.ack_flag = I2C_ACK_ENABLE;                                          //!< 接收当前字节之后发送ACK使能
    i2c_initstruct.ack_addr = I2C_ACK_ADDR_7BITS;                                      //!<  set acknowledge address.It can be a 7bits or 10bits address.
    i2c_init(&i2c_initstruct); //初始化iic
    
    i2c_addr_timeout_set(0x00C8); //25ms timeout  23231201
    i2c_addr_timeout_enable_ctrl(ENABLE);
    
    i2c_wakeup_enable_ctrl(ENABLE);
    i2c_enable_ctrl(ENABLE); //使能

    i2c_busy_timeout_set(0x7FFF);  //240417
    i2c_busy_timeout_enable_ctrl(ENABLE);
   
}

#define I2C_TIME_OUT_CNT        1000
volatile uint16_t I2C_TimeOut_Count = 0;

void set_I2C_TimeOut_Count(uint16_t cnt)
{
    I2C_TimeOut_Count = 0;
}

void IIC_timeout_process(void)
{
    for(uint16_t i = 0;i < I2C_TIME_OUT_CNT;i++)
    {
        if(i2c_flag_status_get(I2C_ISR_BUSY) == SET)
        {
            I2C_TimeOut_Count++;
        }
        else
        {
            break;
        }
        block_delay_us(50);
    }

    if(I2C_TimeOut_Count > (I2C_TIME_OUT_CNT-5))
    {
        i2c_def_init();
        app_iic_init();
        I2C_TimeOut_Count = 0;
    }
}

void HDIV_init(void)
{
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_HDIV, ENABLE);
}

void CRC_init(void)
{
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_CRC, ENABLE);
    crc_def_init();
}

void LN_init(void)
{
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_LN, ENABLE);
    ln_cn_config(LN_CN_5);
}

void SHA256_init(void)
{
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_SHA256, ENABLE);
}

static void modules_gpio_init()
{

    gpio_config_t gpio_config;
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_GPIOA, ENABLE);

    gpio_config.gpio_pin = GPIO_PIN_2;
    gpio_config.gpio_mode = GPIO_MODE_OUTPUT_OD;                                     //推挽输出模式  MCO引脚输出HFO
    gpio_config.gpio_pull = GPIO_PULL_NO_PULL;
    gpio_init(&gpio_config);
    gpio_mf_config(GPIO_PIN_NUM2, GPIO_MF_SEL1);

    gpio_config.gpio_pin = GPIO_PIN_3;
    gpio_config.gpio_mode = GPIO_MODE_OUTPUT_OD;
    gpio_config.gpio_pull = GPIO_PULL_NO_PULL;
    gpio_init(&gpio_config);
    gpio_mf_config(GPIO_PIN_NUM3, GPIO_MF_SEL1);

//    gpio_config.gpio_mode = GPIO_MODE_OUTPUT_PP;                                     //推挽输出模式  MCO引脚输出HFO
//    gpio_config.gpio_pull = GPIO_PULL_DOWN;
//    gpio_config.gpio_pin = GPIO_PIN_0 ;
//    gpio_init(&gpio_config);
//    gpio_mf_config(GPIO_PIN_NUM0, GPIO_MF_SEL2);//2 PA8,PA7,PA6,PA5,PA4,RX,TX,TIM0_CH0, MCO
//    rcc_clkout_config(RCC_CLKOUT_SEL_HFO,RCC_CLKOUT_PDIV_1);


//    nvic_init(&nvic_config_struct);
}

void interrupt_disable(void)    // 芯海更新库函数，增加关闭全局中断的函数
{
    __disable_irq();
}

void interrupt_enable(void)     // 芯海更新库函数，增加关闭全局中断的函数
{
    __enable_irq();
}



void interrupt_init(void)
{
    nvic_config_t nvic_config;

    // 中断优先级 I2C>PA>timer 规避AA版本从睡眠模式唤醒，I2C通信异常的问题 BA版本硬件已经处理

    nvic_config.nvic_IRQ_channel = IRQn_I2C;
    nvic_config.nvic_channel_priority = 0;
    nvic_config.nvic_enable_flag = ENABLE;
    nvic_init(&nvic_config);

    nvic_config.nvic_IRQ_channel = IRQn_PA ;
    nvic_config.nvic_channel_priority = 1;
    nvic_config.nvic_enable_flag = ENABLE;
    nvic_init(&nvic_config);

    nvic_config.nvic_IRQ_channel = IRQn_TMR1;
    nvic_config.nvic_channel_priority = 2;
    nvic_config.nvic_enable_flag = ENABLE;
    nvic_init(&nvic_config);
}


void VADC_init(void)
{
    vadc_config_t vadc_config;
    vadc_channel_config_t vadc_channel_config;

    rcc_apb_periph_clock_enable_ctrl(RCC_APB_PERI_VADC, ENABLE);

    vadc_config.vadc_fclk = VADC_FS_SEL_65536;
    vadc_config.vadc_conversion_mode = VADC_CONVERSION_1_CYCLE;
    vadc_config.vadc_fchop = VADC_FCHOP_0;
    vadc_init(&vadc_config);

    vadc_chop_enable_ctrl(ENABLE);
    vadc_vcm_set(0);

    vadc_channel_config.channels = VADC_CHANNEL_0;
    vadc_channel_config.vadc_vadinchs = VADC_VADINCHS_VBAT;
    vadc_channel_config.vadc_vadvbats = VADC_VADVBATS_SNS;
    vadc_channel_config.vadc_vadchs = VADC_VADCHS_INSIDE_PIN_VOLTAGE;
    vadc_channel_config.vadc_gain = VADC_GAIN_0;
    vadc_channel_init(&vadc_channel_config);

    vadc_channel_config.channels = VADC_CHANNEL_2;
    vadc_channel_config.vadc_vadinchs = VADC_VADINCHS_NORMAL;
    vadc_channel_config.vadc_vadvbats = VADC_VADVBATS_SNS;
    vadc_channel_config.vadc_vadchs = VADC_VADCHS_INSIDE_SENSOR;
    vadc_channel_config.vadc_gain = VADC_GAIN_1;
    vadc_channel_init(&vadc_channel_config);

    // vadc_channel_config.channels = VADC_CHANNEL_3;
    // vadc_channel_config.vadc_vadinchs = VADC_VADINCHS_NORMAL;
    // vadc_channel_config.vadc_vadvbats = VADC_VADVBATS_SNS;
    // vadc_channel_config.vadc_vadchs = VADC_VADCHS_EXTERNAL_SENSOR;
    // vadc_channel_config.vadc_gain = VADC_GAIN_2;
    // vadc_channel_init(&vadc_channel_config);

    vadc_down_sampling_rate_set(750);

    vadc_stop_mode_set(VADC_STOP_INIT);
    vadc_channel_enable_ctrl(VADC_CHANNEL_0,ENABLE);
    vadc_channel_enable_ctrl(VADC_CHANNEL_2,ENABLE);
    //vadc_channel_enable_ctrl(VADC_CHANNEL_3,ENABLE);
    vadc_interrupt_config(DISABLE);
    vadc_enable_ctrl(ENABLE);
    //vadc_enable_ctrl(DISABLE);
}

void CC_lowpower_init(void)
{
    cc_config_t cc_config;

    cc_config.cc_fclk = CC_FS_SEL_65538;
    cc_config.cc_gain = CC_GAIN_20;
    cc_config.cc_sinl = CC_SINL_SRP_SRN;
    cc_config.cc_fchop = CC_FCHOP_2;
    cc_config.cc_imod = CC_IMOD_NOLMAL;
    cc_init(&cc_config);

    cc_chop_enable_ctrl(ENABLE);
    cc_opchop_enable_ctrl(ENABLE);

    cc_vcm_set(CC_STOP_VCMSEL_1);

    cc_down_sampling_rate_set(30000);
    cc_gtc_set(0);

    cc_stop_mode_set(CC_STOP_SLEEP);
    cc_interrupt_config(DISABLE);
    cc_enable_ctrl(ENABLE);
}

void CC_normal_init(void)
{
    cc_config_t cc_config;

    cc_config.cc_fclk = CC_FS_SEL_65538;
    cc_config.cc_gain = CC_GAIN_10;
    cc_config.cc_sinl = CC_SINL_SRP_SRN;
    cc_config.cc_fchop = CC_FCHOP_2;
    cc_config.cc_imod = CC_IMOD_NOLMAL;
    cc_init(&cc_config);

    cc_chop_enable_ctrl(ENABLE);
    cc_opchop_enable_ctrl(ENABLE);

    cc_vcm_set(CC_STOP_VCMSEL_1);

    cc_down_sampling_rate_set(65000);

    cc_gtc_set(0x23);

    cc_stop_mode_set(CC_STOP_SLEEP);
    cc_interrupt_config(DISABLE);
    cc_enable_ctrl(ENABLE);
}

void CC_init(void)
{
    cc_config_t cc_config;
    rcc_apb_periph_clock_enable_ctrl(RCC_APB_PERI_CC, ENABLE);
    
    cc_config.cc_fclk = CC_FS_SEL_65538;
    cc_config.cc_gain = CC_GAIN_10;
    cc_config.cc_sinl = CC_SINL_SRP_SRN;//CC_SINL_SHORT;
    cc_config.cc_fchop = CC_FCHOP_2;
    cc_config.cc_imod = CC_IMOD_NOLMAL;
    cc_init(&cc_config);
    cc_chop_enable_ctrl(ENABLE);
    cc_opchop_enable_ctrl(ENABLE);
    cc_vcm_set(CC_STOP_VCMSEL_1);
    cc_down_sampling_rate_set(65000);
    cc_gtc_set(0x23);   // BA版本通过实际BG温漂，温补系数为0x23 AA版本为0x33
    cc_stop_mode_set(CC_STOP_SLEEP);
    cc_interrupt_config(DISABLE);
    cc_enable_ctrl(ENABLE);
}


/**
* @fn  void timer1_init(void)
* @brief 
* @param 周期定时器初始化，
* @return None.
*/
static void app_timer1_init(void)
{
    timer1_config_t timer1_config;

    nvic_config_t nvic_config_struct;

    nvic_config_struct.nvic_IRQ_channel = IRQn_TMR1 ;
    nvic_config_struct.nvic_channel_priority = 0x01;
    nvic_config_struct.nvic_enable_flag = ENABLE;
    nvic_init(&nvic_config_struct);

    rcc_apb_periph_clock_enable_ctrl(RCC_APB_PERI_TMR1, ENABLE);
    rcc_tim1_clk_config(RCC_TIM1_SEL_LFO);
    timer1_config.int_enable = ENABLE;
    timer1_config.clk_divide = 63;
    timer1_config.period_select_enable = DISABLE;
    timer1_config.cmp_cnt = 1024;
    timer1_config.work_mode = TIM1_MODE_PERIOD;
    tim1_timer_config(&timer1_config);
    tim1_cnt_update_enable_ctrl(ENABLE); 
    tim1_enable_ctrl(ENABLE);
}

/**
* @fn  void modules_fmc_init(void)
* @brief flash模块初始化
* @param None
* @return None.
*/
static void modules_fmc_init(void)
{
    flash_config_t ptr_config;

    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_ROM, ENABLE);             //打开ROM时钟
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_ISP, ENABLE);             //打开IPS时钟

    ptr_config.aprom_update_en = ENABLE;
    ptr_config.cfg_update_en = DISABLE;
    ptr_config.erase_write_en = ENABLE;
    ptr_config.isp_en = ENABLE;
    ptr_config.isp_freq = ISP_FREQ_16MHZ;
    ptr_config.ldrom_update_en = DISABLE;

    gcr_reg_unlock();
    flash_init(&ptr_config);
    flash_wait_counter_set(FMC_WCR_WCNT_0);
    gcr_reg_lock();
}

/**
* @fn  void sysTick_init(void)
* @brief 滴答定时器初始化
* @param None
* @return None.
*/
#if 0
void sysTick_init (uint32_t rvr_value)
{
   SYSTICK->RVR = rvr_value;
   SYSTICK->CVR = 0X00;
   SYSTICK->CSR = 0x07;  /*configure CSR register interrupt enable*/  
}
#endif
//void pmu_deepsleep2_init()
//{
//    volatile uint32_t * scb = (volatile uint32_t *)0xE000Ed10;
//    *scb |= SCB_SCR_SLEEPDEEP_Msk;  /*!< Set SLEEPDEEP bit of Cortex-M0 System Control Register */
//}

void modules_pmu_init(void)
{
    nvic_config_t nvic_config_struct;

    nvic_config_struct.nvic_IRQ_channel = IRQn_WK ;
    nvic_config_struct.nvic_channel_priority = 0x00;
    nvic_config_struct.nvic_enable_flag = ENABLE;
    nvic_init(&nvic_config_struct);
}

void address_gpio_enable_irq(void)
{
    volatile uint32_t* ier = ( uint32_t*)0x5000401c;
    gpio_interrupt_status_clear(GPIO_PIN_2);

    *ier |= 0x80004;
}

void address_gpio_disable_irq(void)
{
    volatile uint32_t* ier = (uint32_t*)0x5000401c;

    *ier &= ~0x80004; // 清除SCL和SDA 两个GPIO的下降沿中断
    gpio_interrupt_status_clear(GPIO_PIN_2);
    NVIC->ISER[0] = (uint32_t)0x01 << (IRQn_PA & (uint8_t)0x1F);
}


//void address_gpio_enable_irq(void)
//{
//	volatile uint32_t* ier = ( uint32_t*)0x5000401c;
//	gpio_interrupt_status_clear(GPIO_PIN_2);

//	*ier |= 0x80004;
//}

//void gpio_disable_irq(void)
//{
//	volatile uint32_t* ier = (uint32_t*)0x5000401c;

//	*ier &= ~0x80004; // 清除SCL和SDA 两个GPIO的下降沿中断
//	gpio_interrupt_status_clear(GPIO_PIN_2);
//	NVIC->ISER[0] = (uint32_t)0x01 << (IRQn_PA & (uint8_t)0x1F);
//}


void address_deepsleep2_enter(void)
{
    uint32_t * i2c_isr = (uint32_t *)0x40005418;
    pmu_deepsleep2_init();

    if(((* i2c_isr ) & 0x00008000) == 0x00008000)
    {
        return;
    }
    address_gpio_enable_irq();  /*!< enable SDA SCL Interrupt */
//  gpio_enable_irq();

    if(((* i2c_isr ) & 0x00008000) == 0x00008000)
    {
        return;
    }
    __WFI(); /*!< Request Wait For Interrupt */
}

/**
  * @fn  void user_app_proc(void)
  * @brief  app function
  * @param
  * @return None
  */
void sleep(void)
{
    //gpio_enable_irq();
    //pmu_deepsleep2_enter();// don't work
    i2c_busy_judge(100);
    //pmu_sleep_mode_enter(PMU_DEEP_SLEEP_MODE2, PMU_DSM_ENTRY_WFI);//enter deep sleep
    //my_sleep_mode_enter(PMU_DEEP_SLEEP_MODE2, PMU_DSM_ENTRY_WFI);
    address_deepsleep2_enter();
}

//void pmu_deepsleep2_enter(void)
//{
//    volatile uint32_t * i2c_isr = (volatile uint32_t *)0x40005418;

//    pmu_deepsleep2_init();

//    if(((* i2c_isr ) & 0x00008000) == 0x00008000)
//    {
//        return;
//    }
//    gpio_enable_irq();
//    if(((* i2c_isr ) & 0x00008000) == 0x00008000)
//    {
//        return;
//    }
//    __WFI();        /*!< Request Wait For Interrupt */
//}

void pmu_deepsleep1_enter(void)
{
    pmu_sleep_mode_enter(PMU_DEEP_SLEEP_MODE1, PMU_DSM_ENTRY_WFI);
}



//void i2c_restart(void)
//{
//    uint32_t reg_CR1 = 0;
//    uint32_t reg_CR2 = 0;
//    uint32_t reg_OAR1 = 0;
//    uint32_t reg_OAR2 = 0;
//    uint32_t reg_TIMMINGR = 0;

//    reg_CR1 =  I2C->CR1;         // 复位之前先读取I2C的当前配置
//    reg_CR2 =  I2C->CR2;
//    reg_OAR1 =  I2C->OAR1;
//    reg_OAR2 =  I2C->OAR2;
//    reg_TIMMINGR = I2C->TIMMINGR;

//    RCC->IPRSTC2 = 0x00000100;     //复位I2C寄存器
//    RCC->IPRSTC2 = 0x00000000;

//    I2C->CR2 = reg_CR2;
//    I2C->OAR1 = reg_OAR1;
//    I2C->OAR2 = reg_OAR2;
//    I2C->TIMMINGR = reg_TIMMINGR;
//    I2C->CR1 = reg_CR1;
//}



#if 0   //Remarked by wuhz, 2022.08.15
void reg_init_test(void)
{
    uint8_t i, j;
    for(i = 0; i < 0x24; i++){
        for(j = 0; j < REG_TABLE[i].Cmd_Buf_Size; j++){
            REG_TABLE[i].p_Cmd_Buf[j] = i+j;
        }
    }
}
#endif 

/**
* @fn modules_init(void)
* @brief 所有模块初始化
* @param None
* @return None.
*/
void modules_init(void)
{
    iwdg_init();                            //看门狗初始化
    interrupt_disable();                    //关总中断
    modules_fmc_init();                     //flash模块初始化
    app_timer1_init();                      //定时器1初始化
    HDIV_init();                            //除法器初始化
    modules_gpio_init();                    //IIC GPIO初始化
    MyI2C_Init();
    app_iic_init();                         //I2C模块初始化
    SHA256_init();                          //SHA256模块初始化
    CRC_init();                             //CRC模块初始化
    pmu_deepsleep2_init();                  //休眠模块初始化
    modules_pmu_init();
    block_delay_ms(2000);
    VADC_init();                           //AFE模块初始化
    cc_enable_ctrl(DISABLE);
    CC_init();
    interrupt_init();                      //模块中断初始化
    interrupt_enable();                    //开总中断

#ifdef DEBUG_MODE
    modules_uart_init(TX_PIN);
#endif

}




/**
* @fn modules_init(void)
* @brief 测试IO
* @param None
* @return None.
*/
void test_io_init(void)
{
    gpio_config_t ptr_config;
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_GPIOA, ENABLE);                   //使能GPIOA时钟
    ptr_config.gpio_mode = GPIO_MODE_OUTPUT_PP;                                     //推挽输出模式
    ptr_config.gpio_pull = GPIO_PULL_DOWN;
    ptr_config.gpio_pin = GPIO_PIN_0 ;
    gpio_init(&ptr_config);
    gpio_mf_config(GPIO_PIN_NUM0, GPIO_MF_SEL1);//1 PA8,PA7,PA6,PA5,PA4,SCL,SDA,PA1,PA0

    //gpio_mf_config(GPIO_PIN_NUM0, GPIO_MF_SEL1);//1 PA8,PA7,PA6,PA5,PA4,SCL,SDA,PA1,PA0
    //gpio_mf_config(GPIO_PIN_NUM0, GPIO_MF_SEL2);//2 PA8,PA7,PA6,PA5,PA4,RX,TX,TIM0_CH0, MCO
    //rcc_clkout_config(RCC_CLKOUT_SEL_HFO,RCC_CLKOUT_PDIV_2);

    //ptr_config.gpio_mode = GPIO_MODE_OUTPUT_PP;                                   //推挽输出模式
    //ptr_config.gpio_pull = GPIO_PULL_DOWN;
    //ptr_config.gpio_pin = GPIO_PIN_1 ;
    //gpio_init(&ptr_config);
    //gpio_mf_config(GPIO_PIN_NUM1, GPIO_MF_SEL1);
}

//    bms_bitregister_init();

/**
  * @fn  void user_app_init(void)
  * @brief  app init
  * @param
  * @return None
  */
void user_app_init(void)
{
    modules_init();
   

    //interrupt_status_init();         //
}




