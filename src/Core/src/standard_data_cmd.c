/**************************************************************************/ /**
                                                                              * @file     main.c
                                                                              * @version  V0.2.0
                                                                              * @author
                                                                              * @date     2022-07-29 AM
                                                                              * @brief
                                                                              *
                                                                              * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
                                                                              *****************************************************************************/

#include "main.h"

#include "bi2cs_interface.h"
#include "data_flash.h"
#include "standard_data_cmd.h"
#include "modules_pmu.h"
#include "comm_protocol.h"
#include "task.h"
#include "Ram.h"
#include "user_config.h"

std_data_cmd_t std_data;

uint8_t t_com3eBufFlg = 0;
uint8_t debug_mode_buf[DEBUG_MODE_BUF_SIZE];
uint16_t nReadLen, nWriteLen;
uint8_t std_data_reg;
uint8_t iic_rx_cnt = 0;
uint8_t iic_tx_cnt = 0;
uint32_t chargetv;
uint32_t chargetC;
uint16_t ccnt;
int16_t t_ChargingVoltage = 4450;
// uint16_t t_com66cnt=0;
// uint16_t t_com84_cwh;
// uint16_t t_com10_cwh;
// uint16_t t_com0f_cwh;
uint8_t subcmd_datalen;
uint8_t t_com62Flg = 0;
uint8_t t_com62Buf[34] = {0};


int16_t t_com09_rep ;

//uint8_t readIPA_huifu=0;
// uint8_t subcmd_datalen;
uint32_t iic_rx_type = 0;
uint8_t iic_send_data = 0;
uint8_t g_i2cBuffRecv[2 + MAC_DATA_LEN + 2];
static uint8_t *iic_reg_pointer = (uint8_t *)&std_data.ContrStatus.Byte.LO; //
static volatile uint8_t register_addr = 0;
extern uint8_t pmu_sleep_timeout;
volatile uint8_t apec = 0; // PEC
uint8_t nPos;
uint32_t TimesTamp = 0;
//////绠楁硶閮ㄥ垎璋冪敤
uint16_t temp_dsg_inner_res;
uint16_t save_volstart_dsg_inner; //
uint16_t save_volend_dsg_inner;

uint16_t old_factor; // to show out information
uint16_t new_factor;
uint16_t old_fcc; // to show out information

// uint16_t twrok1_out;
// uint16_t twrok2_out;
// uint16_t awrok3_out;
// uint16_t awrok4_out;

uint16_t new_fcc;

uint16_t LifeTimeprt;

uint16_t tcpl_v_start1 = 0;     // t_com2a
uint16_t tcpl_v_out = 0;        // t_com2a
uint16_t tcph_v_out = 0;        // t_com2a
uint16_t inner_res_out = 0;     // t_com2b
uint16_t inner_res_dsg_100 = 0; //  t_com2c
uint16_t tcpl_v_end_out = 0;    // t_com2d
uint16_t tabsc_out = 0;         // t_com2e

uint16_t save_tabsc3;
uint16_t outer_tinreg;

/// /////////////////////////////////
uint8_t *pCMDAddress[100] =
    {
        (uint8_t *)NULL,                                           // 0x00
        (uint8_t *)NULL,                                           // 0x01
        (uint8_t *)NULL,                                           // 0x02
        (uint8_t *)NULL,                                           // 0x03
        (uint8_t *)NULL,                                           // 0x04
        (uint8_t *)NULL,                                           // 0x05
        (uint8_t *)NULL,                                           // 0x06
        (uint8_t *)NULL,                                           // 0x07
        (uint8_t *)NULL,                                           // 0x08
        (uint8_t *)NULL,                                           // 0x09
        (uint8_t *)NULL,                                           // 0x0A
        (uint8_t *)NULL,                                           // 0x0B
        (uint8_t *)NULL,                                           // 0x0C    //revse
        (uint8_t *)NULL,                                           // 0x0D
        (uint8_t *)NULL,                                           // 0x0E
        (uint8_t *)NULL,                                           // 0x0F
        (uint8_t *)NULL,                                           // 0x10
        (uint8_t *)NULL,                                           // 0x11
        (uint8_t *)NULL,                                           // 0x12
        (uint8_t *)NULL,                                           // 0x13
        (uint8_t *)NULL,                                           // 0x14
        (uint8_t *)NULL,                                           // 0x15
        (uint8_t *)NULL,                                           // 0x16
        (uint8_t *)NULL,                                           // 0x17
        (uint8_t *)NULL,                                           // 0x18
        (uint8_t *)NULL,                                           // 0x19
        (uint8_t *)NULL,                                           // 0x1A
        (uint8_t *)NULL,                                           // 0x1B
        (uint8_t *)NULL,                                           // 0x1C
        (uint8_t *)NULL,                                           // 0x1D
        (uint8_t *)NULL,                                           // 0x1E
        (uint8_t *)NULL,                                           // 0x1F
        (uint8_t *)NULL,                                           // 0x20
        (uint8_t *)NULL,                                           // 0x21
        (uint8_t *)NULL,                                           // 0x22
        (uint8_t *)NULL,                                           // 0x23
        (uint8_t *)NULL,                                           // 0x24
        (uint8_t *)NULL,                                           // 0x25
        (uint8_t *)NULL,                                           // 0x26
        (uint8_t *)NULL,                                           // 0x27
        (uint8_t *)NULL,                                           // 0x28
        (uint8_t *)NULL,                                           // 0x29
        (uint8_t *)NULL,                                           // 0x2A
        (uint8_t *)NULL,                                           // 0x2B
        (uint8_t *)NULL,                                           // 0x2C
        (uint8_t *)NULL,                                           // 0x2D
        (uint8_t *)NULL,                                           // 0x2E
        (uint8_t *)NULL,                                           // 0x2F
        (uint8_t *)NULL,                                           // 0x30
        (uint8_t *)NULL,                                           // 0x31
        (uint8_t *)NULL,                                           // 0x32			//    t1_com32 = t_com10;
        (uint8_t *)NULL,                                           // 0x33
        (uint8_t *)NULL,                                           // 0x34
        (uint8_t *)NULL,                                           // 0x35
        (uint8_t *)NULL,                                           // 0x36
        (uint8_t *)NULL,                                           // 0x37
        (uint8_t *)NULL,                                           // 0x38
        (uint8_t *)NULL,                                           // 0x39
        (uint8_t *)NULL,                                           // 0x3A
        (uint8_t *)NULL,                                           // 0x3B
        (uint8_t *)NULL,                                           // 0x3C
        (uint8_t *)NULL,                                           // 0x3D
        (uint8_t *)&g_StdCmdData.Field.nAltManufacturerAccess,     // 0x3E
        (uint8_t *)&g_StdCmdData.Field.nAltManufacturerAccess + 1, // 0x3F
        (uint8_t *)&g_StdCmdData.Field.nMACData,                   // 0x40
        (uint8_t *)&g_StdCmdData.Field.nMACData + 1,               // 0x41
        (uint8_t *)&g_StdCmdData.Field.nMACData + 2,               // 0x42
        (uint8_t *)&g_StdCmdData.Field.nMACData + 3,               // 0x43
        (uint8_t *)&g_StdCmdData.Field.nMACData + 4,               // 0x44
        (uint8_t *)&g_StdCmdData.Field.nMACData + 5,               // 0x45
        (uint8_t *)&g_StdCmdData.Field.nMACData + 6,               // 0x46
        (uint8_t *)&g_StdCmdData.Field.nMACData + 7,               // 0x47
        (uint8_t *)&g_StdCmdData.Field.nMACData + 8,               // 0x48
        (uint8_t *)&g_StdCmdData.Field.nMACData + 9,               // 0x49
        (uint8_t *)&g_StdCmdData.Field.nMACData + 10,              // 0x4A
        (uint8_t *)&g_StdCmdData.Field.nMACData + 11,              // 0x4B
        (uint8_t *)&g_StdCmdData.Field.nMACData + 12,              // 0x4C
        (uint8_t *)&g_StdCmdData.Field.nMACData + 13,              // 0x4D
        (uint8_t *)&g_StdCmdData.Field.nMACData + 14,              // 0x4E
        (uint8_t *)&g_StdCmdData.Field.nMACData + 15,              // 0x4F
        (uint8_t *)&g_StdCmdData.Field.nMACData + 16,              // 0x50
        (uint8_t *)&g_StdCmdData.Field.nMACData + 17,              // 0x51
        (uint8_t *)&g_StdCmdData.Field.nMACData + 18,              // 0x52
        (uint8_t *)&g_StdCmdData.Field.nMACData + 19,              // 0x53
        (uint8_t *)&g_StdCmdData.Field.nMACData + 20,              // 0x54
        (uint8_t *)&g_StdCmdData.Field.nMACData + 21,              // 0x55
        (uint8_t *)&g_StdCmdData.Field.nMACData + 22,              // 0x56
        (uint8_t *)&g_StdCmdData.Field.nMACData + 23,              // 0x57
        (uint8_t *)&g_StdCmdData.Field.nMACData + 24,              // 0x58
        (uint8_t *)&g_StdCmdData.Field.nMACData + 25,              // 0x59
        (uint8_t *)&g_StdCmdData.Field.nMACData + 26,              // 0x5A
        (uint8_t *)&g_StdCmdData.Field.nMACData + 27,              // 0x5B
        (uint8_t *)&g_StdCmdData.Field.nMACData + 28,              // 0x5C
        (uint8_t *)&g_StdCmdData.Field.nMACData + 29,              // 0x5D
        (uint8_t *)&g_StdCmdData.Field.nMACData + 30,              // 0x5E
        (uint8_t *)&g_StdCmdData.Field.nMACData + 31,              // 0x5F
        (uint8_t *)&g_StdCmdData.Field.nMACDataSum,                // 0x60
        (uint8_t *)&g_StdCmdData.Field.nMACDataLen,                // 0x61
};
_ST_SMB ssmbdata;
const _ST_SMB scom_no_tbl[] =
    {
        {0x02, (uint8_t *)&t_com00},          // 0x00
        {0x02, (uint8_t *)NULL},               // 0x01 RemainingCapacityAlarm()
        {0x02, (uint8_t *)&t_com02},           // 0x02 RemainingTimeAlarm()
        {0x02, (uint8_t *)&t_com03},           // 0x03 BatteryMode()
        {0x02, (uint8_t *)&t_com04},           // 0x04 AtRate()
        {0x02, (uint8_t *)NULL},               // 0x05 AtRateTimeToFull()
        {0x02, (uint8_t *)&t_com06},           // 0x06 AtRateTimeToEmpty()
        {0x02, (uint8_t *)NULL},               // 0x07 AtRateOK()
        {0x02, (uint8_t *)&t_com08},           // 0x08 Temperature()
        {0x02, (uint8_t *)&t_com09_rep},           // 0x09 Voltage()
        {0x02, (uint8_t *)&t_com0a},           // 0x0a Current()
        {0x02, (uint8_t *)&t_com0b},           // 0x0b AverageCurrent()
        {0x02, (uint8_t *)NULL},               // 0x0c MaxError()
        {0x02, (uint8_t *)&t_com0d},           // 0x0d RelativeStateOfCharge()
        {0x02, (uint8_t *)&t_com0e},           // 0x0e AbsoluteStateOfCharge()
        {0x02, (uint8_t *)&t_com0f_cwh},       // 0x0f RemainingCapacity()
        {0x02, (uint8_t *)&t_com10_cwh},       // 0x10 FullChargeCapacity()
        {0x02, (uint8_t *)&t_com11},           // 0x11 RunTimeToEmpty()
        {0x02, (uint8_t *)NULL},               // 0x12 AverageTimeToEmpty()
        {0x02, (uint8_t *)&t_com13},           // 0x13 AverageTimeToFull()
        {0x02, (uint8_t *)NULL},               // 0x14 ChargingCurrent()
        {0x02, (uint8_t *)NULL},           // 0x15 ChargingVoltage()
        {0x02, (uint8_t *)&t_com16},           // 0x16 BatteryStatus()
        {0x02, (uint8_t *)&t_com17},           // 0x17 CycleCount()
        {0x02, (uint8_t *)&t_com18},           // 0x18 DesignCapacity()
        {0x02, (uint8_t *)&t_com19},           // 0x19 DesignVoltage()
        {0x02, (uint8_t *)&t_com1a},           // 0x1a SpecificationInfo()
        {0x02, (uint8_t *)&t_com1b},           // 0x1b ManufacturerDate()
        {0x02, (uint8_t *)&t_com1c},           // 0x1c SerialNumber()
        {0x02, (uint8_t *)&t_com1d},           // 0x1d
        {0x02, (uint8_t *)NULL},               // 0x1e
        {0x02, (uint8_t *)&t_com1f},           // 0x1f
        {0x15, (uint8_t *)&t_com20},           // 0x20 ManufacturerName()
        {0x08, (uint8_t *)&t_com21},           // 0x21 DeviceName()
        {0x04, (uint8_t *)&t_com22},           // 0x22 DeviceChemistry()
        {0x02, (uint8_t *)&t_com23},           // 0x23 ManufacturerData()
        {0x02, (uint8_t *)NULL},           // 0x24
        {0x02, (uint8_t *)&t_com25},           // 0x25
        {0x02, (uint8_t *)NULL},           // 0x26
        {0x22, (uint8_t *)t_com62Buf},         // 0x27
        {0x15, (uint8_t *)NULL},               // 0x28
        {0x02, (uint8_t *)NULL},               // 0x29
        {0x02, (uint8_t *)NULL},        // 0x2a
        {0x02, (uint8_t *)NULL},        // 0x2b
        {0x02, (uint8_t *)NULL},        // 0x2c
        {0x02, (uint8_t *)NULL},        // 0x2d
        {0x02, (uint8_t *)NULL},        // 0x2e
        {0x19, (uint8_t *)&t_com2f},           // 0x2f OptCommand5()
        {0x0B, (uint8_t *)&t_com30},           // 0x30
        {0x02, (uint8_t *)NULL},               // 0x31
        {0x02, (uint8_t *)NULL},               // 0x32
        {0x02, (uint8_t *)&t_com33},           // 0x33//鍗曡妭34
        {0x02, (uint8_t *)NULL},               // 0x34  shipmode
        {0x02, (uint8_t *)NULL},               // 0x35
        {0x02, (uint8_t *)&t_com36},           // 0x36
        {0x09, (uint8_t *)NULL},               // 0x37
        {0x02, (uint8_t *)&t_com38},           // 0x38
        {0x02, (uint8_t *)NULL},               // 0x39
        {0x02, (uint8_t *)NULL},               // 0x3a
        {0x02, (uint8_t *)NULL},               // 0x3b
        {0x02, (uint8_t *)NULL},               // 0x3c
        {0x04, (uint8_t *)&t1_com3d},          // 0x3d
        {0x02, (uint8_t *)NULL},               // 0x3e blcok
        {0x20, (uint8_t *)NULL},               // 0x3f
        {0x02, (uint8_t *)&t_com40},           // 0x40 CellVoltage1()
        {0x18, (uint8_t *)t_com41},               // 0x41 CellVoltage2()
        {0x02, (uint8_t *)NULL},               // 0x42 CellVoltage3()
        {0x04, (uint8_t *)&t_com43},           // 0x43 ChargingStatus
        {0x04, (uint8_t *)&t_com44},           // 0x44
        {0x04, (uint8_t *)&chargetv},          // 0x45
        {0x04, (uint8_t *)&chargetC},          // 0x46
        {0x04, (uint8_t *)&t_com47},           // 0x47
        {0x02, (uint8_t *)NULL},               // 0x48 GPIORead()
        {0x02, (uint8_t *)NULL},               // 0x49 GPIOWrite()
        {0x02, (uint8_t *)NULL},               // 0x4a BTPDischargeSet()
        {0x02, (uint8_t *)NULL},               // 0x4b BTPChargeSet()
        {0x04, (uint8_t *)&t_com4c},           // 0x4c
        {0x04, (uint8_t *)&t_com4d},           // 0x4d
        {0x04, (uint8_t *)&t_com4e},           // 0x4e
        {0x02, (uint8_t *)NULL},               // 0x4f StateofHealth()
        {0x02, (uint8_t *)&t_com50},           // 0x50 SafetyAlert()
        {0x04, (uint8_t *)NULL},               // 0x51 SafetyStatus()
        {0x04, (uint8_t *)&t1_com52},          // 0x52 PFAlert()
        {0x20, (uint8_t *)t_com53},               // 0x53 PFStatus
        {0x04, (uint8_t *)NULL},               // 0x54 OperationStatus()
        {0x04, (uint8_t *)NULL},               // 0x55 ChargingStatus()
        {0x04, (uint8_t *)NULL},               // 0x56 GaugingStatus()
        {0x04, (uint8_t *)NULL},               // 0x57 ManufacturingStatus()
        {0x15, (uint8_t *)NULL},               // 0x58 AFERegister()
        {0x02, (uint8_t *)NULL},               // 0x59 MaxTurboPwr()
        {0x02, (uint8_t *)NULL},               // 0x5a SusTurboPwr()
        {0x02, (uint8_t *)NULL},               // 0x5b TurboPackR()
        {0x02, (uint8_t *)NULL},               // 0x5c TurboSysR()
        {0x02, (uint8_t *)NULL},               // 0x5d TurboEdv()
        {0x02, (uint8_t *)NULL},               // 0x5e MaxTurboCurr()
        {0x02, (uint8_t *)NULL},               // 0x5f SusTurboCurr()
        {0x02, (uint8_t *)&t_com60},           // 0x60 Available Continuous Discharge Power
        {0x20, (uint8_t *)NULL},               // 0x61
        {0x20, (uint8_t *)&t_com62},           // 0x62
        {0x20, (uint8_t *)&t_com63},           // 0x63 LifetimeDataBlock4()
        {0x20, (uint8_t *)&t_com64},           // 0x64 LifetimeDataBlock5()
        {0x02, (uint8_t *)&t_com65},           // 0x65 LifetimeDataBlock6()
        {0x20, (uint8_t *)&t_com66},           // 0x66 LifetimeDataBlock7()
        {0x02, (uint8_t *)&t_com67},           // 0x67 LifetimeDataBlock8()
        {0x02, (uint8_t *)&t_com68},           // 0x68 TurboRhfEffective()
        {0x20, (uint8_t *)NULL},               // 0x69 TurboVload()
        {0x01, (uint8_t *)&t_com6a},           // 0x6a
        {0x01, (uint8_t *)&t_com6b},           // 0x6b
        {0x01, (uint8_t *)&t_com6c},           // 0x6c
        {0x01, (uint8_t *)&t_com6d},           // 0x6d
        {0x20, (uint8_t *)&t_com6e},           // 0x6e
        {0x02, (uint8_t *)&t_com6f},           // 0x6f
        {0x02, (uint8_t *)&C_InterruptStatus}, // 0x70
        {0x20, (uint8_t *)&t_com71},           // 0x71 DAStatus1()
        {0x02, (uint8_t *)&t_com72},           // 0x72 DAStatus2()
        {0x02, (uint8_t *)&t_com73},           // 0x73 GaugeStatus1()
        {0x20, (uint8_t *)&t_com74},           // 0x74 lifetime()
        {0x02, (uint8_t *)&t_com75},           // 0x75 鍐呴儴娓╁害
        {0x09, (uint8_t *)&t1_com76},          // 0x76 CBStatus()
        {0x04, (uint8_t *)&t_com77},           // 0x77 ()
        {0x02, (uint8_t *)&t_com78},           // 0x78 FilteredCapacity()
        {0x02, (uint8_t *)&t_com79},           // 0x79 ()
        {0x02, (uint8_t *)&t_ChargingVoltage}, // 0x7a ()
        {0x02, (uint8_t *)&t1_com7a},          // 0x7b ()
        {0x02, (uint8_t *)&t_com7c},           // 0x7c ()
        {0x04, (uint8_t *)&t_com7d},           // 0x7d ()
        {0x14, (uint8_t *)&t_com7e},           // 0x7e ()
        {0x20, (uint8_t *)NULL},               // 0x7f ()
        {0x20, (uint8_t *)NULL},               // 0x80 ()
        {0x20, (uint8_t *)NULL},               // 0x81 ()
        {0x02, (uint8_t *)&t_com82},           // 0x82 ()
        {0x20, (uint8_t *)NULL},               // 0x83 ()
        {0x02, (uint8_t *)&t_ipaQmax},       // 0x84 ()
        {0x02, (uint8_t *)&t1_com85},          // 0x85 ()
        {0x04, (uint8_t *)&t_com86},           // 0x86 ()
        {0x02, (uint8_t *)&t_com87},           // 0x87 ()
        {0x02, (uint8_t *)&t1_com88},          // 0x88 ()
        {0x02, (uint8_t *)&t_com89},           // 0x89 ()agvCurrent
        {0x20, (uint8_t *)NULL},               // 0x8a ()
        {0x20, (uint8_t *)NULL},               // 0x8b ()
        {0x04, (uint8_t *)&t_com8c},           // 0x8c ()
        {0x02, (uint8_t *)&t_com8d},           // 0x8d ()
        {0x20, (uint8_t *)NULL},               // 0x8e ()
        {0x20, (uint8_t *)NULL},               // 0x8f ()
        {0x12, (uint8_t *)&t_com90},           // 0x90 ()
        {0x12, (uint8_t *)&t_com91},           // 0x91 ()
        {0x20, (uint8_t *)&t_com92},           // 0x92 ()
        {0x20, (uint8_t *)&t_com93},           // 0x93 ()
        {0x20, (uint8_t *)&t1_com94},          // 0x94 ()
        {0x12, (uint8_t *)&t1_com95},          // 0x95 ()
        {0x03, (uint8_t *)&t1_com96},          // 0x96 ()
        {0x03, (uint8_t *)&t1_com97},          // 0x97 ()
        {0x03, (uint8_t *)&t1_com98},          // 0x98 ()
        {0x03, (uint8_t *)&t1_com99},          // 0x99 ()
        {0x20, (uint8_t *)NULL},               // 0x9a ()
        {0x20, (uint8_t *)NULL},               // 0x9b ()
        {0x20, (uint8_t *)NULL},               // 0x9c ()
        {0x02, (uint8_t *)NULL},               // 0x9d ()
        {0x12, (uint8_t *)&t_com9e},           // 0x9e ResetData
        {0x20, (uint8_t *)NULL},               // 0x9f ()
        {0x02, (uint8_t *)&t_coma0},           // 0xa0 ()
        {0x20, (uint8_t *)t_coma1},               // 0xa1 ()
        {0x02, (uint8_t *)&t_coma2},           // 0xa2 ()
        {0x02, (uint8_t *)&t_coma3},           // 0xa3 ()
        {0x20, (uint8_t *)&t_coma4},               // 0xa4 ()
        {0x04, (uint8_t *)&t_coma5},           // 0xa5 ()
        {0x20, (uint8_t *)&t_coma6},           // 0xa6 ()
        {0x04, (uint8_t *)&t_coma7},           // 0xa7 ()
        {0x18, (uint8_t *)&t_coma8},           // 0xa8 ()
        {0x20, (uint8_t *)NULL},               // 0xa9  ()
        {0x04, (uint8_t *)&t_comaa},           // 0xaa()
        {0x04, (uint8_t *)&t_comab},           // 0xab()
        {0x04, (uint8_t *)&t_comac},           // 0xac()
        {0x04, (uint8_t *)&t1_comad},          // 0xad()
        {0x20, (uint8_t *)NULL},               // 0xae()
        {0x04, (uint8_t *)&t1_comaf},          // 0xaf()
        {0x20, (uint8_t *)NULL},               // 0xb0 ()
        {0x20, (uint8_t *)NULL},               // 0xb1 ()
        {0x20, (uint8_t *)NULL},               // 0xb2 ()
        {0x20, (uint8_t *)NULL},               // 0xb3 ()
        {0x20, (uint8_t *)NULL},               // 0xb4 ()
        {0x20, (uint8_t *)NULL},               // 0xb5 ()
        {0x20, (uint8_t *)NULL},               // 0xb6 ()
        {0x20, (uint8_t *)NULL},               // 0xb7 ()
        {0x20, (uint8_t *)NULL},               // 0xb8 ()
        {0x20, (uint8_t *)NULL},               // 0xb9 ()
        {0x10, (uint8_t *)&t_comba},           // 0xba ()
        {0x20, (uint8_t *)NULL},               // 0xbb ()
        {0x20, (uint8_t *)NULL},               // 0xbc ()
        {0x20, (uint8_t *)NULL},               // 0xbd ()
        {0x20, (uint8_t *)t_combe},               // 0xbe ()
        {0x02, (uint8_t *)&t_combf},               // 0xbf ()
        {0x20, (uint8_t *)NULL},               // 0xc0 ()
        {0x20, (uint8_t *)NULL},               // 0xc1 ()
        {0x20, (uint8_t *)NULL},               // 0xc2 ()
        {0x04, (uint8_t *)&t_comc3},               // 0xc3 ()
        {0x02, (uint8_t *)&t_comc4},               // 0xc4 ()
        {0x20, (uint8_t *)t_comc5},               // 0xc5 ()
        {0x02, (uint8_t *)&t_comc6},           // 0xc6 ()
        {0x20, (uint8_t *)NULL},               // 0xc7 ()
        {0x20, (uint8_t *)NULL},               // 0xc8 ()
        {0x20, (uint8_t *)NULL},               // 0xc9 ()
        {0x20, (uint8_t *)NULL},               // 0xca ()
        {0x20, (uint8_t *)NULL},               // 0xcb ()
        {0x20, (uint8_t *)NULL},               // 0xcc ()
        {0x20, (uint8_t *)NULL},               // 0xcd ()
        {0x20, (uint8_t *)NULL},               // 0xce ()
        {0x20, (uint8_t *)NULL},               // 0xcf ()
        {0x20, (uint8_t *)NULL},               // 0xd0 ()
        {0x20, (uint8_t *)NULL},               // 0xd1 ()
        {0x20, (uint8_t *)NULL},               // 0xd2 ()
        {0x20, (uint8_t *)NULL},               // 0xd3 ()
        {0x20, (uint8_t *)NULL},               // 0xd4 ()
        {0x20, (uint8_t *)NULL},               // 0xd5 ()
        {0x20, (uint8_t *)NULL},               // 0xd6 ()
        {0x20, (uint8_t *)NULL},               // 0xd7 ()
        {0x20, (uint8_t *)NULL},               // 0xd8 ()
        {0x20, (uint8_t *)NULL},               // 0xd9 ()
        {0x20, (uint8_t *)NULL},               // 0xda ()
        {0x20, (uint8_t *)NULL},               // 0xdb ()
        {0x20, (uint8_t *)NULL},               // 0xdc ()
        {0x20, (uint8_t *)NULL},               // 0xdd ()
        {0x20, (uint8_t *)NULL},               // 0xde ()
        {0x20, (uint8_t *)NULL},               // 0xdf ()
        {0x20, (uint8_t *)NULL},               // 0xe0 ()
        {0x20, (uint8_t *)NULL},               // 0xe1 ()
        {0x20, (uint8_t *)NULL},               // 0xe2 ()
        {0x20, (uint8_t *)NULL},               // 0xe3 ()
        {0x20, (uint8_t *)NULL},               // 0xe4 ()
        {0x20, (uint8_t *)NULL},               // 0xe5 ()
        {0x20, (uint8_t *)NULL},               // 0xe6 ()
        {0x20, (uint8_t *)NULL},               // 0xe7 ()
        {0x20, (uint8_t *)NULL},               // 0xe8 ()
        {0x20, (uint8_t *)NULL},               // 0xe9 ()
        {0x20, (uint8_t *)NULL},               // 0xea ()
        {0x20, (uint8_t *)NULL},               // 0xeb ()
        {0x20, (uint8_t *)NULL},               // 0xec ()
        {0x20, (uint8_t *)NULL},               // 0xed ()
        {0x20, (uint8_t *)NULL},               // 0xee ()
        {0x20, (uint8_t *)NULL},               // 0xef ()
        {0x20, (uint8_t *)NULL},               // 0xf0 ()
        {0x20, (uint8_t *)NULL},               // 0xf1 ()
        {0x20, (uint8_t *)NULL},               // 0xf2 ()
        {0x20, (uint8_t *)NULL},               // 0xf3 ()
        {0x20, (uint8_t *)NULL},               // 0xf4 ()
        {0x20, (uint8_t *)NULL},               // 0xf5 ()
        {0x20, (uint8_t *)&t_comf6},           // 0xf6 ()
        {0x20, (uint8_t *)NULL},               // 0xf7 ()
        {0x20, (uint8_t *)NULL},               // 0xf8 ()
        {0x20, (uint8_t *)NULL},               // 0xf9 ()
        {0x0f, (uint8_t *)t_comfa},               // 0xfa ()
        {0x20, (uint8_t *)NULL},               // 0xfb ()
        {0x20, (uint8_t *)NULL},               // 0xfc ()
        {0x20, (uint8_t *)NULL},               // 0xfd ()
        {0x20, (uint8_t *)NULL},               // 0xfe ()

};
// - CRC8 table -
const unsigned char CRC8TBL[] = {
    0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15,
    0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D,
    0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65,
    0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D,
    0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5,
    0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD,
    0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85,
    0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD,
    0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2,
    0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA,
    0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2,
    0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A,
    0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32,
    0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0A,
    0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42,
    0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A,
    0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C,
    0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
    0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC,
    0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
    0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C,
    0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
    0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C,
    0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
    0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B,
    0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
    0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B,
    0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13,
    0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB,
    0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
    0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB,
    0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3};

void CRC8_Calc(uint8_t a)
{
    apec = CRC8TBL[a ^ apec]; // PEC calculation macro
}
//////////////////////////////////////////////////////////
/*0-RO, 1-RW*/
const uint8_t REGISTER_RW_PARA[0x75 + 1] = {
    1, //  0x00   ManufacturerAccess/ControlStatus()
    1, //  0x01   ManufacturerAccess/ControlStatus()
    1, //  0x02   AtRate()
    1, //  0x03   AtRate()
    0, //  0x04   AtRateTimeToEmpty()
    0, //  0x05   AtRateTimeToEmpty()
    0, //  0x06   Temperature()
    0, //  0x07   Temperature()
    0, //  0x08   Voltage()
    0, //  0x09   Voltage()
    0, //  0x0A   BatteryStatus()
    0, //  0x0B   BatteryStatus()
    0, //  0x0C   Current()
    0, //  0x0D   Current()
    0, //  0x0E   REV
    0, //  0x0F   REV
    0, //  0x10   RemainingCapacity()
    0, //  0x11   RemainingCapacity()
    0, //  0x12   FullChargeCapacity()
    0, //  0x13   FullChargeCapacity()
    0, //  0x14   AverageCurrent()
    0, //  0x15   AverageCurrent()
    0, //  0x16   AverageTimeToEmpty()
    0, //  0x17   AverageTimeToEmpty()
    0, //  0x18   AverageTimeToFull()
    0, //  0x19   AverageTimeToFull()
    0, //  0x1A   REV
    0, //  0x1B   REV
    0, //  0x1C   REV
    0, //  0x1D   REV
    0, //  0x1E   MaxLoadCurrent()
    0, //  0x1F   MaxLoadCurrent()
    0, //  0x20/   MaxLoadTimeToEmpty()
    0, //  0x21   MaxLoadTimeToEmpty()
    0, //  0x22   AveragePower()
    0, //  0x23   AveragePower()
    1, //  0x24   BTPDischargeSet()
    1, //  0x25   BTPDischargeSet()
    1, //  0x26   BTPChargeSet()
    1, //  0x27   BTPChargeSet()
    0, //  0x28   InternalTemperature()
    0, //  0x29   InternalTemperature()
    0, //  0x2A   CycleCount()
    0, //  0x2B   CycleCount()
    0, //  0x2C   RelativeStateOfCharge()
    0, //  0x2D   RelativeStateOfCharge()
    0, //  0x2E   StateOfHealth()
    0, //  0x2F   StateOfHealth()
    0, //  0x30   ChargingVoltage()
    0, //  0x31   ChargingVoltage()
    0, //  0x32   ChargingCurrent()
    0, //  0x33   ChargingCurrent()
    0, //  0x34   TerminateVoltage()
    0, //  0x35   TerminateVoltage()
    0, //  0x36   TimeStampUpper()
    0, //  0x37   TimeStampUpper()
    0, //  0x38   TimeStampLower()
    0, //  0x39   TimeStampLower()
    0, //  0x3A   QmaxCycles()
    0, //  0x3B   QmaxCycles()
    0, //  0x3C   DesignCapacity()
    0, //  0x3D   DesignCapacity()
    1, //  0x3E   AltManufacturerAccess()
    1, //  0x3F   AltManufacturerAccess()
    1, //  0x40   MACData()
    1, //  0x41   MACData()
    1, //  0x42   MACData()
    1, //  0x43   MACData()
    1, //  0x44   MACData()
    1, //  0x45   MACData()
    1, //  0x46   MACData()
    1, //  0x47   MACData()
    1, //  0x48   MACData()
    1, //  0x49   MACData()
    1, //  0x4A   MACData()
    1, //  0x4B   MACData()
    1, //  0x4C   MACData()
    1, //  0x4D   MACData()
    1, //  0x4E   MACData()
    1, //  0x4F   MACData()
    1, //  0x50   MACData()
    1, //  0x51   MACData()
    1, //  0x52   MACData()
    1, //  0x53   MACData()
    1, //  0x54   MACData()
    1, //  0x55   MACData()
    1, //  0x56   MACData()
    1, //  0x57   MACData()
    1, //  0x58   MACData()
    1, //  0x59   MACData()
    1, //  0x5A   MACData()
    1, //  0x5B   MACData()
    1, //  0x5C   MACData()
    1, //  0x5D   MACData()
    1, //  0x5E   MACData()
    1, //  0x5F   MACData()
    1, //  0x60   MACDataSum()
    1, //  0x61   MACDataLen()
    1, //  0x62   VoltHiSetThreshold()
    1, //  0x63   VoltHiSetThreshold()
    1, //  0x64   VoltHiClearThreshold()
    1, //  0x65   VoltHiClearThreshold()
    1, //  0x66   VoltLoSetThreshold()
    1, //  0x67   VoltLoSetThreshold()
    1, //  0x68   VoltLoClearThreshold()
    1, //  0x69   VoltLoClearThreshold()
    1, //  0x6A   TempHiSetThreshold()
    1, //  0x6B   TempHiClearThreshold()
    1, //  0x6C   TempLoSetThreshold()
    1, //  0x6D   TempLoClearThreshold()
    0, //  0x6E   InterruptStatus()
    1, //  0x6F   SOCDeltaSetThreshold()
    0, //  0x70   CalibhighPrecision()
    0, //  0x71   CalibhighPrecision()

    1, //  0x72   SOCFlagConfig()
    1, //  0x73   SOCFlagConfig()
    1, //  0x74   SOCFlagConfig()
    1, //  0x75   SOCFlagConfig()
};

uint8_t get_iic_rx_handle_type()
{
    return iic_rx_type;
}

void set_iic_rx_handle_type(uint32_t val, uint8_t add_rm)
{
    if (add_rm)
    {
        iic_rx_type |= val;
    }
    else
    {
        iic_rx_type &= ~val;
    }
}

void clear_TEX_Resiger(void)
{
    uint32_t tex_flag;

    tex_flag = *(uint32_t *)0x40005418;
    *(uint32_t *)0x40005418 = tex_flag | 0x01;
}

void iic_isr_process(void)
{
    volatile uint32_t i2c_isr_buffer = *(volatile uint32_t *)0x40005418;
    uint8_t temp_data;
    uint8_t receive_reg_add;

    pmu_sleep_timeout = 20;
    fw_pmu_set_run_mode(PMU_ACTIVE_MODE);
    set_I2C_TimeOut_Count(0);

    if (i2c_isr_buffer & I2C_ISR_ADDR)
    {
        clear_TEX_Resiger();
        i2c_flag_clear(I2C_ISR_ADDR);
        iic_rx_cnt = 0;
        iic_tx_cnt = 0;
        ccnt = 0;
        nPos = 0;
    }
    else if (i2c_isr_buffer & I2C_ISR_RXNE)
    {
        temp_data = i2c_data_receive();
        if (iic_rx_cnt == 0)
        {
            apec = 0;
            CRC8_Calc(0x16);
            register_addr = temp_data; // reg_addr
            CRC8_Calc(register_addr);
            if (register_addr != DEBUG_MODE_REG)
            {
                if (register_addr == 0x61) // && (!readIPA_huifu))
                {
                    ts_W_H();
                    readIPAmes_flag = 1;
                    // readIPA_huifu=1;
                    open_IPA = 0;
                }
                ssmbdata = scom_no_tbl[register_addr];
                if (register_addr != 0x3e&&register_addr != 0x3f)
                {
                    nReadLen = ssmbdata.acrem;
                    t_com3eBufFlg=0;
                }
                
                if (register_addr == 0x3e || register_addr == 0x3f)
                {
                    if (!t_com3eBufFlg)
                    {
                        g_i2cBuffRecv[0] = 0x22;
                        for (nReadLen = 1; nReadLen < 3 + MAC_DATA_LEN; nReadLen++)
                        {
                            g_i2cBuffRecv[nReadLen] = *pCMDAddress[0x3E + nReadLen - 1];
                        }
                    }
                    else
                    {
                        g_i2cBuffRecv[0] = 0x0c;
                        if (register_addr == 0x3e)
                        {
                            for (nReadLen = 1; nReadLen < 1 + 0x0c; nReadLen++)
                            {
                                g_i2cBuffRecv[nReadLen] = *pCMDAddress[0x3E + nReadLen - 1];
                            }
                        }
                        else if (register_addr == 0x3f)
                        {
                            for (nReadLen = 1; nReadLen < 1 + 0x0c; nReadLen++)
                            {
                                g_i2cBuffRecv[nReadLen] = D_IPA_COM3F[nReadLen-1];
                            }
                        }
                    }
                }
                else
                {
                    if (nReadLen > 2)
                    {
                        g_i2cBuffRecv[0] = ssmbdata.acrem;
                        nReadLen = ssmbdata.acrem + 1;
                        for (ccnt = 1; ccnt < nReadLen; ccnt++)
                        {
                            g_i2cBuffRecv[ccnt] = ssmbdata.aadr[ccnt - 1];
                        }
                    }
                    else
                    {
                        for (ccnt = 0; ccnt < nReadLen; ccnt++)
                        {
                            g_i2cBuffRecv[ccnt] = ssmbdata.aadr[ccnt];
                        }
                    }
                }
            }
            else
            {
                debug_mode_buf[0] = DEBUG_MODE_REG; // header is 0xEE
            }
            iic_rx_cnt++;
        }
        else
        {
            t_com3eBufFlg=0;
            if (register_addr == 0x3e || register_addr == 0x3f)
            {
                g_i2cBuffRecv[iic_rx_cnt - 1] = temp_data;
                if (iic_rx_cnt >= 36)
                {
                    iic_rx_cnt = 35;
                }
                iic_rx_cnt++;
            }
            else if (register_addr == DEBUG_MODE_REG)
            {
                if (iic_rx_cnt < DEBUG_MODE_BUF_SIZE)
                {
                    debug_mode_buf[iic_rx_cnt++] = temp_data;
                }
            }
            else
            {
                g_i2cBuffRecv[iic_rx_cnt - 1] = temp_data;
                if (iic_rx_cnt >= 36)
                {
                    iic_rx_cnt = 35;
                }
                iic_rx_cnt++;
            }
        }
    }
    else if (i2c_isr_buffer & I2C_ISR_TXIS)
    {
        if (register_addr != DEBUG_MODE_REG)
        {
            if (nPos == 0)
            {
                CRC8_Calc(0x17);
            }
            if (nPos == nReadLen)
            {
                i2c_data_send(apec);
            }
            else
            {
                i2c_data_send(g_i2cBuffRecv[nPos]);
                CRC8_Calc(g_i2cBuffRecv[nPos]);
                nPos++;
            }
        }
        else
        {
            if (iic_tx_cnt < DEBUG_MODE_BUF_SIZE)
            {
                // i2c_data_send(debug_mode_buf[iic_tx_cnt++]);
                i2c_data_send(debug_mode_buf[iic_tx_cnt++]);
            }
        }
    }
    else if (i2c_isr_buffer & I2C_ISR_STOPF)
    {
        i2c_flag_clear(I2C_ISR_STOPF);
        if (register_addr != DEBUG_MODE_REG)
        {
            if (iic_rx_cnt < 2)
            {
                if (register_addr == 0x50)
                {
                   
                    //uint8_t t_com3eBuf[0x0c] = {0x36, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x20, 0x15, 0x00, 0x00, 0x40};
                    for (nWriteLen = 0; nWriteLen < 0x0c; nWriteLen++)
                    {
                        *pCMDAddress[0x3E + nWriteLen] = D_IPA_COM3E[nWriteLen];
                    }
                    t_com3eBufFlg=1;
                }
            }
            else if (iic_rx_cnt < 5 && iic_rx_cnt > 1)
            {
                switch (register_addr)
                { // AltManufacturerAccess()  2->The first byte is reg
                case 0x01:
                {
                    ts_W_H();
                    break;
                }
                case 0x07:
                {
                    // uint8_t buf4[34] = {0x20, 0x28, 0x23, 0xF9, 0x83, 0xAD, 0x82, 0x29, 0x09, 0x2A, 0xD8, 0xBD, 0x58, 0x36, 0x49, 0xAE, 0xD1, 0x30,
                    //                     0x34, 0xBA, 0x9D, 0x6A, 0x3C, 0x4D, 0x6B, 0x43, 0x8E, 0x56, 0xCD, 0x0B, 0x78, 0x74, 0xFB, 0x8A};
                    // IIC_WriteIpa(0x61, buf4);
                    // t_com62Flg = 1;
                    // IPHSeril(&t_com4c);
                    // memcpy(t1_com52, t_com4c, 4);
                    ts_W_L();
                    break;
                }
                case 0x39:
                {
                    IIC_ReadReg(g_i2cBuffRecv[0],&t_com06);
                    break;
                }
                case 0x3E:
                {
                    set_iic_rx_handle_type(IIC_RX_ALT_MANU_ACCESS_BIT, ADD_BIT);
                    break;
                }

                case 0x65:
                {
                    t_com65 = g_i2cBuffRecv[0] + (g_i2cBuffRecv[1] << 8);
                    switch (t_com65)
                    {
                    
                   case 0x0000:
                    {
                        uint32_t rs=16384;
                        if(t_com0d>0)
                        {
                            //float dd=(D_COM66_END-D_COM66_HEAD)/97.0;
                            rs=D_COM66_END-(((D_COM66_END-D_COM66_HEAD)/97.0)*(t_com0d-1));
                        }
                        else
                        {
                            rs=16384;
                        }
                        
                        t_com66[0] = 0xe8;
                        t_com66[1] = 0x03;
                        t_com66[2] = 0x00;
                        t_com66[3] = 0x00;

                        t_com66[4] = (uint8_t)t_com11;
                        t_com66[5] = (uint8_t)(t_com11 >> 8);
                        t_com66[6] = (uint8_t)(t_com11 >> 16);
                        t_com66[7] = (uint8_t)(t_com11 >> 24);

                        t_com66[8] = (uint8_t)(rs);
                        t_com66[9] = (uint8_t)((rs) >> 8);
                        t_com66[10] = (uint8_t)((rs)>> 16);
                        t_com66[11] =(uint8_t)((rs) >> 24);

                        
                        // //uint32_t rcu32 = 175000000*0.88*dd/100;
                        uint32_t rcu32 =(t_com0f_cwh)*59000;
                        t_com66[12] = (uint8_t)rcu32;
                        t_com66[13] = (uint8_t)(rcu32 >> 8);
                        t_com66[14] = (uint8_t)(rcu32 >> 16);
                        t_com66[15] = (uint8_t)(rcu32 >> 24);
              

                        t_com66[16] = (uint8_t)rcu32;
                        t_com66[17] = (uint8_t)(rcu32 >> 8);
                        t_com66[18] = (uint8_t)(rcu32 >> 16);
                        t_com66[19] = (uint8_t)(rcu32 >> 24);
                     

                        t_com66[20] = 0x00;
                        t_com66[21] = 0x40;
                        t_com66[22] = 0x00;
                        t_com66[23] = 0x00;
            
                        
                        // //uint32_t    QStart=175000000*0.88*(100-dd)/100;
                        uint32_t   QStart=(t_com10_cwh-t_com0f_cwh)*59000;
                        t_com66[24] =(uint8_t)QStart;
                        t_com66[25] = (uint8_t)(QStart>> 8);
                        t_com66[26] = (uint8_t)(QStart >> 16);
                        t_com66[27] = (uint8_t)(QStart >> 24);
                       

                        t_com66[28] = 0x59;
                        t_com66[29] = 0x00;
                        t_com66[30] = 0x00;
                        t_com66[31] = 0x00;

                        break;
                    }
                   case 0x0001:
                    {
                        t_com66[0] = 0xa5;
                        t_com66[1] = 0x00;
                        t_com66[2] = 0x00;
                        t_com66[3] = 0x00;

                        t_com66[4] = (uint8_t)t_com66_2;
                        t_com66[5] = (uint8_t)(t_com66_2 >> 8);

                        t_com66[6] = 0x1b;
                        t_com66[7] = 0xe8;
                        t_com66[8] = 0x0a;
                        t_com66[9] = 0x01;
                        t_com66[10] = 0xa5;
                        t_com66[11] = 0x00;
                        t_com66[12] = 0x00;
                        t_com66[13] = 0x00;
                        t_com66[14] = 0x00;
                        t_com66[15] = 0x00;
                        t_com66[16] = 0x88;
                        t_com66[17] = 0x2b;
                        t_com66[18] = 0x08;
                        t_com66[19] = 0x00;
                        t_com66[20] = 0xde;
                        t_com66[21] = 0x35;
                        t_com66[22] = 0x01;
                        t_com66[23] = 0x00;
                        t_com66[24] = 0x01;
                        t_com66[25] = 0x00;
                        t_com66[26] = 0x00;
                        t_com66[27] = 0x00;
                        t_com66[28] = 0x00;
                        t_com66[29] = 0x00;
                        t_com66[30] = 0x00;
                        t_com66[31] = 0x00;
                        break;
                    }
                    case 0x0003:
                    {
                        uint8_t buf3[32] = {
                            0x9E, 0xEA, 0x07, 0x00, 0x9E, 0xEA, 0x07, 0x00,
                            0x67, 0x06, 0x02, 0x00, 0x00, 0xAE, 0x00, 0x00,
                            0x7E, 0x7D, 0x00, 0x00, 0x16, 0x68, 0x00, 0x00,
                            0x9D, 0x5E, 0x00, 0x00, 0x2B, 0x55, 0x00, 0x00};
                        memcpy(t_com66, buf3, 32);
                        break;
                    }
                    case 0x0004:
                    {
                        uint8_t buf4[32] = {
                            0x52, 0x4D, 0x00, 0x00, 0x1E, 0x46, 0x00, 0x00,
                            0xAF, 0x3F, 0x00, 0x00, 0xA0, 0x3C, 0x00, 0x00,
                            0xF6, 0x38, 0x00, 0x00, 0x17, 0x37, 0x00, 0x00,
                            0xDE, 0x36, 0x00, 0x00, 0x0D, 0x37, 0x00, 0x00};
                        memcpy(t_com66, buf4, 32);
                        break;
                    }
                    case 0x0005:
                    {
                        uint8_t buf3[32] = {
                            0xFD, 0x35, 0x00, 0x00, 0xE9, 0x34, 0x00, 0x00,
                            0x8B, 0x34, 0x00, 0x00, 0xC6, 0x33, 0x00, 0x00,
                            0xB7, 0x33, 0x00, 0x00, 0x3A, 0x32, 0x00, 0x00,
                            0x97, 0x31, 0x00, 0x00, 0xC7, 0x31, 0x00, 0x00};
                        memcpy(t_com66, buf3, 32);
                        break;
                    }
                    case 0x0006:
                    {
                        uint8_t buf3[32] = {
                            0xD2, 0x31, 0x00, 0x00, 0x50, 0x33, 0x00, 0x00,
                            0x69, 0x34, 0x00, 0x00, 0xD4, 0x35, 0x00, 0x00,
                            0x99, 0x37, 0x00, 0x00, 0x81, 0x3A, 0x00, 0x00,
                            0x19, 0x3C, 0x00, 0x00, 0x80, 0x3D, 0x00, 0x00};
                        memcpy(t_com66, buf3, 32);
                        break;
                    }
                    case 0x0007:
                    {
                        uint8_t buf3[32] = {
                            0xAA, 0x3D, 0x00, 0x00, 0x58, 0x3D, 0x00, 0x00,
                            0xF4, 0x3C, 0x00, 0x00, 0xFA, 0x3B, 0x00, 0x00,
                            0x86, 0x3B, 0x00, 0x00, 0x6F, 0x3A, 0x00, 0x00,
                            0x30, 0x3A, 0x00, 0x00, 0x55, 0x39, 0x00, 0x00};
                        memcpy(t_com66, buf3, 32);
                        break;
                    }
                    case 0x0008:
                    {
                        uint8_t buf3[32] = {
                            0xD9, 0x38, 0x00, 0x00, 0xDB, 0x37, 0x00, 0x00,
                            0x43, 0x37, 0x00, 0x00, 0x8B, 0x36, 0x00, 0x00,
                            0xC2, 0x35, 0x00, 0x00, 0x43, 0x35, 0x00, 0x00,
                            0x9F, 0x34, 0x00, 0x00, 0x15, 0x34, 0x00, 0x00};
                        memcpy(t_com66, buf3, 32);
                        break;
                    }
                    case 0x0009:
                    {
                        uint8_t buf3[32] = {
                            0x7F, 0x33, 0x00, 0x00, 0xE6, 0x32, 0x00, 0x00,
                            0xA4, 0x32, 0x00, 0x00, 0xBB, 0x31, 0x00, 0x00,
                            0x7E, 0x31, 0x00, 0x00, 0xEA, 0x30, 0x00, 0x00,
                            0x88, 0x31, 0x00, 0x00, 0xFB, 0x34, 0x00, 0x00};
                        memcpy(t_com66, buf3, 32);
                        break;
                    }
                    case 0x000a:
                    {
                        uint8_t buf3[32] = {
                            0x0D, 0x3A, 0x00, 0x00, 0xBB, 0x3F, 0x00, 0x00,
                            0x0F, 0x45, 0x00, 0x00, 0x1A, 0x46, 0x00, 0x00,
                            0x73, 0x44, 0x00, 0x00, 0xD6, 0x42, 0x00, 0x00,
                            0x4B, 0x40, 0x00, 0x00, 0xBA, 0x3E, 0x00, 0x00};
                        memcpy(t_com66, buf3, 32);
                        break;
                    }
                    case 0x000b:
                    {
                        uint8_t buf3[32] = {
                            0xB9, 0x3C, 0x00, 0x00, 0xAA, 0x3A, 0x00, 0x00,
                            0x48, 0x39, 0x00, 0x00, 0x29, 0x37, 0x00, 0x00,
                            0xD7, 0x35, 0x00, 0x00, 0xB7, 0x33, 0x00, 0x00,
                            0x0D, 0x33, 0x00, 0x00, 0x82, 0x31, 0x00, 0x00};
                        memcpy(t_com66, buf3, 32);
                        break;
                    }
                    case 0x000c:
                    {
                        uint8_t buf3[32] = {
                            0x60, 0x30, 0x00, 0x00, 0xA9, 0x2F, 0x00, 0x00,
                            0x79, 0x2E, 0x00, 0x00, 0xB0, 0x2D, 0x00, 0x00,
                            0x13, 0x2C, 0x00, 0x00, 0xCA, 0x2B, 0x00, 0x00,
                            0xE5, 0x2A, 0x00, 0x00, 0x22, 0x2A, 0x00, 0x00};
                        memcpy(t_com66, buf3, 32);
                        break;
                    }
                    case 0x000d:
                    {
                        uint8_t buf3[32] = {
                            0xBB, 0x29, 0x00, 0x00, 0x2F, 0x29, 0x00, 0x00,
                            0xDC, 0x28, 0x00, 0x00, 0x68, 0x28, 0x00, 0x00,
                            0x67, 0x28, 0x00, 0x00, 0x29, 0x28, 0x00, 0x00,
                            0x6F, 0x28, 0x00, 0x00, 0x61, 0x28, 0x00, 0x00};
                        memcpy(t_com66, buf3, 32);
                        break;
                    }
                    case 0x000e:
                    {
                        uint8_t buf3[32] = {
                            0x8F, 0x28, 0x00, 0x00, 0xC7, 0x28, 0x00, 0x00,
                            0xE7, 0x28, 0x00, 0x00, 0x30, 0x29, 0x00, 0x00,
                            0x09, 0x29, 0x00, 0x00, 0xFC, 0x29, 0x00, 0x00,
                            0x22, 0x2A, 0x00, 0x00, 0xC4, 0x2A, 0x00, 0x00};
                        memcpy(t_com66, buf3, 32);
                        break;
                    }
                    case 0x000f:
                    {
                        uint8_t buf3[32] = {
                            0x1D, 0x2B, 0x00, 0x00, 0x4F, 0x2B, 0x00, 0x00,
                            0xE4, 0x2C, 0x00, 0x00, 0x7D, 0x2D, 0x00, 0x00,
                            0xAD, 0x2D, 0x00, 0x00, 0xAD, 0x2D, 0x00, 0x00,
                            0xAD, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
                        memcpy(t_com66, buf3, 32);
                        break;
                    }
                }
                    break;
                
                }
                case 0x73:
                {
                    uint16_t com73 = g_i2cBuffRecv[0] + (g_i2cBuffRecv[1] << 8);
                    switch (com73)
                    {
                    case 0x0004:
                    {
                        uint8_t buf3[32] = {
                            0x5D, 0x42, 0x0E, 0x87, 0x9C, 0x46, 0x03, 0x00,
                            0x6D, 0x3E, 0xE0, 0xD4, 0xFE, 0x22, 0x12, 0x00,
                            0x90, 0x03, 0x6B, 0x01, 0x09, 0x00, 0x00, 0x00,
                            0xD8, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
                        memcpy(t_com74, buf3, 32);
                        break;
                    }
                    case 0x0000:
                    {
                        uint8_t buf3[32] = {
                            0xD3, 0xD6, 0x3A, 0x02, 0x8E, 0x02, 0x73, 0x02,
                            0x8B, 0x0E, 0x00, 0x00, 0x74, 0x11, 0x00, 0x00,
                            0xE3, 0xF3, 0xFF, 0xFF, 0xE7, 0x06, 0x00, 0x00,
                            0x8C, 0x13, 0xAE, 0xFC, 0xC0, 0xC2, 0xF4, 0xFF};
                        memcpy(t_com74, buf3, 32);
                        break;
                    }
                    case 0x0001:
                    {
                        uint8_t buf3[32] = {
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x23, 0x0D, 0x00, 0x00, 0x23, 0x0D, 0x00, 0x00,
                            0x13, 0xB8, 0x6A, 0x0B, 0xCB, 0x9F, 0xA8, 0x0B};
                        memcpy(t_com74, buf3, 32);
                        break;
                    }
                    case 0x0002:
                    {
                        uint8_t buf3[32] = {
                            0x9B, 0x0C, 0x00, 0x00, 0x53, 0xF8, 0x53, 0x02,
                            0x38, 0x41, 0xFD, 0xFF, 0x10, 0x0D, 0x00, 0x00,
                            0x20, 0x06, 0x51, 0x02, 0x1B, 0x24, 0x00, 0x00,
                            0x40, 0x93, 0xEA, 0x0F, 0x64, 0xE2, 0x3A, 0x02};
                        memcpy(t_com74, buf3, 32);
                        break;
                    }
                    case 0x0005:
                    {
                        memset(t_com74, 0, 32);
                        break;
                    }
                    case 0x0006:
                    {
                        uint8_t buf3[32] = {
                            0xD1, 0x03, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
                        memcpy(t_com74, buf3, 32);
                        break;
                    }
                    case 0x0007:
                    {
                        uint8_t buf3[32] = { 0x38, 0xEE, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
                    }
                    case 0x0008:
                    {
                        memset(t_com74, 0, 32);
                        break;
                    }
                    case 0x0009:
                    {
                        memset(t_com74, 0, 32);
                        break;
                    }
                    case 0x000a:
                    {
                        memset(t_com74, 0, 32);
                        break;
                    }
                    case 0x000b:
                    {
                        memset(t_com74, 0, 32);
                        break;
                    }
                    }
                }
                case 0x82:
                {
                    t_com50=0x0001;
                    break;
                }
                case 0xbf:
                {
                    t_combf=g_i2cBuffRecv[0] + (g_i2cBuffRecv[1] << 8);
                    break;
                }
                
                default:
                {
                    break;  
                }
                }
            }
            else
            {
                switch (register_addr)
                {
                case 0x3E:
                {

                    for (nWriteLen = 0; nWriteLen < iic_rx_cnt - 2; nWriteLen++)
                    {
                        *pCMDAddress[0x3E + nWriteLen] = g_i2cBuffRecv[nWriteLen];
                        CRC8_Calc(g_i2cBuffRecv[nWriteLen]);
                    }
                    if (apec == g_i2cBuffRecv[iic_rx_cnt - 2])
                    {
                        if (g_StdCmdData.Field.nAltManufacturerAccess >= 0x4000)
                        {
                            DFUpdate.flag = 1;
                            DFUpdate.DataFlash = 1;
                            g_StdCmdData.Field.nMACDataLen = iic_rx_cnt - 4;
                        }
                        else
                        {
                            writeDFbySubcmd(g_StdCmdData.Field.nAltManufacturerAccess);
                        }
                    }
                    break;
                }
                case 0x45:
                {
                    chargetv = g_i2cBuffRecv[1] + (g_i2cBuffRecv[2] << 8) + (g_i2cBuffRecv[3] << 16) + (g_i2cBuffRecv[4] << 24);
                    break;
                }
                case 0x46:
                {
                    chargetC = g_i2cBuffRecv[1] + (g_i2cBuffRecv[2] << 8) + (g_i2cBuffRecv[3] << 16) + (g_i2cBuffRecv[4] << 24);
                    break;
                }
                case 0x53:
                {
                    
                }
                case 0x61:
                {
                    uint8_t buf4[34] = {0};
                    for (nWriteLen = 0; nWriteLen < iic_rx_cnt - 1; nWriteLen++)
                    {
                        // t_com62Buf[nWriteLen]= g_i2cBuffRecv[nWriteLen];
                        buf4[nWriteLen] = g_i2cBuffRecv[nWriteLen];
                    }
                    IIC_WriteIpa(0x61, buf4);
                    t_com62Flg = 1;
                    break;
                }
                case 0x7e:
                {
                    uint8_t com7e[0x14] = {0x00, 0x76, 0x96, 0x0A, 0x71, 0xFB, 0x44, 0x00, 0xFF, 0x92, 0x90, 0x00, 0xC8, 0xAA, 0x3B, 0x00, 0x00, 0x86, 0x86, 0x0A};
                    memcpy(t_com7e, com7e, sizeof(com7e));
                    break;
                }
                case 0xaa:
                {
                    for (int i = 0; i < 0x04; i++)
                    {
                        t_comaa[i] = g_i2cBuffRecv[i+1];
                    }
                    break;

                }
                case 0xab:
                {
                    for (int i = 0; i < 0x04; i++)
                    {
                        t_comab[i] = g_i2cBuffRecv[i+1];
                    }
                    break;
                }
                case 0xac:
                {
                    
                    for (int i = 0; i < 0x04; i++)
                    {
                        t_comac[i] = g_i2cBuffRecv[i+1];
                    }
                    break;
                }
                case 0xad:
                {
                    
                    for (int i = 0; i < 0x04; i++)
                    {
                        t1_comad[i] = g_i2cBuffRecv[i+1];
                    }
                    break;
                }
                case 0xaf:
                {
            
                    for (int i = 0; i < 0x04; i++)
                    {
                        t1_comaf[i] = g_i2cBuffRecv[i+1];
                    }
                    break;
                }
                case 0xa7:
                {
                    uint8_t i;
                    for(i=0;i<4;i++)
                    {
                        t_coma7[i]=g_i2cBuffRecv[i+1];
                    }
                    break;
                }
                case 0xfa:
                {
                    memcpy(t_comfa,  &g_i2cBuffRecv[1], sizeof(t_comfa));
                    break;
                }
                }
            }
        }
        else
        {
            set_iic_rx_handle_type(IIC_RX_DEBUG_MODE_BIT, ADD_BIT);
        }
        iic_tx_cnt = 0;
        // iic_r涓轰簡block
        ccnt = 0;
        nPos = 0;
    }
    else if (i2c_isr_buffer & I2C_ISR_OVR)
    {
        i2c_interrupt_bit_clear(I2C_ISR_OVR);
        i2c_software_reset();
    }
    else if (i2c_isr_buffer & I2C_ISR_NACKF)
    {
        i2c_flag_clear(I2C_ISR_NACKF);
    }
}
void ReadFlashData(uint16_t Command)
{
    int j;
    int8_t FlashCnt;
    subcmd_datalen = 0;

    if (!f_SS)
    {
        for (FlashCnt = 0; FlashCnt < MAC_DATA_LEN; FlashCnt++)
        {
            if ((DF_FLASH_OFFSET + Command + FlashCnt) > 0xFFFF)
            {
                return;
            }
            g_StdCmdData.Field.nMACData[FlashCnt] = *(volatile uint8_t *)((DF_FLASH_OFFSET + Command) + FlashCnt);
        }
    }
    else
    {
        for (j = 0; j < 32; j++)
        {
            g_StdCmdData.Field.nMACData[j] = 0;
        }
    }
}

void ReadRecordData(uint16_t Command)
{
    int j;
    int8_t FlashCnt;
    subcmd_datalen = 0;

    if (!f_SS)
    {
        for (FlashCnt = 0; FlashCnt < MAC_DATA_LEN; FlashCnt++)
        {
            if ((DF_FLASH_OFFSET + Command + FlashCnt) > 0xFFFF)
            {
                return;
            }
            g_StdCmdData.Field.nMACData[FlashCnt] = ReadRecord[Command - 0x4410 + FlashCnt];
            // g_StdCmdData.Field.nMACData[FlashCnt] =*(volatile uint8_t *)((DF_FLASH_OFFSET +( Command-0x4410)) + FlashCnt)
        }
    }
    else
    {
        for (j = 0; j < 32; j++)
        {
            g_StdCmdData.Field.nMACData[j] = 0;
        }
    }
}

void ReadLifeTimeData(uint16_t Command)
{
    int j;
    int8_t FlashCnt;
    subcmd_datalen = 0;

    if (!f_SS)
    {
        for (FlashCnt = 0; FlashCnt < MAC_DATA_LEN; FlashCnt++)
        {
            if ((DF_FLASH_OFFSET + Command + FlashCnt) > 0xFFFF)
            {
                return;
            }

            g_StdCmdData.Field.nMACData[FlashCnt] = *(volatile uint8_t *)((LifeTimeprt + Command - 0x4800) + FlashCnt);
            //t_com06 = LifeTimeprt;
        }
    }
    else
    {
        for (j = 0; j < 32; j++)
        {
            g_StdCmdData.Field.nMACData[j] = 0;
        }
    }
}

void handle_block_read()
{
    iic_rx_cnt -= 1;
    switch (register_addr)
    {
    case 0x3E:
    {
        if (iic_rx_cnt <= 3) // R
        {

            *pCMDAddress[0x3E] = g_i2cBuffRecv[0];
            *pCMDAddress[0x3F] = g_i2cBuffRecv[1];
            if (g_StdCmdData.Field.nAltManufacturerAccess >= 0x4000 && g_StdCmdData.Field.nAltManufacturerAccess < 0x4400 && g_StdCmdData.Field.nAltManufacturerAccess != 0xF081)
            {
                ReadFlashData(g_StdCmdData.Field.nAltManufacturerAccess);
            }
            else if (g_StdCmdData.Field.nAltManufacturerAccess >= 0x4400 && g_StdCmdData.Field.nAltManufacturerAccess < 0x4800 && g_StdCmdData.Field.nAltManufacturerAccess != 0xF081)
            {
                ReadRecordData(g_StdCmdData.Field.nAltManufacturerAccess);
            }
            else if (g_StdCmdData.Field.nAltManufacturerAccess >= 0x4800 && g_StdCmdData.Field.nAltManufacturerAccess < 0x4c00 && g_StdCmdData.Field.nAltManufacturerAccess != 0xF081)
            {
                ReadLifeTimeData(g_StdCmdData.Field.nAltManufacturerAccess);
            }
            else
            {
                SubCmdProcess(g_StdCmdData.Field.nAltManufacturerAccess);
            }
        }
    }
    break;
    default:

        break;
    }
}

void SubCmdProcess(uint16_t Command)
{
    uint8_t i;
    int j;
    for (j = 0; j < 32; j++)
    {
        g_StdCmdData.Field.nMACData[j] = 0;
    }
    subcmd_datalen = 0;
    /*
    锟斤拷锟铰讹拷锟斤拷指锟斤拷锟叫的匡拷写指锟斤拷锟斤拷胁锟斤拷锟�???
    锟斤拷写锟斤拷指锟斤拷锟斤拷?锟斤拷锟街ｏ拷
    1.W锟斤拷   写锟斤拷指锟斤拷执锟斤拷某一锟街癸拷锟杰ｏ拷锟斤拷式为0x00/0x3e+SUB
    2.R/W   写锟斤拷指锟斤拷锟斤拷锟斤拷荩锟斤拷薷锟斤拷锟街碉拷锟揭伙拷锟街碉拷锟斤拷锟斤拷DF锟斤拷锟斤拷锟斤拷式为0x3E+sub+data+length
    锟斤拷锟皆匡拷锟皆革拷锟斤拷	g_i2cBuffRecv[g_i2cRecvCnt]锟叫碉拷g_i2cRecvCnt锟斤拷锟叫讹拷锟斤拷Data锟斤拷锟饺ｏ拷然锟斤拷直锟斤拷锟�???

    锟斤拷指锟斤拷锟叫的匡拷写指锟斤拷为锟斤拷
    0x0012	Reset							W
    0x0021	Gauging(IT Enable)				W
    0x0022	FastChargeTermCC/CV				W	锟斤拷锟斤拷
    0x0023	LifetimeDataCollection		    W
    ---------------------------------------
    0x0013
    0x0014
    0x0015
    0x0024	ReadorWriteON						w
    0x0025	ReadorWriteOFF						w
    ---------------------------------------
    0x0028	LifetimeDataReset					W
    0x002D	CalibrationMode						W
    0x002E	LifetimeDataFlush					W
    0x002F	LifetimeDataSpeedUp Mode	        W
    0x0030	SealDevice							W
    0x0041	Reset								W
    0x0044	SetDeepSleep						W
    0x0045	ClearDeepSleep						W
    0x0046	PulseGPIO							W
    0x0047	TambientSync						W
    0x0048	ClearGPIO							W
    0x0049	SetDGPIO							W
    ----------------------------------------锟斤拷锟斤拷R/W锟叫碉拷W锟斤拷锟斤拷锟斤拷锟解开锟斤拷锟斤拷
    0x0035	SecurityKeys						R/W
    0x004A	Device Name							R/W
    0x004B	Device Chem							R/W
    0x004C	Manufacturer Name					R/W
    0x004D	Manufacturer Date					R/W
    0x004E	Serial Number						R/W
    0x0070	ManufacturerInfo					R/W
    0x007A	ManufacturerInfoB					R/W
    0x007B	ManufacturerInfoC					R/W
    锟矫诧拷锟斤拷锟斤拷指锟斤拷拇锟斤拷锟矫伙拷锟斤拷锟斤拷疲锟斤拷锟斤拷锟斤拷锟�???
    */
    switch (Command)
    {
    case 0x000E: // new
    {
        if (!f_SS)
        {
            f_lt_erase = ON;
            set_task_event(JUMP_EVENT);
        }
        break;
    }
    case 0x0010: // new    SET_FULLSLEEP
    {
        if (!f_SS)
        {
            f_DPSLEEPM = ON;
        }
        break;
    }
    case 0x0011: // new   SET_HIBERNATE
    {
        if (!f_SS)
        {
            f_HIB_MAC = ON;
        }
        break;
    }
    case 0x0012: // new  SET_HIBERNATE
    {
        if (!f_SS)
        {
            f_HIB_MAC = OFF;
        }
        break;
    }
    case 0x0013: // new   CLEAR_FULLSLEEP
    {
        f_DPSLEEPM = OFF;

        break;
    }
    case 0x0020: // new   SEALED
    {
        f_FAS = 1;
        f_SS = 1;
        f_SEC0 = ON;
        f_SEC1 = ON;
        g_StdCmdData.Field.nAltManufacturerAccess = 0;
        //					  f_FAS1 = 1;
        //            f_SS1 = 1;
        break;
    }
    case 0x0025: // new   DISABLE_LIFETIME
    {
        f_LF = OFF;
        DFUpdate.flag = 1;
        DFUpdate.MFGSC = 1;
        break;
    }
    case 0x0026: // new   ENABLE_LIFETIME
    {
        f_LF = ON;
        DFUpdate.flag = 1;
        DFUpdate.MFGSC = 1;
        break;
    }
    case BLOCK_RESET_DEV: // 0041
    {
        if (!f_SS)
        {
            f_reset_mcu = ON;
            set_task_event(JUMP_EVENT);
        }
        break;
    }
    case 0x0021:
    {
        if (!f_SS)
        {
            f_GAUGE_EN = ~f_GAUGE_EN;
            DFUpdate.flag = 1;
            DFUpdate.MFGSC = 1;
        }
        break;
    }
    case 0x0023:
    {
        if (!f_SS)
        {
            f_LF_EN = ~f_LF_EN;
            DFUpdate.flag = 1;
            DFUpdate.MFGSC = 1;
        }
        break;
    }
    case 0x0024:
    {
        break;
    }
    case 0x0028:
    {
        //			0x0028	LifetimeDataReset					W
        if (!f_SS)
        {
            f_lt_erase = ON;
            set_task_event(JUMP_EVENT);
        }
        break;
    }
    case 0x002D:
    {
        //			0x002D	CalibrationMode						W
        if (!f_SS)
        {
            f_CAL_EN = ~f_CAL_EN;
            // pmu_run_mode = PMU_ACTIVE_MODE;
            // cc_enable_ctrl(ENABLE);
            cc_start_connection();
        }
        break;
    }
    case 0x002E:
    {
        if (!f_SS)
        {
            f_lt_W = ON;
        }
        break;
    }
    case 0x002F:
    {
        if (!f_SS)
        {
            f_LT_TEST = ~f_LT_TEST;
            if (f_LT_TEST)
            {
                LtW_CntW = 0;
            }
        }
        break;
    }
    case 0x0030:
    {
        f_FAS = 1;
        f_SS = 1;
        f_SEC0 = ON;
        f_SEC1 = ON;
        g_StdCmdData.Field.nAltManufacturerAccess = 0;
        break;
    }
    case 0x0044:
    {
        f_DPSLEEPM = 1;
        break;
    }
    case 0x0045:
    {
        f_DPSLEEPM = 0;
        break;
    }
    case 0x0046:
    {
        if (!f_SS)
        {
            f_df_eraseflg = ON;
        }
        break;
    }
    case 0x0047:
    {
        if (!f_SS && f_df_eraseflg)
        {
            f_df_eraseflg = OFF;
            f_df_erase = ON;
            set_task_event(JUMP_EVENT);
        }
        break;
    }
    }

    /*
   锟斤拷锟铰讹拷锟斤拷指锟斤拷锟叫的可讹拷指锟斤拷锟斤拷胁锟斤拷锟�???
   锟斤拷指锟斤拷锟叫的可讹拷指锟斤拷为锟斤拷
   0x0001	Device Type						R
   0x0002	FirmwareVersion				R
   0x0003	HardwareVersion				R
   0x0004	IFChecksum						R
   0x0005	StaticDFSignature锟斤拷锟街讹拷锟斤拷锟铰ｏ拷			R -->df_NVRChecksum
   0x0006	ChemID								R
   0x0007	Prev_MacWrite					R
   0x0008	StaticChemDFSignature	R
   0x0009	AllDFSignature锟斤拷锟街讹拷+锟皆讹拷锟斤拷锟铰ｏ拷				R-->df_CODEChecksum
   0x0017	Qmax Day							R
   0x0035	SecurityKeys					R/W
   0x004A	Device Name						R/W
   0x004B	Device Chem						R/W
   0x004C	Manufacturer Name			R/W
   0x004D	Manufacturer Date			R/W
   0x004E	Serial Number					R/W
   0x0054	OperationStatus				R
   0x0055	ChargingStatus				R
   0x0056	GaugingStatus					R
   0x0057	ManufacturingStatus		R
   0x0060	LifetimeDataBlock1		R
   0x0061	LifetimeDataBlock2		R
   0x0062	LifetimeDataBlock3		R
   0x0063	LifetimeDataBlock4		R
   0x0064	LifetimeDataBlock5		R
   0x0065	LifetimeDataBlock6		R
   0x0066	LifetimeDataBlock7		R
   0x0067	LifetimeDataBlock8		R
   0x0068	LifetimeDataBlock9		R
   0x0069	LifetimeDataBlock10		R
   0x006A	LifetimeDataBlock11		R
   0x006B	LifetimeDataBlock12		R
   0x0070	ManufacturerInfo			R/W
   0x0071	DAStatus1							R
   0x0072	DAStatus2							R
   0x0073	ITStatus1							R
   0x0074	ITStatus2							R
   0x0075	ITStatus3							R
   0x0077	FCC_SOH								R
   0x0078	Filtered Capacity			R
   0x007A	ManufacturerInfoB			R/W
   0x007B	ManufacturerInfoC			R/W
   */
    switch (Command)
    {
    case 0x0000:
    {
        // g_StdCmdData.Field.nMACData[0] = (uint8_t)g_StdCmdData.Field.nCtrlStatus1.data;
        // g_StdCmdData.Field.nMACData[1] = (uint8_t)(g_StdCmdData.Field.nCtrlStatus1.data >> 8);
        subcmd_datalen = 2;
    }
    break;
    case 0x0002:
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)FW_VERSION;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(FW_VERSION >> 8);
        g_StdCmdData.Field.nMACData[2] = (uint8_t)(FW_VERSION >> 16);
        subcmd_datalen = 2;
    }
    break;
    case 0x0003:
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)HW_VERSION;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(HW_VERSION >> 8);
        g_StdCmdData.Field.nMACData[2] = (uint8_t)(HW_VERSION >> 16);
        subcmd_datalen = 2;
    }
    break;
    case 0x0009: // ALL Data Checksum
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)CCGAIN;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(CCGAIN >> 8);
        g_StdCmdData.Field.nMACData[2] = (uint8_t)(CCGAIN >> 16);
        g_StdCmdData.Field.nMACData[3] = (uint8_t)(CCGAIN >> 24);
        // new
        subcmd_datalen = 4;
        break;
    }
    case 0x000A: //
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)CELLGAIN;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(CELLGAIN >> 8);
        subcmd_datalen = 2;
        break;
    }
    case 0x000C: // Del_lrc
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)Del_lrc;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(Del_lrc >> 8);
        g_StdCmdData.Field.nMACData[2] = (uint8_t)(Del_lrc >> 16);
        g_StdCmdData.Field.nMACData[3] = (uint8_t)(Del_lrc >> 24);
        subcmd_datalen = 4;
        break;
    }
    case 0x000D: // Ilrc_w
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)Ilrc_w;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(Ilrc_w >> 8);
        g_StdCmdData.Field.nMACData[2] = (uint8_t)(Ilrc_w >> 16);
        g_StdCmdData.Field.nMACData[3] = (uint8_t)(Ilrc_w >> 24);
        subcmd_datalen = 4;
        break;
    }
    case 0x000E: // Chargefactor
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)Chargefactor;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(Chargefactor >> 8);
        subcmd_datalen = 2;
        break;
    }
    case 0x000F: // Dischargefactor
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)Dischargefactor;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(Dischargefactor >> 8);
        subcmd_datalen = 2;
        break;
    }
    case 0x0017: // LastQMaxUpdataCycle
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)LastQMaxUpdataCycle;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(LastQMaxUpdataCycle >> 8);
        subcmd_datalen = 2;
        break;
    }
    case 0x0035:
    {
        if (!f_SS)
        {
            g_StdCmdData.Field.nMACData[0] = (uint8_t)US_KEY1_SW;
            g_StdCmdData.Field.nMACData[1] = (uint8_t)US_KEY2_SW;
            g_StdCmdData.Field.nMACData[2] = (uint8_t)US_KEY3_SW;
            g_StdCmdData.Field.nMACData[3] = (uint8_t)US_KEY4_SW;
            g_StdCmdData.Field.nMACData[4] = (uint8_t)FA_KEY1_SW;
            g_StdCmdData.Field.nMACData[5] = (uint8_t)FA_KEY2_SW;
            g_StdCmdData.Field.nMACData[6] = (uint8_t)FA_KEY3_SW;
            g_StdCmdData.Field.nMACData[7] = (uint8_t)FA_KEY4_SW;
        }
        break;
    }
    case 0x004A:
    {
        for (i = 0; i < 21; i++)
        {
            g_StdCmdData.Field.nMACData[i] = D_DEVNAME[i + 1];
        }
        subcmd_datalen = 21;
        break;
    }
    case 0x004B:
    {
        for (i = 0; i < 5; i++)
        {
            g_StdCmdData.Field.nMACData[i] = D_DEVCHEM[i + 1];
        }
        subcmd_datalen = 5;
        break;
    }
    case 0x004C: //
    {
        for (i = 0; i < 21; i++)
        {
            g_StdCmdData.Field.nMACData[i] = D_MF_NAME[i + 1];
        }
        subcmd_datalen = 21;
        break;
    }
    case 0x004D:
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)D_MF_DATA;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(D_MF_DATA >> 8);
        subcmd_datalen = 2;
        break;
    }
    case 0x004E:
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)D_SERIES;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(D_SERIES >> 8);
        subcmd_datalen = 2;
        break;
    }
    case 0x0054:
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)OperationStatusA.data;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(OperationStatusA.data >> 8);
        g_StdCmdData.Field.nMACData[2] = (uint8_t)(OperationStatusB.data);
        g_StdCmdData.Field.nMACData[3] = (uint8_t)(OperationStatusB.data >> 8);
        subcmd_datalen = 4;
        break;
    }
    case 0x0055:
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)TempRange.data;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)ChargingStatus.data;
        g_StdCmdData.Field.nMACData[2] = (uint8_t)(ChargingStatus.data >> 8);
        subcmd_datalen = 3;
        break;
    }
    case 0x0056:
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)GaugingStatus.data;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(GaugingStatus.data >> 8);
        g_StdCmdData.Field.nMACData[2] = (uint8_t)(GaugingStatus.data >> 16);
        g_StdCmdData.Field.nMACData[3] = (uint8_t)(GaugingStatus.data >> 24);
        subcmd_datalen = 4;
        break;
    }
    case 0x0057:
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)ManufacturingStatus.data;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(ManufacturingStatus.data >> 8);
        subcmd_datalen = 2;
        break;
    }
    case 0x0060: // lifetime
    {
        g_StdCmdData.Field.nMACData[0] = CellMaxVolt;
        g_StdCmdData.Field.nMACData[1] = CellMaxVolt >> 8;
        g_StdCmdData.Field.nMACData[2] = CellMinVolt;
        g_StdCmdData.Field.nMACData[3] = CellMinVolt >> 8;
        g_StdCmdData.Field.nMACData[4] = ChgMaxCurrent;
        g_StdCmdData.Field.nMACData[5] = ChgMaxCurrent >> 8;
        g_StdCmdData.Field.nMACData[6] = DsgMaxCurrent;
        g_StdCmdData.Field.nMACData[7] = DsgMaxCurrent >> 8;
        g_StdCmdData.Field.nMACData[8] = AvgDsgMaxCurrent;
        g_StdCmdData.Field.nMACData[9] = AvgDsgMaxCurrent >> 8;
        g_StdCmdData.Field.nMACData[10] = AvgDsgMaxPower;
        g_StdCmdData.Field.nMACData[11] = AvgDsgMaxPower >> 8;
        g_StdCmdData.Field.nMACData[12] = CellMaxTemp;
        g_StdCmdData.Field.nMACData[13] = CellMinTemp;
        g_StdCmdData.Field.nMACData[14] = IntMaxTemp;
        g_StdCmdData.Field.nMACData[15] = IntMinTemp;
        subcmd_datalen = 16;
        break;
    }
    case 0x0062: // FW锟斤拷锟斤拷锟斤拷时锟斤拷
    {
        g_StdCmdData.Field.nMACData[0] = FwTotalRunTime;
        g_StdCmdData.Field.nMACData[1] = FwTotalRunTime >> 8;
        g_StdCmdData.Field.nMACData[2] = FwTotalRunTime >> 16;
        g_StdCmdData.Field.nMACData[3] = FwTotalRunTime >> 24;
        subcmd_datalen = 4;
        break;
    }
    case 0x0063:
    {
        g_StdCmdData.Field.nMACData[0] = VailChargeTermCnt;
        g_StdCmdData.Field.nMACData[1] = VailChargeTermCnt >> 8;
        g_StdCmdData.Field.nMACData[2] = LastVailChargeTermCycle;
        g_StdCmdData.Field.nMACData[3] = LastVailChargeTermCycle >> 8;
        g_StdCmdData.Field.nMACData[4] = QMaxUpdataCnt;
        g_StdCmdData.Field.nMACData[5] = QMaxUpdataCnt >> 8;
        g_StdCmdData.Field.nMACData[6] = LastQMaxUpdataCycle;
        g_StdCmdData.Field.nMACData[7] = LastQMaxUpdataCycle >> 8;
        g_StdCmdData.Field.nMACData[8] = LastQMaxUpdataValue;
        g_StdCmdData.Field.nMACData[9] = LastQMaxUpdataValue >> 8;
        g_StdCmdData.Field.nMACData[10] = lterase_cnt;
        g_StdCmdData.Field.nMACData[11] = lterase_cnt >> 8;
        g_StdCmdData.Field.nMACData[12] = ChgMinCurrent;
        g_StdCmdData.Field.nMACData[13] = ChgMinCurrent >> 8;
        g_StdCmdData.Field.nMACData[14] = DsgMinCurrent;
        g_StdCmdData.Field.nMACData[15] = DsgMinCurrent >> 8;
        subcmd_datalen = 16;
        break;
    }
    case 0x0064:
    {
        break;
    }
    case 0x0065:
    {
        subcmd_datalen = 32;
        break;
    }
    case 0x0066:
    {
      
        subcmd_datalen = 32;
        break;
    }
    case 0x0067:
    {
       
        subcmd_datalen = 32;
        break;
    }
    case 0x0068:
    {
       
        subcmd_datalen = 32;
        break;
    }
    case 0x0069:
    {
        
        subcmd_datalen = 32;
        break;
    }
    case 0x006A:
    {
        
        subcmd_datalen = 32;
        break;
    }
    case 0x006B: // 0x65 - 6B SOC - Temp  Runtime
    {
       
        subcmd_datalen = 32;
        break;
    }
    case 0x0070: // BlockA
    {
        for (i = 0; i < 32; i++)
        {
            g_StdCmdData.Field.nMACData[i] = *(volatile uint8_t *)((D_MF_BLOCKA) + i);
        }
        subcmd_datalen = 32;
        break;
    }
    case 0x0071:
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)t_com09;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(t_com09 >> 8);
        g_StdCmdData.Field.nMACData[12] = (uint8_t)t_com0a;
        g_StdCmdData.Field.nMACData[13] = (uint8_t)(t_com0a >> 8);
        g_StdCmdData.Field.nMACData[20] = (uint8_t)CurrentPower; // 实时锟斤拷锟斤拷
        g_StdCmdData.Field.nMACData[21] = (uint8_t)(CurrentPower >> 8);
        //			g_StdCmdData.Field.nMACData[28] = (uint8_t)Power;
        //			g_StdCmdData.Field.nMACData[29] = (uint8_t)(Power>>8);
        g_StdCmdData.Field.nMACData[30] = (uint8_t)t_com1f;
        g_StdCmdData.Field.nMACData[31] = (uint8_t)(t_com1f >> 8);
        subcmd_datalen = 32;
        break;
    }
    case 0x0072:
    {
        g_StdCmdData.Field.nMACData[0] = (uint8_t)t_com75;
        g_StdCmdData.Field.nMACData[1] = (uint8_t)(t_com75 >> 8);
        g_StdCmdData.Field.nMACData[2] = (uint8_t)t_com08;
        g_StdCmdData.Field.nMACData[3] = (uint8_t)(t_com08 >> 8);
        g_StdCmdData.Field.nMACData[4] = (uint8_t)t_com09;
        g_StdCmdData.Field.nMACData[5] = (uint8_t)(t_com09 >> 8);
        g_StdCmdData.Field.nMACData[6] = (uint8_t)t_com0a;
        g_StdCmdData.Field.nMACData[7] = (uint8_t)(t_com0a >> 8);
        subcmd_datalen = 8;
        break;
    }
    case 0x0073:
    {
        break;
    }
    case 0x0074:
    {
        break;
    }
    case 0x0075:
    {
        break;
    }
    case 0x0077:
    {
        break;
    }
    case 0x0078:
    {
        break;
    }
    case 0x007A: // BlockB
    {
        for (i = 0; i < 32; i++)
        {
            g_StdCmdData.Field.nMACData[i] = *(volatile uint8_t *)((D_MF_BLOCKB) + i);
        }
        subcmd_datalen = 32;
        break;
    }
    case 0x007B:
    {
        break;
    }
    case 0x007C:
    {
        // g_StdCmdData.Field.nMACData[0] = RST.Reset_Flag;
        break;
    }
    case 0x00B0: // Status //TempRange Charging Voltage
    {
        if (!f_SS)
        {
            g_StdCmdData.Field.nMACData[0] = (uint8_t)LT_CV;
            g_StdCmdData.Field.nMACData[1] = (uint8_t)(LT_CV >> 8);
            g_StdCmdData.Field.nMACData[2] = (uint8_t)STL_CV;
            g_StdCmdData.Field.nMACData[3] = (uint8_t)(STL_CV >> 8);
            g_StdCmdData.Field.nMACData[4] = (uint8_t)RT_CV;
            g_StdCmdData.Field.nMACData[5] = (uint8_t)(RT_CV >> 8);
            g_StdCmdData.Field.nMACData[6] = (uint8_t)STH_CV;
            g_StdCmdData.Field.nMACData[7] = (uint8_t)(STH_CV >> 8);
            g_StdCmdData.Field.nMACData[8] = (uint8_t)HT_CV;
            g_StdCmdData.Field.nMACData[9] = (uint8_t)(HT_CV >> 8);
            subcmd_datalen = 10;
        }
        break;
    }
    case 0xF081:
    {
        if (f_CAL_EN)
        {
            if (!f_SS)
            {

                g_StdCmdData.Field.nMACData[0] = (uint8_t)t_com0a;
                g_StdCmdData.Field.nMACData[1] = (uint8_t)(t_com0a >> 8);
                g_StdCmdData.Field.nMACData[2] = (uint8_t)(t_com09);
                g_StdCmdData.Field.nMACData[3] = (uint8_t)(t_com09 >> 8);
                g_StdCmdData.Field.nMACData[4] = (uint8_t)(t_com08);
                g_StdCmdData.Field.nMACData[5] = (uint8_t)(t_com08 >> 8);
                g_StdCmdData.Field.nMACData[6] = (uint8_t)(t_com75);
                g_StdCmdData.Field.nMACData[7] = (uint8_t)(t_com75 >> 8);
                subcmd_datalen = 8;
            }
        }
        break;
    }
    default:
        break;
    }
    // g_StdCmdData.nMACDataLength = 2 + subcmd_datalen + 2;
    //  if(subcmd_datalen)
    // {
    // 	*pCMDAddress[0x61] = 2 + subcmd_datalen + 2;
    // 	ChecksumCalculate(*pCMDAddress[0x61]);
    // }
}

void writeDFbySubcmd(uint16_t Command)
{
    // 写指锟筋部锟街ｏ拷锟斤拷锟节革拷锟斤拷锟叫达拷锟斤拷锟斤拷--20220610
    /*
    R/W   写锟斤拷指锟斤拷锟斤拷锟斤拷荩锟斤拷薷锟斤拷锟街碉拷锟揭伙拷锟街碉拷锟斤拷锟斤拷DF锟斤拷锟斤拷锟斤拷式为0x3E+sub+data+length
    0x0035	SecurityKeys							R/W
    0x004A	Device Name								R/W
    0x004B	Device Chem								R/W
    0x004C	Manufacturer Name					R/W
    0x004D	Manufacturer Date					R/W
    0x004E	Serial Number							R/W
    0x0070	ManufacturerInfo					R/W
    0x007A	ManufacturerInfoB					R/W
    0x007B	ManufacturerInfoC					R/W
    锟斤拷锟斤拷RW锟斤拷指锟斤拷锟絎锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟绞碉拷锟�???
    锟斤拷锟斤拷
    0x0000	SHA256锟斤拷证
    */
    switch (Command)
    {
    case 0x000B:
    {

        DFUpdate.FUseTime = 1;
        DFUpdate.flag = 1;
        break;
    }
    // case 0x0035:
    // {
    // 	if(!f_SS)
    // 	{
    // 		DFUpdate.SecKEY =1;
    // 		DFUpdate.flag = 1;
    // 	}
    // 	break;
    // }
    case 0x004A:
    {
        DFUpdate.DeviceName = 1;
        DFUpdate.flag = 1;
        break;
    }
    case 0x004B:
    {
        DFUpdate.DeviceChem = 1;
        DFUpdate.flag = 1;
        break;
    }
    case 0x004C:
    {
        DFUpdate.ManuName = 1;
        DFUpdate.flag = 1;
        break;
    }
    case 0x004D:
    {
        DFUpdate.ManuDate = 1;
        DFUpdate.flag = 1;
        break;
    }
    case 0x004E:
    {
        DFUpdate.SerialNum = 1;
        DFUpdate.flag = 1;
        break;
    }
    case 0x0070:
    {
        DFUpdate.ManuA = 1;
        DFUpdate.flag = 1;
        break;
    }
    case 0x007A:
    {
        DFUpdate.ManuB = 1;
        DFUpdate.flag = 1;
        break;
    }
    case 0x007B:
    {
        break;
    }
        // case 0x00B0:
        // {
        // 	DFUpdate.CVOverride = 1;
        // 	DFUpdate.flag = 1;
        // 	break;
        // }
    }
}
