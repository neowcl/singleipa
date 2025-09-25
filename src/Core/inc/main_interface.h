/***************************************************************************
 * @file     main_interface.h
 * @version  V1.0.0
 * @author   sz414
 * @date     2022-06-13 PM
 * @brief    该文件包含Core层导出的接口声明
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 ****************************************************************************/


#ifndef __MAIN_INTERFACE_H__
#define __MAIN_INTERFACE_H__

// Include external header file.
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
#define _CSX_CALL	__cdecl
#else
#define _CSX_CALL	
#endif /* __cplusplus */

#ifndef __STDINT_DECLS
/*
数据类型重定义，如果外部已经定义了这些类型，请在包含csx_datapack.h头文件前，
先#define CS_DATATYPE_DECL
*/
#ifndef CS_DATATYPE_DECL
#define CS_DATATYPE_DECL
	typedef char int8_t;
	typedef unsigned char uint8_t;
	typedef uint8_t byte;
	typedef short int16_t;
	typedef unsigned short uint16_t;
	typedef int int32_t;
	typedef unsigned int uint32_t;
#ifdef CSX_SUPPORT_INT64
	typedef long long int64_t;
	typedef unsigned long long uint64_t;
#endif
#endif //CS_DATATYPE_DECL
#endif

#include "main_diagnostic.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void os_sleep(uint16_t millisecond);
extern void os_i2c_data_send(uint8_t data);
extern int os_read_flash(uint16_t addr, uint8_t* data, uint16_t len);
extern int os_write_flash(uint16_t addr, const uint8_t* data, uint16_t len);
extern void os_enable_interrupt(bool enable);
extern void os_reset_system(void);

/* voltage unit mV */
int16_t get_voltage(void);

/* current unit mA */
int16_t get_current(void);

/* average current unit mA */
int16_t get_average_current(void);

/* get chip temperature 0.1deg */
int16_t get_temperatureIn(void);

/* get NTC temperature 0.1deg */
int16_t get_temperatureEx(void);


int16_t get_high_speed_current(void);

#ifdef __cplusplus
}
#endif

#endif  //__MAIN_INTERFACE_H__


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
