/***************************************************************************//**
 * @file     i2c_coms.h
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    I2C模块头文件
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 ****************************************************************************/

#ifndef __COMM_PROTOCOL_H__
#define __COMM_PROTOCOL_H__
#include"stdint.h"
#include "app_inc.h"

#define SYNC_CODE                0xEE
#define CONNECTED_CMD            0x50
#define READ_INFO_CMD            0x51
#define AUTHEN_CMD               0x52
#define JUMP_CMD                 0x53
#define WRITE_PARAM_CMD          0x55
#define UNLOCK_PARAM_CMD         0x56
#define READ_DATA_MEMORY_CMD     0x57
#define WRITE_DATA_MEMORY_CMD    0x58

#define DISCONNECT_CMD           0x5A

#define WRITE_REGISTER_CMD       0x5B
#define READ_REGISTER_CMD        0x5C

#define CAL_ENABLE_CMD           0x5D
#define CAL_WRITEVALUE_CMD       0x5E

#define READ_BLOCK_CMD           0x5F
#define WRITE_BLOCK_CMD          0x60


#define JUMP_EVENT        0x01

typedef enum
{
    RET_OK = 0,
    RET_BUSY = 1,
    RET_FAIL = -1,
    RET_NO_CONNECT = -2,
    RET_NO_HANDSHAKE = -3,
    RET_CHECK_ERROR = -4,
    RET_SECRET_KEY_ERROR = -5,
    RET_RANDOM_ERROR = -6,
    RET_FLASH_ERASE_FAIL = -7,
    RET_FLASH_WRITE_FAIL = -8,
    RET_FLASH_READ_FAIL = -9,
    RET_FW_HEAD_ERR = -10,
    RET_CRC32_ERR = -11,
    RET_UNSEAL_ERR = -12,
}cmd_result;

typedef struct
{
    uint8_t sync;
    uint8_t cmd;
    uint8_t len[2];
    uint8_t random;
    //uint8_t payload[COMM_PAYLOAD_MAX_SIZE];
    //uint8_t checksum;
}comm_rx_packet_t;

typedef struct
{
    uint8_t sync;
    uint8_t cmd;
    uint8_t len[2];
    uint8_t errcode;
    uint8_t random[2];
    //uint8_t payload[COMM_PAYLOAD_MAX_SIZE];
    //uint8_t checksum;
}comm_tx_packet_t;

uint8_t get_new_random(uint8_t last_random);
uint8_t cal_crc8_check( unsigned char *data, unsigned char len);
int8_t check_rx_data_packet(uint8_t *input_data);
void filled_connected_cmd(uint8_t *data);

int8_t parse_rx_data_packet(uint8_t *input_data);
void tx_err_code_packet(uint8_t *data, uint8_t err_code);

void run_task_event(void);
void set_task_event(uint8_t event);

#endif 

/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
