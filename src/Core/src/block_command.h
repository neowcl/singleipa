/***************************************************************************//**
 * @file     main.h
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    main主程序头文件
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 ****************************************************************************
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/01/25  <td>1.0      <td>chensj0621  <td>创建初始版本
 * </table>
 *
 *****************************************************************************/


#ifndef __BLOCK_COMMAND_H__
#define __BLOCK_COMMAND_H__

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
    SYS_SEALED = 0,
    SYS_UNSEALED,
    SYS_FULL_ACCESS
}sys_seal_t;

extern sys_seal_t sys_seal_type;

void read_command_id_handle(uint8_t *data);
void write_command_id_handle(uint8_t *data);
uint8_t get_sys_seal_type(void);
void set_sys_seal_type(sys_seal_t val);

#ifdef __cplusplus
}
#endif

#endif


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
