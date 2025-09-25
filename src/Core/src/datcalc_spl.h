/*******************************************************************************
* Copyright(C) 2008, 2019 Renesas Electronics Corporation
* RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY
* This program must be used solely for the purpose for which
* it was furnished by Renesas Electronics Corporation. No part of this
* program may be reproduced or disclosed to others, in any
* form, without the prior written permission of Renesas Electronics
* Corporation.
*******************************************************************************
*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corp. and is only 
* intended for use with Renesas products. No other uses are authorized.
*
* This software is owned by Renesas Electronics Corp. and is protected under 
* all applicable laws, including copyright laws.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.
*
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORP. NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
*
* http://www.renesas.com/disclaimer

*""FILE COMMENT""***************************************************************
* System Name	: RAJ240090/100 sample code
* File Name		: datcalc_spl.h
* Contents		: SMBus data calculating function header file
* Device		: RAJ240090/100
* Compiler		: CC-RL (V.1.04)
* Note			: 
*""FILE COMMENT END""**********************************************************/

#ifndef _DATCALC_SPL_H
#define _DATCALC_SPL_H


#include "base_types.h"

/***********************************************************************
Global functions
***********************************************************************/
extern void Calc_RC(void);						// RemainingCapacity() calc
extern void Make_RC(void);						// RC calc from integration
extern void Calc_CC(void);						// CycleCount() calc
extern void Init_Cap(void);						// Initial capacity calc
extern void Calc_RSOC(void);
extern void ClearStudey(void);
extern void Calc_iRSOC(void);
extern void Make_iRC(void);
extern void ful_chg_acc_cap_updated(void);

// - Internal functions - 
void FCC_Limit_Chk(void);						// FCC Limit check function

// - Grobal variable -
extern uint8_t		arelearn_cnt;					// Relearn counter
extern uint16_t		toldrc;							// last RemCap value
extern uint16_t		tdfup_cnt;						// DataFlash update counter 
extern uint32_t		lmaxerr_cnt;					// MaxError integration counter
extern uint16_t		tccup;							// CycleCount increment cap.
extern uint32_t		lrlstp_cnt;						// Relearn stop time counter

extern uint16_t		tcom10c_w;						// FCC temporary save area
extern uint16_t		tcph_v;							// CP_H
extern uint16_t		tcpl_v;							// CP_L
extern uint8_t		arcflg;							// Flags for RC
extern uint16_t     t_0PVOLT;                         // 0 % Voltage
//extern int16_t      lastFccTemp;               		//Calc Fcc last Temp
extern int32_t		lrccr_w;						// Charge relearn capacity
extern int32_t		lrcdr_w;						// Discharge relearn capacity
extern uint16_t  	tcom2a_w;
extern uint16_t oldNcc;
//extern uint16_t t_com17_new;
extern uint16_t t_com0f_cwh;
extern uint16_t t_com10_cwh;
extern uint8_t  f_study_d1 ;
extern uint8_t  f_study_d2 ;
extern uint32_t cap_accmu_chg_update ;
extern uint16_t fcc_last_cpl_pinghua  ;


 extern uint8_t f_ful_chg_once ;
// extern uint8_t  f_chg_update_20 ;

//extern uint8_t  f_init_first_time; 
// extern uint16_t fcc_last ;

 typedef union
 {
   uint8_t data;
   struct
   {
     uint8_t discharge_last : 1;
     uint8_t init_first_time : 1;
     uint8_t chg_update_20 : 1; // kpfa2
     uint8_t ful_chg_acc_cap_updated : 1;
     uint8_t chg_last_state : 1;
     uint8_t pinghua_work : 1; // kpfa2
     uint8_t pinghua_conditon : 1;
     uint8_t cap_detected_20rc : 1;

   } FLAG_PINGHUA_f;
 } nFLAG_PINGHUA;
extern nFLAG_PINGHUA		FLAG_PINGHUA;
#define f_20rc_cap_detected              FLAG_PINGHUA.FLAG_PINGHUA_f.cap_detected_20rc  // kpfa2 20240511
#define f_pinghua_work                   FLAG_PINGHUA.FLAG_PINGHUA_f.pinghua_work
#define f_pinghua_conditon               FLAG_PINGHUA.FLAG_PINGHUA_f.pinghua_conditon
#define f_chg_update_20                  FLAG_PINGHUA.FLAG_PINGHUA_f.chg_update_20  // kpfa2 20240511
#define f_ful_chg_acc_cap_updated        FLAG_PINGHUA.FLAG_PINGHUA_f.ful_chg_acc_cap_updated
#define f_chg_last_state                 FLAG_PINGHUA.FLAG_PINGHUA_f.chg_last_state
#define f_init_first_time                FLAG_PINGHUA.FLAG_PINGHUA_f.init_first_time
#define  f_discharge_last                FLAG_PINGHUA.FLAG_PINGHUA_f.discharge_last
extern uint8_t t_com0drsoclast; 

extern int8_t CellTemp_last_time_update ; 

// - bit / union variable definition -								// Flags for RC
#define f_studied	DEF_BIT2(&arcflg)			// relearned flag



#endif
