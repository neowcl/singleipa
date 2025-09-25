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
#include "modules_pmu.h"
#include "bms_register_inc.h"
#include "comm_protocol.h"
#include "user_config.h"
#include "task.h"
#include "block_command.h"
#include "bit_register.h"
/**         
  * @brief  power up init 
  * @param  None
  * @retval None
  */

#define COMMAND_ID_NUM    11

//const uint8_t unseal_password[4] = UNSEAL_PASSWORD;
//const uint8_t full_unseal_password[4] = FULL_UNSEAL_PASSWORD;

extern uint8_t rcv_random ;
extern uint8_t new_random ;

sys_seal_t sys_seal_type = SYS_SEALED;


uint8_t read_DeviceType_fun( uint8_t *data);
uint8_t read_FirmwareVersion_fun(uint8_t *data);

uint8_t read_ChemID_fun(uint8_t *data);
uint8_t write_unseal_fun(uint8_t *data);
uint8_t write_full_unseal_fun(uint8_t *data);

uint8_t write_Reset_sys_fun(uint8_t *data);
uint8_t write_life_time_enable_fun(uint8_t *data);
uint8_t write_life_time_flush_fun(uint8_t *data);
uint8_t write_calibration_enable_fun(uint8_t *data);

uint8_t read_serial_number(uint8_t *data);
uint8_t write_SealDevice_fun(uint8_t *data);

/***********************
*不同ID号对应的操作函数和属性
*************************/
const command_id_t command_id_fun[COMMAND_ID_NUM] = {
    {0x0001, READ_ONLY, read_DeviceType_fun},      //01 R Device Type
    {0x0002, READ_ONLY, read_FirmwareVersion_fun}, //02 R Firmware version
    {0x0003, READ_ONLY, read_ChemID_fun},          //03 R Chemical Id

    {0x0004, WRITE_ONLY, write_unseal_fun},        //04 W Unseal
    {0x0005, WRITE_ONLY, write_full_unseal_fun},   //05 W Full Unseal

    {0x0006, WRITE_ONLY, write_Reset_sys_fun},          //06 W Full Reset
    {0x0007, WRITE_ONLY, write_life_time_enable_fun},   //07 W Lifetime EN

    {0x0008, WRITE_ONLY, write_life_time_flush_fun},    //08 W LT flush -
    {0x0009, WRITE_ONLY, write_calibration_enable_fun}, //09 W Calibration EN
    {0x000A, READ_ONLY,  read_serial_number},     //0A R Serial Number -
    {0x000B, WRITE_ONLY, write_SealDevice_fun},   //0B W Seal
} ;

/**
  * @brief  获取加密状态
  * @param  None
  * @retval None
  */
uint8_t get_sys_seal_type(void)
{
    #if SEAL_ENABLE
        return  sys_seal_type;
    #else
        return  SYS_FULL_ACCESS;
    #endif 
}

void set_sys_seal_type(sys_seal_t val)
{
    sys_seal_type = val;
}


/**
  * @brief  read_command_id_handle
  * @param  None
  * @retval None
  */
void read_command_id_handle(uint8_t *data)
{
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;
    volatile uint8_t i;
    int8_t  err_code = 0;

    volatile uint8_t data_len = 0;
    volatile uint8_t tx_data_len  = 0;
    volatile uint16_t command_id = 0;
    volatile uint8_t command_id_LSB = 0;

    data_len = *(data + 2); // get len
    if(data_len < 2){
        err_code = RET_FAIL;
    }
    pdata =  data + 5;      // data
    if(*pdata != 0x3E) {
        err_code = RET_FAIL;
    };
    pdata++;
    command_id_LSB = *pdata;
    pdata++;
    command_id = *pdata;
    command_id = (command_id<<8) + command_id_LSB;

    pdata =  data + 7;
    *pdata = command_id&0xFF; pdata++;
    *pdata = (command_id>>8)&0xFF; pdata++;  //Tag command id

     pdata++; 
    for(i = 0; i < COMMAND_ID_NUM; i++){     //V
        if(command_id_fun[i].id == command_id){
            tx_data_len = command_id_fun[i].command_fun(pdata);
            break;
        }
    }
    if(tx_data_len >= 250){//长度大于250 错误
        tx_data_len = 0;
        err_code = RET_FAIL;
    }

    pdata =  data + 9; //Len
    *pdata = tx_data_len;

    tx_packet =  (comm_tx_packet_t*)data;
    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd = READ_BLOCK_CMD + 0x80;
    tx_packet->len[0]  = 4 + tx_data_len + 3; //T(2)+L(1)
    tx_packet->len[1]  = 0;
    tx_packet->errcode = RET_OK;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;

    pdata =  data + tx_packet->len[0] + 3;
    *pdata = cal_crc8_check(data, tx_packet->len[0]+3);
}

/**
  * @brief  command_id_handle
  * @param  None
  * @retval None
  */
 void write_command_id_handle(uint8_t *data)
 {
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;
    volatile uint8_t i;
    int8_t  err_code = 0;

    volatile uint8_t data_len = 0;

    volatile uint16_t command_id = 0;
    volatile uint8_t command_id_LSB = 0;

    data_len = *(data + 2); // get len
    if(data_len < 2){
        err_code = RET_FAIL;
    }
    //[5] tag-->0x3E
    pdata =  data + 6;      //[6] command id
    command_id_LSB = *pdata;
    pdata++;
    command_id = *pdata;
    command_id = (command_id<<8) + command_id_LSB;
    pdata++;
    for(i = 0; i < COMMAND_ID_NUM; i++){
        if(command_id_fun[i].id == command_id){
            data_len = command_id_fun[i].command_fun(pdata);
            break;
        }
    }
    if(i >= COMMAND_ID_NUM){//没有找到ID错误
        err_code = RET_FAIL;
    }
    if(data_len >= 250){    //长度大于250 错误
        data_len = 0;
        err_code = RET_FAIL;
    }
    /********response********/
    tx_packet =  (comm_tx_packet_t*)data;
    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd = WRITE_BLOCK_CMD + 0x80;
    tx_packet->len[0]  = 4 + 1;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = (err_code >= 0)? RET_OK:RET_FAIL;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;
    pdata =  data + 7;
    *pdata = 0x01; //ACK

    pdata =  data + tx_packet->len[0] + 3;
    *pdata = cal_crc8_check(data, tx_packet->len[0]+3);
 }

/**
  * @brief  DeviceType
  * @param  None
  * @retval None
  */
uint8_t read_DeviceType_fun(uint8_t *data)
{
    *data = 'C'; data++;
    *data = 'B'; data++;
    *data = 'M'; data++;
    *data = 'X'; data++;
    *data = '5'; data++;
    *data = '6'; data++;
    *data = 'X'; data++;
    return 7;
}

/**
  * @brief  FirmwareVersion
  * @param  None
  * @retval None
  */
uint8_t read_FirmwareVersion_fun(uint8_t *data)
{
    *data = FW_VERSION & 0xFF; data++;
    *data = (uint8_t)(FW_VERSION >> 8); data++;
    *data = (uint8_t)(FW_VERSION >> 16); data++;
    return 3;
}

/**
  * @brief  HardwareVersion
  * @param  None
  * @retval None
  */
uint8_t read_HardwareVersion_fun(uint8_t *data)
{
    *data = HW_VERSION & 0xFF; data++;
    *data = HW_VERSION >> 8; data++;
    return 2;
}

/**
  * @brief  ChemID
  * @param  None
  * @retval None
  */
uint8_t read_ChemID_fun(uint8_t *data)
{
    *data = 0x01; data++;
    *data = 0x00; data++;
    *data = 0x00; data++;
    *data = 0x00; data++;
    return 4;
}

/**
  * @brief  unseal_fun
  * @param  None
  * @retval 0-ok
  */
uint8_t write_unseal_fun(uint8_t *data)
{
    uint8_t ret = 0xFF;
    
    return ret;
}

/**
  * @brief  write_full_unseal_fun
  * @param  None
  * @retval 0-ok
  */
uint8_t write_full_unseal_fun(uint8_t *data)
{
    uint8_t ret = 0xFF;
    
    return ret;
}

uint8_t write_Reset_sys_fun(uint8_t *data)
{
    //reset system
    set_task_event(JUMP_EVENT);
    return 0;
}

uint8_t write_life_time_enable_fun(uint8_t *data)
{
    //ManufacturingStatus_LF_EN_bit_reg(1);
    uint8_t bit_val;
    if(get_sys_seal_type() != SYS_SEALED){ //解锁状态
        //bit_val = read_ManufacturingStatus_LF_EN_bit_reg();
        //ManufacturingStatus_LF_EN_bit_reg(!bit_val);
    }
    return 0;
}

uint8_t write_life_time_flush_fun(uint8_t *data)
{

    
    return 0;
}

uint8_t write_calibration_enable_fun(uint8_t *data)
{
    //ManufacturingStatus_CAL_EN_bit_reg(1);
    //setManufacturingStatus_CAL_EN(1);
    uint8_t CAL_EN_bit_val;
    if(get_sys_seal_type() != SYS_SEALED){ //解锁状态
       // CAL_EN_bit_val = read_ManufacturingStatus_CAL_EN_bit_reg();
       // ManufacturingStatus_CAL_EN_bit_reg(!CAL_EN_bit_val);
    }
    return 0;
}

uint8_t read_serial_number(uint8_t *data)
{
    *data = 0x01; data++;
    *data = 0x02; data++;
    *data = 0x03; data++;
    *data = 0x04; data++;
    return 4;
}

uint8_t write_SealDevice_fun(uint8_t *data)
{
    uint8_t buf[4] = {0x55,0xFF,0xFF,0xFF};
   
    return 0;
}
