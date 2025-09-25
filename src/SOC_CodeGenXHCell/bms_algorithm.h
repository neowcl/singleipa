/*
 * File: bms_algorithm.h
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

#ifndef RTW_HEADER_bms_algorithm_h_
#define RTW_HEADER_bms_algorithm_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef bms_algorithm_COMMON_INCLUDES_
# define bms_algorithm_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* bms_algorithm_COMMON_INCLUDES_ */

#include "bms_algorithm_types.h"

/* Child system includes */
#include "HysDebounce.h"

/* Includes for objects with custom storage classes. */
//#include "BMS_Const.h"
//#include "BMS_Parameter.h"
//#include "BMS_ParamConfig.h"
//#include "BMS_Signal.h"
//#include "rt_nonfinite.h"
//#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S413>/温度正常范围' */
typedef struct {
  boolean_T SOC_ASS2;                  /* '<S424>/SOC_ASS2' */
} B_u_bms_algorithm_T;

/* Block signals for system '<S4>/SOH_SubPack' */
typedef struct {
  real32_T Merge3[2];                  /* '<S418>/Merge3' */
  real32_T Merge2[2];                  /* '<S418>/Merge2' */
  boolean_T LogicalOperator1;          /* '<S424>/Logical Operator1' */
  boolean_T soh_FlgOnce_ob;            /* '<S411>/Chart' */
  B_u_bms_algorithm_T u;               /* '<S413>/温度正常范围' */
} B_SOH_SubPack_bms_algorithm_T;

/* Block states (default storage) for system '<S4>/SOH_SubPack' */
typedef struct {
  real32_T Delay7_DSTATE;              /* '<S411>/Delay7' */
  real32_T Delay5_DSTATE;              /* '<S418>/Delay5' */
  real32_T Delay3_DSTATE;              /* '<S418>/Delay3' */
  real32_T Delay4_DSTATE;              /* '<S418>/Delay4' */
  real32_T Delay2_DSTATE;              /* '<S418>/Delay2' */
  real32_T Delay2_DSTATE_p;            /* '<S419>/Delay2' */
  real32_T Delay4_DSTATE_l;            /* '<S419>/Delay4' */
  real32_T DataBuff[51];               /* '<S479>/MovingSum' */
  real32_T int_timer;                  /* '<S411>/Chart' */
  real32_T counter;                    /* '<S411>/Chart' */
  boolean_T Delay1_DSTATE;             /* '<S419>/Delay1' */
  uint8_T is_active_c11_bms_algorithm; /* '<S479>/MovingSum' */
  uint8_T is_c11_bms_algorithm;        /* '<S479>/MovingSum' */
  uint8_T is_active_c9_bms_algorithm;  /* '<S411>/Chart' */
  uint8_T is_c9_bms_algorithm;         /* '<S411>/Chart' */
  boolean_T soh_InputInitFinished;     /* '<S411>/Chart' */
  DW_HysDebounce_T HysteresisDebounce2;/* '<S419>/HysteresisDebounce2' */
} DW_SOH_SubPack_bms_algorithm_T;

/* Block signals for system '<Root>/SOH' */
typedef struct {
  B_SOH_SubPack_bms_algorithm_T SOH_SubPack;/* '<S4>/SOH_SubPack' */
} B_SOH_bms_algorithm_T;

/* Block states (default storage) for system '<Root>/SOH' */
typedef struct {
  DW_SOH_SubPack_bms_algorithm_T SOH_SubPack;/* '<S4>/SOH_SubPack' */
} DW_SOH_bms_algorithm_T;

/* Block signals for system '<S7>/Subsystem5' */
typedef struct {
  real32_T Merge1;                     /* '<S204>/Merge1' */
  real32_T SOC_ASS_SOCOCVCell;         /* '<S203>/SOC_ASS_SOCOCVCell' */
} B_Subsystem5_bms_algorithm_T;

/* Block states (default storage) for system '<S7>/Subsystem5' */
typedef struct {
  real32_T Delay_DSTATE;               /* '<S25>/Delay' */
} DW_Subsystem5_bms_algorithm_T;

/* Block signals for system '<S2>/SOC_SubPack' */
typedef struct {
  real32_T soc_Vse_vs_V;               /* '<S19>/Subtract3' */
  real32_T Divide;                     /* '<S7>/Divide' */
  real32_T Switch2_k;                  /* '<S17>/Switch2' */
  real32_T Switch1;                    /* '<S17>/Switch1' */
  real32_T Switch1_g;                  /* '<S238>/Switch1' */
  real32_T Merge2;                     /* '<S236>/Merge2' */
  real32_T Merge2_f[2];                /* '<S235>/Merge2' */
  real32_T Merge3[2];                  /* '<S219>/Merge3' */
  real32_T SOC_ASS;                    /* '<S242>/SOC_ASS' */
  real32_T SOC_ASS_qfSOCVChgCell;      /* '<S27>/SOC_ASS_qfSOCVChgCell' */
  real32_T Merge3_e[2];                /* '<S24>/Merge3' */
  real32_T Merge1[2];                  /* '<S22>/Merge1' */
  real32_T SOC_ASS_SOCCell1_j;         /* '<S22>/SOC_ASS_SOCCell1' */
  real32_T Merge1_j;                   /* '<S53>/Merge1' */
  real32_T SOC_ASS1;                   /* '<S13>/SOC_ASS1' */
  real32_T soc_OCVCorrRelaxTime_os_s;  /* '<S7>/Chart' */
  real32_T Merge1_h;                   /* '<S80>/Merge1' */
  real32_T SOC_ASS_SOCOCVCell;         /* '<S79>/SOC_ASS_SOCOCVCell' */
  real32_T Delay_i;                    /* '<S25>/Delay' */
  real32_T SOC_ASS_SOCOCVCell_d;       /* '<S202>/SOC_ASS_SOCOCVCell' */
  real32_T SOC_ASS_qfSOCOCVCell;       /* '<S33>/SOC_ASS_qfSOCOCVCell' */
  real32_T Merge1_f;                   /* '<S35>/Merge1' */
  real32_T SOC_ASS_SOCOCVCell_o;       /* '<S34>/SOC_ASS_SOCOCVCell' */
  real32_T SOC_ASS_qfSOCOCVCell_f;     /* '<S34>/SOC_ASS_qfSOCOCVCell' */
  uint8_T DataTypeConversion;          /* '<S235>/Data Type Conversion' */
  uint8_T DataTypeConversion_n;        /* '<S237>/Data Type Conversion' */
  uint8_T SOC_ASS3;                    /* '<S13>/SOC_ASS3' */
  boolean_T RelationalOperator2;       /* '<S29>/Relational Operator2' */
  boolean_T SOC_ASS2;                  /* '<S220>/SOC_ASS2' */
  boolean_T SOC_ASS_SOCCell3;          /* '<S24>/SOC_ASS_SOCCell3' */
  boolean_T DataTypeConversion2;       /* '<S24>/Data Type Conversion2' */
  boolean_T LogicalOperator1_i;        /* '<S32>/Logical Operator1' */
  boolean_T SOC_ASS2_n;                /* '<S31>/SOC_ASS2' */
  boolean_T LogicalOperator1_b;        /* '<S31>/Logical Operator1' */
  boolean_T soc_InitOK;                /* '<S7>/Chart' */
  boolean_T soc_FlgOnce_ob;            /* '<S7>/Chart' */
  B_u_bms_algorithm_T u_n;             /* '<S11>/温度正常范围' */
  B_Subsystem5_bms_algorithm_T Subsystem5;/* '<S7>/Subsystem5' */
} B_SOC_SubPack_bms_algorithm_T;

/* Block states (default storage) for system '<S2>/SOC_SubPack' */
typedef struct {
  real32_T Delay10_DSTATE;             /* '<S7>/Delay10' */
  real32_T Delay11_DSTATE;             /* '<S7>/Delay11' */
  real32_T Delay1_DSTATE;              /* '<S236>/Delay1' */
  real32_T Delay8_DSTATE;              /* '<S7>/Delay8' */
  real32_T Delay1_DSTATE_o;            /* '<S234>/Delay1' */
  real32_T Delay2_DSTATE;              /* '<S7>/Delay2' */
  real32_T Delay7_DSTATE;              /* '<S7>/Delay7' */
  real32_T Delay3_DSTATE;              /* '<S7>/Delay3' */
  real32_T Delay4_DSTATE;              /* '<S7>/Delay4' */
  real32_T Delay5_DSTATE;              /* '<S7>/Delay5' */
  real32_T Delay6_DSTATE;              /* '<S7>/Delay6' */
  real32_T Delay1_DSTATE_a;            /* '<S235>/Delay1' */
  real32_T Delay_DSTATE;               /* '<S234>/Delay' */
  real32_T Delay2_DSTATE_a;            /* '<S234>/Delay2' */
  real32_T Delay_DSTATE_h;             /* '<S219>/Delay' */
  real32_T Delay_DSTATE_o;             /* '<S14>/Delay' */
  real32_T Delay_DSTATE_n;             /* '<S12>/Delay' */
  real32_T int_timer;                  /* '<S7>/Chart' */
  real32_T VocCond_timer;              /* '<S7>/Chart' */
  real32_T VseCond_timer;              /* '<S7>/Chart' */
  real32_T Chgtimer;                   /* '<S7>/Chart' */
  uint32_T OCVtimer;                   /* '<S7>/Chart' */
  uint32_T Vsetimer;                   /* '<S7>/Chart' */
  uint16_T counter1min;                /* '<S30>/Schedule' */
  uint16_T counter1s;                  /* '<S30>/Schedule' */
  uint8_T Delay1_DSTATE_l;             /* '<S7>/Delay1' */
  boolean_T Delay12_DSTATE;            /* '<S7>/Delay12' */
  boolean_T Delay1_DSTATE_j;           /* '<S225>/Delay1' */
  boolean_T Delay7_DSTATE_b;           /* '<S24>/Delay7' */
  boolean_T Delay1_DSTATE_n;           /* '<S24>/Delay1' */
  boolean_T Delay6_DSTATE_p;           /* '<S24>/Delay6' */
  uint8_T is_active_c2_bms_algorithm;  /* '<S30>/Schedule' */
  uint8_T is_active_c1_bms_algorithm;  /* '<S7>/Chart' */
  uint8_T is_c1_bms_algorithm;         /* '<S7>/Chart' */
  boolean_T SOC_OCVCorrStart_b;        /* '<S7>/Chart' */
  boolean_T SOC_OCVCorrStop_b;         /* '<S7>/Chart' */
  boolean_T SOC_InputInitFinished;     /* '<S7>/Chart' */
  boolean_T SOC_VseCorrStart_b;        /* '<S7>/Chart' */
  boolean_T SOC_VseCorrStop_b;         /* '<S7>/Chart' */
  boolean_T SOC_ChgCorrStop_b;         /* '<S7>/Chart' */
  boolean_T SOC_ChgCorrStart_b;        /* '<S7>/Chart' */
  boolean_T SOC_DisChgCorrStart_b;     /* '<S7>/Chart' */
  boolean_T SOC_DisChgCorrStop_b;      /* '<S7>/Chart' */
  DW_HysDebounce_T HysteresisDebounce2_p;/* '<S288>/HysteresisDebounce2' */
  DW_HysDebounce_T HysteresisDebounce3_i;/* '<S138>/HysteresisDebounce3' */
  DW_HysDebounce_T HysteresisDebounce3;/* '<S24>/HysteresisDebounce3' */
  DW_HysDebounce_T HysteresisDebounce2_pj;/* '<S24>/HysteresisDebounce2' */
  DW_HysDebounce_T HysteresisDebounce; /* '<S24>/HysteresisDebounce' */
  DW_HysDebounce_T HysteresisDebounce2;/* '<S23>/HysteresisDebounce2' */
  DW_Subsystem5_bms_algorithm_T Subsystem5;/* '<S7>/Subsystem5' */
} DW_SOC_SubPack_bms_algorithm_T;

/* Block signals (default storage) */
typedef struct {
  real32_T SOC_ASS_SOCCell2;           /* '<S6>/SOC_ASS_SOCCell2' */
  real32_T SOC_ASS;                    /* '<S220>/SOC_ASS' */
  real32_T soh_CntCC_os;
  real32_T soh_SOHBatSub_os_pct_h;
  real32_T soh_QminCapSub_os_Ah;
  real32_T soh_RMSub_os_Ah;
  real32_T soh_QChg_os_Ah;
  real32_T soh_QDisChg_os_Ah;
  real32_T soh_RCellSub_os_mohm;
  uint8_T SOC_ASS3;                    /* '<S220>/SOC_ASS3' */
  B_SOC_SubPack_bms_algorithm_T SOC_SubPack;/* '<S2>/SOC_SubPack' */
  B_SOH_bms_algorithm_T SOH;           /* '<Root>/SOH' */
} B_bms_algorithm_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint16_T counter;                    /* '<Root>/Chart' */
  uint8_T is_active_c13_bms_algorithm; /* '<Root>/Chart' */
  DW_SOC_SubPack_bms_algorithm_T SOC_SubPack;/* '<S2>/SOC_SubPack' */
  DW_SOH_bms_algorithm_T SOH;          /* '<Root>/SOH' */
} DW_bms_algorithm_T;

/* Invariant block signals for system '<S4>/SOH_SubPack' */
typedef struct {
  const real32_T Divide2;              /* '<S422>/Divide2' */
  const real32_T Divide1;              /* '<S422>/Divide1' */
} ConstB_SOH_SubPack_bms_algori_T;

/* Invariant block signals for system '<Root>/SOH' */
typedef struct {
  ConstB_SOH_SubPack_bms_algori_T SOH_SubPack;/* '<S4>/SOH_SubPack' */
} ConstB_SOH_bms_algorithm_T;

/* Invariant block signals (default storage) */
typedef struct {
  ConstB_SOH_bms_algorithm_T SOH;      /* '<Root>/SOH' */
} ConstB_bms_algorithm_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: uDLookupTable_bp01Data
   * Referenced by: '<S260>/2-D Lookup Table'
   */
  real32_T uDLookupTable_bp01Data[11];

  /* Expression: single(reshape([2.5999999046325684,2.5999999046325684,2.4000000953674316,0.5699999928474426,0.4,0.800000011920929,1.2000000476837158,0.5699999928474426],4,2));
   * Referenced by: '<S19>/2-D Lookup Table1'
   */
  real32_T uDLookupTable1_tableData[8];

  /* Computed Parameter: uDLookupTable1_bp01Data
   * Referenced by: '<S19>/2-D Lookup Table1'
   */
  real32_T uDLookupTable1_bp01Data[4];

  /* Expression: single([0.6000000238418579,1.5]);
   * Referenced by: '<S19>/2-D Lookup Table1'
   */
  real32_T uDLookupTable1_bp02Data[2];

  /* Computed Parameter: SOH_QCellDisChg_maxIndex
   * Referenced by: '<S411>/SOH_QCellDisChg'
   */
  uint32_T SOH_QCellDisChg_maxIndex[2];

  /* Computed Parameter: SOH_R0DisChg_maxIndex
   * Referenced by: '<S419>/SOH_R0DisChg'
   */
  uint32_T SOH_R0DisChg_maxIndex[2];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S35>/2-D Lookup Table1'
   *   '<S204>/2-D Lookup Table1'
   */
  uint32_T pooled11[2];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S80>/2-D Lookup Table1'
   *   '<S80>/2-D Lookup Table2'
   *   '<S80>/2-D Lookup Table6'
   */
  uint32_T pooled13[2];

  /* Computed Parameter: uDLookupTable_maxIndex
   * Referenced by: '<S260>/2-D Lookup Table'
   */
  uint32_T uDLookupTable_maxIndex[2];

  /* Computed Parameter: uDLookupTable1_maxIndex
   * Referenced by: '<S19>/2-D Lookup Table1'
   */
  uint32_T uDLookupTable1_maxIndex[2];

  /* Computed Parameter: uDLookupTable2_tableData
   * Referenced by: '<S233>/1-D Lookup Table2'
   */
  uint8_T uDLookupTable2_tableData[9];

  /* Computed Parameter: uDLookupTable2_tableData_k
   * Referenced by: '<S232>/1-D Lookup Table2'
   */
  uint8_T uDLookupTable2_tableData_k[9];
} ConstP_bms_algorithm_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  InpSingnalBusSub InpBusSub1;         /* '<Root>/InpBusSub1' */
  InpStateBus InpStateBusTotal;        /* '<Root>/InpStateBusTotal' */
  InpEEPBusSub InpEEPBusSub1;          /* '<Root>/InpEEPBusSub1' */
} ExtU_bms_algorithm_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  OuPBusSOCSub SOCSub1;                /* '<Root>/SOCSub1' */
  OuPBusSOFSub SOFSub1;                /* '<Root>/SOFSub1' */
  OuPBusSOHSub SOHSub1;                /* '<Root>/SOHSub1' */
} ExtY_bms_algorithm_T;

/* Real-time Model Data Structure */
struct tag_RTM_bms_algorithm_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_bms_algorithm_T bms_algorithm_B;

/* Block states (default storage) */
extern DW_bms_algorithm_T bms_algorithm_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_bms_algorithm_T bms_algorithm_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_bms_algorithm_T bms_algorithm_Y;

/* External data declarations for dependent source files */
extern const OuPBusSOFSub bms_algorithm_rtZOuPBusSOFSub;/* OuPBusSOFSub ground */
extern const ConstB_bms_algorithm_T bms_algorithm_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_bms_algorithm_T bms_algorithm_ConstP;

/* Model entry point functions */
extern void bms_algorithm_initialize(void);
extern void bms_algorithm_step(void);
extern void bms_algorithm_terminate(void);

/* Real-time Model object */
extern RT_MODEL_bms_algorithm_T *const bms_algorithm_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S7>/Delay9' : Unused code path elimination
 * Block '<S7>/Display2' : Unused code path elimination
 * Block '<S7>/Display3' : Unused code path elimination
 * Block '<S7>/Display4' : Unused code path elimination
 * Block '<S7>/MinMax' : Unused code path elimination
 * Block '<S13>/Display1' : Unused code path elimination
 * Block '<S13>/Display2' : Unused code path elimination
 * Block '<S13>/Display3' : Unused code path elimination
 * Block '<S13>/SOC_ASS2' : Unused code path elimination
 * Block '<S69>/Display1' : Unused code path elimination
 * Block '<S77>/Display1' : Unused code path elimination
 * Block '<S78>/SOC_ASS_qfSOCVChgCell' : Unused code path elimination
 * Block '<S79>/SOC_ASS_qfSOCOCVCell' : Unused code path elimination
 * Block '<S7>/Scope' : Unused code path elimination
 * Block '<S7>/Scope2' : Unused code path elimination
 * Block '<S7>/Scope7' : Unused code path elimination
 * Block '<S19>/AND1' : Unused code path elimination
 * Block '<S19>/Constant2' : Unused code path elimination
 * Block '<S19>/Constant4' : Unused code path elimination
 * Block '<S19>/Constant5' : Unused code path elimination
 * Block '<S19>/Constant7' : Unused code path elimination
 * Block '<S19>/Delay' : Unused code path elimination
 * Block '<S19>/Discrete Filter' : Unused code path elimination
 * Block '<S19>/Divide2' : Unused code path elimination
 * Block '<S19>/Divide3' : Unused code path elimination
 * Block '<S19>/Gain5' : Unused code path elimination
 * Block '<S19>/Relational Operator2' : Unused code path elimination
 * Block '<S19>/Relational Operator3' : Unused code path elimination
 * Block '<S19>/SOH_R0DisChg' : Unused code path elimination
 * Block '<S19>/Scope' : Unused code path elimination
 * Block '<S19>/Scope1' : Unused code path elimination
 * Block '<S19>/Scope2' : Unused code path elimination
 * Block '<S19>/Subtract1' : Unused code path elimination
 * Block '<S19>/Switch1' : Unused code path elimination
 * Block '<S23>/Display' : Unused code path elimination
 * Block '<S23>/Display1' : Unused code path elimination
 * Block '<S23>/Display2' : Unused code path elimination
 * Block '<S121>/Data Type Duplicate' : Unused code path elimination
 * Block '<S132>/Data Type Duplicate' : Unused code path elimination
 * Block '<S133>/Data Type Duplicate' : Unused code path elimination
 * Block '<S134>/Data Type Duplicate' : Unused code path elimination
 * Block '<S24>/IDX10' : Unused code path elimination
 * Block '<S24>/Scope' : Unused code path elimination
 * Block '<S24>/Scope1' : Unused code path elimination
 * Block '<S24>/Scope2' : Unused code path elimination
 * Block '<S24>/Scope3' : Unused code path elimination
 * Block '<S24>/Scope4' : Unused code path elimination
 * Block '<S184>/Data Type Duplicate' : Unused code path elimination
 * Block '<S200>/Scope' : Unused code path elimination
 * Block '<S202>/SOC_ASS_qfSOCOCVCell' : Unused code path elimination
 * Block '<S203>/SOC_ASS_qfSOCOCVCell' : Unused code path elimination
 * Block '<S219>/Constant1' : Unused code path elimination
 * Block '<S219>/Constant3' : Unused code path elimination
 * Block '<S219>/Constant4' : Unused code path elimination
 * Block '<S219>/Constant5' : Unused code path elimination
 * Block '<S219>/Constant6' : Unused code path elimination
 * Block '<S219>/Constant7' : Unused code path elimination
 * Block '<S219>/Constant8' : Unused code path elimination
 * Block '<S219>/Constant9' : Unused code path elimination
 * Block '<S219>/Data Type Conversion' : Unused code path elimination
 * Block '<S219>/Logical Operator' : Unused code path elimination
 * Block '<S219>/Logical Operator2' : Unused code path elimination
 * Block '<S219>/Relational Operator1' : Unused code path elimination
 * Block '<S219>/Relational Operator3' : Unused code path elimination
 * Block '<S219>/Relational Operator4' : Unused code path elimination
 * Block '<S219>/Relational Operator5' : Unused code path elimination
 * Block '<S219>/Switch1' : Unused code path elimination
 * Block '<S219>/Switch2' : Unused code path elimination
 * Block '<S220>/Display1' : Unused code path elimination
 * Block '<S220>/Display2' : Unused code path elimination
 * Block '<S220>/Display3' : Unused code path elimination
 * Block '<S220>/Display4' : Unused code path elimination
 * Block '<S220>/Display5' : Unused code path elimination
 * Block '<S220>/Display6' : Unused code path elimination
 * Block '<S220>/Scope' : Unused code path elimination
 * Block '<S220>/Scope1' : Unused code path elimination
 * Block '<S220>/Scope2' : Unused code path elimination
 * Block '<S220>/Scope3' : Unused code path elimination
 * Block '<S232>/Scope' : Unused code path elimination
 * Block '<S233>/Scope1' : Unused code path elimination
 * Block '<S233>/Scope2' : Unused code path elimination
 * Block '<S233>/Scope3' : Unused code path elimination
 * Block '<S236>/Gain' : Unused code path elimination
 * Block '<S236>/Scope1' : Unused code path elimination
 * Block '<S236>/Scope2' : Unused code path elimination
 * Block '<S260>/Scope' : Unused code path elimination
 * Block '<S236>/Subtract1' : Unused code path elimination
 * Block '<S236>/Subtract2' : Unused code path elimination
 * Block '<S288>/Display' : Unused code path elimination
 * Block '<S292>/Data Type Duplicate' : Unused code path elimination
 * Block '<S470>/Display1' : Unused code path elimination
 * Block '<S419>/AND' : Unused code path elimination
 * Block '<S419>/Add1' : Unused code path elimination
 * Block '<S419>/Add2' : Unused code path elimination
 * Block '<S471>/Compare' : Unused code path elimination
 * Block '<S471>/Constant' : Unused code path elimination
 * Block '<S473>/Compare' : Unused code path elimination
 * Block '<S473>/Constant' : Unused code path elimination
 * Block '<S419>/Constant10' : Unused code path elimination
 * Block '<S419>/Constant4' : Unused code path elimination
 * Block '<S419>/Delay5' : Unused code path elimination
 * Block '<S419>/Delay6' : Unused code path elimination
 * Block '<S419>/Divide3' : Unused code path elimination
 * Block '<S419>/Gain' : Unused code path elimination
 * Block '<S419>/Gain1' : Unused code path elimination
 * Block '<S476>/Data Type Duplicate' : Unused code path elimination
 * Block '<S419>/OR' : Unused code path elimination
 * Block '<S419>/Saturation3' : Unused code path elimination
 * Block '<S419>/Switch6' : Unused code path elimination
 * Block '<S411>/Scope' : Unused code path elimination
 * Block '<S411>/soh_R' : Unused code path elimination
 * Block '<Root>/Scope58' : Unused code path elimination
 * Block '<Root>/Scope59' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<Root>/Scope1' : Unused code path elimination
 * Block '<Root>/Scope10' : Unused code path elimination
 * Block '<Root>/Scope11' : Unused code path elimination
 * Block '<Root>/Scope12' : Unused code path elimination
 * Block '<Root>/Scope13' : Unused code path elimination
 * Block '<Root>/Scope14' : Unused code path elimination
 * Block '<Root>/Scope15' : Unused code path elimination
 * Block '<Root>/Scope16' : Unused code path elimination
 * Block '<Root>/Scope17' : Unused code path elimination
 * Block '<Root>/Scope18' : Unused code path elimination
 * Block '<Root>/Scope19' : Unused code path elimination
 * Block '<Root>/Scope2' : Unused code path elimination
 * Block '<Root>/Scope20' : Unused code path elimination
 * Block '<Root>/Scope21' : Unused code path elimination
 * Block '<Root>/Scope22' : Unused code path elimination
 * Block '<Root>/Scope23' : Unused code path elimination
 * Block '<Root>/Scope24' : Unused code path elimination
 * Block '<Root>/Scope25' : Unused code path elimination
 * Block '<Root>/Scope26' : Unused code path elimination
 * Block '<Root>/Scope27' : Unused code path elimination
 * Block '<Root>/Scope28' : Unused code path elimination
 * Block '<Root>/Scope29' : Unused code path elimination
 * Block '<Root>/Scope3' : Unused code path elimination
 * Block '<Root>/Scope30' : Unused code path elimination
 * Block '<Root>/Scope31' : Unused code path elimination
 * Block '<Root>/Scope32' : Unused code path elimination
 * Block '<Root>/Scope33' : Unused code path elimination
 * Block '<Root>/Scope34' : Unused code path elimination
 * Block '<Root>/Scope35' : Unused code path elimination
 * Block '<Root>/Scope36' : Unused code path elimination
 * Block '<Root>/Scope37' : Unused code path elimination
 * Block '<Root>/Scope38' : Unused code path elimination
 * Block '<Root>/Scope39' : Unused code path elimination
 * Block '<Root>/Scope4' : Unused code path elimination
 * Block '<Root>/Scope40' : Unused code path elimination
 * Block '<Root>/Scope41' : Unused code path elimination
 * Block '<Root>/Scope42' : Unused code path elimination
 * Block '<Root>/Scope43' : Unused code path elimination
 * Block '<Root>/Scope44' : Unused code path elimination
 * Block '<Root>/Scope45' : Unused code path elimination
 * Block '<Root>/Scope46' : Unused code path elimination
 * Block '<Root>/Scope47' : Unused code path elimination
 * Block '<Root>/Scope48' : Unused code path elimination
 * Block '<Root>/Scope49' : Unused code path elimination
 * Block '<Root>/Scope5' : Unused code path elimination
 * Block '<Root>/Scope50' : Unused code path elimination
 * Block '<Root>/Scope51' : Unused code path elimination
 * Block '<Root>/Scope52' : Unused code path elimination
 * Block '<Root>/Scope53' : Unused code path elimination
 * Block '<Root>/Scope54' : Unused code path elimination
 * Block '<Root>/Scope55' : Unused code path elimination
 * Block '<Root>/Scope56' : Unused code path elimination
 * Block '<Root>/Scope57' : Unused code path elimination
 * Block '<Root>/Scope6' : Unused code path elimination
 * Block '<Root>/Scope60' : Unused code path elimination
 * Block '<Root>/Scope61' : Unused code path elimination
 * Block '<Root>/Scope62' : Unused code path elimination
 * Block '<Root>/Scope63' : Unused code path elimination
 * Block '<Root>/Scope64' : Unused code path elimination
 * Block '<Root>/Scope7' : Unused code path elimination
 * Block '<Root>/Scope8' : Unused code path elimination
 * Block '<Root>/Scope9' : Unused code path elimination
 * Block '<S7>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S10>/Logical Operator1' : Eliminated due to no operation
 * Block '<S11>/Logical Operator1' : Eliminated due to no operation
 * Block '<S22>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S122>/Logical Operator' : Eliminated due to no operation
 * Block '<S24>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S24>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S24>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S219>/Logical Operator1' : Eliminated due to no operation
 * Block '<S234>/MinMax' : Eliminated since input is scalar
 * Block '<S239>/Logical Operator1' : Eliminated due to no operation
 * Block '<S240>/MinMax' : Eliminated since input is scalar
 * Block '<S241>/Logical Operator1' : Eliminated due to no operation
 * Block '<S243>/Logical Operator1' : Eliminated due to no operation
 * Block '<S287>/Logical Operator' : Eliminated due to no operation
 * Block '<S413>/Logical Operator1' : Eliminated due to no operation
 * Block '<S411>/Max' : Eliminated since input is scalar
 * Block '<S419>/Gain3' : Eliminated nontunable gain of 1
 * Block '<Root>/XY Graph' : Eliminate redundant data type conversion
 * Block '<Root>/XY Graph' : Eliminate redundant data type conversion
 * Block '<S419>/AND2' : Unused code path elimination
 * Block '<S419>/Abs' : Unused code path elimination
 * Block '<S419>/Abs1' : Unused code path elimination
 * Block '<S419>/Add' : Unused code path elimination
 * Block '<S472>/Compare' : Unused code path elimination
 * Block '<S472>/Constant' : Unused code path elimination
 * Block '<S474>/Compare' : Unused code path elimination
 * Block '<S474>/Constant' : Unused code path elimination
 * Block '<S475>/Compare' : Unused code path elimination
 * Block '<S475>/Constant' : Unused code path elimination
 * Block '<S419>/Constant2' : Unused code path elimination
 * Block '<S419>/Constant3' : Unused code path elimination
 * Block '<S419>/Delay3' : Unused code path elimination
 * Block '<S419>/Divide1' : Unused code path elimination
 * Block '<S419>/Divide2' : Unused code path elimination
 * Block '<S419>/Divide4' : Unused code path elimination
 * Block '<S419>/Divide5' : Unused code path elimination
 * Block '<S419>/Divide6' : Unused code path elimination
 * Block '<S419>/Gain2' : Unused code path elimination
 * Block '<S477>/AND1' : Unused code path elimination
 * Block '<S477>/Delay3' : Unused code path elimination
 * Block '<S488>/AND1' : Unused code path elimination
 * Block '<S488>/Abs1' : Unused code path elimination
 * Block '<S488>/Constant10' : Unused code path elimination
 * Block '<S488>/Constant11' : Unused code path elimination
 * Block '<S488>/Relational Operator3' : Unused code path elimination
 * Block '<S488>/Relational Operator4' : Unused code path elimination
 * Block '<S489>/AND1' : Unused code path elimination
 * Block '<S489>/Abs1' : Unused code path elimination
 * Block '<S489>/Constant10' : Unused code path elimination
 * Block '<S489>/Constant11' : Unused code path elimination
 * Block '<S489>/Relational Operator3' : Unused code path elimination
 * Block '<S489>/Relational Operator4' : Unused code path elimination
 * Block '<S477>/NOT' : Unused code path elimination
 * Block '<S419>/Saturation' : Unused code path elimination
 * Block '<S419>/Switch3' : Unused code path elimination
 * Block '<S419>/Switch4' : Unused code path elimination
 * Block '<S419>/Switch5' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'bms_algorithm'
 * '<S1>'   : 'bms_algorithm/Chart'
 * '<S2>'   : 'bms_algorithm/SOC'
 * '<S3>'   : 'bms_algorithm/SOF'
 * '<S4>'   : 'bms_algorithm/SOH'
 * '<S5>'   : 'bms_algorithm/SOC/SOC_SubPack'
 * '<S6>'   : 'bms_algorithm/SOC/Subsystem'
 * '<S7>'   : 'bms_algorithm/SOC/SOC_SubPack/SOC1'
 * '<S8>'   : 'bms_algorithm/SOC/SOC_SubPack/Task_Shedule'
 * '<S9>'   : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Chart'
 * '<S10>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/For Iterator Subsystem'
 * '<S11>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/For Iterator Subsystem1'
 * '<S12>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT'
 * '<S13>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc'
 * '<S14>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT'
 * '<S15>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SimpleCount'
 * '<S16>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem'
 * '<S17>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem1'
 * '<S18>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem11'
 * '<S19>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem12'
 * '<S20>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem13'
 * '<S21>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem14'
 * '<S22>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem2'
 * '<S23>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem3'
 * '<S24>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4'
 * '<S25>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5'
 * '<S26>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6'
 * '<S27>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem7'
 * '<S28>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8'
 * '<S29>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem9'
 * '<S30>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Task_Shedule'
 * '<S31>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/For Iterator Subsystem/电压正常范围'
 * '<S32>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/For Iterator Subsystem1/温度正常范围'
 * '<S33>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable'
 * '<S34>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem'
 * '<S35>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem'
 * '<S36>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem1'
 * '<S37>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem2'
 * '<S38>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem/1'
 * '<S39>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem/2'
 * '<S40>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem/3'
 * '<S41>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem/4'
 * '<S42>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem/5'
 * '<S43>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem/6'
 * '<S44>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action1'
 * '<S45>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action2'
 * '<S46>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action3'
 * '<S47>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action4'
 * '<S48>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action5'
 * '<S49>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_OCV_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action6'
 * '<S50>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/Subsystem'
 * '<S51>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/Subsystem1'
 * '<S52>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/Subsystem2'
 * '<S53>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/Subsystem3'
 * '<S54>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/Subsystem4'
 * '<S55>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action1'
 * '<S56>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action2'
 * '<S57>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action3'
 * '<S58>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action4'
 * '<S59>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action5'
 * '<S60>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action6'
 * '<S61>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/Subsystem3/Subsystem'
 * '<S62>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/Subsystem3/Subsystem1'
 * '<S63>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/Subsystem3/Subsystem2'
 * '<S64>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/Subsystem3/action1'
 * '<S65>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/Subsystem3/action2'
 * '<S66>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/Subsystem3/action3'
 * '<S67>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action1/Compare To Zero'
 * '<S68>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action1/Subsystem'
 * '<S69>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action1/Subsystem1'
 * '<S70>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action2/Subsystem'
 * '<S71>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action2/Subsystem1'
 * '<S72>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action2/Subsystem2'
 * '<S73>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action2/Subsystem3'
 * '<S74>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action2/Subsystem4'
 * '<S75>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action6/Compare To Zero'
 * '<S76>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action6/Subsystem'
 * '<S77>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_QCalc/action6/Subsystem1'
 * '<S78>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable'
 * '<S79>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem'
 * '<S80>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem'
 * '<S81>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem1'
 * '<S82>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem2'
 * '<S83>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/1'
 * '<S84>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/2'
 * '<S85>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/3'
 * '<S86>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/4'
 * '<S87>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action1'
 * '<S88>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action2'
 * '<S89>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action3'
 * '<S90>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action6'
 * '<S91>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action1/Subsystem'
 * '<S92>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action1/Subsystem/Subsystem'
 * '<S93>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action1/Subsystem/Subsystem1'
 * '<S94>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action2/Subsystem'
 * '<S95>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action2/Subsystem1'
 * '<S96>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action2/Subsystem/Subsystem'
 * '<S97>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action2/Subsystem/Subsystem1'
 * '<S98>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action2/Subsystem1/Subsystem'
 * '<S99>'  : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action2/Subsystem1/Subsystem1'
 * '<S100>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action3/Subsystem'
 * '<S101>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action3/Subsystem1'
 * '<S102>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action3/Subsystem/Subsystem'
 * '<S103>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action3/Subsystem/Subsystem1'
 * '<S104>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action3/Subsystem1/Subsystem'
 * '<S105>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action3/Subsystem1/Subsystem1'
 * '<S106>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action6/Subsystem'
 * '<S107>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action6/Subsystem/Subsystem'
 * '<S108>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/SOC_VChg_LUT/OCVSOC LookupTable/Subsystem/Subsystem/action6/Subsystem/Subsystem1'
 * '<S109>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem12/Mean1'
 * '<S110>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem12/Mean1/Model'
 * '<S111>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem2/Subsystem1'
 * '<S112>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem2/Subsystem3'
 * '<S113>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem2/Subsystem4'
 * '<S114>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem2/Subsystem5'
 * '<S115>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem2/Subsystem6'
 * '<S116>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem2/action1'
 * '<S117>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem2/action2'
 * '<S118>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem2/action3'
 * '<S119>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem2/action4'
 * '<S120>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem2/action5'
 * '<S121>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem3/HysteresisDebounce2'
 * '<S122>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem3/Subsystem3'
 * '<S123>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem3/Subsystem4'
 * '<S124>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem3/HysteresisDebounce2/Detect Decrease'
 * '<S125>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem3/HysteresisDebounce2/Detect Decrease2'
 * '<S126>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem3/HysteresisDebounce2/Detect Increase1'
 * '<S127>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem3/HysteresisDebounce2/Detect Increase3'
 * '<S128>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem3/HysteresisDebounce2/Subsystem'
 * '<S129>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem3/HysteresisDebounce2/Subsystem1'
 * '<S130>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem3/HysteresisDebounce2/Subsystem/Detect Increase1'
 * '<S131>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem3/HysteresisDebounce2/Subsystem1/Detect Increase1'
 * '<S132>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce'
 * '<S133>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce2'
 * '<S134>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce3'
 * '<S135>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem'
 * '<S136>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem1'
 * '<S137>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem10'
 * '<S138>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem11'
 * '<S139>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem12'
 * '<S140>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem2'
 * '<S141>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem3'
 * '<S142>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem4'
 * '<S143>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem5'
 * '<S144>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem6'
 * '<S145>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem7'
 * '<S146>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem8'
 * '<S147>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem9'
 * '<S148>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action1'
 * '<S149>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action10'
 * '<S150>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action11'
 * '<S151>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action2'
 * '<S152>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action3'
 * '<S153>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action4'
 * '<S154>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action5'
 * '<S155>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action6'
 * '<S156>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action7'
 * '<S157>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action8'
 * '<S158>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action9'
 * '<S159>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/overwrite'
 * '<S160>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce/Detect Decrease'
 * '<S161>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce/Detect Decrease2'
 * '<S162>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce/Detect Increase1'
 * '<S163>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce/Detect Increase3'
 * '<S164>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce/Subsystem'
 * '<S165>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce/Subsystem1'
 * '<S166>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce/Subsystem/Detect Increase1'
 * '<S167>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce/Subsystem1/Detect Increase1'
 * '<S168>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce2/Detect Decrease'
 * '<S169>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce2/Detect Decrease2'
 * '<S170>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce2/Detect Increase1'
 * '<S171>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce2/Detect Increase3'
 * '<S172>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce2/Subsystem'
 * '<S173>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce2/Subsystem1'
 * '<S174>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce2/Subsystem/Detect Increase1'
 * '<S175>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce2/Subsystem1/Detect Increase1'
 * '<S176>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce3/Detect Decrease'
 * '<S177>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce3/Detect Decrease2'
 * '<S178>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce3/Detect Increase1'
 * '<S179>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce3/Detect Increase3'
 * '<S180>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce3/Subsystem'
 * '<S181>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce3/Subsystem1'
 * '<S182>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce3/Subsystem/Detect Increase1'
 * '<S183>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/HysteresisDebounce3/Subsystem1/Detect Increase1'
 * '<S184>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem11/HysteresisDebounce3'
 * '<S185>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem11/HysteresisDebounce3/Detect Decrease'
 * '<S186>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem11/HysteresisDebounce3/Detect Decrease2'
 * '<S187>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem11/HysteresisDebounce3/Detect Increase1'
 * '<S188>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem11/HysteresisDebounce3/Detect Increase3'
 * '<S189>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem11/HysteresisDebounce3/Subsystem'
 * '<S190>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem11/HysteresisDebounce3/Subsystem1'
 * '<S191>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem11/HysteresisDebounce3/Subsystem/Detect Increase1'
 * '<S192>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/Subsystem11/HysteresisDebounce3/Subsystem1/Detect Increase1'
 * '<S193>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action8/Subsystem'
 * '<S194>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action8/Subsystem1'
 * '<S195>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action8/Subsystem2'
 * '<S196>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action8/action1'
 * '<S197>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action8/action2'
 * '<S198>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action8/action5'
 * '<S199>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action8/action7'
 * '<S200>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action8/action1/Chg'
 * '<S201>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem4/action8/action1/Dischg'
 * '<S202>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable'
 * '<S203>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem'
 * '<S204>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem'
 * '<S205>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem1'
 * '<S206>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem2'
 * '<S207>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem/1'
 * '<S208>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem/2'
 * '<S209>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem/3'
 * '<S210>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem/4'
 * '<S211>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem/5'
 * '<S212>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem/6'
 * '<S213>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem/action1'
 * '<S214>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem/action2'
 * '<S215>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem/action3'
 * '<S216>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem/action4'
 * '<S217>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem/action5'
 * '<S218>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem5/Vse_SOC LookupTable/Subsystem/Subsystem/action6'
 * '<S219>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem'
 * '<S220>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem3'
 * '<S221>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem/action1'
 * '<S222>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem/action5'
 * '<S223>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem3/SOC_Smooth_speed'
 * '<S224>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem3/Subsystem'
 * '<S225>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem3/Subsystem2'
 * '<S226>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem3/action4'
 * '<S227>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem3/action5'
 * '<S228>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem3/SOC_Smooth_speed/初上电1'
 * '<S229>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem3/SOC_Smooth_speed/升slope'
 * '<S230>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem3/SOC_Smooth_speed/范围内1'
 * '<S231>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem3/SOC_Smooth_speed/降slope1'
 * '<S232>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem3/Subsystem2/Subsystem'
 * '<S233>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem6/Subsystem3/Subsystem2/Subsystem1'
 * '<S234>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/For Iterator Subsystem2'
 * '<S235>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem1'
 * '<S236>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2'
 * '<S237>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem3'
 * '<S238>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7'
 * '<S239>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/For Iterator Subsystem2/Subsystem'
 * '<S240>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/For Iterator Subsystem2/Subsystem1'
 * '<S241>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/For Iterator Subsystem2/Subsystem2'
 * '<S242>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/For Iterator Subsystem2/Subsystem3'
 * '<S243>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/For Iterator Subsystem2/Subsystem4'
 * '<S244>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/For Iterator Subsystem2/Subsystem5'
 * '<S245>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/For Iterator Subsystem2/Subsystem3/action4'
 * '<S246>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/For Iterator Subsystem2/Subsystem3/action5'
 * '<S247>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/For Iterator Subsystem2/Subsystem5/Compare To Zero'
 * '<S248>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem1/Subsystem'
 * '<S249>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem1/Subsystem1'
 * '<S250>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem1/Subsystem2'
 * '<S251>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem1/Subsystem3'
 * '<S252>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem1/action1'
 * '<S253>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem1/action2'
 * '<S254>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem1/action4'
 * '<S255>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem1/action5'
 * '<S256>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Compare To Zero'
 * '<S257>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/SOC_Smooth_speed'
 * '<S258>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem'
 * '<S259>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem1'
 * '<S260>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem2'
 * '<S261>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem3'
 * '<S262>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem4'
 * '<S263>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem5'
 * '<S264>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem6'
 * '<S265>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem7'
 * '<S266>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem8'
 * '<S267>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/SOC_Smooth_speed/初上电1'
 * '<S268>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/SOC_Smooth_speed/升slope'
 * '<S269>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/SOC_Smooth_speed/范围内1'
 * '<S270>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/SOC_Smooth_speed/降slope1'
 * '<S271>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem1/Compare To Zero'
 * '<S272>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem1/Compare To Zero1'
 * '<S273>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem3/Compare To Zero'
 * '<S274>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem4/Compare To Zero'
 * '<S275>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem5/Compare To Zero'
 * '<S276>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem6/Compare To Zero'
 * '<S277>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem7/Compare To Zero'
 * '<S278>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem7/Compare To Zero1'
 * '<S279>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem2/Subsystem8/Compare To Zero'
 * '<S280>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem3/Subsystem1'
 * '<S281>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem3/Subsystem2'
 * '<S282>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem3/Subsystem3'
 * '<S283>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem3/Subsystem4'
 * '<S284>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem3/Subsystem6'
 * '<S285>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem'
 * '<S286>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2'
 * '<S287>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/Subsystem1'
 * '<S288>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/Subsystem2'
 * '<S289>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/action1'
 * '<S290>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/action2'
 * '<S291>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/action3'
 * '<S292>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/Subsystem2/HysteresisDebounce2'
 * '<S293>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/Subsystem2/Subsystem4'
 * '<S294>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/Subsystem2/HysteresisDebounce2/Detect Decrease'
 * '<S295>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/Subsystem2/HysteresisDebounce2/Detect Decrease2'
 * '<S296>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/Subsystem2/HysteresisDebounce2/Detect Increase1'
 * '<S297>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/Subsystem2/HysteresisDebounce2/Detect Increase3'
 * '<S298>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/Subsystem2/HysteresisDebounce2/Subsystem'
 * '<S299>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/Subsystem2/HysteresisDebounce2/Subsystem1'
 * '<S300>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/Subsystem2/HysteresisDebounce2/Subsystem/Detect Increase1'
 * '<S301>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Subsystem8/Subsystem7/Subsystem2/Subsystem2/HysteresisDebounce2/Subsystem1/Detect Increase1'
 * '<S302>' : 'bms_algorithm/SOC/SOC_SubPack/SOC1/Task_Shedule/Schedule'
 * '<S303>' : 'bms_algorithm/SOC/SOC_SubPack/Task_Shedule/Schedule'
 * '<S304>' : 'bms_algorithm/SOF/SOFSub'
 * '<S305>' : 'bms_algorithm/SOF/SOFSub/BMSMode'
 * '<S306>' : 'bms_algorithm/SOF/SOFSub/BatModel'
 * '<S307>' : 'bms_algorithm/SOF/SOFSub/Chart'
 * '<S308>' : 'bms_algorithm/SOF/SOFSub/R0'
 * '<S309>' : 'bms_algorithm/SOF/SOFSub/SOF_Map'
 * '<S310>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH'
 * '<S311>' : 'bms_algorithm/SOF/SOFSub/Subsystem3'
 * '<S312>' : 'bms_algorithm/SOF/SOFSub/current'
 * '<S313>' : 'bms_algorithm/SOF/SOFSub/BMSMode/StBMSMode1'
 * '<S314>' : 'bms_algorithm/SOF/SOFSub/BMSMode/StBMSMode1/ERROR_IDisChgLimit'
 * '<S315>' : 'bms_algorithm/SOF/SOFSub/BMSMode/StBMSMode1/Error'
 * '<S316>' : 'bms_algorithm/SOF/SOFSub/BMSMode/StBMSMode1/HV_OFF'
 * '<S317>' : 'bms_algorithm/SOF/SOFSub/BMSMode/StBMSMode1/HV_OFF_IDisChgLimit'
 * '<S318>' : 'bms_algorithm/SOF/SOFSub/BMSMode/StBMSMode1/HV_ON'
 * '<S319>' : 'bms_algorithm/SOF/SOFSub/BMSMode/StBMSMode1/HV_ON_IDisChgLimit'
 * '<S320>' : 'bms_algorithm/SOF/SOFSub/BMSMode/StBMSMode1/Service'
 * '<S321>' : 'bms_algorithm/SOF/SOFSub/BMSMode/StBMSMode1/Service_IDisChgLimit'
 * '<S322>' : 'bms_algorithm/SOF/SOFSub/BMSMode/StBMSMode1/other'
 * '<S323>' : 'bms_algorithm/SOF/SOFSub/BatModel/Subsystem2'
 * '<S324>' : 'bms_algorithm/SOF/SOFSub/BatModel/Subsystem2/0'
 * '<S325>' : 'bms_algorithm/SOF/SOFSub/BatModel/Subsystem2/1'
 * '<S326>' : 'bms_algorithm/SOF/SOFSub/BatModel/Subsystem2/SOF_IDisChgMax'
 * '<S327>' : 'bms_algorithm/SOF/SOFSub/BatModel/Subsystem2/simple model'
 * '<S328>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IBOL'
 * '<S329>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IEOL'
 * '<S330>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IBOL/SOF_Map30sDisChrgI'
 * '<S331>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IBOL/SOF_Map30sDisChrgI1'
 * '<S332>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IBOL/SOF_MapContDisChrgI'
 * '<S333>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IBOL/SOF_MapContDisChrgI1'
 * '<S334>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IBOL/Subsystem2'
 * '<S335>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IBOL/Subsystem4'
 * '<S336>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IBOL/Subsystem2/Subsystem'
 * '<S337>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IBOL/Subsystem2/Subsystem1'
 * '<S338>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IBOL/Subsystem2/Subsystem2'
 * '<S339>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IBOL/Subsystem4/Subsystem'
 * '<S340>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IBOL/Subsystem4/Subsystem1'
 * '<S341>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IBOL/Subsystem4/Subsystem2'
 * '<S342>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IEOL/SOF_Map30sDisChrgI'
 * '<S343>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IEOL/SOF_Map30sDisChrgI1'
 * '<S344>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IEOL/SOF_Map5sDisChrgI'
 * '<S345>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IEOL/SOF_Map5sDisChrgI1'
 * '<S346>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IEOL/Subsystem2'
 * '<S347>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IEOL/Subsystem4'
 * '<S348>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IEOL/Subsystem2/Subsystem'
 * '<S349>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IEOL/Subsystem2/Subsystem1'
 * '<S350>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IEOL/Subsystem2/Subsystem2'
 * '<S351>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IEOL/Subsystem4/Subsystem'
 * '<S352>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IEOL/Subsystem4/Subsystem1'
 * '<S353>' : 'bms_algorithm/SOF/SOFSub/SOF_Map/SOF_IEOL/Subsystem4/Subsystem2'
 * '<S354>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_cont_DisChg_SOH'
 * '<S355>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_peak_DisChg_SOH'
 * '<S356>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_cont_DisChg_SOH/(0,SOHEol)'
 * '<S357>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_cont_DisChg_SOH/(SOHEol,SOHBol)'
 * '<S358>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_cont_DisChg_SOH/0 ＜ SOH ≤ SOHEol'
 * '<S359>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_cont_DisChg_SOH/SOH ≤ 0'
 * '<S360>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_cont_DisChg_SOH/SOH ≤ 0 '
 * '<S361>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_cont_DisChg_SOH/SOH ≥ SOHBol'
 * '<S362>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_cont_DisChg_SOH/SOHBol'
 * '<S363>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_cont_DisChg_SOH/SOHEol ＜ SOH ＜ SOHBol'
 * '<S364>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_peak_DisChg_SOH/(0,SOHEol)'
 * '<S365>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_peak_DisChg_SOH/(SOHEol,SOHBol)'
 * '<S366>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_peak_DisChg_SOH/0 ＜ SOH ≤ SOHEol'
 * '<S367>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_peak_DisChg_SOH/SOH ≤ 0'
 * '<S368>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_peak_DisChg_SOH/SOH ≤ 0 '
 * '<S369>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_peak_DisChg_SOH/SOH ≥ SOHBol'
 * '<S370>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_peak_DisChg_SOH/SOHBol'
 * '<S371>' : 'bms_algorithm/SOF/SOFSub/SOF_SOH/SOF_I_peak_DisChg_SOH/SOHEol ＜ SOH ＜ SOHBol'
 * '<S372>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem3'
 * '<S373>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem4'
 * '<S374>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Total_Smooth_speed1'
 * '<S375>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem3/SOF_IFltLmt'
 * '<S376>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem3/SOF_IFltLmt/=Lv2'
 * '<S377>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem3/SOF_IFltLmt/>Lv2'
 * '<S378>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem3/SOF_IFltLmt/＜Lv2'
 * '<S379>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem4/Subsystem'
 * '<S380>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem4/Subsystem1'
 * '<S381>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem4/Subsystem2'
 * '<S382>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem4/Subsystem3'
 * '<S383>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem4/Subsystem7'
 * '<S384>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem4/Subsystem9'
 * '<S385>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem4/Violate_Smooth_speed'
 * '<S386>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem4/Violate_Smooth_speed/初上电1'
 * '<S387>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem4/Violate_Smooth_speed/升slope'
 * '<S388>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem4/Violate_Smooth_speed/范围内1'
 * '<S389>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Subsystem4/Violate_Smooth_speed/降slope1'
 * '<S390>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Total_Smooth_speed1/初上电1'
 * '<S391>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Total_Smooth_speed1/升slope'
 * '<S392>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Total_Smooth_speed1/范围内1'
 * '<S393>' : 'bms_algorithm/SOF/SOFSub/Subsystem3/Total_Smooth_speed1/降slope1'
 * '<S394>' : 'bms_algorithm/SOF/SOFSub/current/MovingSum1'
 * '<S395>' : 'bms_algorithm/SOF/SOFSub/current/Smooth_speed1'
 * '<S396>' : 'bms_algorithm/SOF/SOFSub/current/Subsystem4'
 * '<S397>' : 'bms_algorithm/SOF/SOFSub/current/Subsystem5'
 * '<S398>' : 'bms_algorithm/SOF/SOFSub/current/Subsystem6'
 * '<S399>' : 'bms_algorithm/SOF/SOFSub/current/aboveZero'
 * '<S400>' : 'bms_algorithm/SOF/SOFSub/current/MovingSum1/MovingSum'
 * '<S401>' : 'bms_algorithm/SOF/SOFSub/current/Smooth_speed1/初上电1'
 * '<S402>' : 'bms_algorithm/SOF/SOFSub/current/Smooth_speed1/升slope'
 * '<S403>' : 'bms_algorithm/SOF/SOFSub/current/Smooth_speed1/范围内1'
 * '<S404>' : 'bms_algorithm/SOF/SOFSub/current/Smooth_speed1/降slope1'
 * '<S405>' : 'bms_algorithm/SOF/SOFSub/current/Subsystem6/K_LengthTopBottom'
 * '<S406>' : 'bms_algorithm/SOF/SOFSub/current/Subsystem6/Smooth_speed'
 * '<S407>' : 'bms_algorithm/SOF/SOFSub/current/Subsystem6/Smooth_speed/初上电1'
 * '<S408>' : 'bms_algorithm/SOF/SOFSub/current/Subsystem6/Smooth_speed/升slope'
 * '<S409>' : 'bms_algorithm/SOF/SOFSub/current/Subsystem6/Smooth_speed/范围内1'
 * '<S410>' : 'bms_algorithm/SOF/SOFSub/current/Subsystem6/Smooth_speed/降slope1'
 * '<S411>' : 'bms_algorithm/SOH/SOH_SubPack'
 * '<S412>' : 'bms_algorithm/SOH/SOH_SubPack/Chart'
 * '<S413>' : 'bms_algorithm/SOH/SOH_SubPack/For Iterator Subsystem1'
 * '<S414>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem'
 * '<S415>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1'
 * '<S416>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CAP'
 * '<S417>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CAP1'
 * '<S418>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC'
 * '<S419>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R'
 * '<S420>' : 'bms_algorithm/SOH/SOH_SubPack/SimpleCount'
 * '<S421>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem'
 * '<S422>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem1'
 * '<S423>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10'
 * '<S424>' : 'bms_algorithm/SOH/SOH_SubPack/For Iterator Subsystem1/温度正常范围'
 * '<S425>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem/Subsystem1'
 * '<S426>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem/电压正常范围'
 * '<S427>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem/Subsystem1/For Iterator Subsystem'
 * '<S428>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem/Subsystem1/Subsystem'
 * '<S429>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem'
 * '<S430>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2'
 * '<S431>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/Subsystem'
 * '<S432>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/Subsystem1'
 * '<S433>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge'
 * '<S434>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge/s4_csoc_vk_div_lsb'
 * '<S435>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge/s4_csoc_vk_div_lsb/discharge'
 * '<S436>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge/s4_csoc_vk_div_lsb/discharge/If Action Subsystem'
 * '<S437>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge/s4_csoc_vk_div_lsb/discharge/If Action Subsystem1'
 * '<S438>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge/s4_csoc_vk_div_lsb/discharge/If Action Subsystem2'
 * '<S439>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge/s4_csoc_vk_div_lsb/discharge/If Action Subsystem3'
 * '<S440>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge/s4_csoc_vk_div_lsb/discharge/Subsystem'
 * '<S441>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge/s4_csoc_vk_div_lsb/discharge/Subsystem1'
 * '<S442>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge/s4_csoc_vk_div_lsb/discharge/Subsystem2'
 * '<S443>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge/s4_csoc_vk_div_lsb/discharge/Subsystem3'
 * '<S444>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge/s4_csoc_vk_div_lsb/discharge/Subsystem4'
 * '<S445>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge/s4_csoc_vk_div_lsb/discharge/discharge'
 * '<S446>' : 'bms_algorithm/SOH/SOH_SubPack/Function-Call Subsystem1/Subsystem2/discharge/s4_csoc_vk_div_lsb/discharge/discharge1'
 * '<S447>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CAP/DetaQ'
 * '<S448>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CAP/Subsystem1'
 * '<S449>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CAP1/DetaQ'
 * '<S450>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CAP1/Subsystem1'
 * '<S451>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/Ah2As'
 * '<S452>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/Ah2As1'
 * '<S453>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/As2Ah'
 * '<S454>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/As2Ah1'
 * '<S455>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/SOH_ChgEEP'
 * '<S456>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/SOH_DisChgEEP'
 * '<S457>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/Subsystem'
 * '<S458>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/action1'
 * '<S459>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/action2'
 * '<S460>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/action3'
 * '<S461>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/action4'
 * '<S462>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/action5'
 * '<S463>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/action6'
 * '<S464>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/SOH_ChgEEP/初上电1'
 * '<S465>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/SOH_ChgEEP/正常运行过程中'
 * '<S466>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/SOH_DisChgEEP/初上电1'
 * '<S467>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/SOH_DisChgEEP/正常运行过程中'
 * '<S468>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/action1/Compare To Zero'
 * '<S469>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/action1/Subsystem'
 * '<S470>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_CC/action1/Subsystem1'
 * '<S471>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/Compare To Constant'
 * '<S472>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/Compare To Constant1'
 * '<S473>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/Compare To Constant2'
 * '<S474>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/Compare To Constant3'
 * '<S475>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/Compare To Constant4'
 * '<S476>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/HysteresisDebounce2'
 * '<S477>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/I_Conditon'
 * '<S478>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/I_Conditon1'
 * '<S479>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/MovingSum1'
 * '<S480>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/HysteresisDebounce2/Detect Decrease'
 * '<S481>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/HysteresisDebounce2/Detect Decrease2'
 * '<S482>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/HysteresisDebounce2/Detect Increase1'
 * '<S483>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/HysteresisDebounce2/Detect Increase3'
 * '<S484>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/HysteresisDebounce2/Subsystem'
 * '<S485>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/HysteresisDebounce2/Subsystem1'
 * '<S486>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/HysteresisDebounce2/Subsystem/Detect Increase1'
 * '<S487>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/HysteresisDebounce2/Subsystem1/Detect Increase1'
 * '<S488>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/I_Conditon/I_Conditon1'
 * '<S489>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/I_Conditon/I_Conditon2'
 * '<S490>' : 'bms_algorithm/SOH/SOH_SubPack/SOH_R/MovingSum1/MovingSum'
 * '<S491>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem/电流正常范围'
 * '<S492>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem1/SOH_ChgEEP'
 * '<S493>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem1/SOH_ChgEEP/初上电1'
 * '<S494>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem1/SOH_ChgEEP/正常运行过程中'
 * '<S495>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1'
 * '<S496>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem2'
 * '<S497>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem1'
 * '<S498>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem2'
 * '<S499>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem3'
 * '<S500>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem4'
 * '<S501>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem5'
 * '<S502>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem6'
 * '<S503>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem7'
 * '<S504>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem8'
 * '<S505>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem1/Subsystem9'
 * '<S506>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem2/Subsystem9'
 * '<S507>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem3/Subsystem9'
 * '<S508>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem4/Subsystem9'
 * '<S509>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem5/Subsystem9'
 * '<S510>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem7/Subsystem9'
 * '<S511>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem1/Subsystem8/Subsystem9'
 * '<S512>' : 'bms_algorithm/SOH/SOH_SubPack/Subsystem10/Subsystem2/Subsystem9'
 */
#endif                                 /* RTW_HEADER_bms_algorithm_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
