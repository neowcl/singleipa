#ifndef __CELL_H__
#define __CELL_H__

#include "stdint.h"
#include "base_types.h"


typedef struct
{
	uint8_t f_FccUpdateDel	:1;		// bit  0 : 2nd Th using flag
	uint8_t f_CorrectRCL	:1;		// bit  1 : Cell balancing enable
	uint8_t f_DhgRelPoint	:1;		// bit  2 : Calibration 1 point flag
	uint8_t f_initcap		:1;		// bit  3 : InitCap table using flag
	uint8_t f_sysconen		:1;		// bit  4 : SYS-connect using flag
	uint8_t f_DisRelChg		:1;		// bit  5 : Battery Cell Voltage Detection using flag
	uint8_t f_DisRelDhg		:1;		// bit  6 : Temperature Voltage Detection using flag
	uint8_t f_usedfdat		:1;		// bit  7 : Initialize with Flexible data using flag
	uint8_t f_100ToFcc		:1;		// bit  8 : Resreved
	uint8_t f_Cap_uint	    :1;		// bit  9 : Resreved
	uint8_t f_QMaxChgUpdata	:1;		// bit 10 : Resreved
	uint8_t f_QMaxDsgUpdata	:1;		// bit 11 : Resreved
	uint8_t DUMMY12	:1;		// bit 12 : Resreved
	uint8_t DUMMY13	:1;		// bit 13 : Resreved
	uint8_t DUMMY14	:1;		// bit 14 : Resreved
	uint8_t DUMMY15	:1;		// bit 15 : Reserved

}_ST_CTLFLG1;

typedef struct
{
	uint8_t f_dspt	:1;		// bit  0 : Discharge relearning point
							//         (1=CP_H, 0=CP_L)
	uint8_t f_csdis	:1;		// bit  1 : Disable charge relearning
							//         (1=Disable, 0=Enable)
	uint8_t f_dsdis	:1;		// bit  2 : Disable discharge relearning
							//         (1=Disable, 0=Enable)
	uint8_t f_cpldrop	:1;		// bit  3 : Correct RC flag
							//          (1=Use,0=Not use)
	uint8_t f_fccup	:1;		// bit  4 : Fcc update point flag
							//          (0=when detect CP)
							//          (1=when detect charging)
	uint8_t DUMMY5	:1;		// bit  5 : Resreved
	uint8_t DUMMY6	:1;		// bit  6 : Resreved
	uint8_t DUMMY7	:1;		// bit  7 : Resreved
	uint8_t DUMMY8	:1;		// bit  8 : Resreved
	uint8_t DUMMY9	:1;		// bit  9 : Resreved
	uint8_t DUMMY10	:1;		// bit 10 : Resreved
	uint8_t DUMMY11	:1;		// bit 11 : Resreved
	uint8_t DUMMY12	:1;		// bit 12 : Resreved
	uint8_t DUMMY13	:1;		// bit 13 : Reserved
	uint8_t DUMMY14	:1;		// bit 14 : Resreved
	uint8_t DUMMY15	:1;		// bit 15 : Reserved
}_ST_CTLFLG2;
#pragma pack(1)
typedef struct
{

	uint16_t	d_PDVOLT;			//Power Down voltage

	int16_t 	d_SleepCurrent;

	int16_t 	d_DeepSleepCurrent;

	uint8_t 	d_VoltageTime;

	uint8_t 	d_DeepSleepVoltageTime;

	uint8_t 	d_WakeCheckTime;

	uint8_t 	d_AutoTime;
								
	uint16_t	d_THERM_TBL[39];		//Thermistor table
	
	uint16_t	INITV_tbl[21];		//Initial voltage table

	uint16_t	CPH_tbl[20];		//Correction point High Voltage table

	uint16_t	CPL_tbl[20];		//Correction point Low Voltage table

	uint16_t    Qcap_tbl[20];

	int16_t     UpFccTemp_Th;

	uint16_t    d_DeadBand;

	uint16_t	d_0PVOLT;			// 0% voltage

	uint16_t    d_FULLCHG_TV;

	uint16_t    d_FULLCHG_CURR;

	uint16_t	d_FULLCHG_T;

	uint16_t    d_MinFULLCAP;

	uint16_t	d_DCDET;			//Discharge detection current

	uint16_t	d_CCDET;			//Charge detection current

	uint8_t     d_DRELAXJT;

	uint8_t     d_CRELAXJT;

	uint16_t	d_RLSTPT;			//Relearn stop time [hour]

	uint8_t	    d_CP_H;				//Correction point(H) [%]

	uint8_t	    d_CP_L;				//Correction point(L) [%]

	uint8_t	    d_CPHCOE;			//CPH Coefficient

	uint8_t	    d_CPLCOE;			//CPL Coefficient

	uint8_t     d_FCCCOE;           //FCC Coefficient

	uint8_t	    d_CRATE_tbl[4];		//CP table C-rate [0.01C]

	int8_t	    d_TRATE_tbl[5];		//CP table T-rate [-128degC]

	uint16_t	INREG_cycle[6];		//cycle count for Internal impedance table

	uint8_t	    INREG_tbl[6];		//Internal impedance table

	uint16_t    INREG_fcc[6];	

		//SUBCLASS27---FC(len=6)
	int16_t 	d_FCSetVoltageThreshold;

	int16_t 	d_FCClearVoltageThreshold;

	uint8_t 	d_FCSetRSOCThreshold;

	uint8_t 	d_FCClearRSOCThreshold;

//SUBCLASS28---FD(len=6)
	int16_t 	d_FDSetVoltageThreshold;

	int16_t 	d_FDClearVoltageThreshold;

	uint8_t 	d_FDSetRSOCThreshold;

	uint8_t 	d_FDClearRSOCThreshold;

//SUBCLASS34---TC(len=6)
	int16_t 	d_TCSetVoltageThreshold;

	int16_t 	d_TCClearVoltageThreshold;

	uint8_t 	d_TCSetRSOCThreshold;

	uint8_t 	d_TCClearRSOCThreshold;

//SUBCLASS35---TD(len=6)
	int16_t 	d_TDSetVoltageThreshold;

	int16_t 	d_TDClearVoltageThreshold;

	uint8_t 	d_TDSetRSOCThreshold;

	uint8_t 	d_TDClearRSOCThreshold;


	uint16_t	d_DesCap;			//DesignCapacity [mAh]

	uint16_t	d_DesVolt;         //Des voltage

	uint16_t    d_ChargeVoltageInit;

	uint16_t	d_NORMAL_CV;		// Charging voltage
								
	uint16_t	d_NORMAL_CC;		//Charging current

	

	int8_t 		d_JT1;              //JT1

	int8_t 		d_JT2;				//JT2

	int8_t 		d_JT5;				//JT5

	int8_t 		d_JT6;				//JT6

	int8_t 		d_JT3;				//JT3

	int8_t 		d_JT4;				//JT4

	int8_t 		d_HysTemp;			//HysTemp

////SUBCLASS7---IR Correction(len=1)
//	INT8U 	df_AveragingInterval;


//SUBCLASS8---Low TempCharging(len=8)
	int16_t 	d_LowTempChargingVoltage;
	int16_t 	d_LTCurrentLow;
	int16_t 	d_LTCurrentMed;
	int16_t 	d_LTCurrentHigh;

//SUBCLASS14---Standard TempLow Charging(len=8)
	int16_t 	d_StandardTempLowChargingVoltage;
	int16_t 	d_STLCurrentLow;
	int16_t 	d_STLCurrentMed;
	int16_t 	d_STLCurrentHigh;

//SUBCLASS11---Rec TempCharging(len=8)
	int16_t 	d_RecTempChargingVoltage;
	int16_t 	d_RTCurrentLow;
	int16_t 	d_RTCurrentMed;
	int16_t 	d_RTCurrentHigh;

//SUBCLASS13---Standard TempHigh Charging(len=8)
	int16_t 	d_StandardTempHighChargingVoltage;
	int16_t 	d_STHCurrentLow;
	int16_t 	d_STHCurrentMed;
	int16_t 	d_STHCurrentHigh;

//SUBCLASS6---High TempCharging(len=8)
	int16_t 	d_HighTempChargingVoltage;
	int16_t 	d_HTCurrentLow;
	int16_t 	d_HTCurrentMed;
	int16_t 	d_HTCurrentHigh;

//SUBCLASS9---MaintenanceCharging(len=2)
	int16_t 	d_MaintenanceChargingCurrent;

//SUBCLASS10---Pre-Charging(len=2)
	int16_t 	d_Pre_ChargingCurrent;

	//SUBCLASS17---Voltage Range(len=9)
	uint16_t 	d_PrechargeStartVoltage;

	uint16_t 	d_CVLow;

	uint16_t 	d_CVMed;

	uint16_t 	d_CVHigh;

	uint8_t 	d_CVHys;

	uint16_t     d_HighVolt;

	int8_t       d_HighTemp;

	uint16_t     d_DegradeStartCycleCnt;

	uint16_t      d_DegradeCycleCnt1;

	uint8_t       d_DegradeSOH1;

	uint16_t      d_DegradeRuntime1;

	uint16_t      d_DegradeHighTV1;

	uint16_t      d_DegradeCV1;

	uint16_t      d_DegradeCC1;

	uint16_t      d_DegradeCycleCnt2;

	uint8_t       d_DegradeSOH2;

	uint16_t      d_DegradeRuntime2;

	uint16_t      d_DegradeHighTV2;

	uint16_t      d_DegradeCV2;

	uint16_t      d_DegradeCC2;

	uint16_t      d_DegradeCycleCnt3;

	uint8_t       d_DegradeSOH3;

	uint16_t      d_DegradeRuntime3;

	uint16_t      d_DegradeHighTV3;

	uint16_t      d_DegradeCV3;

	uint16_t      d_DegradeCC3;

	uint16_t      d_R_Bmu;

	uint16_t      d_R_System;

	int8_t        d_CsTemp_Th;

	uint16_t      d_CsVolt_Th;

	uint16_t      d_CsTime_IntVal;

	uint16_t      d_CsVolt_Delta;

	uint16_t      d_CS_MinCV;
	
	
	
	uint16_t      d_FSChargeCC1;

	uint16_t      d_FSChargeCV2;
	
	uint16_t      d_FSChargeCC2;

	uint16_t      d_FSChargeCV3;
	
	uint16_t      d_FSChargeCC3;
	
	uint16_t      d_CCStepDelta;
	
	uint16_t      d_CCStepDown;
	
	uint16_t      d_CCStepDelay;
	
	uint16_t      d_MinStepCC;

	// _ST_CTLFLG1	d_CTLFLG1;		    //Control flag 1

	// _ST_CTLFLG2	d_CTLFLG2;		    // Control flag 2

	uint16_t	d_CTLFLG1;		    //Control flag 1

	uint16_t	d_CTLFLG2;		    // Control flag 2

	uint8_t 	d_I2CConfiguration;

	uint8_t 	d_AuthConfig;

	uint8_t 	d_PowerConfig;

	uint8_t 	d_IOConfig;

	uint16_t 	d_SOCFlagConfigA;

	uint8_t     d_SOCFlagConfigB;

	uint16_t 	d_DAConfiguration;

	uint16_t 	d_ChargingConfiguration;

	uint16_t 	d_LifetimesConfiguration;
	
	uint8_t	    d_INIT_RSOC;		//Initial RelativeStateOfCharge
	
	uint16_t   d_INITMAXLOADCUR;

	int8_t	    d_CCCPER;			//CycleCount couting percent [%]

	uint8_t	    d_RCCMIN;			//Minimum Current of capacity calculation [mA]

	uint8_t	    d_DLOGC;			//Consumption current of discharge circuit [100 uA]

	uint8_t	    d_REKKA;			//Deterioration capacity [10uA]

	uint16_t	d_RCLMT;			//FCC variance limit [mV]

	int8_t	    d_STUDYT;			//Relearning temp. limit [degC]

	uint8_t    VarSoc;                // [1byte] Varition SOC

	uint8_t    TempLimit_L;           // [1byte] Temp Low Limit

	uint8_t    TempLimit_H;           // [1byte] Temp High Limit

	uint8_t    C_Rate_L;              // [1byte] C Rate Low Limit

	uint8_t    C_Rate_H; 			   // [1byte] C Rate High Limit

	uint8_t    SOC_L;                 // [1byte] SOC Low Limit

	uint8_t    SOC_H; 				   // [1byte] SOC High Limit

	uint8_t    CycleLimt;             // [1byte] Cycle Limit

	int16_t 	d_InitDischargeSet;

	int16_t 	d_InitChargeSet;

	uint8_t 	d_InitDischargeSetRSOC;

	uint8_t 	d_InitChargeSetRSOC;

	uint8_t 	d_TimeRSOCThresholdA;

	uint8_t 	d_TimeRSOCThresholdB;

	uint8_t 	d_TimeRSOCThresholdC;

	uint8_t 	d_TimeRSOCThresholdD;

	uint8_t 	d_TimeRSOCThresholdE;

	uint8_t 	d_TimeRSOCThresholdF;

	uint8_t 	d_TimeRSOCThresholdG;
	
	uint16_t 	d_SOCFSetThreshold;

	uint16_t 	d_SOCFClearThreshold;

	uint16_t 	d_SOC1SetThreshold;

	uint16_t 	d_SOC1ClearThreshold;

	int16_t     d_ODCDetection;

	int16_t		d_ODCRecovery;

	uint8_t 	d_ODCDelay;

	int16_t 	d_OCCDetection;

	int16_t 	d_OCCRecovery;

	uint8_t 	d_OCCDelay;

	uint16_t 	d_BATLOWDetection;

	uint16_t 	d_BATLOWRecovery;

	uint8_t 	d_BATLOWDelay;

	uint16_t 	d_BATHIDetection;

	uint16_t 	d_BATHIRecovery;

	uint8_t 	d_BAITHIDelay;

	int16_t 	d_DsgCurrent;

	int16_t 	d_ChgCurrent;

	int16_t 	d_OTCDetection;

	int16_t 	d_OTCRecovery;

	uint8_t 	d_OTCDelay;

	int16_t		d_OTDDetection;

	int16_t		d_OTDRecovery;

	uint8_t 	d_OTDDelay;
	
	int16_t 	d_InitVoltageHighSet;

	int16_t 	d_InitVoltageHighClear;

	int16_t 	d_InitVoltageLowSet;

	int16_t 	d_InitVoltageLowClear;

	int8_t 		d_InitTemperatureHighSet;

	int8_t 		d_InitTemperatureHighClear;

	int8_t 		d_InitTemperatureLowSet;

	int8_t 		d_InitTemperatureLowClear;

	uint8_t 	d_SOCDelta;

	uint8_t 	d_GPIOPulseWidth;

	uint16_t 	d_MfgStatusinit;

	uint16_t    d_CellGain;         // Calibration Voltage Gain

	uint16_t    d_CCGain;           // CC Gain
	int16_t    d_CCoffset; // CC offset
	
	int16_t     d_CellTempOffset;
	
	int16_t     d_IntTempOffset;

	uint16_t 	d_ManufactureDate;

	uint16_t 	d_SerialNumber;

	uint8_t 	d_ManufacturerName[21];

	uint8_t 	d_DeviceName[21];

	uint8_t 	d_DeviceChemistry[5];

	uint8_t 	d_ManufacturerInfoBlockA[32];

	uint8_t 	d_ManufacturerInfoBlockB[32];
	

	uint16_t 	d_StaticDFSignature;

	uint16_t 	d_DynamicDFSignature;

	uint8_t    d_US_KEY1_SW;

	uint8_t    d_US_KEY2_SW;

	uint8_t    d_US_KEY3_SW;

	uint8_t    d_US_KEY4_SW;

	uint8_t    d_FA_KEY1_SW;

	uint8_t    d_FA_KEY2_SW;

	uint8_t    d_FA_KEY3_SW;

	uint8_t d_FA_KEY4_SW;
	uint16_t d_fccMaxlimit;
	uint16_t d_fccMinlimit;
	uint16_t d_currentlimit;
	uint16_t d_currentlimittime;
	uint16_t d_pinghua_chgvol_thresh;
	uint16_t d_pinghua_chgcur_low;
	uint16_t d_pinghua_chgcur_high;
	uint16_t d_pinghua_time;
	uint16_t d_pinghua_cur_range;
	uint16_t d_pinghua_cap;

	int16_t d_spl_Tmep;

	uint8_t ipa_com53[0x20];
	uint8_t ipa_com76[0x09];
	uint8_t ipa_com77[0x04];
	uint8_t ipa_comaa[4];
	uint8_t ipa_comab[4];
	uint8_t ipa_comac[4];
	uint8_t ipa_comad[4];
	uint8_t ipa_comaf[4];
	uint8_t ipa_comba[0x10];
	uint8_t ipa_com3e[0x0c];
	uint8_t ipa_com3f[0x0c];
	
	uint8_t d_dsg_pinghua_mul;
	uint8_t d_dsg_pinghua_div;

	uint16_t d_0PVOLT5_Tempera_10 ;
	uint16_t d_0PVOLT_Tempera_less_than_5;
	uint16_t d_IPA_ManufactureDate;

} _ST_FIXED_DATA;
#pragma pack()

//#define   u_fd   (uint8_t *)DATA_FLASH_START_ADDRESS
//extern   _ST_FIXED_DATA  *u_fd_rom;
#define         DATA_FLASH_START_ADDRESS 	0xE400
extern  const _ST_FIXED_DATA  u_fd_rom;

#define	D_PDVOLT		u_fd_rom.d_PDVOLT		// [2byte] Power Down voltage
#define	D_SLPCURR		u_fd_rom.d_SleepCurrent// [2byte] Sleep Current
#define D_DSLPCURR      u_fd_rom.d_DeepSleepCurrent   // [2byte] Deep Sleep Current 
#define D_VOLTTIME      u_fd_rom.d_VoltageTime //[2byte]
#define D_DSLPVOLTTIME  u_fd_rom.d_DeepSleepVoltageTime
#define D_WAKECHECKTIME u_fd_rom.d_WakeCheckTime
#define D_AUTOTIME      u_fd_rom.d_AutoTime
#define	THERM_TBL		u_fd_rom.d_THERM_TBL	// [16byte] Thermistor table
//#define	ttempidx		u_fd_rom.d_ttempidx		// [16byte] Thermistor characteristic temperature index table

#define OCV_SOC			u_fd_rom.INITV_tbl				// [12byte] Initial voltage table

#define	CPH_TBL			u_fd_rom.CPH_tbl				// [40byte] Correction point High Voltage table
#define	CPL_TBL			u_fd_rom.CPL_tbl				// [40byte] Correction point Low Voltage table
#define QCAP_TBL		u_fd_rom.Qcap_tbl				// [40byte] FCC Correction point
#define UPFCTEMP_TH     u_fd_rom.UpFccTemp_Th			// [2byte]
#define D_DEADBAND		u_fd_rom.d_DeadBand
#define	D_0PVOLT		u_fd_rom.d_0PVOLT		// [2byte] 0% voltage

#define	FULLCHG_TV		u_fd_rom.d_FULLCHG_TV	// [2byte] Fullcharge taper voltage
#define	FULLCHG_CURR	u_fd_rom.d_FULLCHG_CURR // [2byte] Fullcharge judgement current
#define	FULLCHG_T		u_fd_rom.d_FULLCHG_T	// [2byte] Fullcharge judgement time
#define D_MINFULLCAP    u_fd_rom.d_MinFULLCAP // [2byte]

#define	D_DCDET			u_fd_rom.d_DCDET		// [2byte] Discharge detection current
#define	D_CCDET			u_fd_rom.d_CCDET		// [2byte] Charge detection current
#define D_DRELAXJT      u_fd_rom.d_DRELAXJT             // [2byte] discharge Relax detection current time
#define D_CRELAXJT     	u_fd_rom.d_CRELAXJT             // [2byte] charge  relax detection time
// Capacity correction
#define D_RLSTPT		u_fd_rom.d_RLSTPT				// [2byte] Relearn stop time [hour]
#define	D_CP_H			u_fd_rom.d_CP_H				// [1byte] Correction point(H) [%]
#define	D_CP_L			u_fd_rom.d_CP_L				// [1byte] Correction point(L) [%]
#define	D_CPHCOE		u_fd_rom.d_CPHCOE				// [1byte] CP1 Coefficient
#define	D_CPLCOE		u_fd_rom.d_CPLCOE				// [1byte] CP2 Coefficient
#define D_FCCCOE        u_fd_rom.d_FCCCOE				// [1byte]  FCC Coefficient
#define	D_CRATE_TBL		u_fd_rom.d_CRATE_tbl			// [4byte] CP table C-rate [0.01C]
#define	D_TRATE_TBL		u_fd_rom.d_TRATE_tbl			// [5byte] CP table T-rate [-128degC]

#define	INREG_CYCLE		u_fd_rom.INREG_cycle			// [12byte] Internal impedance table
#define	INREG_TBL		u_fd_rom.INREG_tbl				// [6byte] Internal impedance table
#define INREG_FCC       u_fd_rom.INREG_fcc				// [12byte] FCC mpedance table
#define D_FCVOLTTHR  	u_fd_rom.d_FCSetVoltageThreshold
#define D_FCCLVOLTTHR	u_fd_rom.d_FCClearVoltageThreshold
#define D_FCRSOCTHR		u_fd_rom.d_FCSetRSOCThreshold
#define D_FCCLRSOCTHR   u_fd_rom.d_FCClearRSOCThreshold
#define D_FDVOLTTHR     u_fd_rom.d_FDSetVoltageThreshold
#define D_FDCLVOLTTHR   u_fd_rom.d_FDClearVoltageThreshold
#define D_FDRSOCTHR     u_fd_rom.d_FDSetRSOCThreshold
#define D_FDCLRSOCTHR   u_fd_rom.d_FDClearRSOCThreshold
#define D_TCVOLTTHR     u_fd_rom.d_TCSetVoltageThreshold
#define D_TCCLVOLTTHR   u_fd_rom.d_TCClearVoltageThreshold
#define D_TCRSOCTHR     u_fd_rom.d_TCSetRSOCThreshold
#define D_TCCLRSOCTHR   u_fd_rom.d_TCClearRSOCThreshold
#define D_TDVOLTTHR     u_fd_rom.d_TDSetVoltageThreshold
#define D_TDCLVOLTTHR   u_fd_rom.d_TDClearVoltageThreshold
#define D_TDRSOCTHR     u_fd_rom.d_TDSetRSOCThreshold
#define D_TDCLRSOCTHR   u_fd_rom.d_TDClearRSOCThreshold
#define	D_DCAP			u_fd_rom.d_DesCap				// [2byte] 0x18:DesignCapacity [mAh]
#define D_DVOLT         u_fd_rom.d_DesVolt             // [2byte] Design Voltage
#define D_INITVOLTAGEINIT u_fd_rom.d_ChargeVoltageInit // [2byte] Initial charging voltage

#define	INIT_FCC		u_fd_rom.d_NORMAL_CV	// [2byte] Charging voltage
#define	INIT_IDRFCC		u_fd_rom.d_NORMAL_CC	// [2byte] Charging current


#define D_JT1           u_fd_rom.d_JT1					// [1byte] 
#define D_JT2           u_fd_rom.d_JT2
#define D_JT5           u_fd_rom.d_JT5
#define D_JT6           u_fd_rom.d_JT6
#define D_JT3           u_fd_rom.d_JT3
#define D_JT4           u_fd_rom.d_JT4
#define D_HYSTEMP       u_fd_rom.d_HysTemp

#define LT_CV			u_fd_rom.d_LowTempChargingVoltage
#define LT_CCL          u_fd_rom.d_LTCurrentLow
#define LT_CCM          u_fd_rom.d_LTCurrentMed
#define LT_CCH          u_fd_rom.d_LTCurrentHigh

#define STL_CV			u_fd_rom.d_StandardTempLowChargingVoltage
#define STL_CCL         u_fd_rom.d_STLCurrentLow
#define STL_CCM         u_fd_rom.d_STLCurrentMed
#define STL_CCH         u_fd_rom.d_STLCurrentHigh

#define RT_CV			u_fd_rom.d_RecTempChargingVoltage
#define RT_CCL          u_fd_rom.d_RTCurrentLow
#define RT_CCM          u_fd_rom.d_RTCurrentMed
#define RT_CCH          u_fd_rom.d_RTCurrentHigh

#define STH_CV			u_fd_rom.d_StandardTempHighChargingVoltage
#define STH_CCL         u_fd_rom.d_STHCurrentLow
#define STH_CCM         u_fd_rom.d_STHCurrentMed
#define STH_CCH         u_fd_rom.d_STHCurrentHigh

#define HT_CV			u_fd_rom.d_HighTempChargingVoltage
#define HT_CCL          u_fd_rom.d_HTCurrentLow
#define HT_CCM          u_fd_rom.d_HTCurrentMed
#define HT_CCH          u_fd_rom.d_HTCurrentHigh

#define MCHG_CC    		u_fd_rom.d_MaintenanceChargingCurrent
#define PRE_CC          u_fd_rom.d_Pre_ChargingCurrent

#define D_PRESVOLT 		u_fd_rom.d_PrechargeStartVoltage
#define D_CVLOW         u_fd_rom.d_CVLow
#define D_CVMED 		u_fd_rom.d_CVMed
#define D_CVHIGH        u_fd_rom.d_CVHigh
#define D_CVHYS         u_fd_rom.d_CVHys

#define D_HIGHVOLT      u_fd_rom.d_HighVolt
#define D_HIGHTEMP      u_fd_rom.d_HighTemp

#define D_DGSTARTCYCLECNT 	u_fd_rom.d_DegradeStartCycleCnt
// #define D_DGSOH 		u_fd_rom.d_DegradeSOH
// #define D_DGRUNTIME     u_fd_rom.d_DegradeRuntime
// #define D_DGHIGH_TV     u_fd_rom.d_DegradeHighTV

#define D_DGCYCLECNT1 	u_fd_rom.d_DegradeCycleCnt1
#define D_DGSOH1 		u_fd_rom.d_DegradeSOH1
#define D_DGRUNTIME1    u_fd_rom.d_DegradeRuntime1
#define D_DGHIGH_TV1    u_fd_rom.d_DegradeHighTV1
#define D_DG_CV1        u_fd_rom.d_DegradeCV1
#define D_DG_CC1        u_fd_rom.d_DegradeCC1

#define D_DGCYCLECNT2 	u_fd_rom.d_DegradeCycleCnt2
#define D_DGSOH2 		u_fd_rom.d_DegradeSOH2
#define D_DGRUNTIME2    u_fd_rom.d_DegradeRuntime2
#define D_DGHIGH_TV2    u_fd_rom.d_DegradeHighTV2
#define D_DG_CV2        u_fd_rom.d_DegradeCV2
#define D_DG_CC2        u_fd_rom.d_DegradeCC2

#define D_DGCYCLECNT3 	u_fd_rom.d_DegradeCycleCnt3
#define D_DGSOH3 		u_fd_rom.d_DegradeSOH3
#define D_DGRUNTIME3    u_fd_rom.d_DegradeRuntime3
#define D_DGHIGH_TV3    u_fd_rom.d_DegradeHighTV3
#define D_DG_CV3        u_fd_rom.d_DegradeCV3
#define D_DG_CC3        u_fd_rom.d_DegradeCC3

#define D_R_BMU         u_fd_rom.d_R_Bmu
#define D_R_SYSTEM      u_fd_rom.d_R_System

#define D_CSTEMP_TH		u_fd_rom.d_CsTemp_Th
#define D_CSVOLT_TH     u_fd_rom.d_CsVolt_Th
#define D_CSTIME_InV    u_fd_rom.d_CsTime_IntVal 
#define D_CSVOLT_DT     u_fd_rom.d_CsVolt_Delta
#define D_CS_MINCV      u_fd_rom.d_CS_MinCV


#define D_FS_CC1				u_fd_rom.d_FSChargeCC1
#define D_FS_CV2				u_fd_rom.d_FSChargeCV2
#define D_FS_CC2				u_fd_rom.d_FSChargeCC2
#define D_FS_CV3				u_fd_rom.d_FSChargeCV3
#define D_FS_CC3				u_fd_rom.d_FSChargeCC3

#define D_CCStepDelta  u_fd_rom.d_CCStepDelta
#define D_CCStepDown    u_fd_rom.d_CCStepDown
#define D_CCStepDelay  u_fd_rom.d_CCStepDelay
#define D_MinStepCC     u_fd_rom.d_MinStepCC

#define D_CTLFLG1		u_fd_rom.d_CTLFLG1				// [2byte] Control flag 
// #define F_FCCUPDATADEL	u_fd_rom.d_CTLFLG1.f_FccUpdateDel	// bit 0
// #define F_CORRRCTRCL    u_fd_rom.d_CTLFLG1.f_CorrectRCL		// bit 1
// #define F_DHGRELPOINT 	u_fd_rom.d_CTLFLG1.f_DhgRelPoint    // bit 2
// #define	F_INITCAP		u_fd_rom.d_CTLFLG1.f_initcap		// bit 3
// #define	F_SYSCONEN		u_fd_rom.d_CTLFLG1.f_sysconen		// bit 4
// #define F_DISRELCHG     u_fd_rom.d_CTLFLG1.f_DisRelChg		// bit 5
// #define F_DISRELDHG     u_fd_rom.d_CTLFLG1.f_DisRelDhg		// bit 6
// #define	F_USEDFDAT		u_fd_rom.d_CTLFLG1.f_usedfdat		// bit 7
// #define F_100TOFCC      u_fd_rom.d_CTLFLG1.f_100ToFcc      // bit 8
// #define F_CAPUINT       u_fd_rom.d_CTLFLG1.f_Cap_uint   
// #define F_QMAXCHGUPDATA u_fd_rom.d_CTLFLG1.f_QMaxChgUpdata
// #define F_QMAXDSGUPDATA u_fd_rom.d_CTLFLG1.f_QMaxDsgUpdata

#define F_FCCUPDATADEL	DEF_BIT0(&D_CTLFLG1)	// bit 0
#define F_CORRRCTRCL    DEF_BIT1(&D_CTLFLG1)		// bit 1
#define F_DHGRELPOINT 	DEF_BIT2(&D_CTLFLG1)    // bit 2
#define	F_INITCAP		DEF_BIT3(&D_CTLFLG1)		// bit 3
#define	F_NOREADNCC		DEF_BIT4(&D_CTLFLG1)		// bit 4
#define F_DISRELCHG     DEF_BIT5(&D_CTLFLG1)		// bit 5
#define F_DISRELDHG     DEF_BIT6(&D_CTLFLG1)		// bit 6
#define	F_USEDFDAT		DEF_BIT7(&D_CTLFLG1)		// bit 7
#define F_100TOFCC      DEF_BIT8(&D_CTLFLG1)      // bit 8
#define F_CAPUINT       DEF_BIT9(&D_CTLFLG1)  
#define F_QMAXCHGUPDATA DEF_BITA(&D_CTLFLG1)
#define F_QMAXDSGUPDATA DEF_BITB(&D_CTLFLG1)
#define F_0TOFD         DEF_BITC(&D_CTLFLG1)
#define F_IGENABLE      DEF_BITD(&D_CTLFLG1)

#define D_CTLFLG2		u_fd_rom.d_CTLFLG2				// [2byte] Control flag 2
// #define F_DSPT			u_fd_rom.d_CTLFLG2.f_dspt		// bit 0
// #define F_CSDIS			u_fd_rom.d_CTLFLG2.f_csdis		// bit 1
// #define F_DSDIS			u_fd_rom.d_CTLFLG2.f_dsdis		// bit 2
// #define F_CPLDROP		u_fd_rom.d_CTLFLG2.f_cpldrop	// bit 3
// #define F_FCCUP			u_fd_rom.d_CTLFLG2.f_fccup		// bit 4

#define F_DSPT			DEF_BIT0(&D_CTLFLG2)		// bit 0
#define F_CSDIS			DEF_BIT1(&D_CTLFLG2)		// bit 1
#define F_DSDIS			DEF_BIT2(&D_CTLFLG2)		// bit 2
#define F_CPLDROP		DEF_BIT3(&D_CTLFLG2)	// bit 3
#define F_FCCUP			DEF_BIT4(&D_CTLFLG2)		// bit 4

#define D_I2CCONFIG     u_fd_rom.d_I2CConfiguration

#define D_AUTHCONFIG    u_fd_rom.d_AuthConfig

#define f_IPH13MODE     DEF_BIT0(&D_AUTHCONFIG) 
#define f_IPH13MODE1    DEF_BIT1(&D_AUTHCONFIG)

#define D_POWERCONFIG   u_fd_rom.d_PowerConfig
#define f_DP_SleepEn    DEF_BIT6(&D_POWERCONFIG)
#define f_HibernateEn   DEF_BIT1(&D_POWERCONFIG)

#define D_IOCONFIG   	u_fd_rom.d_IOConfig
#define f_BTP_POL   	DEF_BIT3(&D_IOCONFIG)
#define f_BTP_SRC   	DEF_BIT1(&D_IOCONFIG)
#define f_BTP_En   	    DEF_BIT0(&D_IOCONFIG)

#define D_SOCCONFIGA    u_fd_rom.d_SOCFlagConfigA
#define f_TDSETV        DEF_BIT0(&D_SOCCONFIGA)
#define f_TDCLV         DEF_BIT1(&D_SOCCONFIGA)
#define f_TDSETRSOC     DEF_BIT2(&D_SOCCONFIGA)
#define f_TDCLRSOC      DEF_BIT3(&D_SOCCONFIGA)
#define f_TCSETV        DEF_BIT4(&D_SOCCONFIGA)
#define f_TCCLV         DEF_BIT5(&D_SOCCONFIGA)
#define f_TCSETRSOC     DEF_BIT6(&D_SOCCONFIGA)
#define f_TCCLRSOC      DEF_BIT7(&D_SOCCONFIGA)
#define f_FCSETVCT      DEF_BITA(&D_SOCCONFIGA)
#define f_TCSETVCT      DEF_BITB(&D_SOCCONFIGA)

#define D_SOCCONFIGB    u_fd_rom.d_SOCFlagConfigB
#define f_FDSETV        DEF_BIT0(&D_SOCCONFIGB)
#define f_FDCLV         DEF_BIT1(&D_SOCCONFIGB)
#define f_FDSETRSOC     DEF_BIT2(&D_SOCCONFIGB)
#define f_FDCLRSOC      DEF_BIT3(&D_SOCCONFIGB)
#define f_FCSETV        DEF_BIT4(&D_SOCCONFIGB)
#define f_FCCLV         DEF_BIT5(&D_SOCCONFIGB)
#define f_FCSETRSOC     DEF_BIT6(&D_SOCCONFIGB)
#define f_FCCLRSOC      DEF_BIT7(&D_SOCCONFIGB)


#define D_DACONFIG		u_fd_rom.d_DAConfiguration
#define f_SleepEn       DEF_BIT4(&D_DACONFIG)

#define D_CHGCONFIG     u_fd_rom.d_ChargingConfiguration
#define D_CRATE         DEF_BIT0(&D_CHGCONFIG)
#define D_DEGRADE_En    DEF_BIT1(&D_CHGCONFIG)
#define D_CS_CV         DEF_BIT7(&D_CHGCONFIG)
#define D_COMP_IR       DEF_BIT8(&D_CHGCONFIG)
#define D_DEGRADE_CC    DEF_BIT9(&D_CHGCONFIG)
#define D_DEGRADE_CV    DEF_BITA(&D_CHGCONFIG)  
#define D_FSCharge      DEF_BITC(&D_CHGCONFIG)
#define D_CCStep_EN     DEF_BITD(&D_CHGCONFIG)

#define D_LTCONFIG      u_fd_rom.d_LifetimesConfiguration

// Capacity
#define	INIT_RSOC		u_fd_rom.d_INIT_RSOC			// [1byte] Initial RelativeStateOfCharge
#define D_INITMAXLOADCUR u_fd_rom.d_INITMAXLOADCUR
#define	D_CCCPER		u_fd_rom.d_CCCPER				// [1byte] CycleCount couting percent [%]
#define	D_RCCMIN		u_fd_rom.d_RCCMIN				// [1byte] Minimum Current of capacity calculation [mA]
#define	D_DLOGC			u_fd_rom.d_DLOGC				// [1byte] Consumption current of discharge circuit [100 uA]
#define	D_REKKA			u_fd_rom.d_REKKA				// [1byte] Deterioration capacity [10uA]
#define	D_RCLMT			u_fd_rom.d_RCLMT				// [2byte] FCC variance limit [mV]
#define	D_STUDYT		u_fd_rom.d_STUDYT				// [1byte] Relearning temp. limit [degC]
#define VARSOC          u_fd_rom.VarSoc                // [1byte] Variasion SOC
#define TEMPLIMIT_L     u_fd_rom.TempLimit_L			// [1byte] Temp Limit Low
#define TEMPLIMIT_H     u_fd_rom.TempLimit_H           // [1byte] Temp Limit High
#define C_RATE_L        u_fd_rom.C_Rate_L				// [1byte] C Rate Low
#define C_RATE_H 		u_fd_rom.C_Rate_H              // [1byte] C Rate High
#define SOC_L           u_fd_rom.SOC_L	 				// [1byte] SOC Low
#define SOC_H 			u_fd_rom.SOC_H 				// [1byte] SOC High	
#define CYCLELIMIT      u_fd_rom.CycleLimt 			// [1byte] CYCLE Limit
#define D_INITDSGRC     u_fd_rom.d_InitDischargeSet
#define D_INITCHGRC     u_fd_rom.d_InitChargeSet
#define D_INITDSGRSOC   u_fd_rom.d_InitDischargeSetRSOC
#define D_INITCHGRSOC   u_fd_rom.d_InitChargeSetRSOC

#define D_LFRSOCA		u_fd_rom.d_TimeRSOCThresholdA
#define D_LFRSOCB		u_fd_rom.d_TimeRSOCThresholdB
#define D_LFRSOCC		u_fd_rom.d_TimeRSOCThresholdC
#define D_LFRSOCD		u_fd_rom.d_TimeRSOCThresholdD
#define D_LFRSOCE		u_fd_rom.d_TimeRSOCThresholdE
#define D_LFRSOCF		u_fd_rom.d_TimeRSOCThresholdF
#define D_LFRSOCG		u_fd_rom.d_TimeRSOCThresholdG

#define D_SOCFSetThreshold 		u_fd_rom.d_SOCFSetThreshold
#define D_SOCFClearThreshold 	u_fd_rom.d_SOCFClearThreshold
#define D_SOC1SetThreshold 		u_fd_rom.d_SOC1SetThreshold
#define D_SOC1ClearThreshold 	u_fd_rom.d_SOC1ClearThreshold

#define D_ODCDetection 			u_fd_rom.d_ODCDetection
#define D_ODCRecovery 			u_fd_rom.d_ODCRecovery
#define D_ODCDelay 				u_fd_rom.d_ODCDelay
#define D_OCCDetection 			u_fd_rom.d_OCCDetection
#define D_OCCRecovery 			u_fd_rom.d_OCCRecovery
#define D_OCCDelay 				u_fd_rom.d_OCCDelay
#define D_BATLOWDetection 		u_fd_rom.d_BATLOWDetection
#define D_BATLOWRecovery 		u_fd_rom.d_BATLOWRecovery
#define D_BATLOWDelay 			u_fd_rom.d_BATLOWDelay
#define D_BATHIDetection 		u_fd_rom.d_BATHIDetection
#define D_BATHIRecovery 		u_fd_rom.d_BATHIRecovery
#define D_BAITHIDelay 			u_fd_rom.d_BAITHIDelay
#define D_DsgCurrent 			u_fd_rom.d_DsgCurrent
#define D_ChgCurrent 			u_fd_rom.d_ChgCurrent
#define D_OTCDetection 			u_fd_rom.d_OTCDetection
#define D_OTCRecovery 			u_fd_rom.d_OTCRecovery
#define D_OTCDelay 				u_fd_rom.d_OTCDelay
#define D_OTDDetection 			u_fd_rom.d_OTDDetection
#define D_OTDRecovery 			u_fd_rom.d_OTDRecovery
#define D_OTDDelay 				u_fd_rom.d_OTDDelay

#define D_INITHIGHVOLT    u_fd_rom.d_InitVoltageHighSet
#define D_INITHIGHVOLTCL  u_fd_rom.d_InitVoltageHighClear
#define D_INITLOWVOLT     u_fd_rom.d_InitVoltageLowSet
#define D_INITLOWVOLTCL   u_fd_rom.d_InitVoltageLowClear
#define D_INITTEMPHIGH    u_fd_rom.d_InitTemperatureHighSet
#define D_INITTEMPHIGHCL  u_fd_rom.d_InitTemperatureHighClear
#define D_INITTEMPLOW     u_fd_rom.d_InitTemperatureLowSet
#define D_INITTEMPLOWCL   u_fd_rom.d_InitTemperatureLowClear

#define D_SOCDELTA        u_fd_rom.d_SOCDelta
#define D_GPIOPULSEWIDTH  u_fd_rom.d_GPIOPulseWidth

#define D_MFGSTATUSINIT   u_fd_rom.d_MfgStatusinit
#define f_GAUGE          DEF_BIT3(&D_MFGSTATUSINIT)
#define f_LF             DEF_BIT5(&D_MFGSTATUSINIT)
//cail
#define CELLGAIN        u_fd_rom.d_CellGain     				// [2byte] Cell gain
#define CCGAIN          u_fd_rom.d_CCGain       				// [2byte] CC gain
#define CCOFFSET        u_fd_rom.d_CCoffset
#define CELLTEMPOFFSET  u_fd_rom.d_CellTempOffset
#define INTTEMPOFFSET    u_fd_rom.d_IntTempOffset

#define D_MF_DATA		u_fd_rom.d_ManufactureDate
#define D_SERIES  		u_fd_rom.d_SerialNumber   
#define D_MF_NAME       u_fd_rom.d_ManufacturerName
#define D_DEVNAME       u_fd_rom.d_DeviceName
#define D_DEVCHEM       u_fd_rom.d_DeviceChemistry
#define D_MF_BLOCKA     u_fd_rom.d_ManufacturerInfoBlockA
#define D_MF_BLOCKB     u_fd_rom.d_ManufacturerInfoBlockB
#define D_SDFCHECKSUM       u_fd_rom.d_StaticDFSignature
#define D_DYNAMICDFCHECKSUM u_fd_rom.d_DynamicDFSignature

#define US_KEY1_SW  	u_fd_rom.d_US_KEY1_SW
#define US_KEY2_SW	  	u_fd_rom.d_US_KEY2_SW
#define US_KEY3_SW  	u_fd_rom.d_US_KEY3_SW
#define US_KEY4_SW	  	u_fd_rom.d_US_KEY4_SW

#define FA_KEY1_SW  	u_fd_rom.d_FA_KEY1_SW
#define FA_KEY2_SW  	u_fd_rom.d_FA_KEY2_SW
#define FA_KEY3_SW  	u_fd_rom.d_FA_KEY3_SW
#define FA_KEY4_SW  	u_fd_rom.d_FA_KEY4_SW
#define D_FCCMAXLIMIT  u_fd_rom.d_fccMaxlimit   // kpfa1 20240511
#define D_FCCMINLIMIT	u_fd_rom.d_fccMinlimit
#define D_CURRENTLIMIT   u_fd_rom.d_currentlimit
#define D_CURRENTLIMITTIME  u_fd_rom.d_currentlimittime

#define D_PINGHUA_CHGVOL_THRESH	u_fd_rom.d_pinghua_chgvol_thresh  //100
#define D_PINGHUA_CHGCUR_LOW    u_fd_rom.d_pinghua_chgcur_low    // 230
#define D_PINGHUA_CHGCUR_HIGH   u_fd_rom.d_pinghua_chgcur_high      // 350 
#define D_PINGHUA_TIME	        u_fd_rom.d_pinghua_time                   // 40
#define D_PINGHUA_CUR_RANGE     u_fd_rom.d_pinghua_cur_range        // 3
#define D_PINGHUA_CAP           u_fd_rom.d_pinghua_cap                     // 30  *3600/100/1400

#define D_SPL_TEMP              u_fd_rom.d_spl_Tmep

#define D_IPA_COM53            u_fd_rom.ipa_com53
#define D_IPA_COM76            u_fd_rom.ipa_com76
#define D_IPA_COM77            u_fd_rom.ipa_com77
#define D_IPA_COMAA            u_fd_rom.ipa_comaa
#define D_IPA_COMAB            u_fd_rom.ipa_comab
#define D_IPA_COMAC            u_fd_rom.ipa_comac
#define D_IPA_COMAD            u_fd_rom.ipa_comad
#define D_IPA_COMAF            u_fd_rom.ipa_comaf
#define D_IPA_COMBA            u_fd_rom.ipa_comba
#define D_IPA_COM3E            u_fd_rom.ipa_com3e
#define D_IPA_COM3F            u_fd_rom.ipa_com3f

#define D_DSG_PINGHUA_MUL         u_fd_rom.d_dsg_pinghua_mul                     //  
#define D_DSG_PINGHUA_DIV        u_fd_rom.d_dsg_pinghua_div                   // 
#define D_0PVOLT5_Tempera_10   		  u_fd_rom.d_0PVOLT5_Tempera_10  
#define D_0PVOLT_Tempera_less_than_5   u_fd_rom.d_0PVOLT_Tempera_less_than_5

#define D_IPA_MANUFACTURE_DATE  u_fd_rom.d_IPA_ManufactureDate

void StaticDFCrc_Chk(void);
void DynamicDFCrc_Chk(void);

/*
config  
*/


#endif

