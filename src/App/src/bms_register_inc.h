/***************************************************************************//**
 * @file     bms_register_inc.h
 * @version  V1.0.0
 * @author   sz414
 * @date     2022-08-09 PM
 * @brief
 *
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

#ifndef __BMS_REGISTER_INC_H__
#define __BMS_REGISTER_INC_H__
#include "stdint.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#pragma pack(push,8)

typedef enum {
    REGTYPE_REGISTER,  //通用寄存器.
    REGTYPE_MEMORY, //DataMemory寄存器.
} regtype_t;

typedef uint8_t   regid_t;

#include "app_inc.h"


// 保留的寄存器范围0xF0 ~ 0xFF
#define UNKOWN_REGID        ((regid_t)250)
#define ENCRYPT_REGID       ((regid_t)254)
#define INVALID_REGID       ((regid_t)255) // Invalid register id
#define IS_LEGAL_REGID(_regid)    (((regid_t)_regid) < UNKOWN_REGID)

// register access mode.
//#define REG_ACCESS_NONE   0x00
#define REG_ACCESS_READ   0x01
#define REG_ACCESS_WRITE  0x02
#define REG_UNIT_ELEMENT  0x08  //数量el_num是指元素的数量，寄存器是一个数组，数据类型为数组元素的类型.
#define REG_ACCESS_ALL    (REG_ACCESS_READ | REG_ACCESS_WRITE)
#define REG_DEFAULT_VALUE 0x10   //寄存器有默认值
#define REG_MIN_VALUE   0x20   //寄存器有最小值
#define REG_MAX_VALUE   0x40   //寄存器有最大值
#define REG_MINMAX_VALUE  (REG_MIN_VALUE | REG_MAX_VALUE)

// register state.
//#define E_VALUE_INVALID 0x01   //寄存器是无效的
//#define REG_VALUE_CHANGED 0x02   //寄存器内容发生改变.
//#define REG_STATE_PENDING 0x04   //寄存器被标记为悬而未决的，正在处理中的状态。

// register data type.
typedef enum {
    DT_INVALID = 0,   //数据类型无效.
    //DT_PTR,   //指针类型.
    DT_UINT8,
    DT_UINT16,
    DT_UINT32,
    DT_INT8,
    DT_INT16,
    DT_INT32,
    DT_FLOAT,
} data_type_t;

#define IS_DECIMAL_TYPE(_type)  ((_type) < DT_UINT8)
#define IS_INT_TYPE(_type)      (_type == DT_INT8 || _type == DT_INT16 || _type == DT_INT32)
#define IS_UINT_TYPE(_type)     (_type == DT_UINT8 || _type == DT_UINT16 || _type == DT_UINT32)


// A data structure used to save register values
typedef union {
    int32_t   i32;
    uint32_t  u32;
    float   f;
    struct {
        uint8_t*  ptr; //长度小于255的buffer.
        uint8_t     len; //ptr的长度.
    } sptr;
} data_value_t;

typedef union {
    int32_t   i32;
    uint32_t  u32;
    float   f;
} boundary_t;

typedef union {
    uint32_t  u;
    float   f;
} uintfloat_t;

/*
typedef struct {
  data_type_t type;
  data_value_t value;
} type_value_t;*/

// reg_item_t表示一个寄存器项，如果修改该结构体大小，需要同步修改上位机自动代码生成模块.
#pragma pack (1)
//typedef __align(1) struct {


// 包含一个值范围的数据类型
typedef struct {
    uint16_t  from;  //寄存器的值, 对于hex和string类型，如果长度大于4，则不缓存该值.
    uint16_t  to; //寄存器相关属性：INVALID，CHANGED
} range_t;

// 初始化寄存器的数据列表.
void bms_register_init(void);

//const reg_item_t* get_reg_item_list(regtype_t regtype);
uint16_t get_reg_item_count(regtype_t regtype);
uint16_t get_reg_addr_range(regtype_t regtype, uint16_t base_addr, range_t * range);

regid_t get_regid_by_addr(regtype_t regtype, uint16_t addr);
//const reg_item_t* get_reg_item(regtype_t regtype, regid_t regid);

// 改变寄存器的状态.
//uint8_t change_reg_state(regtype_t regtype, regid_t regid, uint8_t removed, uint8_t added);
//uint8_t get_reg_state(regtype_t regtype, regid_t regid);

// access函数组
// access_reg_item_begin: 表示访问寄存器项开始，返回寄存器ID号, see on_slave_io_event_data函数.
regid_t access_reg_item_begin(regtype_t regtype, uint16_t addr);
void access_reg_item_end(access_mode_t access_mode);
uint8_t next_reg_data(void);
error_t append_reg_data(uint8_t data);

void clear_positon(void);
// access函数组

// 与寄存器值相关的操作.
//uint16_t  get_reg_item_bytes(const reg_item_t* regitem);  //得到寄存器的字节数.
//uint8_t   get_reg_value_element_num(const reg_item_t* regitem);
uint8_t   get_reg_value(regtype_t regtype, regid_t regid, uint8_t index, uint8_t* buffer, uint8_t len);
error_t   set_reg_value(regtype_t regtype, regid_t regid, uint8_t index, const uint8_t* buffer, uint8_t len);
uint8_t*  get_reg_value_ptr(regtype_t regtype, regid_t regid, uint8_t index);

#define   set_reg_value_i8(regtype, regid, index, value)    set_reg_value_u32(regtype, regid, index, value)
#define   set_reg_value_i16(regtype, regid, index, value)   set_reg_value_u32(regtype, regid, index, value)
#define   set_reg_value_i32(regtype, regid, index, value)   set_reg_value_u32(regtype, regid, index, value)
#define   set_reg_value_u8(regtype, regid, index, value)    set_reg_value_u32(regtype, regid, index, value)
#define   set_reg_value_u16(regtype, regid, index, value)   set_reg_value_u32(regtype, regid, index, value)
error_t   set_reg_value_u32(regtype_t regtype, regid_t regid, uint8_t index, uint32_t value);
error_t   set_reg_value_float(regtype_t regtype, regid_t regid, uint8_t index, float value);
//error_t   set_reg_field_value(regtype_t regtype, regid_t regid, uint8_t index, uint32_t field_mask, uint32_t field_value);

#define   get_reg_value_i8(regtype, regid, index)     ((int8_t)get_reg_value_u32(regtype, regid, index))
#define   get_reg_value_i16(regtype, regid, index)    ((int16_t)get_reg_value_u32(regtype, regid, index))
#define   get_reg_value_i32(regtype, regid, index)    ((int32_t)get_reg_value_u32(regtype, regid, index))
#define   get_reg_value_u8(regtype, regid, index)     ((uint8_t)get_reg_value_u32(regtype, regid, index))
#define   get_reg_value_u16(regtype, regid, index)    ((uint16_t)get_reg_value_u32(regtype, regid, index))
uint32_t  get_reg_value_u32(regtype_t regtype, regid_t regid, uint8_t index);
float     get_reg_value_float(regtype_t regtype, regid_t regid, uint8_t index);
#define   get_reg_field_value(regtype, regid, index, field_mask)    (get_reg_value_u32(regtype, regid, index) & (field_mask))

#define   is_valid_reg_value_i8(regtype, regid, value)    is_valid_reg_value_u32(regtype, regid, value)
#define   is_valid_reg_value_i16(regtype, regid, value)   is_valid_reg_value_u32(regtype, regid, value)
#define   is_valid_reg_value_i32(regtype, regid, value)   is_valid_reg_value_u32(regtype, regid, value)
#define   is_valid_reg_value_u8(regtype, regid, value)    is_valid_reg_value_u32(regtype, regid, value)
#define   is_valid_reg_value_u16(regtype, regid, value)   is_valid_reg_value_u32(regtype, regid, value)
bool      is_valid_reg_value_u32(regtype_t regtype, regid_t regid, uint32_t value);
bool      is_valid_reg_value_float(regtype_t regtype, regid_t regid, float value);

// 计算寄存器数据表的校验和
uint16_t  calc_reg_table_checksum(regtype_t regtype);

#pragma pack(pop)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__BMS_REGISTER_INC_H__
