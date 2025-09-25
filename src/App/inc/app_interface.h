/***************************************************************************//**
 * @file     app_interface.h
 * @version  V1.0.0
 * @author   sz414
 * @date     2022-06-13 PM
 * @brief    该文件声明了APP层导出的接口
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 ****************************************************************************
 * @attention
 *  硬件平台:  \n
 *  SDK版本： V0.9.0
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date        <th>Version  <th>Author    <th>Description
 * <tr><td>2022/06/10  <td>1.0      <td>SZ404  <td>创建初始版本
 * </table>
 *
 *****************************************************************************/

#ifndef __APP_INTERFACE_H__
#define __APP_INTERFACE_H__

#ifndef APP_VER
#define APP_VER		0x01
#endif
#define APP_NAME	"CSB22002-BMS"

#ifdef _WINDOWS
#define CS_DATATYPE_DECL
#endif

#ifdef __UVISION_VERSION
#define CS_DATATYPE_DECL
#define _CSX_CALL	
#include <stdbool.h>
#include <stdint.h>
#endif

//#include "stm32f0xx_hal.h"
#include <stdio.h>

#include "ic_config.h"  //Configure about IC.

// Include external header file.

#ifdef __cplusplus
extern "C" {
#endif

extern void app_init(void);
extern void app_handle_task(void);

typedef enum {
    ACCESS_NONE,
    ACCESS_READ,
    ACCESS_WRITE,
} access_mode_t;

typedef enum {
    SLAVE_IO_EVENT_START,
    SLAVE_IO_EVENT_DATA,
    SLAVE_IO_EVENT_TRANSMIT,
    SLAVE_IO_EVENT_STOP,
} slave_io_event_t;

// on_slave_io_event用于处理IO事件.
extern void on_slave_io_event(slave_io_event_t event, uint8_t data);


#ifdef __cplusplus
}
#endif

#endif  //__APP_INTERFACE_H__


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/


