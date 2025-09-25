/**************************************************************************//**
 * @file     main.c
 * @version  V0.2.0
 * @author   
 * @date     2022-07-29 AM
 * @brief
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

#include "main.h"
#include "modules_init.h"
#include "modules_pmu.h"

#include "comm_protocol.h"
#include "data_flash.h"
#include "user_config.h"
#include "bms_register_inc.h"
#include "bi2cs_interface.h"
#include "standard_data_cmd.h"
#include "base_types.h"
#include "bi2cs_interface.h"
#include "Cell.h"
#include "Ram.h"
#include "Cell.h"


#if UPDATE_FLAG_ENABLE
const uint32_t FW_REVS[4] __attribute__((used)) __attribute__((section(".ARM.__at_0x00000110"))) = {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF};
//const uint32_t FW_UPDATE_FLAG __attribute__((used)) __attribute__((section(".ARM.__at_0x00000110"))) = 0xA55AC33C;
#endif
const uint32_t FW_BIN_VER __attribute__((used)) __attribute__((section(".ARM.__at_0x00000100"))) = FW_VERSION;
const uint32_t DEVICE_TYPE __attribute__((used)) __attribute__((section(".ARM.__at_0x00000620"))) = 0x58353658;//devices

const uint32_t Long_BIN_VER __attribute__((used)) __attribute__((section(".ARM.__at_0x0000EFF0"))) = 0xFFFF;
//block_delay_ms(1000);

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    user_app_init();        // 硬件和数据初始化
    app_init();             // 调用APP层的初始化.
    while(1)
    {
        clear_dog();        // iwdg feed 
        IIC_timeout_process(); // IIC忙超时判断
        app_handle_task();  // 交给APP层进行任务处理
        app_task_loop();    // AFE采集和算法处理
       
    }
}
