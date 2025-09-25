/***************************************************************************//**
 * @file     protocol.c
 * @version  V1.0.0
 * @author
 * @date
 * @brief
 *
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

#include "main.h"
#include "comm_protocol.h"
#include "app_inc.h"
#include "main_interface.h"
#include "data_flash.h"
#include <string.h>
#include "bms_register_inc.h"
#include "block_command.h"
#include "calibration_handle.h"
#include "user_config.h"
//#include "cbmx56x_reg.h"

#define HMAC_SHA256_LENGTH             32

uint8_t rcv_random = 0;
uint8_t new_random = 0;

/**
  * @brief  cal_crc8_check
  * @param  input data
  * @retval crc8
  */
uint8_t cal_crc8_check(unsigned char *data, unsigned char len)
{
    uint8_t crc = 0;
    uint8_t i;

    while(len--){
        crc ^= *data++;
        for(i = 0; i < 8; i++){
            if(crc & 0x80){
                crc = (uint8_t)((crc << 1) ^ 0x07);
            }else{
                crc <<= 1;
            }
        }
    }
    return crc;
}

error_t set_reg_field_value(regtype_t regtype, regid_t regid, uint8_t index, uint32_t field_mask, uint32_t field_value)
{
	uint32_t value ;
	value &= ~field_mask;
	value |= field_value;
	return 0;
}

/**
  * @brief  get_new_random
  * @param  输入上一次的随机数
  * @retval 新随机数
  */
uint8_t get_new_random(uint8_t last_random)
{
    //srand(SYSTICK->CVR);
    //srand(TIM1->CNT);
    uint8_t ret;
//    srand(tim1_counter_get());
//    ret = (uint8_t)(rand()&0xFF);
    ret = get_sys_run_time();
    
    if(ret == last_random){
        ret += 1;
    }
    if(ret == 0){
        ret += 1;
    }
    return ret;
}

uint8_t task_event = 0;

/**
  * @brief  设置任务事件，用于debugmode接收完成操作
  * @param  事件值，按位计算
  * @retval none
  */
void set_task_event(uint8_t event)
{
    task_event |= event;
}

/**
  * @brief  check_rx_data_packet
  * @param  input data
  * @retval crc8
  */
int8_t check_rx_data_packet(uint8_t *input_data)
{
    uint8_t  cal_crc = 0;
    uint16_t packet_len;
    comm_rx_packet_t *rx_packet;

    if(input_data == NULL){
        return RET_FAIL;
    }
    rx_packet = (comm_rx_packet_t*) input_data;

    /*len check*/
    packet_len = rx_packet->len[1];
    packet_len =(packet_len << 8) + rx_packet->len[0] + 4;
    if(packet_len > (255-1)){
        return RET_FAIL;
    }

    /*crc check*/
    cal_crc = cal_crc8_check(input_data, packet_len-1);
    if(cal_crc != *(input_data+packet_len-1)){
        return RET_CHECK_ERROR;
    }

    /*random check*/
    rcv_random = rx_packet->random;
    if((rx_packet->cmd != CONNECTED_CMD)&&(rx_packet->cmd != READ_INFO_CMD)){
        if(rcv_random != new_random){
            return RET_RANDOM_ERROR;
        }
    }
    return RET_OK;
}

/**
  * @brief  read ap information
  * @param  input data
  * @retval crc8
  */
void filled_info_cmd(uint8_t *data)
{
    char sp_buf[50] = {0x00};

    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;

    if(data == NULL){
        return;
    }
    tx_packet =  (comm_tx_packet_t*)data;

    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd = READ_INFO_CMD + 0x80;
    tx_packet->len[0]  = 4 + 8;//
    tx_packet->len[1]  = 0;
    tx_packet->errcode = RET_OK;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;

    pdata =  data + 7;

    gcr_reg_unlock();
    flash_get_ChipUID_value((uint8_t*)sp_buf, 12);
    gcr_reg_lock();

    memcpy(pdata, sp_buf, 16);  //chip id
    pdata += 16;

    *pdata = 0x02; pdata++;//APP

    *pdata = (uint8_t)(FW_VERSION >> 16); pdata++;//ver H
    *pdata = (uint8_t)(FW_VERSION >> 8); pdata++;//ver M
    *pdata = FW_VERSION &0xFF; pdata++;//ver L
    
    *pdata = 52; pdata++;//app size L -->52k
    *pdata = 0; pdata++; //app size H
    *pdata = 8; pdata++; //param size

    tx_packet->len[0]  = 4 + 23;
    *pdata = cal_crc8_check(data, tx_packet->len[0]+3);
}

/**
  * @brief  connected_cmd
  * @param  input data
  * @retval crc8
  */
void filled_connected_cmd(uint8_t *data)
{
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;

    if(data == NULL){
        return;
    }
    tx_packet =  (comm_tx_packet_t*)data;

    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd = CONNECTED_CMD+0x80;
    tx_packet->len[0]  = 4+9;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = RET_OK;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;
    pdata =  data + 7;
    *pdata = 0x02 ; pdata++; //0x02 --> APP
    *pdata = 'C' ; pdata++;
    *pdata = 'B' ; pdata++;
    *pdata = 'M' ; pdata++;
    *pdata = 'X' ; pdata++;
    *pdata = '5' ; pdata++;
    *pdata = '6' ; pdata++;
    *pdata = 'X' ; pdata++;
    *pdata = 0 ; pdata++;
    *pdata = cal_crc8_check(data, tx_packet->len[0]+3);
}

/**
  * @brief  disconnected_cmd
  * @param  input data
  * @retval crc8
  */
void filled_disconnected_cmd(uint8_t *data)
{
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;
    if(data == NULL){
        return;
    }
    tx_packet = (comm_tx_packet_t*)data;

    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd = DISCONNECT_CMD+0x80;
    tx_packet->len[0]  = 4+0;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = RET_OK;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;
    pdata =  data+7;
    *pdata = cal_crc8_check(data, tx_packet->len[0]+3);
}

/**
  * @brief  Command handshake authentication .
  * @param  None
  * @return command execute result.
  */
int8_t cmd_handshake(uint8_t *input_data)
{
    /* the hamc sha256 key define User-provided key */
    uint8_t hmac_sha256_key[] = { 0xFF,0xFF,0x00,0x00,0xEE,0xEE,0x11,0x11,\
                                  0xDD,0XDD,0x22,0x22,0xCC,0xCC,0x33,0x33,\
                                  0xBB,0XBB,0X44,0X44,0XAA,0XAA,0X55,0X55,\
                                  0X99,0X99,0X88,0X88,0X66,0X66,0X77,0X77 };
    int8_t res = RET_OK;
    uint8_t  sha256_radombuff[HMAC_SHA256_LENGTH] = {0};
    uint8_t buf_calc_summary[HMAC_SHA256_LENGTH];

    if(input_data == NULL){
        return RET_FAIL;
    }

    memcpy(sha256_radombuff, &input_data[5], HMAC_SHA256_LENGTH);
    sha256_hmac_calc(&sha256_radombuff[0],
                    HMAC_SHA256_LENGTH,
                    &hmac_sha256_key[0],
                    sizeof(hmac_sha256_key),
                    &buf_calc_summary[0]);

    if(0 != memcmp(&input_data[5+32], &buf_calc_summary[0], HMAC_SHA256_LENGTH)){
        res = RET_FAIL;
    }
    return res;
}

/**
  * @brief  filled_authen_cmd.
  * @param  None
  * @return none.
  */
void filled_authen_cmd(uint8_t *data)
{
    int res;
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;

    if(data == NULL){
        return;
    }

    res = cmd_handshake(data);

    tx_packet = (comm_tx_packet_t*)data;

    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd = AUTHEN_CMD+0x80;
    tx_packet->len[0]  = 4+0;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = res;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;
    pdata =  data+7;
    *pdata = cal_crc8_check(data, tx_packet->len[0]+3);
}

/**
  * @brief  filled_write_block_cmd.
  * @param
  * @return none.
  */
void filled_write_block_cmd(uint8_t *data)
{
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;

    if(data == NULL){
        return;
    }
    tx_packet = (comm_tx_packet_t*)data;

    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd = WRITE_BLOCK_CMD + 0x80;
    tx_packet->len[0]  = 4+0;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = RET_OK;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;
    pdata =  data+7;
    *pdata = cal_crc8_check( data, tx_packet->len[0]+3);
}

/**
  * @brief  filled_read_block_cmd.
  * @param
  * @return none.
  */
void filled_read_block_cmd(uint8_t *data)
{
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;
    if(data == NULL){
        return;
    }
    tx_packet = (comm_tx_packet_t*)data;

    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd  = READ_BLOCK_CMD + 0x80;
    tx_packet->len[0]  = 4+0;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = RET_OK;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;
    pdata =  data+7;
    *pdata = cal_crc8_check( data, tx_packet->len[0]+3);
}

/**
  * @brief  校准使能.
  * @param
  * @return none.
  */
void filled_calibration_enable_cmd(uint8_t *data)
{
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;
    uint32_t cal_res = 0;
    if(data == NULL){
        return;
    }
    tx_packet = (comm_tx_packet_t*)data;
    //setManufacturingStatus_CAL_EN(*(data+5));  // 1开启校准使能   0关闭校准使能
    //cal_data._CalEn = *(data+5);
    //write_calibration_enable_flag(*(data+5));

    cal_res = *(data+6)+(*(data+7)<<8)+(*(data+8)<<16)+(*(data+9)<<24); //电阻值
    //cal_data._Reference_value_resistence = cal_res;

    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd  = CAL_ENABLE_CMD + 0x80;
    tx_packet->len[0]  = 5 + 0;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = RET_OK;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;
    pdata =  data+7;
    *pdata = RET_OK;
    pdata =  data+8;
    *pdata = cal_crc8_check(data, tx_packet->len[0]+3);
}

/**
  * @brief  写入校准参数值.
  * @param
  * @return none.
  */
void filled_write_calibration_value_cmd(uint8_t *data)
{
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;
    int16_t calwrite_type = 0;
    int16_t calwrite_value = 0;
    if(data == NULL){
        return;
    }
    calwrite_type = *(data+5);
    calwrite_value = *(data+6) + (*(data+7)<<8);
    tx_packet = (comm_tx_packet_t*)data;

    //fmc_calibration_data_write(*(data+5), calwrite_value);

    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd  = CAL_WRITEVALUE_CMD + 0x80;
    tx_packet->len[0]  = 4 + 2;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = RET_OK;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;
    pdata =  data + 7;
    *pdata = calwrite_type;
    pdata =  data + 8;
    *pdata = RET_OK;
    pdata =  data + 9;
    *pdata = cal_crc8_check(data, tx_packet->len[0]+3);
}

/**
  * @brief  跳转至boot
  * @param
  * @return none.
  */
void filled_jump_cmd(uint8_t *data)
{
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;
    int8_t err_code = RET_OK;
    if(data == NULL){
        return;
    }
    tx_packet = (comm_tx_packet_t*)data;
    err_code = RET_UNSEAL_ERR;

    // if(get_sys_seal_type() == SYS_FULL_ACCESS)
    //{ //已解锁
    err_code = RET_OK;
    set_task_event(JUMP_EVENT);
    // }

    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd = JUMP_CMD + 0x80;
    tx_packet->len[0]  = 4 + 0;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = err_code;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;
    pdata =  data+7;
    *pdata = cal_crc8_check( data, tx_packet->len[0]+3);
}

/**
  * @brief  解锁memory操作.
  * @param
  * @return none.
  */
void filled_unlock_memory_cmd(uint8_t *data)
{
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;
    if(data == NULL){
        return;
    }
    tx_packet = (comm_tx_packet_t*)data;

    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd = UNLOCK_PARAM_CMD + 0x80;
    tx_packet->len[0]  = 4+0;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = RET_OK;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;
    pdata =  data+7;
    *pdata = cal_crc8_check( data, tx_packet->len[0]+3);
}


void run_task_event(void)
{
    if(task_event&JUMP_EVENT){
        task_event ^= JUMP_EVENT;
        clear_dog();
        block_delay_ms(100);
        os_reset_system();
    }
}

/**
  * @brief  错误码响应帧.
  * @param
  * @return none.
  */
void tx_err_code_packet(uint8_t *data, uint8_t err_code)
{
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;
    if(data == NULL){
        return;
    }
    tx_packet =  (comm_tx_packet_t*)data;

    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd |= 0x80;
    tx_packet->len[0]  = 4+0;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = err_code;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;
    pdata =  data+7;
    *pdata = cal_crc8_check(data, tx_packet->len[0]+3);
}


/**
  * @brief  解析接收帧.
  * @param
  * @return none.
  */
int8_t parse_rx_data_packet(uint8_t *input_data)
{
    comm_rx_packet_t *rx_packet;
    if(input_data == NULL){
        return 0;
    }
    rx_packet = (comm_rx_packet_t*) input_data;
//    rcv_random = rx_packet->random;

    switch(rx_packet->cmd)
    {
        case CONNECTED_CMD: //50 连接扫描
            filled_connected_cmd(input_data);
            break;
        case READ_INFO_CMD: //51 读取信息
            filled_info_cmd(input_data);
            break;
        case AUTHEN_CMD:    //52 鉴权
            filled_authen_cmd(input_data);
            break;
        case JUMP_CMD:      //53 跳转
            filled_jump_cmd(input_data);
            break;
        case UNLOCK_PARAM_CMD: //56 解锁命令
            filled_unlock_memory_cmd(input_data);
            break;
        case READ_DATA_MEMORY_CMD:  //57 读取参数区
            data_memory_read_fun(input_data);
            break;
        case WRITE_DATA_MEMORY_CMD: //58 写参数区
            data_memory_write_fun(input_data);
            break;
        case DISCONNECT_CMD:        //5A 断开连接命令
            filled_disconnected_cmd(input_data);
            break;
        case WRITE_REGISTER_CMD:   //5B 写寄存器
            register_write_fun(input_data);
            break;
        case READ_REGISTER_CMD:     //5C 读寄存器
            register_read_fun(input_data);
            break;
        case WRITE_BLOCK_CMD:       //60写command 命令
            //filled_write_block_cmd(input_data);
            write_command_id_handle(input_data);
            break;
        case READ_BLOCK_CMD:        //5F 读command 命令
            //filled_read_block_cmd(input_data);
            read_command_id_handle(input_data);
            break;
        case CAL_ENABLE_CMD:        //5D 校准使能
            filled_calibration_enable_cmd(input_data);
            break;
        case CAL_WRITEVALUE_CMD:    //5E 写校准参数
            filled_write_calibration_value_cmd(input_data);
            break;
    }
    return 0;
}
