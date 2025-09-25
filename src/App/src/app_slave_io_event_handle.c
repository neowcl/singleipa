/***************************************************************************//**
 * @file     bms_slave_io_event_handle.c
 * @version  V1.0.0
 * @author   sz414
 * @date     2022-08-09 PM
 * @brief    
 *
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

#include "app_inc.h"
#include "modules_pmu.h"
 // 寄存器的基地址.
#define REG_BASE_ADDR   0x00

// 表示处理在处理的寄存器ID
//static regid_t reg_id = UNKOWN_REGID;
static access_mode_t access_mode = ACCESS_NONE;
static uint8_t slave_io_state = 0; //IO状态.  pending, debug mode
static uint8_t encrypt_key = 0xFF;

static uint8_t i2c_start_flag = 0;

uint8_t get_slave_io_state(void)
{
    return slave_io_state;
}

void set_slave_io_state(uint8_t removed, uint8_t added)
{
    slave_io_state &= ~removed;
    slave_io_state |= added;
}

static void on_slave_io_event_start(void)
{
    TRACE0("on_slave_io_event_start()\n");
    //reg_id = UNKOWN_REGID;
    i2c_start_flag = 1;
}

//regid_t get_regid_by_addr(REGTYPE_REGISTER , 0xEE )

static void on_slave_io_event_data(uint8_t data)
{
    TRACE1("on_slave_io_event_data(%x)\n", data);

    //data ^= encrypt_key;

    /*if( reg_id == ENCRYPT_REGID )  //设置加密KEY.
    {
        encrypt_key = data;
    }
    else */  #if 0
    if( reg_id == UNKOWN_REGID ) 
    {
        if( data == ENCRYPT_REGID ) //第一个字符就是设置加密KEY.
        {
            reg_id = ENCRYPT_REGID;
            return;
        }
        if(start_flag ){
            // 第一个字节是寄存器地址.
            // 通过寄存器地址偏移，开始访问寄存器项，返回寄存器ID号.
            reg_id = access_reg_item_begin(REGTYPE_REGISTER, data - REG_BASE_ADDR);
            ASSERT(IS_LEGAL_REGID(reg_id));

            access_mode = ACCESS_NONE;
            prehandle_reg_command(REGTYPE_REGISTER, reg_id);
        }
    }
    else if( reg_id != INVALID_REGID )
    {
        access_mode = ACCESS_WRITE;

        // 如果主机在发送完地址后，没有停止，继续发送数据，则表示是向该寄存器项写数据.
        // 调用append_reg_data把数据附加到寄存器项相关的buffer中.
        append_reg_data(data);
    }
#endif
    if(i2c_start_flag ){
        // 第一个字节是寄存器地址.
        // 通过寄存器地址偏移，开始访问寄存器项，返回寄存器ID号.
        //reg_id = access_reg_item_begin(REGTYPE_REGISTER, data - REG_BASE_ADDR);
        ASSERT(IS_LEGAL_REGID(reg_id));

        access_mode = ACCESS_NONE;
     
    }

    
    i2c_start_flag = 0;
}


static void on_slave_io_event_transmit()
{
    TRACE0("on_slave_io_event_transmit()\n");
    ASSERT(IS_LEGAL_REGID(reg_id));

    uint8_t  value = INVALID_BYTE;

    if(i2c_start_flag ){
        //clear_positon();
        //reg_id = access_reg_item_begin(REGTYPE_REGISTER, 0xEE - REG_BASE_ADDR);
    }
    i2c_start_flag = 0;
    
    
    //value ^= encrypt_key;

    // 发送数据到主机.
    os_i2c_data_send(value);
}

static void on_slave_io_event_stop()
{
    TRACE0("on_slave_io_event_stop()\n");
    
    i2c_start_flag = 0;
//    if( access_mode != ACCESS_NONE )
//    {
//        reg_id = UNKOWN_REGID;
//    }
}

void on_slave_io_event(slave_io_event_t event, uint8_t data)
{
    switch(event)
    {
    case SLAVE_IO_EVENT_START:
        on_slave_io_event_start();  //io开始
        break;
    case SLAVE_IO_EVENT_DATA:
        on_slave_io_event_data(data);  //收到一个data.
        break;
    case SLAVE_IO_EVENT_TRANSMIT:
        on_slave_io_event_transmit();  //返回数据.
        break;
    case SLAVE_IO_EVENT_STOP:
        on_slave_io_event_stop();  //io结束.
        break;
    }
}
