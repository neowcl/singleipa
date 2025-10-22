#ifndef __BI2CS_INTERFACE_H__
#define __BI2CS_INTERFACE_H__

#include "standard_data_cmd.h"
#include "Cell.h"
#include "Ram.h"
#include "LifeTime.h"


#if   defined (__CC_ARM)
#pragma anon_unions
#endif


#define MAXRECVDATALEN          (256)
#define MAXSENDDATALEN          (256)

#define DATA_CMD_LEN            0xA8

#define MAC_DATA_LEN        32

#define IPA_32     (256*256*2)

//DATA_COMMAND
#define DATA_CMD_CNTL       0x00
#define DATA_CMD_AR         0x02
#define DATA_CMD_ARTTE      0x04
#define DATA_CMD_TEMP       0x06
#define DATA_CMD_VOLT       0x08
#define DATA_CMD_FLAGS      0x0A
#define DATA_CMD_INSTCURR   0x0C
#define DATA_CMD_RM         0x10
#define DATA_CMD_FCC        0x12
#define DATA_CMD_AI         0x14
#define DATA_CMD_TTE        0x16
#define DATA_CMD_TTF        0x18
#define DATA_CMD_MLI        0x1E
#define DATA_CMD_MLTTE      0x20
#define DATA_CMD_AP         0x22
#define DATA_CMD_BTPD       0x24
#define DATA_CMD_BTPC       0x26
#define DATA_CMD_INT_TEMP   0x28
#define DATA_CMD_CYCLE      0x2A
#define DATA_CMD_RSOC       0x2C
#define DATA_CMD_SOH        0x2E
#define DATA_CMD_CV         0x30
#define DATA_CMD_CC         0x32
#define DATA_CMD_TVOL       0x34
#define DATA_CMD_TSU        0x36
#define DATA_CMD_TSL        0x38
#define DATA_CMD_QC         0x3A
#define DATA_CMD_DC         0x3C
#define DATA_CMD_AMA        0x3E
#define DATA_CMD_MACD       0x40
#define DATA_CMD_MACDS      0x60
#define DATA_CMD_MACDL      0x61


extern  uint16_t jiavotage;

typedef union
{
    uint16_t data; 
    struct 
    {
        uint16_t QEN                : 1;
        uint16_t VOK                : 1;
        uint16_t RDIS               : 1;   //阻抗更新
        uint16_t LDMD               : 1;   //0:恒流或 1:恒功率
        uint16_t RSVD1              : 5;
        uint16_t CheckSumValid      : 1;   //低压不能操作Flash
        uint16_t RSVD2              : 3;
        uint16_t FAS                : 1;
        uint16_t SS                 : 1;
        uint16_t NVR                : 1;   //操作FLASH
    }ContorlStatus_Field;
    
} ContorlStatus_Field_T;





typedef union
{
    uint16_t data; 
    struct 
    {
        uint16_t RSVD1                  : 4;
        uint16_t FD                     : 1;
        uint16_t FC                     : 1;
        uint16_t DSG                    : 1;
        uint16_t INIT                   : 1;
        uint16_t RSVD2                  : 1;
        uint16_t RCA                    : 1;   //剩余容量警告
        uint16_t RSVD3                  : 1;
        uint16_t TDA                    : 1;
        uint16_t RSVD4                  : 2;
        uint16_t TCA                    : 1;
        uint16_t RSVD5                  : 1;
    }BatteryStatus_Field;
} BatteryStatus_Field_T;



typedef union
{
    uint8_t data;
    struct 
    {
        uint8_t VOLT_HI             : 1;
        uint8_t VOLT_LO             : 1;
        uint8_t TEMP_HI             : 1;
        uint8_t TEMP_LO             : 1;
        uint8_t SOC_DELTA           : 1;
        uint8_t RSVD1               : 3;
    }InterruptStatus_Field;
} InterruptStatus_Field_T;



typedef struct
{
    uint16_t RSVD1                      : 3;
    uint16_t HIB                        : 1;
    uint16_t HIB_MAC                    : 1;
    uint16_t GPIO_LVL                   : 1;
    uint16_t DP_SLP                     : 1;
    uint16_t BTP_INT                    : 1;
    uint16_t SEC0                        : 1;
    uint16_t SEC1                        : 1;
    uint16_t RSVD2                      : 5;
    uint16_t SLEEP                      : 1;
} OperationStatusA_Field_T;

typedef union 
{
		uint16_t data;    
		OperationStatusA_Field_T nOperationStatus_f;
}nOperationStatusA;
extern nOperationStatusA 			OperationStatusA;
#define t_com72                     OperationStatusA.data
#define f_HIB                       OperationStatusA.nOperationStatus_f.HIB
#define f_HIB_MAC                   OperationStatusA.nOperationStatus_f.HIB_MAC
#define f_GPIO_LVL                  OperationStatusA.nOperationStatus_f.GPIO_LVL
#define f_DP_SLP                    OperationStatusA.nOperationStatus_f.DP_SLP
#define f_BTP_INT                   OperationStatusA.nOperationStatus_f.BTP_INT       //IO 引脚电平输出
#define f_SEC0                      OperationStatusA.nOperationStatus_f.SEC0
#define f_SEC1                      OperationStatusA.nOperationStatus_f.SEC1
#define f_SLEEP                     OperationStatusA.nOperationStatus_f.SLEEP


typedef union 
{
    uint16_t data;    
    struct 
    {
        uint16_t t_com66_DSG                      : 1;
        uint16_t t_com66_SOCF                      : 1;
        uint16_t t_com66_SOC1                     : 1;
        uint16_t t_com66_IMAX_INTR_STAT                      : 1;
        uint16_t t_com66_LOWV                       : 1;
        uint16_t t_com66_CCA_REQ                      : 1;    
        uint16_t t_com66_OT                      : 1;
        uint16_t t_com66_OCVTAKEN                       : 1;
        uint16_t t_com66_OCVTttt                      : 1;
        uint16_t t_com66_FC                      : 1;
        uint16_t t_com66_TC1                     : 1;    
        uint16_t t_com66_TC2                     : 1;
        uint16_t t_com66_CALMODE                     : 1;
        uint16_t t_com66_IMAXOK                     : 1;
        uint16_t t_com66_FASTQ_UP                     : 1;
        uint16_t t_com66_FS_ACT                     : 1;
    }tt_com66_f;
}ut_com66_f;

extern ut_com66_f ut_com66;
#define t_com66_2                     ut_com66.data
#define f_t_com66_DSG                ut_com66.tt_com66_f.t_com66_DSG
#define f_t_com66_SOCF               ut_com66.tt_com66_f.t_com66_SOCF
#define f_t_com66_SOC1               ut_com66.tt_com66_f.t_com66_SOC1
#define f_t_com66_LOWV               ut_com66.tt_com66_f.t_com66_LOWV
#define f_t_com66_OCVTAKEN           ut_com66.tt_com66_f.t_com66_OCVTAKEN
#define f_t_com66_FC                 ut_com66.tt_com66_f.t_com66_FC
#define f_t_com66_IMAXOK             ut_com66.tt_com66_f.t_com66_IMAXOK


typedef struct
{
    uint16_t RSVD1                      : 2;
    uint16_t AUTH                       : 1;
    uint16_t RSVD2                      : 1;
    uint16_t RSVD3                        : 1;
    uint16_t RSVD4                      : 1;
    uint16_t RSVD5                         : 1;
    uint16_t DPSLEEPM                   : 1;
    uint16_t RSVD6                       : 1;
    uint16_t RSVD7                      : 1;
    uint16_t RSVD8                      : 1;
    uint16_t RSVD9                      : 5;
} OperationStatusB_Field_T;
typedef union 
{
		uint16_t data;    
		OperationStatusB_Field_T nOperationStatus_f;
}nOperationStatusB;
extern nOperationStatusB 			OperationStatusB;
#define t_com73           OperationStatusB.data
#define f_AUTH                    OperationStatusB.nOperationStatus_f.AUTH   //SHA256
// #define f_CAL                     OperationStatusB.nOperationStatus_f.CAL    //Cali
// #define f_XL                      OperationStatusB.nOperationStatus_f.XL     //400K
#define f_DPSLEEPM                OperationStatusB.nOperationStatus_f.DPSLEEPM
//#define f_INIT                    OperationStatusB.nOperationStatus_f.INIT
// #define f_SLPAD                   OperationStatusB.nOperationStatus_f.SLPAD  //NOTE

typedef struct
{
    uint8_t UT              : 1;
    uint8_t LT              : 1;
    uint8_t STL             : 1;
    uint8_t RT              : 1;
    uint8_t STH             : 1;
    uint8_t HT              : 1;
    uint8_t OT              : 1;
    uint8_t RSVD1           : 1;
    uint8_t RSVD2           : 8;
} TempRangeStatus_Field_T;
typedef union 
{
		uint16_t data;    
		TempRangeStatus_Field_T nTempRange_f;
}nTempRange;
extern nTempRange TempRange;
#define t_com71    TempRange.data
#define f_UT     TempRange.nTempRange_f.UT
#define f_LT     TempRange.nTempRange_f.LT
#define f_STL    TempRange.nTempRange_f.STL
#define f_RT     TempRange.nTempRange_f.RT
#define f_STH    TempRange.nTempRange_f.STH
#define f_HT     TempRange.nTempRange_f.HT
#define f_OT     TempRange.nTempRange_f.OT

#define	TR_UT   0x01		
#define	TR_LT   0x02
#define	TR_STL  0x04
#define	TR_RT   0x08
#define	TR_STH  0x10
#define	TR_HT   0x20
#define	TR_OT   0x40

typedef struct
{
    uint16_t PV                             : 1;
    uint16_t LV                             : 1;
    uint16_t MV                             : 1;
    uint16_t HV                             : 1;
    uint16_t IN                             : 1;
    uint16_t SU                             : 1;
    uint16_t MCHG                           : 1;
    uint16_t VCT                            : 1;
    uint16_t CV_DGRD                        : 2;
    uint16_t RSVD1                          : 1;
    uint16_t RSVD6                          : 1;
    uint16_t RSVD2                          : 1;
    uint16_t RSVD3                          : 1;
    uint16_t RSVD4                          : 1;
    uint16_t RSVD5                          : 1;
} CHGING_STATUS_T;

typedef union 
{
		uint16_t data;    
		CHGING_STATUS_T nChargingStatus_f;
}nChargingStatus;

extern nChargingStatus 	ChargingStatus;
#define t_com78     ChargingStatus.data
#define  f_PV      ChargingStatus.nChargingStatus_f.PV
#define  f_LV      ChargingStatus.nChargingStatus_f.LV
#define  f_MV      ChargingStatus.nChargingStatus_f.MV
#define  f_HV      ChargingStatus.nChargingStatus_f.HV
#define  f_IN      ChargingStatus.nChargingStatus_f.IN
#define  f_SU      ChargingStatus.nChargingStatus_f.SU
//#define  f_MCHG    ChargingStatus.nChargingStatus_f.MCHG   //满充状态下上报充电电压电流   FCC清除灭
#define  f_VCT     ChargingStatus.nChargingStatus_f.VCT    //满充状态
#define  f_CV_DGRD ChargingStatus.nChargingStatus_f.CV_DGRD//降充电电压功能
//#define  f_NCT     ChargingStatus.nChargingStatus_f.NCT
// #define  f_DGRD1   ChargingStatus.nChargingStatus_f.DGRD1
// #define  f_DGRD2   ChargingStatus.nChargingStatus_f.DGRD2
// #define  f_DGRD3   ChargingStatus.nChargingStatus_f.DGRD3
typedef struct
{
	uint32_t CFET		          : 3;
	uint32_t DFET		          : 1;     
	uint32_t SETC	              : 1;     
	uint32_t SOKC                  : 1;
    uint32_t SCC           	       : 1;
    uint32_t SFC                  : 1;
    uint32_t SMC          	      : 1;     
    uint32_t RSVD                : 23;
	
} newCHARGING_STATUS;//ChargingStatus 0X43

// typedef union
// {
//   uint8_t data[4];
//   uint32_t data32;
//   newCHARGING_STATUS newChargingStatus_f;
// }newChargingStatus;

// extern newChargingStatus newChargingStatu;
// //#define t_com43  newChargingStatu.data32
// #define f_CFET   newChargingStatu.newChargingStatus_f.CFET
// #define f_DFET   newChargingStatu.newChargingStatus_f.DFET
// #define f_SETC   newChargingStatu.newChargingStatus_f.SETC
// #define f_SOKC   newChargingStatu.newChargingStatus_f.SOKC
// #define f_SCC   newChargingStatu.newChargingStatus_f.SCC
// #define f_SFC   newChargingStatu.newChargingStatus_f.SFC
// #define f_SMC   newChargingStatu.newChargingStatus_f.SMC

//GaugingStatus
typedef struct
{
	uint16_t FD		          : 1;
	uint16_t FC		          : 1;     
	uint16_t TD		          : 1;     
	uint16_t TC		          : 1;
    uint16_t RSVD1            : 1;
    uint16_t RSVD2              : 1;
    uint16_t DSG              : 1;     
    uint16_t RESERVED0		  : 9;     
} GAUGING_STATUS_T;
typedef union 
{
		uint16_t data;    
		GAUGING_STATUS_T nGaugingStatus_f;
}nGaugingStatus;
extern nGaugingStatus			GaugingStatus;
//#define t_com7a          GaugingStatus.data
#define f_FD                    GaugingStatus.nGaugingStatus_f.FD
#define f_FC                    GaugingStatus.nGaugingStatus_f.FC
#define f_TD                    GaugingStatus.nGaugingStatus_f.TD
#define f_TC                    GaugingStatus.nGaugingStatus_f.TC
//#define f_EDV                   GaugingStatus.nGaugingStatus_f.EDV  //NOTE
#define f_DSG1                  GaugingStatus.nGaugingStatus_f.DSG



// typedef struct
// {
//     uint32_t FD                             : 1;
//     uint32_t FC                             : 1;
//     uint32_t TD                             : 1;
//     uint32_t TC                             : 1;
//     uint32_t RSVD1                          : 1;
//     uint32_t EDV                            : 1;
//     uint32_t DSG                            : 1;
//     uint32_t RSVD2                          : 1;
//     uint32_t REST                           : 1;
//     uint32_t RSVD3                          : 1;
//     uint32_t RDIS                           : 1;
//     uint32_t VOK                            : 1;
//     uint32_t QEN                            : 1;
//     uint32_t SLPQMax                        : 1;
//     uint32_t OCVPRED                        : 1;
//     uint32_t NSFM                           : 1;
//     uint32_t VDQ                            : 1;
//     uint32_t QMax                           : 1;
//     uint32_t RX                             : 1;
//     uint32_t LDMD                           : 1;
//     uint32_t OCVFR                          : 1;
//     uint32_t QMAXDODOK                      : 1;
//     uint32_t RSVD4                          : 10;
// } GaugingStatus_Field_T;


// typedef union
// {
//     uint16_t data; 
//     struct 
//     {
//         uint16_t QEN                 : 1;
//         uint16_t VOK                 : 1;
//         uint16_t DNR                 : 1;
//         uint16_t LDMD                : 1;   
//         uint16_t SLEEP               : 1;
//         uint16_t FULLSLEEP           : 1;
//         uint16_t HIBERNATE           : 1;
//         uint16_t SHUTDOWN            : 1;
//         uint16_t RSVD1               : 1;   
//         uint16_t QMAXUPDATE          : 1;   
//         uint16_t RSVD2               : 2;
//         uint16_t CALMODE             : 1;   
//         uint16_t FAS                 : 1;
//         uint16_t SS                  : 1;
//         uint16_t RSVD3               : 1;  
//     }ContorlStatus_Field1;
    
// } ContorlStatus_Field_T1;

typedef struct
{
    uint16_t RSVD1                          : 3;
    uint16_t GAUGE_EN                       : 1;
    uint16_t RSVD2                          : 1;
    uint16_t LF_EN                          : 1;  //kpfa2 20240511
    uint16_t RSVD3                          : 8;
    uint16_t LT_TEST                        : 1;
    uint16_t CAL_EN                         : 1;
} ManufacturingStatus_Field_T;
typedef union 
{
		uint16_t data;    
		ManufacturingStatus_Field_T nManufacturingStatus_f;
}nManufacturingStatus;


extern nManufacturingStatus		ManufacturingStatus;
#define t_com7c                 ManufacturingStatus.data
#define f_GAUGE_EN              ManufacturingStatus.nManufacturingStatus_f.GAUGE_EN
#define f_LF_EN                 ManufacturingStatus.nManufacturingStatus_f.LF_EN  // kpfa2 20240511
#define f_LT_TEST               ManufacturingStatus.nManufacturingStatus_f.LT_TEST
#define f_CAL_EN                ManufacturingStatus.nManufacturingStatus_f.CAL_EN



 typedef struct
    {
        //ContorlStatus_Field_T1 nCtrlStatus1;           /* 0X00,0X01 */
        ContorlStatus_Field_T nCtrlStatus;           /* 0X00,0X01 */
        int16_t  nAtRate;                             /* 0X02,0X03 */
        uint16_t  nBatteryMode; 
          uint8_t  nHardwareDeviceID[4];                        /* 0X06,0X07 */
        uint16_t nAtRateTime;                        /* 0X04,0X05 */
        uint16_t Hdq_test;
        int16_t  nTemperature;                        /* 0X06,0X07 */
        int16_t  nVoltage;                            /* 0X08,0X09 */
        BatteryStatus_Field_T nBatteryStatus;        /* 0X0A,0X0B */
        int16_t ntcom0b;                  /*0x0b*/
        int16_t  nCurrent;               /* 0X0C,0X0D */
                /* 0X0E,0X0F REVERSED */
        uint16_t nPackStatus;           /* 0X0E,0X0F REVERSED */
        uint16_t nRemainingCapacity;    /* 0X10,0X11 */
        uint16_t nFullChargeCapacity;   /* 0X12,0X13 */
        int16_t  nAverageCurrent;        /* 0X14,0X15 */
        uint16_t nBatter;  
        uint16_t nCycleCount;         /* 0X2A,0X2B */
        uint16_t nAverageTimeToFull;  /* 0X18,0X19 */
        uint16_t nSBSInfo;
		uint16_t nIdealRcCwh;								 /* 0X1A,0X1B */
        uint16_t nManufactdata;
		uint16_t nIdealFccCwh;								 /* 0X1C,0X1D */
       int16_t  nMaxLoadCurrent;        /* 0X1E,0X1F */
        uint16_t nMaxLoadTimeToEmpty;   /* 0X20,0X21 */
        uint8_t nManufacturerName[21];
        uint8_t nDeviceName[21];        /*0x21*/
        uint8_t  nChemistry[4];         /*0x22*/
        int16_t  nAveragePower;          /* 0X22,0X23 */
        uint16_t nDischargef;
        //uint16_t nBTPDischargeSet;     /* 0X24,0X25 */
        uint16_t nBTPChargeSet;/* 0X26,0X27 */
        uint16_t nInternalTemperature;  /* 0X28,0X29 */
        uint16_t nAverageTimeToEmpty;   /* 0X16,0X17 */
        uint16_t nDegsinVolltage;    /*0x19*/
        int16_t nRelativeStateOfCharge; /* 0X2C,0X2D */
        int16_t nStateOfHealth;         /* 0X2E,0X2F */
        int16_t nChargingVoltage;       /* 0X30,0X31 */
        int16_t nChargingCurrent;       /* 0X32,0X33 */
        uint16_t nTerminateVoltage;    /* 0X34,0X35 */
        uint16_t nTimesTampHi;         /* 0X36~0X37 TimesTampHi */
		uint16_t nTimesTampLo;          /*0X38~0X39 TimesTampLo*/
        uint16_t nQmaxCycle;                 /* 0X3A~0X3B QMax */
        int16_t nDesignCapacity;        /* 0X3C,0X3D */
        uint16_t nAltManufacturerAccess; /* 0X3E,0X3F */
        uint8_t nMACData[MAC_DATA_LEN];  /* 0X40~0X5F */
        uint8_t  PeriodicData[0x18];
        uint8_t   nCHGtatus[4];   /*0x43*/ 
        uint8_t nChipSerialNumber[4];    /*0x4c*/
        uint16_t  FailureAlert[4];/*0x4d*/
        uint8_t  Failure[4];/*0x4e*/  
        uint16_t nTimeStamp;             /*0x40*/
        uint16_t nSmcVoltageTargetLLoop; /*0x45*/
        uint8_t nNotChargingReason[4];/*0x44*/
        uint8_t  nChemicalSOC[4];     /*0x47*/
        uint16_t nt_com50;
        uint8_t nt_com53[0x20];
        int8_t nMACDataSum;             /* 0X60 */
        uint16_t nt_com60;
        int8_t nMACDataLen;             /* 0X61 */
        int16_t  nVoltHiSetThreshold;    /* 0X62,0X63 */
        uint8_t nt_com62Buf[MAC_DATA_LEN];
        uint8_t nt_com63Buf[MAC_DATA_LEN];
        uint8_t nt_com64Buf[MAC_DATA_LEN];
        int16_t nVoltHiClearThreshold;  /* 0X64,0X65 */
        uint16_t nT_com66status;       /*0x65*/
        uint8_t nLegacyDataRdcSteadyState[MAC_DATA_LEN];/*0x66*/
        int16_t nVoltLoSetThreshold;    /* 0X66,0X67 */
        int16_t nVoltLoClearThreshold;  /* 0X68,0X69 */
        int8_t nTempHiSetThreshold;     /* 0X6A */
        int8_t nTempHiClearThreshold;   /* 0X6B */
        int8_t nTempLoSetThreshold;     /* 0X6C */
        int8_t nTempLoClearThreshold;   /* 0X6D */

        uint8_t t_com6e[32];
        InterruptStatus_Field_T nInterruptStatus;        /* 0X6E */
        int8_t nSOCDeltaSetThreshold;   /* 0X6F */
        uint16_t nQmax;                 /* 0X70 0x71*/
        uint16_t nAlgorithmsEnabled;     /*0x70*/
        uint8_t nLifetimeMess[MAC_DATA_LEN];         /*0x74*/
        uint16_t  nReserved5[7];         /* 0X70~0X7F REVERSED */
        uint8_t nSerialNo[0x09];              /*0X74,0X75*/
        uint8_t  nCellID[4];              /*0x77*/
        int16_t nSystemPassedCharge;    /*0x79*/
        uint8_t nt_com7dBuf[4];
        uint8_t nt_com7eBuf[0x14];     
        uint16_t nAccessModeInfo;        /*0x80*/
        uint16_t  nFullyCharged;        /*0x82*/
        uint16_t  nipaQmax;
        uint8_t   nAdcBypassDataCellCurrent[4];  /*0x86*/  
        int16_t  n0Current;             /*0x87*/
        uint8_t  nOCV_V[4];             /*0x8c*/ 
        uint8_t  nPCMSerial[0x12];           /*0x90*/  
        uint8_t  nPACKSerial[18];           /*0x91*/ 
        uint8_t  nPCMManufacturerInfo[MAC_DATA_LEN];   /*0x92*/
        uint8_t  nPACKManufacturerInfo[MAC_DATA_LEN];  /*0x93*/
          uint8_t nPCMAdditionaInfo[MAC_DATA_LEN];         /* 0x94 */
           uint16_t ncom7a;
         uint16_t ncom88;
         uint16_t ncom85;
         uint8_t ncom52[4];
            uint8_t nCell1Seril[0x12];
         uint8_t nCell1Seri2[3];
         uint8_t nCell1Seri3[3];
         uint8_t nCell1Seri4[3];
         uint8_t nCell1Seri5[3];
        uint8_t nResetData[0x12];         /*0x9e*/
        uint16_t nNCC;
        uint8_t DnvdData[0x20];
        uint16_t ntcoma2;               /*0xa2*/
        uint16_t nCycleCountAtQmax;     /*0xA3*/
        uint16_t nAppleBatteryStatus[4];

        uint8_t  ntcoma4[32];
        uint8_t  t_coma6Buf[MAC_DATA_LEN];   /*0xa6*/
        uint8_t  nBootloaderVersion[4];   /*0xa7*/
        uint8_t nADCreading[24];          /*0xa8*/
        uint8_t  nConfigurationsID[4];     /*0xaa*/
        uint8_t nDNVD1ID[4];               /*0xab*/
           uint8_t nDeviceType[4];    /*0xad*/
        uint8_t nDNVD2ID[4];               /*0xac*/
        uint8_t  n_tcomba[0x10];
        uint8_t  n_tcombe[0x20];
        uint8_t nFirmareVerial[4]; /*0xaf*/
        uint16_t nt_comc6;
        uint8_t  n_tcomf6[32];
        uint8_t n_tcomc3[4];
        uint16_t n_tcomc4;
        uint16_t n_tcombf;
        uint8_t n_tcomc5[0x20];
        uint8_t n_comfa[0x0f];
    } nField;

typedef union
{
    uint8_t data[sizeof(nField)];
    nField Field;

} BMS_CMD_DATA_T;

extern BMS_CMD_DATA_T g_StdCmdData;


extern uint16_t	    tabsc;							// Current absolute value
extern int8_t        CellTemp;                      
extern int8_t        IntTemp;

///////////////////////////////////////////////////



#define t_ipaQmax  g_StdCmdData.Field.nipaQmax
#define t_combe  g_StdCmdData.Field.n_tcombe
#define t_comc5  g_StdCmdData.Field.n_tcomc5 
#define t_comfa  g_StdCmdData.Field.n_comfa
#define t_combf  g_StdCmdData.Field.n_tcombf
#define t_comc4  g_StdCmdData.Field.n_tcomc4
#define t_coma4  g_StdCmdData.Field.ntcoma4
#define t_comc3  g_StdCmdData.Field.n_tcomc3
#define t_com06   g_StdCmdData.Field.Hdq_test
#define t_com19    g_StdCmdData.Field.nDegsinVolltage
#define t_coma5    g_StdCmdData.Field.nAppleBatteryStatus
#define t_com03    g_StdCmdData.Field.nBatteryMode
#define t1_com3d    g_StdCmdData.Field.nHardwareDeviceID
#define  t1_com76     g_StdCmdData.Field.nSerialNo
#define t1_comad   g_StdCmdData.Field.nDeviceType
#define t1_comaf   g_StdCmdData.Field.nFirmareVerial
#define t1_com94   g_StdCmdData.Field.nPCMAdditionaInfo
#define t1_com95   g_StdCmdData.Field.nCell1Seril
#define t1_com96   g_StdCmdData.Field.nCell1Seri2
#define t1_com97   g_StdCmdData.Field.nCell1Seri3
#define t1_com98   g_StdCmdData.Field.nCell1Seri4
#define t1_com99   g_StdCmdData.Field.nCell1Seri5
#define t1_com88   g_StdCmdData.Field.ncom88
#define t1_com85   g_StdCmdData.Field.ncom85
#define t1_com52   g_StdCmdData.Field.ncom52
#define t1_com7a   g_StdCmdData.Field.ncom7a

#define t_coma1    g_StdCmdData.Field.DnvdData
#define t_com41    g_StdCmdData.Field.PeriodicData
#define t_com53   g_StdCmdData.Field.nt_com53
#define t_com50   g_StdCmdData.Field.nt_com50
#define t_comf6   g_StdCmdData.Field.n_tcomf6
#define t_comc6   g_StdCmdData.Field.nt_comc6
#define t_comba   g_StdCmdData.Field.n_tcomba
#define t_com6e  g_StdCmdData.Field.t_com6e
#define t_com1a   g_StdCmdData.Field.nSBSInfo
#define t_com65    g_StdCmdData.Field.nT_com66status
#define t_com66    g_StdCmdData.Field.nLegacyDataRdcSteadyState
#define t_com08    g_StdCmdData.Field.nTemperature
#define t_com09    g_StdCmdData.Field.nVoltage
#define t_com0a    g_StdCmdData.Field.nCurrent
#define t_com0b    g_StdCmdData.Field.ntcom0b
#define t_com0f    g_StdCmdData.Field.nRemainingCapacity
#define t_com10    g_StdCmdData.Field.nFullChargeCapacity
#define t_com11    g_StdCmdData.Field.nAverageTimeToEmpty
#define t_com13    g_StdCmdData.Field.nAverageTimeToFull
#define t_com1b    g_StdCmdData.Field.nManufactdata
#define t_com20    g_StdCmdData.Field.nManufacturerName
#define t_com21    g_StdCmdData.Field.nDeviceName
#define t_com22    g_StdCmdData.Field.nChemistry
#define t_com89    g_StdCmdData.Field.nAverageCurrent
#define t_com40    g_StdCmdData.Field.nTimeStamp
#define t_com44    g_StdCmdData.Field.nNotChargingReason
#define t_com45    g_StdCmdData.Field.nSmcVoltageTargetLLoop 
#define t_com74    g_StdCmdData.Field.nLifetimeMess
#define t_coma8    g_StdCmdData.Field.nADCreading
#define t_com47    g_StdCmdData.Field.nChemicalSOC
#define t_com43    g_StdCmdData.Field.nCHGtatus
#define t_com4c    g_StdCmdData.Field.nChipSerialNumber
#define t_com4e    g_StdCmdData.Field.Failure
#define t_com4d    g_StdCmdData.Field.FailureAlert
#define t_com60    g_StdCmdData.Field.nt_com60
#define t_com62    g_StdCmdData.Field.nt_com62Buf
#define t_com63    g_StdCmdData.Field.nt_com63Buf
#define t_com64    g_StdCmdData.Field.nt_com64Buf
#define t_com75    g_StdCmdData.Field.nInternalTemperature
#define t_com77    g_StdCmdData.Field.nCellID
#define g_ChargingVoltage    g_StdCmdData.Field.nChargingVoltage   
#define t_com7d    g_StdCmdData.Field.nt_com7dBuf
#define t_com7e    g_StdCmdData.Field.nt_com7eBuf 
#define t_com8c    g_StdCmdData.Field.nOCV_V
#define t_com87    g_StdCmdData.Field.n0Current
#define t_com9e    g_StdCmdData.Field.nResetData
#define t_com82    g_StdCmdData.Field.nFullyCharged
#define t_com79    g_StdCmdData.Field.nSystemPassedCharge
#define t_com8d    g_StdCmdData.Field.nAccessModeInfo
#define t_com86    g_StdCmdData.Field.nAdcBypassDataCellCurrent
#define t_coma0    g_StdCmdData.Field.nNCC
#define t_com70    g_StdCmdData.Field.nAlgorithmsEnabled
#define t_coma3    g_StdCmdData.Field.nCycleCountAtQmax
#define t_com3f    g_StdCmdData.Field.nMACData
#define t_coma2    g_StdCmdData.Field.ntcoma2
#define t_com90    g_StdCmdData.Field.nPCMSerial
#define t_com91    g_StdCmdData.Field.nPACKSerial
#define t_com92    g_StdCmdData.Field.nPCMManufacturerInfo
#define t_com93    g_StdCmdData.Field.nPACKManufacturerInfo
#define t_coma6    g_StdCmdData.Field.t_coma6Buf
#define t_coma7    g_StdCmdData.Field.nBootloaderVersion
#define t_comaa    g_StdCmdData.Field.nConfigurationsID
#define t_comab    g_StdCmdData.Field.nDNVD1ID
#define t_comac    g_StdCmdData.Field.nDNVD2ID

////////////////////////////////////////////
#define t_com00    g_StdCmdData.Field.nCtrlStatus.data
#define f_QEN      g_StdCmdData.Field.nCtrlStatus.ContorlStatus_Field.QEN
#define f_VOK      g_StdCmdData.Field.nCtrlStatus.ContorlStatus_Field.VOK
#define f_RDIS     g_StdCmdData.Field.nCtrlStatus.ContorlStatus_Field.RDIS
#define f_LDMD     g_StdCmdData.Field.nCtrlStatus.ContorlStatus_Field.LDMD
#define f_CheckSum g_StdCmdData.Field.nCtrlStatus.ContorlStatus_Field.CheckSumValid
#define f_FAS      g_StdCmdData.Field.nCtrlStatus.ContorlStatus_Field.FAS
#define f_SS       g_StdCmdData.Field.nCtrlStatus.ContorlStatus_Field.SS
#define f_NVR       g_StdCmdData.Field.nCtrlStatus.ContorlStatus_Field.NVR

// #define t1_com00					  g_StdCmdData.Field.nCtrlStatus1.data
// #define f_QEN1              g_StdCmdData.Field.nCtrlStatus1.ContorlStatus_Field1.QEN
// #define f_VOK1              g_StdCmdData.Field.nCtrlStatus1.ContorlStatus_Field1.VOK
// #define f_DNR1              g_StdCmdData.Field.nCtrlStatus1.ContorlStatus_Field1.DNR
// #define f_LDMD1             g_StdCmdData.Field.nCtrlStatus1.ContorlStatus_Field1.LDMD
// #define f_SLEEP1            g_StdCmdData.Field.nCtrlStatus1.ContorlStatus_Field1.SLEEP
// #define f_FULLSLEEP1        g_StdCmdData.Field.nCtrlStatus1.ContorlStatus_Field1.FULLSLEEP
// #define f_HIBERNATE1        g_StdCmdData.Field.nCtrlStatus1.ContorlStatus_Field1.HIBERNATE
// #define f_SHUTDOWN1         g_StdCmdData.Field.nCtrlStatus1.ContorlStatus_Field1.SHUTDOWN
// #define f_QMAXUPDATE1       g_StdCmdData.Field.nCtrlStatus1.ContorlStatus_Field1.QMAXUPDATE
// #define f_CALMODE1          g_StdCmdData.Field.nCtrlStatus1.ContorlStatus_Field1.CALMODE
// #define f_FAS1              g_StdCmdData.Field.nCtrlStatus1.ContorlStatus_Field1.FAS
// #define f_SS1               g_StdCmdData.Field.nCtrlStatus1.ContorlStatus_Field1.SS



#define t_com02    g_StdCmdData.Field.nAtRate
#define t_com04    g_StdCmdData.Field.nAtRateTime


//#define t_com03    g_StdCmdData.Field.nBatteryStatus.data
#define f_dsg       g_StdCmdData.Field.nBatteryStatus.BatteryStatus_Field.DSG
#define f_init      g_StdCmdData.Field.nBatteryStatus.BatteryStatus_Field.INIT
#define f_full      g_StdCmdData.Field.nBatteryStatus.BatteryStatus_Field.FC
#define f_fd        g_StdCmdData.Field.nBatteryStatus.BatteryStatus_Field.FD
#define f_rca       g_StdCmdData.Field.nBatteryStatus.BatteryStatus_Field.RCA
#define f_tda       g_StdCmdData.Field.nBatteryStatus.BatteryStatus_Field.TDA
#define f_tca       g_StdCmdData.Field.nBatteryStatus.BatteryStatus_Field.TCA



#define t_com0e    g_StdCmdData.Field.nPackStatus
#define f_cp_h          DEF_BIT0(&t_com0e)      // cph flag
#define f_cp_l          DEF_BIT1(&t_com0e)      // cpl flag
#define f_ccp			DEF_BIT2(&t_com0e)	    // Capacity correction point flag	1=detect, 0=not detect
#define f_relax     	DEF_BIT3(&t_com0e)      // relax                flag 
#define f_charge		DEF_BIT4(&t_com0e)	    // Charging             flag
#define f_discharge		DEF_BIT5(&t_com0e)	    // Discharging          flag
#define f_study_d       DEF_BIT6(&t_com0e)	    // Discharging  study   flag
#define f_study_c       DEF_BIT7(&t_com0e)	    // charging  study      flag
#define f_relearn       DEF_BIT8(&t_com0e)      // study flag
#define f_rcsame        DEF_BIT9(&t_com0e)      // RC same
#define f_fullchg       DEF_BITA(&t_com0e)      // Fullcharge

extern uint8_t  readIPAmes_flag;
extern int32_t tcom89_new;
extern int32_t t_com09_new;
extern int32_t t_com0a_new;
extern int32_t t_com08_new;
extern uint32_t t_com75_new;
extern int32_t t_com8c_new;
extern uint8_t  readIPAmesCnt;

//extern   uint16_t t_com66cnt;

#define t_com16    g_StdCmdData.Field.nBatter
#define t_com23    g_StdCmdData.Field.nIdealRcCwh
#define t_com1c    g_StdCmdData.Field.nIdealFccCwh
#define t_com1e    g_StdCmdData.Field.nMaxLoadCurrent
#define t_com1d    g_StdCmdData.Field.nMaxLoadTimeToEmpty
#define t_com1f    g_StdCmdData.Field.nAveragePower
//#define t_com24    g_StdCmdData.Field.nBTPDischargeSet
//#define t_com26    g_StdCmdData.Field.nBTPChargeSet
#define t_com25   g_StdCmdData.Field.nDischargef

#define t_com17    g_StdCmdData.Field.nCycleCount
#define t_com0d    g_StdCmdData.Field.nRelativeStateOfCharge
#define t_com2e    g_StdCmdData.Field.nStateOfHealth

#define t_com32    g_StdCmdData.Field.nChargingCurrent
#define t_com33    g_StdCmdData.Field.nTerminateVoltage
#define t_com36    g_StdCmdData.Field.nTimesTampHi
#define t_com38    g_StdCmdData.Field.nTimesTampLo
#define t_com3a    g_StdCmdData.Field.nQmaxCycle
#define t_com18    g_StdCmdData.Field.nDesignCapacity
#define t_com2f    g_StdCmdData.Field.nVoltHiSetThreshold
#define t_com30    g_StdCmdData.Field.nVoltHiClearThreshold
#define t_com67    g_StdCmdData.Field.nVoltLoSetThreshold
#define t_com68    g_StdCmdData.Field.nVoltLoClearThreshold
#define t_com6a    g_StdCmdData.Field.nTempHiSetThreshold
#define t_com6b    g_StdCmdData.Field.nTempHiClearThreshold
#define t_com6c    g_StdCmdData.Field.nTempLoSetThreshold
#define t_com6d    g_StdCmdData.Field.nTempLoClearThreshold

#define C_InterruptStatus    g_StdCmdData.Field.nInterruptStatus.data
#define f_VOLT_HI  g_StdCmdData.Field.nInterruptStatus.InterruptStatus_Field.VOLT_HI
#define f_VOLT_LO  g_StdCmdData.Field.nInterruptStatus.InterruptStatus_Field.VOLT_LO
#define f_TEMP_HI  g_StdCmdData.Field.nInterruptStatus.InterruptStatus_Field.TEMP_HI
#define f_TEMP_LO  g_StdCmdData.Field.nInterruptStatus.InterruptStatus_Field.TEMP_LO
#define f_SOC_DELTA g_StdCmdData.Field.nInterruptStatus.InterruptStatus_Field.SOC_DELTA

#define t_com6f    g_StdCmdData.Field.nSOCDeltaSetThreshold
#define t_com84    g_StdCmdData.Field.nQmax





///////////////////////////////////////////////

void bi2cs_dataCmd_init(void);
void bi2cs_dataCmd_Save(void);
void readIPAmessage(void);

void barcode_Init(void);
extern   uint16_t t_com86cnt;



// typedef union
// {
//     uint16_t data;
// 		struct
// 		{
//         uint16_t DSG                  : 1;
//         uint16_t SOCF                 : 1;
//         uint16_t SOC1                 : 1;
//         uint16_t UT                   : 1;
//         uint16_t OT                   : 1;
//         uint16_t ODC                  : 1;
//         uint16_t OCC                  : 1;   
//         uint16_t OCVTAKEN             : 1;
//         uint16_t CHG                  : 1;
//         uint16_t FC                   : 1;
//         uint16_t RSVD                 : 1;
//         uint16_t CHG_INH              : 1;
//         uint16_t BATLOW               : 1;
//         uint16_t BATHI                : 1;
//         uint16_t OTD                  : 1;
//         uint16_t OTC                  : 1;
// 		} FLAG_Field;
// } FLAG_Field_T;


// typedef union
// {
//     uint16_t data; 
//     struct 
//     {
//         uint16_t TEMPS                  : 1;
//         uint16_t RSVD                   : 4;
//         uint16_t SLEEP                  : 1;
//         uint16_t RSVD2                  : 7;
//         uint16_t INTSel                 : 1;   
//         uint16_t INTPol                 : 1;
//         uint16_t RSVD3                  : 1;
//     }Pack_Field;
// } Pack_Field_T;


// typedef union
// {
// 	uint16_t data;
// 	struct
// 	{
// 		uint16_t NORMAL            :1;
// 		uint16_t SLEEP             :1;
// 		uint16_t SHUTDOWN          :1;
// 		uint16_t STANDBY           :1;
// 		uint16_t OCVM              :1;
// 		uint16_t OCVA              :1;
// 		uint16_t LockLevel         :1;
// 		uint16_t Reset             :1;
// 		uint16_t RSVD1             :8;	
// 	}FG_Field;
// }FG_Field_T;

// typedef struct
//     {
//         // ContorlStatus_Field_T1 nCtrlStatus1;           /* 0X00,0X01 */
//         // uint16_t  nBatteryMode;                             /* 0X02,0X03 */
//         // uint16_t nAppleBatteryStatus[4];                        /* 0X04,0X05 */
//         // uint8_t  nHardwareDeviceID[4];                        /* 0X06,0X07 */
//         // uint16_t Hdq_test;
//         //FLAG_Field_T nFLAG;        /* 0X0A,0X0B */
//         uint16_t nRemainingCapacity;    /* 0X10,0X11 */
//         uint16_t nFullChargeCapacity;   /* 0X12,0X13 */
//         int16_t  nAverageCurrent;        /* 0X14,0X15 */
//         uint16_t nAverageTimeToEmpty;   /* 0X16,0X17 */
//         // uint16_t nDegsinVolltage;    /*0x19*/
//         uint16_t nFastQmaxl;    /* 0X18,0X19 */
//         int16_t StandbyCurrent;    /*0X1A,0X1B*/
//         uint16_t nPresentDOD; /*0X1C,0X1D*/
//          uint16_t BTPSOC1Set;     /* 0X24,0X25 */
//          uint16_t BTPSOC1Clear;/* 0X26,0X27 */
//          uint16_t nOCV_Voltage;  /* 0X28,0X29 */ 
//          int16_t nRemainingCapacity1;    /* 0X32,0X33 */
//          uint16_t nPassedCharge;         /* 0X34,0X35 */
//          uint16_t nDOD0;                 /* 0X36~0X37 TimesTampHi */
//          int16_t SelfDsgCurrent;         /*0X38~0X39 */
//          uint16_t nDesignCapacity;       /* 0X3C,0X3D */
//          uint8_t nMACData[MAC_DATA_LEN]; /* 0X40~0X5F */
//          int8_t nMACDataSum;   /* 0X60 */
//          int8_t nMACDataLen;   /* 0X61 */
    
//          uint16_t nTempLoSetThreshold; /* 0X6C,0X6D*/         // 6d
//          FG_Field_T nFGCondition;
//          uint16_t nReserved4;             /* 0X70 0x71*/
//          uint16_t nNominalChargeCapacity; /*0X72,0X73*/
//         //  uint8_t nSerialNo[0x09];              /*0X74,0X75*/
//          uint16_t nAnalogCur;      /*0X7A~0X7B*/
//          uint16_t nAnalogVoltage;  /*0X7A~0X7B*/
//         //  uint16_t ncom7a;
//         //  uint16_t ncom88;
//         //  uint16_t ncom85;
//         //  uint8_t ncom52[4];
//         //  uint8_t nPCMAdditionaInfo[MAC_DATA_LEN];         /* 0x94 */
//         //  uint8_t nCell1Seril[0x11];
//         //  uint8_t nCell1Seri2[3];
//         //  uint8_t nCell1Seri3[3];
//         //  uint8_t nCell1Seri4[3];
//         //  uint8_t nCell1Seri5[3];
//         //  uint8_t nDeviceType[4];    /*0xad*/
//         //  uint8_t nFirmareVerial[4]; /*0xaf*/

//     } nField1;
// typedef union
// {
//     uint8_t data[sizeof(nField1)];
//     nField1 Field;
// } BMS_CMD_DATA_T1;

// extern BMS_CMD_DATA_T1 g_StdCmdData1;

// #define t1_com00					  g_StdCmdData1.Field.nCtrlStatus1.data
// #define f_QEN1              g_StdCmdData1.Field.nCtrlStatus1.ContorlStatus_Field1.QEN
// #define f_VOK1              g_StdCmdData1.Field.nCtrlStatus1.ContorlStatus_Field1.VOK
// #define f_DNR1              g_StdCmdData1.Field.nCtrlStatus1.ContorlStatus_Field1.DNR
// #define f_LDMD1             g_StdCmdData1.Field.nCtrlStatus1.ContorlStatus_Field1.LDMD
// #define f_SLEEP1            g_StdCmdData1.Field.nCtrlStatus1.ContorlStatus_Field1.SLEEP
// #define f_FULLSLEEP1        g_StdCmdData1.Field.nCtrlStatus1.ContorlStatus_Field1.FULLSLEEP
// #define f_HIBERNATE1        g_StdCmdData1.Field.nCtrlStatus1.ContorlStatus_Field1.HIBERNATE
// #define f_SHUTDOWN1         g_StdCmdData1.Field.nCtrlStatus1.ContorlStatus_Field1.SHUTDOWN
// #define f_QMAXUPDATE1       g_StdCmdData1.Field.nCtrlStatus1.ContorlStatus_Field1.QMAXUPDATE
// #define f_CALMODE1          g_StdCmdData1.Field.nCtrlStatus1.ContorlStatus_Field1.CALMODE
// #define f_FAS1              g_StdCmdData1.Field.nCtrlStatus1.ContorlStatus_Field1.FAS
// #define f_SS1               g_StdCmdData1.Field.nCtrlStatus1.ContorlStatus_Field1.SS

/////////////////////////////////////////////////////////////////////////////
// #define t_com06   g_StdCmdData1.Field.Hdq_test
// #define t_com19    g_StdCmdData1.Field.nDegsinVolltage
// #define t_coma5    g_StdCmdData1.Field.nAppleBatteryStatus
// #define t_com03    g_StdCmdData1.Field.nBatteryMode
// #define t1_com3d    g_StdCmdData1.Field.nHardwareDeviceID
// #define  t1_com76     g_StdCmdData1.Field.nSerialNo
// #define t1_comad   g_StdCmdData1.Field.nDeviceType
// #define t1_comaf   g_StdCmdData1.Field.nFirmareVerial
// #define t1_com94   g_StdCmdData1.Field.nPCMAdditionaInfo
// #define t1_com95   g_StdCmdData1.Field.nCell1Seril
// #define t1_com96   g_StdCmdData1.Field.nCell1Seri2
// #define t1_com97   g_StdCmdData1.Field.nCell1Seri3
// #define t1_com98   g_StdCmdData1.Field.nCell1Seri4
// #define t1_com99   g_StdCmdData1.Field.nCell1Seri5
// #define t1_com88   g_StdCmdData1.Field.ncom88
// #define t1_com85   g_StdCmdData1.Field.ncom85
// #define t1_com52   g_StdCmdData1.Field.ncom52
// #define t1_com7a   g_StdCmdData1.Field.ncom7a

/////////////////////////////////////////////////////////////
// #define t_com15    g_StdCmdData1.Field.nFLAG.data
// #define f_DSG2      g_StdCmdData1.Field.nFLAG.FLAG_Field.DSG
// #define f_SOCF1     g_StdCmdData1.Field.nFLAG.FLAG_Field.SOCF
// #define f_SOC1      g_StdCmdData1.Field.nFLAG.FLAG_Field.SOC1
// #define f_UT1       g_StdCmdData1.Field.nFLAG.FLAG_Field.UT
// #define f_OT1       g_StdCmdData1.Field.nFLAG.FLAG_Field.OT
// #define f_ODC1      g_StdCmdData1.Field.nFLAG.FLAG_Field.ODC
// #define f_OCC1      g_StdCmdData1.Field.nFLAG.FLAG_Field.OCC
// #define f_OCVTAKEN1 g_StdCmdData1.Field.nFLAG.FLAG_Field.OCVTAKEN
// #define f_CHG1      g_StdCmdData1.Field.nFLAG.FLAG_Field.CHG
// #define f_FC1       g_StdCmdData1.Field.nFLAG.FLAG_Field.FC
// #define f_CHG_INH1  g_StdCmdData1.Field.nFLAG.FLAG_Field.CHG_INH
// #define f_BATLOW1   g_StdCmdData1.Field.nFLAG.FLAG_Field.BATLOW
// #define f_BATHI1    g_StdCmdData1.Field.nFLAG.FLAG_Field.BATHI
// #define f_OTD1      g_StdCmdData1.Field.nFLAG.FLAG_Field.OTD
// #define f_OTC1      g_StdCmdData1.Field.nFLAG.FLAG_Field.OTC

// #define t1_com1a    g_StdCmdData1.Field.StandbyCurrent
// #define t1_com24    g_StdCmdData1.Field.BTPSOC1Set
// #define t1_com26    g_StdCmdData1.Field.nOCV_Voltage
// #define t1_com38    g_StdCmdData1.Field.SelfDsgCurrent

//#define t1_com3a    g_StdCmdData1.Field.nPackConfig.data
//#define f_temps     g_StdCmdData1.Field.nPackConfig.Pack_Field.TEMPS
//#define f_sleep1    g_StdCmdData1.Field.nPackConfig.Pack_Field.SLEEP
//#define f_intsel    g_StdCmdData1.Field.nPackConfig.Pack_Field.INTSel
//#define f_intpol    g_StdCmdData1.Field.nPackConfig.Pack_Field.INTPol


// #define t1_com62    g_StdCmdData1.Field.DeviceLength

// //#define t1_com6e    g_StdCmdData1.Field.nFGCondition.data
// #define f_normal1   g_StdCmdData1.Field.nFGCondition.FG_Field.NORMAL
// #define f_sleep3    g_StdCmdData1.Field.nFGCondition.FG_Field.SLEEP
// #define f_shutdown1 g_StdCmdData1.Field.nFGCondition.FG_Field.SHUTDOWN
// #define f_standby1  g_StdCmdData1.Field.nFGCondition.FG_Field.STANDBY
// #define f_ocvm1   	g_StdCmdData1.Field.nFGCondition.FG_Field.OCVM
// #define f_ocva1     g_StdCmdData1.Field.nFGCondition.FG_Field.OCVA
// #define f_lock1     g_StdCmdData1.Field.nFGCondition.FG_Field.LockLevel
// #define f_reset1    g_StdCmdData1.Field.nFGCondition.FG_Field.Reset



//#define  t1_com74    g_StdCmdData1.Field.ElapsedTimeMonth

//#define  t1_com78     g_StdCmdData1.Field.ElapsedTimeHour
//void new_dataCmd(void);
extern int16_t t_com09_rep;
extern uint16_t t_com62cnt;
extern int8_t CellTemp_use_rsoc;
/*


在这里定义一些  参数  ，这些参数主要用于上位机首页显示的那些word命令参数

用t1_com,t_com不要动



*/

#endif

