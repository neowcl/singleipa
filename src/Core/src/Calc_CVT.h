#ifndef __CALC_CVT_H__
#define __CALC_CVT_H__

#include "base_types.h"


extern int16_t  		CalcCur[4];                     // Calc Current
extern uint8_t          AveCurNum;						// Aveage Current Num
extern int16_t          LastCur;                        // Last Current
extern int32_t          AverageCurSum;
extern uint8_t          aaveragecur_cnt;            // Average Calc


extern int8_t   SOC_Init;
extern int8_t   SOC_End;
extern int32_t  at_startqmax_cnt;   // Start Count
extern int32_t  at_endqmax_cnt;     // End  Count
extern int8_t   f_Qmax_ctrl;        // QMax control
extern int32_t  QmaxCapcity_Calc;   // QMax Capcity



#define f_Qmax_start   DEF_BIT0(&f_Qmax_ctrl) // Qmax start SOC
#define f_Qmax_end     DEF_BIT1(&f_Qmax_ctrl) // Qmax end SOC

extern uint8_t relaxing;
// extern uint8_t cp_updated;
extern uint16_t relaxingCnt;

extern uint16_t	tfc_cnt;				// Full Charge check count

extern uint16_t	t_com84_cwh;



void Calc_AvgCur(void);

void Calc_ATTE(void);

void Calc_ATTF(void);

void Calc_FullCharge(void);

void FullCharge(void);

void Calc_QMax(void);

void DCR_Mode(void);

//void Calc_Res(void);






















#endif

