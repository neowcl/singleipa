/*
 * File: HysDebounce.h
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

#ifndef RTW_HEADER_HysDebounce_h_
#define RTW_HEADER_HysDebounce_h_
#ifndef bms_algorithm_COMMON_INCLUDES_
# define bms_algorithm_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* bms_algorithm_COMMON_INCLUDES_ */

#include "bms_algorithm_types.h"

/* Block states (default storage) for system '<S419>/HysteresisDebounce2' */
typedef struct {
  real32_T UnitDelay2_DSTATE;          /* '<S484>/Unit Delay2' */
  real32_T UnitDelay2_DSTATE_n;        /* '<S485>/Unit Delay2' */
  boolean_T UnitDelay2_DSTATE_l;       /* '<S476>/Unit Delay2' */
  boolean_T DelayInput1_DSTATE;        /* '<S483>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_p;      /* '<S481>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_pb;     /* '<S486>/Delay Input1' */
  boolean_T UnitDelay1_DSTATE;         /* '<S476>/Unit Delay1' */
  boolean_T DelayInput1_DSTATE_o;      /* '<S487>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_pd;     /* '<S482>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_h;      /* '<S480>/Delay Input1' */
} DW_HysDebounce_T;

extern void HysDebounce_Init(DW_HysDebounce_T *localDW);
extern void HysDebounce(boolean_T rtu_Sig_Up, boolean_T rtu_Sig_Dwn, real32_T
  rtu_BaseTimer, real32_T rtu_UpTimer, real32_T rtu_DownTimer, boolean_T
  *rty_Sig_Out, DW_HysDebounce_T *localDW);

#endif                                 /* RTW_HEADER_HysDebounce_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
