/***************************************************************************//**
 * @file     main.h
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    main主程序头文件
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 **************************************************************************** 
 * @par 修改日志:
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/01/25  <td>1.0      <td>chensj0621  <td>创建初始版本
 * </table>
 *
 *****************************************************************************/


#ifndef __STANDARD_DATA_CMD_H__
#define __STANDARD_DATA_CMD_H__
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif


#define   DF_FLASH_OFFSET  0xA400
#define   DF_FLASH_START   0x4000
#define   DF_FLASH_END     0xE7FF
#define JUMP_EVENT        0x01

#define DEBUG_MODE_REG                0xEE
#define DEBUG_MODE_BUF_SIZE           250

#define ADD_BIT                       0x01
#define REMOVE_BIT                    0x00

#define IIC_RX_CTL_ST_BIT             0x01
#define IIC_RX_ALT_MANU_ACCESS_BIT    0x02
#define IIC_RX_MACDATA_BIT            0x04
#define IIC_RX_MACDATA_CS_BIT         0x08
#define IIC_RX_MACDATA_LEN_BIT        0x10

#define IIC_RX_DEBUG_MODE_BIT         0x20
////////////////////////////////////////////////////////////////
typedef struct									// smbus function data
{
	uint8_t	acrem;								// read data num
	uint8_t *aadr;								// access address
} _ST_SMB;
///////////////////////////////////////////////////////////////////////////////
typedef union
{
    struct
    {
        volatile uint8_t LO;
        volatile uint8_t HI;
    }Byte;
    int16_t Word;
} hf_word_t;

#pragma pack(push,1)
typedef struct
{
    hf_word_t ContrStatus;  //0x00/0x01
    hf_word_t AtRate;       //0x02/0x03
    hf_word_t AtRateToEmp;  //0x04/0x05
    hf_word_t Temp;         //0x06/0x07
    hf_word_t Voltage;      //0x08/0x09
    hf_word_t BatteryStatus; //0x0A/0x0B
    hf_word_t Current;       //0x0C/0x0D
    hf_word_t IMAX;
    hf_word_t RemCap;     //0x10/0x11
    hf_word_t FCC;        //0x12/0x13
    hf_word_t AvgCurrent; //0x14/0x15
    hf_word_t AvgToEmp;   //x16/0x17
    hf_word_t AvgToFull;  //0x18/0x19
    volatile uint8_t RSV2[4];
    hf_word_t MaxLoadCurrent; //0x1E/0x1F
    hf_word_t MaxLoadToEmpty;  //0x20/0x21
    hf_word_t AveragePower;    //0x22/0x23
    volatile uint8_t RSV3[4];
    hf_word_t InternalTemp; //0x28/0x29
    hf_word_t CycleCount;   //0x2A/0x2B
    hf_word_t RSOC;         //0x2C/0x2D
    hf_word_t SOH;          //0x2E/0x2F
    hf_word_t ChgVoltage;   //0x30/0x31
    hf_word_t ChgCurrent;    //0x32/0x33
    volatile uint8_t RSV4[8];
    hf_word_t DesignCap;     //0x3C/0x3D
    hf_word_t AltMfAccess;   //0x3E/0x3F
    volatile uint8_t MACData[32]; //0x40
    volatile uint8_t MAC_ChkSum;
    volatile uint8_t MAC_Length;
    hf_word_t VoltHiSet;
    hf_word_t VoltHiClear;
    hf_word_t VoltLoSet;
    hf_word_t VoltLoClear;
    volatile uint8_t TempHiSet;
    volatile uint8_t TempHiClear;
    volatile uint8_t TempLoSet;
    volatile uint8_t TempLoClear;
    volatile uint8_t InterruptStatus; //0x6E
    volatile uint8_t SocSetDelta;     //0x6F
    hf_word_t CalibhighPrecision;     //0x70 0x71
    uint32_t SOCFlagConfig_bit;       //0x72
}std_data_cmd_t;

#pragma pack(pop)


enum COMMAND_ID_e 
{
    // Read
    BLOCK_AUTHEN = 0x0000,
    BLOCK_DEV_TYPE = 0x0001,
    BLOCK_FW_VER = 0x0002,
    BLOCK_HW_VER = 0x0003,

    BLOCK_IF_CS = 0x0004,
    BLOCK_STATIC_DF_SIGN = 0x0005,
    BLOCK_CHEM_ID = 0x0006,
    BLOCK_PRE_MAC_WRITE = 0x0007,
    BLOCK_STATIC_CHEM_SIGN = 0x0008,
    BLOCK_ALL_DF_SIGN = 0x0009,
    // Write
    BLOCK_RESET = 0x0012,
    BLOCK_GAUGING = 0x0021,
    BLOCK_LIFE_TIME_COLLECTION = 0x0023,
    BLOCK_LIFE_TIME_DATA_RESET=0x0028,
    BLOCK_CALIBRATION_MODE = 0x002D,
    BLOCK_LIFE_TIME_DATA_FLUSH = 0x002E,
    BLOCK_SEAL_DEVICE = 0x0030,
    //Read Write
    BLOCK_SECURITY_KEY = 0x0035,
    BLOCK_AUTHEN_KEY = 0x0037,

    //Write
    BLOCK_RESET_DEV = 0x0041,

    BLOCK_SET_DEEP_SLEEP = 0x0044,
    BLOCK_CLR_DEEP_SLEEP  = 0x0045,

    //Read Write
    BLOCK_DEVICE_NAME = 0x004A,
    BLOCK_DEVICE_CHEM,
    BLOCK_MANUFACTURER_NAME,
    BLOCK_MANUFACTURER_DATE,
    BLOCK_Serial_Number = 0x004E,
    // Read
    BLOCK_OPERATION_STATUS = 0x0054,
    BLOCK_CHARGING_STATUS,
    BLOCK_GAUGING_STATUS,
    BLOCK_MANUFACTURING_STATUS = 0x0057,

    BLOCK_LIFE_TIME_DATA_BLOCK1 = 0x0060,
    BLOCK_LIFE_TIME_DATA_BLOCK3 = 0x0062,

    //Read
    BLOCK_ManufacturerInfo=0x0070,
    BLOCK_DASTATUS1,
    BLOCK_DASTATUS2,
    BLOCK_ITSTATUS1,
    BLOCK_ITSTATUS2,
    BLOCK_ITSTATUS3=0x0075,
};

extern uint8_t* pCMDAddress[100];
extern std_data_cmd_t std_data;
extern _ST_SMB ssmbdata;
extern uint8_t debug_mode_buf[];
extern const uint8_t REGISTER_RW_PARA[];


extern uint16_t t_com84_cwh;
extern uint16_t t_com10_cwh;
extern uint16_t t_com0f_cwh;
extern uint32_t TimesTamp;
extern uint16_t temp_dsg_inner_res;

extern uint16_t inner_res_dsg_100;
extern uint16_t save_volstart_dsg_inner;
extern uint16_t save_volend_dsg_inner;

extern uint16_t old_factor  ;  // to show out information
extern uint16_t new_factor; 
extern uint16_t old_fcc  ;  // to show out information
extern uint16_t new_fcc ;
// extern uint16_t twrok1_out ;
// extern uint16_t twrok2_out ;
// extern uint16_t awrok3_out ;
// extern uint16_t awrok4_out ;



extern uint16_t save_tabsc3;
extern uint16_t outer_tinreg ;

extern  uint16_t tcpl_v_start1;  // t_com2a 
extern uint16_t tcpl_v_out ;     // t_com2a
extern uint16_t tcph_v_out ;     // t_com2a
extern  uint16_t inner_res_out;   // t_com2b
extern uint16_t inner_res_dsg_100;
extern uint16_t tabsc_out;       // t_com2e
extern uint16_t tcpl_v_end_out ;       // t_com2d
extern uint16_t   LifeTimeprt;

void iic_isr_process(void);
uint8_t get_iic_rx_handle_type();
extern void handle_block_read();
void ReadFlashData(uint16_t Command);
void ReadRecordData(uint16_t Command);
void ReadLifeTimeData(uint16_t Command);
void SubCmdProcess(uint16_t Command);
void writeDFbySubcmd(uint16_t Command);

extern uint16_t open_IPA;
extern uint8_t t_com62Flg;
extern uint32_t chargetv;
extern uint32_t chargetC;

void set_iic_rx_handle_type(uint32_t val, uint8_t add_rm);

#ifdef __cplusplus
}
#endif

#endif


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
