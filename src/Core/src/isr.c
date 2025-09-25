/**************************************************************************//**
 * @file     isr.c
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    中断模块
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

// Include header file.
#include "isr.h"
#include "modules_init.h"
#include "modules_pmu.h"
#include "standard_data_cmd.h"

#ifdef _RTE_
#include "RTE_Components.h"             /*!< Component selection */
#endif


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**@brief  This function handles NMI exception.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return 	None.
 */
void NMI_Handler(void)
{
}

/**@brief  This function handles Hard Fault exception.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return 	None.
 */
void HardFault_Handler(void)
{
    /*!< Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**@brief  This function handles SVCall exception.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return 	None.
 */
#ifndef RTE_CMSIS_RTOS2_RTX5
void SVC_Handler(void)
{
}
#endif

/**@brief  This function handles PendSVC exception.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return 	None.
 */
#ifndef RTE_CMSIS_RTOS2_RTX5
void PendSV_Handler(void)
{
}
#endif

/**@brief  This function handles SysTick Handler.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return 	None.
 */

void SysTick_Handler(void)
{

}

//TMR1_IRQHandler
void TMR1_IRQHandler(void)
{
    app_task_isr_process();
}

//WDT_IRQHandler
void WDT_IRQHandler(void)
{


}

//CC_IRQHandler
void CC_IRQHandler(void)
{
    if (cc_intetrrupt_status_get(CC_INTR_CCIF))
    {
        cc_intetrrupt_flag_clear(CC_INTR_CCIF);
        //modules_cc_isr_process(); 
    }
}

//VADC_IRQHandler
void VADC_IRQHandler(void)
{
    if(vadc_intetrrupt_status_get(VADC_INTR_VADCIF) == SET)
    {
        vadc_intetrrupt_flag_clear(VADC_INTR_VADCIF);
        //modules_vbat_isr_process();
    }
}

uint8_t  protocol_type = 1; //0-customer, 1-Chipsea

//I2C中断
void I2C_IRQHandler(void)
{
    pmu_sleep_timeout = 20;
    fw_pmu_set_run_mode(PMU_ACTIVE_MODE);
    
    if(protocol_type == 0){//other
        //customer iic process
    }else{  //CS
        iic_isr_process();
    }
}

void PA_IRQHandler(void)
{
    volatile uint32_t * scb = (volatile uint32_t *)0xE000Ed10;
    volatile uint32_t * i2c_isr = (volatile uint32_t *)0x40005418;
    volatile uint32_t * isrc = (uint32_t*)0x50004020;
    *scb &= ~SCB_SCR_SLEEPDEEP_Msk; 
    address_gpio_disable_irq();  //关闭SDA和SCL同时  ligx adjust at 2022.12.06
//    gpio_disable_irq();

    if(((*isrc) & 0x4) == 1)  //SDA和SCL同时可以作为触发条件
    {   
        if(((* i2c_isr ) & 0x00008000) != 0x00008000)
        {
//          i2c_restart();
          i2c_def_init();
          app_iic_init();
//          i2c_init_ext();
        }
    }
}

//void WK_IRQHandler()
//{
//    if(pmu_sleep_wakeup_status_get(PMU_DEEP_SLEEP_MODE2))
//    {
//        pmu_sleep_wakeup_status_clear(PMU_DEEP_SLEEP_MODE2);
//        if((gpio_interrupt_status_get(GPIO_PIN_3)||gpio_interrupt_status_get(GPIO_PIN_2)))
//        {
//            if(i2c_flag_status_get(I2C_ISR_BUSY) == 0)
//            {
//                i2c_restart();
//            }
//        }
//        gpio_disable_irq();
//    }
//}
