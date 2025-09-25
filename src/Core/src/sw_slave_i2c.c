// \brief
//	software simulation I2C slave device
//
// \version
// v1.1: 2022.11.05, Initial version.
// v1.2: 2022.11.07, 中断函数改用寄存器操作，55K速率测试通过
///////////////////////////////////////////////////////////////////////////////

#include "sw_slave_i2c.h"

#define USE_SWD_IIC               0    //是否使用SWD口作为模拟IIC接口

#define I2C_STA_IDLE			    0
#define I2C_STA_START			1
#define I2C_STA_DATA			    2
#define I2C_STA_ACK				3
#define I2C_STA_NACK			    4
#define I2C_STA_STOP			5

#define I2C_READ				        1
#define I2C_WRITE				    0

#define GPIO_DIR_IN				GPIO_MODE_INPUT
#define GPIO_DIR_OUT		GPIO_MODE_OUTPUT_OD

#define SET_SDA_PIN()			(SW_SLAVE_SDA_PRT->DOUT |= SW_SLAVE_SDA_PIN)
#define CLR_SDA_PIN()			(SW_SLAVE_SDA_PRT->DOUT &= ~SW_SLAVE_SDA_PIN)

#if USE_SWD_IIC
    #define SCL_PIN_NUM       GPIO_PIN_NUM0
    #define SDA_PIN_NUM        GPIO_PIN_NUM1

    #define SW_SLAVE_SCL_PRT		GPIOA
    #define SW_SLAVE_SCL_PIN		GPIO_PIN_0

    #define SW_SLAVE_SDA_PRT	GPIOA
    #define SW_SLAVE_SDA_PIN		GPIO_PIN_1
#else
    #define SCL_PIN_NUM       GPIO_PIN_NUM3
    #define SDA_PIN_NUM        GPIO_PIN_NUM2

    #define SW_SLAVE_SCL_PRT		GPIOA
    #define SW_SLAVE_SCL_PIN		GPIO_PIN_3

    #define SW_SLAVE_SDA_PRT	GPIOA
    #define SW_SLAVE_SDA_PIN		GPIO_PIN_2
#endif

volatile uint8_t RxDataBuf[56]={0};
volatile uint8_t TxDataBuf[56]={0x55,0x11,0x22,0x33,0x44};

SwSlaveI2C_t SwSlaveI2C =
{
    I2C_STA_IDLE,		// State
    I2C_WRITE,			// Rw
    0, 					// SclFallCnt
    0,					// Flag
    0,					// StartMs
    RxDataBuf,			// RxBuf
    TxDataBuf,			// TxBuf
    0,					// RxIdx
    0					// TxIdx
};

uint32_t SET_sda_dir_first =  ~((GPIO_PMD_PMD0) << ((uint32_t)SDA_PIN_NUM * 2));
uint32_t SET_sda_dir_second_out =  (uint32_t)(((uint32_t)GPIO_DIR_OUT) << ((uint32_t)SDA_PIN_NUM * 2));
uint32_t SET_sda_dir_second_in =  (uint32_t)(((uint32_t)GPIO_DIR_IN) << ((uint32_t)SDA_PIN_NUM * 2));

#define SET_SDA_OUT()     \
            SW_SLAVE_SDA_PRT->PMD &= SET_sda_dir_first;         \
            SW_SLAVE_SDA_PRT->PMD |= SET_sda_dir_second_out;

#define SET_SDA_IN()     \
            SW_SLAVE_SDA_PRT->PMD &= SET_sda_dir_first;         \
            SW_SLAVE_SDA_PRT->PMD |= SET_sda_dir_second_in;

#if USE_SWD_IIC
    #define GPIO_multi_function GPIO_MF_SEL1        /*!< PA8,PA7,PA6,PA5,PA4,SCL,SDA,PA1,PA0 */
#else
    #define GPIO_multi_function GPIO_MF_SEL0      /*!< PA8,PA7,PA6,PA5,PA4,PA3,PA2,SWDIO,SWCLK */
#endif

void (*SW_IIC_CallBack)(void);//IIC回调函数，在stop信号之后调用

//新的gpio中断初始化函数，同时开启上升沿和下降沿中断
void new_gpio_interrupt_init(gpio_interrupt_config_t* ptr_config)
{
    uint32_t pin = 0x00;
    uint32_t pos = 0x00;
    uint32_t current_pin = 0x00;
    
    ASSERT(GPIO_PIN_CHECK(ptr_config->gpio_pin));
    ASSERT(GPIO_INT_MODE_CHECK(ptr_config->gpio_int_mode));
    ASSERT(GPIO_INT_TRI_CHECK(ptr_config->gpio_int_tri));
    ASSERT(FUNCTIONAL_STATE_CHECK(ptr_config->int_enable));
    
    for (pin = 0x00; pin < 0x08; pin++)
    {
        pos = ((uint32_t)0x01) << pin;

        current_pin = (ptr_config->gpio_pin) & pos;     /*!< Get the port pins position */

        if (current_pin == pos)
        {
            GPIOA->IMD &= (uint32_t)~((uint32_t)GPIO_IMD_IMD0 << ((uint16_t)pin));
            GPIOA->IMD |= (ptr_config->gpio_int_mode << ((uint16_t)pin));
            
            if (ptr_config->int_enable != DISABLE)
            {
                GPIOA->ISRC |= (uint32_t)ptr_config->gpio_pin;
                #if 1
                GPIOA->IER |= ((GPIO_IER_RIER0 << ((uint16_t)pin)));
                GPIOA->IER |= (GPIO_IER_FIER0 << ((uint16_t)pin));
                #else
                if (ptr_config->gpio_int_tri == GPIO_INTMODE_HIGH_OR_RISING)
                {
                    GPIOA->IER |= ((GPIO_IER_RIER0 << ((uint16_t)pin)));
                }
                else 
                {
                    GPIOA->IER |= (GPIO_IER_FIER0 << ((uint16_t)pin));
                }
                #endif
            }
            else
            {
                if (ptr_config->gpio_int_tri == GPIO_INTMODE_HIGH_OR_RISING)
                {
                    GPIOA->IER &= (uint32_t)~(GPIO_IER_RIER0 << ((uint16_t)pin));
                }
                else 
                {
                    GPIOA->IER &=  (uint32_t)~(GPIO_IER_FIER0 << ((uint16_t)pin));
                }
            }
        }
    }
}

/**
  * @brief  Configures slave I2C GPIO pin in interrupt mode
  * @param  None
  * @retval None
  */
void InitSwSlaveI2C(void)
{
    gpio_config_t ptr_config;
    gpio_interrupt_config_t init_config;
    nvic_config_t nvic_config_struct;
    
    //SDA
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_GPIOA, ENABLE);
    ptr_config.gpio_mode = GPIO_MODE_INPUT;

    ptr_config.gpio_pull = GPIO_PULL_NO_PULL;
    ptr_config.gpio_pin = SW_SLAVE_SDA_PIN;
    gpio_init(&ptr_config);
    gpio_mf_config(SDA_PIN_NUM, GPIO_multi_function);
    
    init_config.gpio_int_mode = GPIO_INTMODE_EDGE;
    init_config.gpio_int_tri = GPIO_INTMODE_HIGH_OR_RISING;
    init_config.gpio_pin = SW_SLAVE_SDA_PIN;
    init_config.int_enable = ENABLE;
    new_gpio_interrupt_init(&init_config);
    
    nvic_config_struct.nvic_IRQ_channel = IRQn_PA ;
    nvic_config_struct.nvic_channel_priority = 0x01;
    nvic_config_struct.nvic_enable_flag = ENABLE;
    nvic_init(&nvic_config_struct);
    //SCL
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_GPIOA, ENABLE);
    ptr_config.gpio_mode = GPIO_MODE_INPUT;

    ptr_config.gpio_pull = GPIO_PULL_NO_PULL;
    ptr_config.gpio_pin = SW_SLAVE_SCL_PIN;
    gpio_init(&ptr_config);
    gpio_mf_config(SCL_PIN_NUM, GPIO_multi_function);
    
    init_config.gpio_int_mode = GPIO_INTMODE_EDGE;
    init_config.gpio_int_tri = GPIO_INTMODE_HIGH_OR_RISING;
    init_config.gpio_pin = SW_SLAVE_SCL_PIN;
    init_config.int_enable = ENABLE;
    new_gpio_interrupt_init(&init_config);
    
    nvic_config_struct.nvic_IRQ_channel = IRQn_PA ;
    nvic_config_struct.nvic_channel_priority = 0x01;
    nvic_config_struct.nvic_enable_flag = ENABLE;
    nvic_init(&nvic_config_struct);
}

/**
  * @brief EXTI line interruption service
  * @param None
  * @retval None
  */
void PA_IRQHandler(void)
{
    // 处理SCL的上下沿中断
    if ((GPIOA->ISRC & SW_SLAVE_SCL_PIN) != RESET)
    {
        GPIOA->ISRC |= SW_SLAVE_SCL_PIN;
        // 更新通信起始时间
        //todo:SwSlaveI2C.StartMs = HAL_GetTick();
        // SCL的下降沿事件处理，此时需要更新要传输的数据
        if ((SW_SLAVE_SCL_PRT->PIN & SW_SLAVE_SCL_PIN) == BIT_RESET)
        {
            switch (SwSlaveI2C.State)
            {
                case I2C_STA_START:		// 起始信号的下降沿，初始化相关参数并转到接收比特数据状态
                    SwSlaveI2C.SclFallCnt = 0;
                    SwSlaveI2C.RxIdx = 0;
                    SwSlaveI2C.TxIdx = 0;
                    SwSlaveI2C.Flag = 0;	// 默认地址不匹配
                    SwSlaveI2C.RxBuf[SwSlaveI2C.RxIdx] = 0;
                    SwSlaveI2C.Rw = I2C_WRITE;	// 第1字节为设备地址，一定是写入
                    SwSlaveI2C.State = I2C_STA_DATA;
                    break;
                case I2C_STA_DATA:
                    SwSlaveI2C.SclFallCnt++;
                    if (8 > SwSlaveI2C.SclFallCnt)
                    {
                        // 如果是主机读取数据，则在SCL低电平时更新比特数据
                        if (SwSlaveI2C.Rw == I2C_READ)
                        {
                            if (SwSlaveI2C.TxBuf[SwSlaveI2C.TxIdx] & (1 << (7 - SwSlaveI2C.SclFallCnt)))
                            {
                                SET_SDA_PIN();
                            }
                            else
                            {
                                CLR_SDA_PIN();
                            }
                        }
                    }
                    else if (8 == SwSlaveI2C.SclFallCnt)
                    {
                        if (SwSlaveI2C.Rw == I2C_WRITE)
                        {
                            // 从第一个地址字节中获取读写标志位，并判断地址是否匹配
                            if (SwSlaveI2C.RxIdx == 0)
                            {
                                if ((SwSlaveI2C.RxBuf[0] & 0xFE) == SW_SLAVE_ADDR)
                                {
                                    SwSlaveI2C.Flag = 1;	// 地址匹配                                    
                                    SwSlaveI2C.Rw = SwSlaveI2C.RxBuf[0] & 0x01;
                                }
                            }
                            if (SwSlaveI2C.Flag)
                            {
                                // 如果是主机写入数据，且地址匹配，则接收完8比特数据后，需要发送ACK信号进行应答                                                            
                                SET_SDA_OUT();
                            }
                        }
                        else
                        {
                            // 如果是主机读取数据，需要将SDA设置成输入以便判断应答标志位状态
                            SET_SDA_IN();
                            // 如果是主机读取数据，准备发送下一个字节的数据
                            SwSlaveI2C.TxIdx++;
                        }
                        // 接收或发送完8比特数据后，准备发送或接收应答信号
                        SwSlaveI2C.State = I2C_STA_ACK;
                    }
                    break;
                case I2C_STA_ACK:
                    SwSlaveI2C.SclFallCnt = 0;
                    if (SwSlaveI2C.Rw == I2C_WRITE)
                    {
                        // 如果是主机写入数据，且ACK发送完毕，则SDA设置成输入，继续接收数据
                        SET_SDA_IN();
                        SwSlaveI2C.RxIdx++;
                        SwSlaveI2C.RxBuf[SwSlaveI2C.RxIdx] = 0;                     
                    }
                    else
                    {
                        // 如果是主机读取数据，且ACK接收完毕，则SDA设置成输出，继续发送数据
                        SET_SDA_OUT();
                        if (SwSlaveI2C.TxBuf[SwSlaveI2C.TxIdx] & 0x80)
                        {
                            SET_SDA_PIN();
                        }
                        else
                        {
                            CLR_SDA_PIN();
                        }
                    }
                    SwSlaveI2C.State = I2C_STA_DATA;
                    break;
                case I2C_STA_NACK:		// 如果收到了NACK，则后面将是STOP或者ReSTART信号，需要将SDA设置成输入
                    SwSlaveI2C.SclFallCnt = 0;
                    SET_SDA_IN();
                    break;
            }
        }
        // SCL的上升沿事件处理，此时需要采集数据，而且在数据阶段，SCL高电平时数据必须保持不变
        else
        {
            switch (SwSlaveI2C.State)
            {
                case I2C_STA_DATA:	// 数据阶段，如果是主机写入数据，则采集比特数据
                    if ((I2C_WRITE == SwSlaveI2C.Rw) && (8 > SwSlaveI2C.SclFallCnt))
                    {
                        if (SW_SLAVE_SDA_PRT->PIN & SW_SLAVE_SDA_PIN)
                        {
                            SwSlaveI2C.RxBuf[SwSlaveI2C.RxIdx] |= (1 << (7 - SwSlaveI2C.SclFallCnt));
                        }
                    }
                    break;
                case I2C_STA_ACK:	// 应答阶段，如果是主机读取数据，则判断ACK/NACK信号，默认状态是ACK
                    if ((SwSlaveI2C.Rw == I2C_READ) && (SW_SLAVE_SDA_PRT->PIN & SW_SLAVE_SDA_PIN))
                    {
                        SwSlaveI2C.State = I2C_STA_NACK;
                    }
                    break;
            }
        }
    }
    else if ((GPIOA->ISRC & SW_SLAVE_SDA_PIN) != RESET)
    {
        GPIOA->ISRC |= SW_SLAVE_SDA_PIN;
        if ((SW_SLAVE_SDA_PRT->PIN & SW_SLAVE_SDA_PIN) == BIT_RESET)
        {
            // SCL为高电平时，SDA从高变低，说明是起始信号
            if (SW_SLAVE_SCL_PRT->PIN & SW_SLAVE_SCL_PIN)
            {
                SwSlaveI2C.State = I2C_STA_START;
            }
        }
        else
        {
            // SCL为高电平时，SDA从低变高，说明是停止信号，一次I2C通信结束，直接将状态设置成空闲
            if (SW_SLAVE_SCL_PRT->PIN & SW_SLAVE_SCL_PIN)
            {
                SwSlaveI2C.State = I2C_STA_IDLE;
                //通信结束，通知用户进行操作
                SW_IIC_CallBack();
            }
        }
    }
}


//void CheckSwSlaveI2cTimeout(void)
//{
//	uint32_t TimeMs, TimeCurMs;

//	if(SwSlaveI2C.State != I2C_STA_IDLE)
//	{
//		//todo:TimeCurMs = HAL_GetTick();
//		if(TimeCurMs >= SwSlaveI2C.StartMs)
//		{
//			TimeMs = TimeCurMs - SwSlaveI2C.StartMs;
//		}
//		else
//		{
//			TimeMs = ~(SwSlaveI2C.StartMs - TimeCurMs) + 1;
//		}
//		if(500 <= TimeMs)
//		{
//			// I2C通信超时的话，重置状态机，并把SDA设置成输入
//			SwSlaveI2C.State = I2C_STA_IDLE;
//			//todo:SET_SDA_DIR(TimeMs, GPIO_DIR_IN);
//		}
//	}
//}

