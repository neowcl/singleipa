/***************************************************************************//**
 * @file     app_const_to_struct.h
 * @version  V1.0.0
 * @author   ligx
 * @date     2022-10-26 PM
 * @brief    APP �ṹ�����ת��Ϊ �㷨�������
 *
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

#ifndef __APP_CONST_TO_STRUCT_H__
#define __APP_CONST_TO_STRUCT_H__
#include "bms_register_config.h"


	#define  FlgEEPReadFnSub                 BatteryConfig.A_FlgEEPReadFinSub
	#define  SOC_SOCOCVTemp_XAS_degC         BatteryConfig.A_SOC_SOCOCVTemp_XAS_degC
	#define  SOC_SOCOCVVol_YAS_V             BatteryConfig.A_SOC_SOCOCVVol_YAS_V
	#define  SOC_SOCOCVTempVolSOH1_TAS_pct   BatteryConfig.A_SOC_SOCOCVTempVolSOH1_TAS_pct
	#define  SOC_SOCVChgTemp_XAS_degC        BatteryConfig.A_SOC_SOCVChgTemp_XAS_degC
	#define  SOC_SOCVChgVol01C_YAS_V         BatteryConfig.A_SOC_SOCVChgVol01C_YAS_V
	#define  SOC_SOCVChgVol05C_YAS_V         BatteryConfig.A_SOC_SOCVChgVol05C_YAS_V
	#define  SOC_SOCVChgVol1C_YAS_V          BatteryConfig.A_SOC_SOCVChgVol1C_YAS_V
	#define  SOC_SOCVChgTempVolSOH1_TAS_pct  BatteryConfig.A_SOC_SOCVChgTempVolSOH1_TAS_pct
	#define  BMS_R0CellTemp_YAS_degC         BatteryConfig.A_BMS_R0CellTemp_YAS_degC
	#define  BMS_R0CellSOC_XAS_pct           BatteryConfig.A_BMS_R0CellSOC_XAS_pct
	#define  BMS_R0CellDisChg_TAS_mOhm       BatteryConfig.A_BMS_R0CellDisChg_TAS_mOhm
	#define  BMS_QCellCapInit_TAS_Ah         BatteryConfig.A_BMS_QCellCapInit_TAS_Ah
	#define  SOC_IChg01CThres_OAS_A          BatteryConfig.A_SOC_IChg01CThres_OAS_A
	#define  SOC_IChg05CThres_OAS_A          BatteryConfig.A_SOC_IChg05CThres_OAS_A
	#define  SOC_IChg1CThres_OAS_A           BatteryConfig.A_SOC_IChg1CThres_OAS_A
	#define  CntCCEEPSub                     BatteryConfig.A_CntCCEEPSub
	#define  SOHBatEEPSub                    BatteryConfig.A_SOHBatEEPSub
	#define  SOCBatDispEEPSub                BatteryConfig.A_SOCBatDispEEPSub
	#define  SOCCellEEPSub                   BatteryConfig.A_SOCCellEEPSub
	#define  QDisChgEEPSub                   BatteryConfig.A_QDisChgEEPSub
	#define  QChgEEPSub                      BatteryConfig.A_QChgEEPSub
	

	#define      ManufacturerName              SysConfig.A_ManufacturerName
	#define      DeviceName                    SysConfig.A_DeviceName
	#define      ManufacturerData              SysConfig.A_ManufacturerData
	#define      DeviceChemistry               SysConfig.A_DeviceChemistry
	#define      StaticDFSignature             SysConfig.A_StaticDFSignature
	#define      BMS_NumModuleInPack_ODU8      SysConfig.A_BMS_NumModuleInPack_ODU8
	#define      BMS_NumCellInModule_ODU8      SysConfig.A_BMS_NumCellInModule_ODU8
	#define      BMS_NumCellInPack_ODU8        SysConfig.A_BMS_NumCellInPack_ODU8
	#define      Desigh_Voltage                SysConfig.A_Desigh_Voltage
	#define      SOH_QCellCapInit_OAS_Ah       SysConfig.A_SOH_QCellCapInit_OAS_Ah
	#define      SOC_VCellHLim_OAS_V           SysConfig.A_SOC_VCellHLim_OAS_V
	#define      SOC_VCellLLim_OAS_V           SysConfig.A_SOC_VCellLLim_OAS_V
	#define      SOC_SOCUpperLim_OAS_pct       SysConfig.A_SOC_SOCUpperLim_OAS_pct
	#define      SOC_SOCLowerLim_OAS_pct       SysConfig.A_SOC_SOCLowerLim_OAS_pct
	             
	
	

	
#endif //__APP_CONST_H__

