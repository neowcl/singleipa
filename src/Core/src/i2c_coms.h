/***************************************************************************//**
 * @file     i2c_coms.h
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    I2C模块头文件
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

#ifndef __I2C_COMS_H__
#define __I2C_COMS_H__

// Include external header file.
#include "cbmx56x_conf.h"
#include "modules_vbat.h"
#include "modules_temp.h"
#include "modules_current.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2CSLAVE_ADDR               (0xAA)   //slave 7bit-address
#define REG_DATA_LEN                (112)    //寄存器数组长度
#define READ_MODE                   (1)
#define WRITE_MODE                  (2)

#define REG_CNTL            0x00
#define REG_AR              0x02
#define REG_ARTTE           0x04
#define REG_TEMP            0x06
#define REG_VOLT            0x08
#define REG_INSTCURR        0x0C

#define REG_RM              0x10
#define REG_TEMP_IN         0x28
#define REG_TEST            0x60
#define REG_NULL            0x6F
/**************IIC Cmd***************/
#define IIC_CMD_CALIBRATION_VBAT 0x70
#define IIC_CMD_CALIBRATION_CC   0x71
#define IIC_CMD_TEST             0x72

typedef struct
{
    uint8_t IIC_AddrFlag;
    uint8_t IIC_ReadFlag;
    uint8_t IIC_WriteFlag;
    uint8_t IIC_RegisterAddr;
    uint8_t IIC_UpdateFlag;
}slave_i2c_control_t;

typedef struct
{
    uint8_t IIC_RegAddr;
    void *  IIC_Function;
}slave_i2c_rw_data_t;



typedef struct
{
    uint8_t IIC_CmdMode;
    uint8_t IIC_CmdType;
    uint8_t IIC_CmdFlag;

}slave_i2c_command_t;


extern char reg_data[REG_DATA_LEN];

/**@brief I2C模块三处理函数.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
void app_iic_isr_process(void);

/**@brief I2C模块数据更新函数.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
void app_i2c_updata_deal(uint8_t *add,uint8_t mode);


/**@brief 电池电压温度扫描.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
void app_i2c_updata_vbat(void);

/**@brief 电池内部温度扫描.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
void app_i2c_updata_temp_in(void);

/**@brief 电池外部温度扫描.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
void app_i2c_updata_temp_ex(void);

/**@brief 电池高精度电流扫描函数.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
void app_i2c_updata_cc_hp(void); 

/**@brief 电池更新SOC值.
 * 
 * @param[in]  None.
 * @param[out] None.
 * 
 * @return  None
 */
void app_i2c_updata_soc(void);


#ifdef __cplusplus
}
#endif

#endif  //__I2C_COMS_H__


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
