//	sw_slave_i2c.h
///////////////////////////////////////////////////////////////////////////////

#ifndef __SW_SLAVE_I2C_H_
#define __SW_SLAVE_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cse7561_conf.h"


#define SW_SLAVE_ADDR			0xAA    //器件地址

//模拟iic从机结构体
typedef struct _SwSlaveI2C_t
{
    volatile uint8_t State;					// I2C通信状态
    volatile uint8_t Rw;						// I2C读写标志：0-写，1-读
    volatile uint8_t SclFallCnt;				// SCL下降沿计数
    volatile uint8_t Flag;					// I2C状态标志，BIT0：0-地址无效，1-地址匹配
    volatile uint32_t StartMs;				// I2C通信起始时间，单位ms，用于判断通信是否超时
    volatile uint8_t *RxBuf;					// 指向接收缓冲区的指针
    volatile uint8_t *TxBuf;					// 指向发送缓冲区的指针
    volatile uint8_t RxIdx;					// 接收缓冲区数据写入索引，最大值255
    volatile uint8_t TxIdx;					// 发送缓冲区数据读取索引，最大值255
} SwSlaveI2C_t;
extern SwSlaveI2C_t SwSlaveI2C;

void InitSwSlaveI2C(void);
void I2cGpioIsr(void);
extern void (*SW_IIC_CallBack)(void);

#ifdef __cplusplus
}
#endif

#endif /* __SW_TIMER_H_ */
