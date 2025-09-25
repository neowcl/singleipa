/***************************************************************************//**
 * @file     app_inc.h
 * @version  V1.0.0
 * @author   sz414
 * @date     2022-08-09 PM
 * @brief    APP层内部的头文件
 *
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

#ifndef __APP_INC_H__
#define __APP_INC_H__

#ifdef __UVISION_VERSION
#else
#endif

// 固件和硬件版本.
//#define VER_FIRMWARE        0x1234
//#define VER_HARDWARE        0x5678


// 非法或无效的字符
#define INVALID_BYTE        0xff
#define PENDING_STATE_BYTE  0xfe

// 错误码定义.
typedef enum {
    E_OK                = 0,
    E_NOTHING           = 1,
    E_VALUE_INVALID     = 2,  //寄存器是无效的
    E_NO_PERMISSION     = 3,  //无权限
    E_SEALED_MODE       = 4,  //SEALED模式中.
    E_OUTOFMEM          = 5,  //超出Memory的范围
    E_UNSUPPORT         = 6,  //不支持的功能
    E_PARAM             = 7,  //参数错误
    E_CHECKSUM          = 8,  //校验和错误
    E_FAIL              = 255,  //Register operation failed
} error_t;

// 权限码定义.
typedef enum {
    PRIVILTY_NONE       = 0,
    PRIVILTY_DATASHEET  = 1,  //DATA SHEET区访问
    PRIVILTY_CODE       = 2,  //CODE区访问
} privilty_code_t;


#include "main_interface.h"
#include "app_interface.h"

#include "data_flash.h"
#include "modules_reg.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#pragma pack(push,8)

#pragma pack(pop)

// API of app_reg_cmd_handle.

extern void timer_reg_command(void);


// API of app_debug_mode.
void handle_debug_mode(uint8_t * data);
//void handle_authen_mode(uint8_t data_type);


// API of slave_io_handle.

// Slave io state.
#define SLAVE_IO_STATE_PENDING		0x01
#define SLAVE_IO_STATE_DEBUGMODE	0x02

#define SLAVE_IO_STATE_ALT_MANU	    0x04
#define SLAVE_IO_STATE_MACDATA	    0x08
#define SLAVE_IO_STATE_MACDATAH	    0x10
#define SLAVE_IO_STATE_CSUM	        0x20


extern uint8_t get_slave_io_state(void);
extern void set_slave_io_state(uint8_t removed, uint8_t added);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__APP_INC_H__
