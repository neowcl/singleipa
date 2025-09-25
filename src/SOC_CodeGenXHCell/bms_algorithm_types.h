/*
 * File: bms_algorithm_types.h
 *
 * Code generated for Simulink model 'bms_algorithm'.
 *
 * Model version                  : V1.13.5_修改初上电温度取消无效判断_2023/11/22
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Wed Nov 22 15:31:52 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_bms_algorithm_types_h_
#define RTW_HEADER_bms_algorithm_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_InpSingnalBusSub_
#define DEFINED_TYPEDEF_FOR_InpSingnalBusSub_

typedef struct {
  real32_T inp_UCellSub_vs_V;
  uint8_T inp_qfUCellSub_vu8;
  real32_T btm_TModuSub_vs_degC;
  uint8_T btm_qfTModuSub_vu8;
  real32_T inp_IBatSub_os_A;
  uint8_T inp_qfIBatSub_ou8;
  boolean_T inp_BalSwitchStatusSub_vb;
  real32_T inp_UPackSub_os_V;
} InpSingnalBusSub;

#endif

#ifndef DEFINED_TYPEDEF_FOR_InpStateBus_
#define DEFINED_TYPEDEF_FOR_InpStateBus_

typedef struct {
  real32_T soc_tmBase_ODS_ms;
  uint8_T bsc_StBMSMode_ou8;
  boolean_T bal_FlgBalState_ob;
  real32_T soh_SOCWinH_os_pct;
  real32_T soh_SOCWinL_os_pct;
  boolean_T inp_RunOutCmd_ob;
  uint32_T rcm_tmSleep_ou32_min;
  uint8_T dem_StBMSWrnLvl_ou8;
} InpStateBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_InpEEPBusSub_
#define DEFINED_TYPEDEF_FOR_InpEEPBusSub_

typedef struct {
  boolean_T inp_FlgEEPReadFinSub_ob;
  real32_T soh_QDisChgEEPSub_os_Ah;
  real32_T soh_QChgEEPSub_os_Ah;
  real32_T soh_CntCCEEPSub_os;
  real32_T inp_SOCBatDispEEPSub_os_pct;
  real32_T inp_SOHBatEEPSub_os_pct;
  real32_T inp_SOCCellEEPSub_vs_pct;
} InpEEPBusSub;

#endif

#ifndef DEFINED_TYPEDEF_FOR_OuPBusSOHSub_
#define DEFINED_TYPEDEF_FOR_OuPBusSOHSub_

typedef struct {
  real32_T soh_CntCC_os;
  real32_T soh_SOHBatSub_os_pct;
  real32_T soh_QminCapSub_os_Ah;
  real32_T soh_RMSub_os_Ah;
  real32_T soh_QChg_os_Ah;
  real32_T soh_QDisChg_os_Ah;
  real32_T soh_RCellSub_os_mohm;
} OuPBusSOHSub;

#endif

#ifndef DEFINED_TYPEDEF_FOR_OuPBusSOCSub_
#define DEFINED_TYPEDEF_FOR_OuPBusSOCSub_

typedef struct {
  real32_T soc_socWinHSub_os_pct;
  real32_T soc_socWinLSub_os_pct;
  real32_T soc_SOCCellAvgSub_os_pct;
  real32_T soc_SOCCellMinSub_os_pct;
  real32_T soc_SOCCellMaxSub_os_pct;
  real32_T soc_SOCBatRealSub_os_pct;
  real32_T soc_SOCDispSub_os_pct;
  uint8_T soc_qfSOCDispSub_ou8;
  real32_T soc_SOCDispCANSub_os_pct;
  uint8_T soc_qfSOCDispCANSub_ou8;
  real32_T soc_SOCCellSub_vs_pct;
  uint8_T soc_qfSOCCellSub_vu8;
} OuPBusSOCSub;

#endif

#ifndef DEFINED_TYPEDEF_FOR_OuPBusSOFSub_
#define DEFINED_TYPEDEF_FOR_OuPBusSOFSub_

typedef struct {
  real32_T sof_ItotalDisChgLimit_os_A;
} OuPBusSOFSub;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_bms_algorithm_T RT_MODEL_bms_algorithm_T;

#endif                                 /* RTW_HEADER_bms_algorithm_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
