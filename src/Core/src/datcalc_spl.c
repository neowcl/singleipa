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
* System Name	: RAJ240090/100 sample program
* File Name		: datcalc_spl.c
* Contents		: Data calculation function source file
* Device		: RAJ240090/100
* Compiler		: CC-RL (V.4.01)
* Note			:
*""FILE COMMENT END""**********************************************************/
#include "datcalc_spl.h" // datcalc_spl.c
#include "Cell.h"		 // cell.c
#include "Ram.h"
#include "bi2cs_interface.h"
// #include "Calc_CVT.h"
#include "standard_data_cmd.h"
#include "Protect.h"

uint8_t arelearn_cnt; // Relearn counter
uint16_t toldrc;	  // last RemCap value
uint16_t tdfup_cnt;	  // DataFlash update counter
uint32_t lmaxerr_cnt; // MaxError integration counter
uint16_t tccup;		  // CycleCount increment cap.
uint32_t lrlstp_cnt;  // Relearn stop time counter

uint16_t tcom10c_w; // FCC temporary save area
uint16_t tcph_v;	// CP_H
uint16_t tcpl_v;	// CP_L
uint8_t arcflg;		// Flags for RC
uint16_t t_0PVOLT;	// 0 % Voltage
uint16_t IdealFcc_last;

int32_t lrccr_w; // Charge relearn capacity
int32_t lrcdr_w; // Discharge relearn capacity
uint16_t tcom2a_w;
// int16_t    	lastFccTemp;

uint16_t t_com0f_cwh;
uint16_t t_com10_cwh;
// uint16_t    t_com17_new;
uint8_t sochold1;
uint8_t isochold1;
uint8_t Count_0volt;
uint8_t Count_0Vlt_soctimehold0 ;

uint8_t f_study_d1;
uint8_t f_study_d2;
uint8_t f_bat_init;
uint8_t f_count3s_en;
uint8_t f_count3s_en_b;
uint8_t f_bigger_than_zero;
uint8_t count_3s;
uint8_t f_cp_l_off_delay_count ;
// uint8_t cp_updated;
// uint16_t fcc_last ;

uint32_t cap_accmu_chg_update;
uint32_t accu_chg_cap;

uint32_t keep_rc_rsoc20 = 0;
uint8_t t_com0drsoclast;
int8_t pinghua_soc_start;
uint8_t buchang_conditon_cnt; // condition reach  + 1
int16_t temp_Current;
int16_t current_dsg_keep;

uint8_t save_soc;
int16_t keep_volt_new = 0;

int16_t save_volta;
int16_t voltage_new;
int16_t volt_keep[3];
int16_t curr_keep[3];
uint8_t i;
uint8_t j;
uint16_t rsoc_enlarge_1000 ;

uint8_t f_chg_last2;

uint8_t f_ful_chg_once;

uint8_t f_start_add_chg;
uint32_t leiji;

uint16_t chg_pinghua_current;

int8_t dsg_upfcc_keep_temp;
uint8_t f_discharge_last2;
int16_t dsg_upfcc_keep_current;
uint16_t save_dsg_upd_fcc;
uint16_t save_fac_dsg_upd;
uint8_t f_relax_last_dsgupdate_use  ; 
uint8_t	f_charge_last_dsgupdate_use  ;


// dsg inner  resis
uint8_t f_cnt_30m_start;
uint8_t f_chg_last_state1;
uint8_t f_cnt_30m_start;
uint16_t cnt_30m;
uint8_t cnt5_i; //
uint8_t f_relex3_last;
uint8_t cnt5_j;
// uint16_t save_volstart_dsg_inner;
// uint16_t save_volend_dsg_inner;
uint8_t f_start_save;
uint8_t f_cp_h_fccupdated ;
uint8_t	f_cp_l_fccupdated ;
int32_t lrc_w_last ;
int8_t CellTemp_last_time_update ; 

// uint16_t  inner_res_dsg_100 ;  // t_com2a
// uint16_t  temp_dsg_inner_res;  // t_com2b

uint16_t Vol3[5];

// uint16_t outer_tinreg ;
uint16_t inner_res_old_buchang_vol;
uint16_t inner_res_buchang_vol;
uint16_t f_calc_inner_3res_work = 0;

int16_t dis_fac_cpl = 100  ; // discharge factor when reach cpl voltage .
int16_t t_com0dlast ; 
uint8_t f_cp_l_last ;
uint16_t fcc_last_cpl_pinghua  ;

// dsg inner  resis

nFLAG_PINGHUA FLAG_PINGHUA;

/***********************************************************************
** Announcement of internal function prototype
***********************************************************************/
static void Calc_NormalRC(uint32_t lrc);

void Calc_inner_3res(void)
{
	uint32_t restemp_vol;

	if (t_com0d != 100 || f_fullchg == OFF || f_charge == ON)
	{
		f_cnt_30m_start = 0;
		cnt5_i = 0;
		cnt5_j = 0;
		cnt_30m = 0;
		f_start_save = 0;
		f_cnt_30m_start = 0;
	}

	if (f_fullchg && f_chg_last_state1 == ON && f_charge == OFF && f_relax == ON)
	{

		f_cnt_30m_start = 1; // 1. fullchg 2. last state chg 3. this state relax
	}

	f_chg_last_state1 = f_charge;
	// //1. fullchg 2. last state chg 3. this state relax , start count
	if (f_cnt_30m_start == 1)
	{
		cnt_30m++;
		if (cnt_30m >= 1795)
		{
			Vol3[cnt5_i] = t_com09; //
			//	Cur3[cnt5_i] = t_com0a;
			cnt5_i++;
			if (cnt5_i >= 5)
			{
				cnt5_i = 0;
			}
			if (cnt_30m >= 1800)
			{
				cnt_30m = 1800;
				if (f_relex3_last == ON && f_discharge == ON)
				{
					save_volstart_dsg_inner = Vol3[cnt5_i];
					// save_curstart_inner = tabsc ;
					f_start_save = 1;
				}
				if (f_start_save == 1 && f_discharge == ON)
				{
					cnt5_j++;
				}

				if (cnt5_j >= 5)
				{
					cnt5_i = 0;
					cnt5_j = 0;
					cnt_30m = 0;
					f_start_save = 0;
					f_cnt_30m_start = 0;
					// save_curend_dsg_inner = tabsc ;
					// save_volend_dsg_inner = t_com09 ;

					if (tabsc > t_com18 / 10 && tabsc < t_com18 / 2) // t_com18  Design Capacity
					{
						// (volt start - vol end ) / tabsc
						save_volend_dsg_inner = t_com09;
						restemp_vol = save_volstart_dsg_inner - save_volend_dsg_inner;
						save_tabsc3 = tabsc;
						inner_res_dsg_100 = restemp_vol * 1000 / tabsc; // the result of inner resistance
						temp_dsg_inner_res = CellTemp;
						f_calc_inner_3res_work = 1;
					}
				}
			}
			else
			{
				f_start_save = 0;
			}
		}
	}
	f_relex3_last = f_relax;
}

/*""FUNC COMMENT""***************************************************
 * ID			: 1.0
 * module outline: Internal resistance calculation function
 *-------------------------------------------------------------------
 * Include		:
 *-------------------------------------------------------------------
 * Declaration	: WORD Calc_InReg(void)
 *-------------------------------------------------------------------
 * Function		:
 *				: Calculate capacity correction voltage adjusting value
 *				: by increasing the internal resistance.
 *-------------------------------------------------------------------
 * Argument		: None
 *-------------------------------------------------------------------
 * Return		: WORD	: Correction voltage
 *-------------------------------------------------------------------
 * Input			: None
 * Output		: None
 *-------------------------------------------------------------------
 * Used function :
 *-------------------------------------------------------------------
 * Caution		:
 *-------------------------------------------------------------------
 * History		: 2012.08.01 Ver 0.01
 * 				: New create
 *
 *""FUNC COMMENT END""**********************************************/
uint16_t Calc_InReg(void)
{
	uint8_t awork1, awork2;
	uint16_t twork1, twork2;
	uint8_t al1;
	// Search the index
	for (al1 = 0; t_com17 >= INREG_CYCLE[al1] && al1 < 5; al1++)
		;
	// Set each correction data
	if (al1 == 0) // First index ?
	{
		awork1 = 0;
		awork2 = INREG_TBL[0];
		twork1 = t_com17;
		twork2 = INREG_CYCLE[0];
	}
	else
	{ // 2nd or more
		al1--;
		awork1 = INREG_TBL[al1];
		awork2 = INREG_TBL[al1 + 1] - INREG_TBL[al1];
		twork1 = t_com17 - INREG_CYCLE[al1];
		twork2 = INREG_CYCLE[al1 + 1] - INREG_CYCLE[al1];
	}
	// Correction voltage[mV] = Internal resistance x Current / 1000
	return ((((uint32_t)awork2 * twork1 / twork2) + awork1) * tabsc / 1000);
}

uint16_t Calc_InRegFcc(void)
{
	uint16_t awork1, awork2;
	uint16_t twork1, twork2;
	uint8_t al1;
	// Search the index
	for (al1 = 0; t_com17 >= INREG_CYCLE[al1] && al1 < 5; al1++)
		;
	// Set each correction data
	if (al1 == 0) // First index ?
	{
		awork1 = 0;
		awork2 = INREG_FCC[0];
		twork1 = t_com17;
		twork2 = INREG_CYCLE[0];
	}
	else
	{ // 2nd or more
		al1--;
		awork1 = INREG_FCC[al1];
		awork2 = INREG_FCC[al1 + 1] - INREG_FCC[al1];
		twork1 = t_com17 - INREG_CYCLE[al1];
		twork2 = INREG_CYCLE[al1 + 1] - INREG_CYCLE[al1];
	}
	return (((uint32_t)awork2 * twork1 * 100 / twork2) + awork1 * 100);
}

void Calc_factor_of_fcc(void)
{
	uint8_t aidx;
	uint8_t awork1, awork2, awork3, awork4;
	uint16_t twork1, twork2;
	uint16_t tinreg;
	int32_t ccwork;
	int32_t dcwork;

	// Calc [C]x100 from current
	twork1 = (uint16_t)((long)tabsc * 100 / D_DCAP); // eg :   3600 mAh  = 3600mA * 1h

	// - Make [C]index -
	// linear interporation: y = (y2-y1)*(x-x1)/(x2-x1) + y1
	//						   = y1 - (y1-y2)*(x-x1)/(x2-x1)
	// awork1: x-x1
	// awork2: x2-x1
	if (twork1 <= D_CRATE_TBL[1]) // <= C-rate2 ?
	{
		aidx = 0;					  // Table index = 0
		if (twork1 <= D_CRATE_TBL[0]) // <= C-rate1 ?
		{
			awork1 = 0; // SetC-rate1
		}
		else
		{ // > C-rate1
			// Calculate value index
			awork1 = (uint8_t)(twork1 - D_CRATE_TBL[0]);
		}

		// Data area is within C-rate1 to C-rate2
		awork2 = D_CRATE_TBL[1] - D_CRATE_TBL[0];
	}
	else
	{								  // > C-rate2
		if (twork1 <= D_CRATE_TBL[2]) // <= C-rate3 ?
		{
			aidx = 5; // Table index = 5
			// Calculate value index
			awork1 = (uint8_t)(twork1 - D_CRATE_TBL[1]);
			// Data area is within C-rate2 to C-rate3
			awork2 = D_CRATE_TBL[2] - D_CRATE_TBL[1];
		}
		else
		{			   // > C-rate3
			aidx = 10; // Table index = 10
			twork1 = twork1 - D_CRATE_TBL[2];
			if (twork1 > 255) // bigger than 1byte value ?
			{
				awork1 = 255; // Set max value
			}
			else
			{
				awork1 = (uint8_t)twork1;
			}
			// Data area is within C-rate3 to C-rate4
			awork2 = D_CRATE_TBL[3] - D_CRATE_TBL[2];
		}
	}

	// - Make Temperature index -
	awork3 = CellTemp - D_TRATE_TBL[0]; // Make the value of T-rate1 base
	if (CellTemp >= D_TRATE_TBL[1])		// >= T-rate2 ?
	{
		aidx++;							// Increment table index
		if (CellTemp >= D_TRATE_TBL[2]) // >= T-rate3 ?
		{
			aidx++;							// Increment table index
			if (CellTemp >= D_TRATE_TBL[3]) // >= T-rate4 ?
			{
				aidx++; // Increment table index
						// Data area is within T-rate4 to T-rate5
				awork4 = D_TRATE_TBL[4] - D_TRATE_TBL[3];
				if (CellTemp >= D_TRATE_TBL[4]) // >= T-rate5 ?
				{
					awork3 = awork4; // Value index is max value
				}
				else
				{ // T-rate4 <= Temp. < T-rate5
				  // Calculate value index
					awork3 = CellTemp - D_TRATE_TBL[3];
				}
			}
			else
			{ // T-rate3 <= Temp. < T-rate4
			  // Data area is within T-rate3 to T-rate4
				awork4 = D_TRATE_TBL[3] - D_TRATE_TBL[2];
				// Calculate value index
				awork3 = CellTemp - D_TRATE_TBL[2];
			}
		}
		else
		{ // T-rate2 <= Temp. < T-rate3
			// Data area is within T-rate2 to T-rate3
			awork4 = D_TRATE_TBL[2] - D_TRATE_TBL[1];
			awork3 = CellTemp - D_TRATE_TBL[1]; // Calculate value index
		}
	}
	else
	{ // < T-rate2
		// Data area is within T-rate1 to T-rate2
		awork4 = D_TRATE_TBL[1] - D_TRATE_TBL[0];

		if (CellTemp <= D_TRATE_TBL[0]) // <= T-rate1 ?
		{
			awork3 = 0; // Value index = 0
		}
	}

	if (aidx >= 10 && awork1 > awork2) // > C-Rate4 ?
	{
		// Calculate by coefficient
		twork1 = QCAP_TBL[aidx + 5] - // Coefficient/((C-rate4 - C-rate3)*10
				 (uint16_t)((((long)QCAP_TBL[aidx] - QCAP_TBL[aidx + 5]) * (awork1 - awork2) * D_FCCCOE / ((uint16_t)awork2 * 10)));

		twork2 = QCAP_TBL[aidx + 6] -
				 (uint16_t)((((long)QCAP_TBL[aidx + 1] - QCAP_TBL[aidx + 6]) * (awork1 - awork2) * D_FCCCOE / ((uint16_t)awork2 * 10)));
	}
	else
	{ // <= C-Rate4
		twork1 = QCAP_TBL[aidx] -
				 (uint16_t)((((long)QCAP_TBL[aidx] - QCAP_TBL[aidx + 5]) * awork1 / awork2));

		twork2 = QCAP_TBL[aidx + 1] -
				 (uint16_t)((((long)QCAP_TBL[aidx + 1] - QCAP_TBL[aidx + 6]) * awork1 / awork2));
	}

	Dischargefactor = twork1 + (uint16_t)((((long)twork2 - twork1) * awork3 / awork4)); // discharge Q

	if (Dischargefactor)
	{
		save_fac_dsg_upd = Dischargefactor;
		// save_dsg_upd_fcc = t_com10 ;
	}
}

/*""FUNC COMMENT""***************************************************
 * ID			: 1.0
 * module outline: Correction voltage calculation function
 *-------------------------------------------------------------------
 * Include		:
 *-------------------------------------------------------------------
 * Declaration	: void Calc_CPVolt(void)
 *-------------------------------------------------------------------
 * Function		: CP_H,CP_L
 *				: Calculate correction voltage CP_H and CP_L.
 *-------------------------------------------------------------------
 * Argument		: None
 *-------------------------------------------------------------------
 * Return		: None
 *-------------------------------------------------------------------
 * Input			: None
 * Output		: CP_H : Voltage of correction point high
 *				: CP_L : Voltage of correction point low
 *-------------------------------------------------------------------
 *Used function 	: Calc_InReg()
 *-------------------------------------------------------------------
 * Caution		:
 *-------------------------------------------------------------------
 * History		: 2012.08.01 Ver 0.01
 * 				: New create
 *
 *""FUNC COMMENT END""**********************************************/
void Calc_CPVolt(void)
{
	uint8_t aidx;
	uint8_t awork1, awork2, awork3, awork4;
	uint16_t twork1, twork2;
	uint16_t tinreg;
	int32_t ccwork;
	int32_t dcwork;

	// Calc [C]x100 from current
	twork1 = (uint16_t)((long)tabsc * 100 / D_DCAP); // eg :   3600 mAh  = 3600mA * 1h

	// - Make [C]index -
	// linear interporation: y = (y2-y1)*(x-x1)/(x2-x1) + y1
	//						   = y1 - (y1-y2)*(x-x1)/(x2-x1)
	// awork1: x-x1
	// awork2: x2-x1
	if (twork1 <= D_CRATE_TBL[1]) // <= C-rate2 ?
	{
		aidx = 0;					  // Table index = 0
		if (twork1 <= D_CRATE_TBL[0]) // <= C-rate1 ?
		{
			awork1 = 0; // SetC-rate1
		}
		else
		{ // > C-rate1
			// Calculate value index
			awork1 = (uint8_t)(twork1 - D_CRATE_TBL[0]);
		}

		// Data area is within C-rate1 to C-rate2
		awork2 = D_CRATE_TBL[1] - D_CRATE_TBL[0];
	}
	else
	{								  // > C-rate2
		if (twork1 <= D_CRATE_TBL[2]) // <= C-rate3 ?
		{
			aidx = 5; // Table index = 5
			// Calculate value index
			awork1 = (uint8_t)(twork1 - D_CRATE_TBL[1]);
			// Data area is within C-rate2 to C-rate3
			awork2 = D_CRATE_TBL[2] - D_CRATE_TBL[1];
		}
		else
		{			   // > C-rate3
			aidx = 10; // Table index = 10
			twork1 = twork1 - D_CRATE_TBL[2];
			if (twork1 > 255) // bigger than 1byte value ?
			{
				awork1 = 255; // Set max value
			}
			else
			{
				awork1 = (uint8_t)twork1;
			}
			// Data area is within C-rate3 to C-rate4
			awork2 = D_CRATE_TBL[3] - D_CRATE_TBL[2];
		}
	}

	// - Make Temperature index -
	awork3 = CellTemp - D_TRATE_TBL[0]; // Make the value of T-rate1 base
	if (CellTemp >= D_TRATE_TBL[1])		// >= T-rate2 ?
	{
		aidx++;							// Increment table index
		if (CellTemp >= D_TRATE_TBL[2]) // >= T-rate3 ?
		{
			aidx++;							// Increment table index
			if (CellTemp >= D_TRATE_TBL[3]) // >= T-rate4 ?
			{
				aidx++; // Increment table index
						// Data area is within T-rate4 to T-rate5
				awork4 = D_TRATE_TBL[4] - D_TRATE_TBL[3];
				if (CellTemp >= D_TRATE_TBL[4]) // >= T-rate5 ?
				{
					awork3 = awork4; // Value index is max value
				}
				else
				{ // T-rate4 <= Temp. < T-rate5
				  // Calculate value index
					awork3 = CellTemp - D_TRATE_TBL[3];
				}
			}
			else
			{ // T-rate3 <= Temp. < T-rate4
			  // Data area is within T-rate3 to T-rate4
				awork4 = D_TRATE_TBL[3] - D_TRATE_TBL[2];
				// Calculate value index
				awork3 = CellTemp - D_TRATE_TBL[2];
			}
		}
		else
		{ // T-rate2 <= Temp. < T-rate3
			// Data area is within T-rate2 to T-rate3
			awork4 = D_TRATE_TBL[2] - D_TRATE_TBL[1];
			awork3 = CellTemp - D_TRATE_TBL[1]; // Calculate value index
		}
	}
	else
	{ // < T-rate2
		// Data area is within T-rate1 to T-rate2
		awork4 = D_TRATE_TBL[1] - D_TRATE_TBL[0];

		if (CellTemp <= D_TRATE_TBL[0]) // <= T-rate1 ?
		{
			awork3 = 0; // Value index = 0
		}
	}

	tinreg = Calc_InReg(); // Calc internal resistance V
	outer_tinreg = tinreg;

	// - Calculate CP_H voltage -
	// - [C] interpolation -
	if ((aidx >= 10) && (awork1 > awork2)) // > C-Rate 4 ?
	{
		// Calculate by coefficient
		twork1 = CPH_TBL[aidx + 5] - // Coefficient/((C-rate4 - C-rate3)*10
				 (uint16_t)((((long)CPH_TBL[aidx] - CPH_TBL[aidx + 5]) * (awork1 - awork2) * D_CPHCOE / ((uint16_t)awork2 * 10)));

		twork2 = CPH_TBL[aidx + 6] -
				 (uint16_t)((((long)CPH_TBL[aidx + 1] - CPH_TBL[aidx + 6]) * (awork1 - awork2) * D_CPHCOE / ((uint16_t)awork2 * 10)));
	}
	else
	{ // <= C-Rate 4
		twork1 = CPH_TBL[aidx] -
				 (uint16_t)((((long)CPH_TBL[aidx] - CPH_TBL[aidx + 5]) * awork1 / awork2));

		twork2 = CPH_TBL[aidx + 1] -
				 (uint16_t)((((long)CPH_TBL[aidx + 1] - CPH_TBL[aidx + 6]) * awork1 / awork2));
	}

	// - degC interpolation -
	tcph_v = twork1 + (uint16_t)((((long)twork2 - twork1) * awork3 / awork4)) - tinreg;

	// - Calculate CP_L voltage -
	// - [C] interpolation -
	if (aidx >= 10 && awork1 > awork2) // > C-Rate4 ?
	{
		// Calculate by coefficient
		twork1 = CPL_TBL[aidx + 5] - // Coefficient/((C-rate4 - C-rate3)*10
				 (uint16_t)((((long)CPL_TBL[aidx] - CPL_TBL[aidx + 5]) * (awork1 - awork2) * D_CPLCOE / ((uint16_t)awork2 * 10)));

		twork2 = CPL_TBL[aidx + 6] -
				 (uint16_t)((((long)CPL_TBL[aidx + 1] - CPL_TBL[aidx + 6]) * (awork1 - awork2) * D_CPLCOE / ((uint16_t)awork2 * 10)));
	}
	else
	{ // <= C-Rate4
		twork1 = CPL_TBL[aidx] -
				 (uint16_t)((((long)CPL_TBL[aidx] - CPL_TBL[aidx + 5]) * awork1 / awork2));

		twork2 = CPL_TBL[aidx + 1] -
				 (uint16_t)((((long)CPL_TBL[aidx + 1] - CPL_TBL[aidx + 6]) * awork1 / awork2));
	}

	// - degC interpolation -
	tcpl_v = twork1 + (uint16_t)((((long)twork2 - twork1) * awork3 / awork4)) - tinreg;

	if(tcph_v <= 3450 )
	{
		tcph_v = 3450 ;
	}else if(tcph_v >= 3964)  // data come from data cph table 
	{
		tcph_v = 3964 ;
	}

	// if (tcpl_v <= (D_0PVOLT + 50))
	// {
	// 	tcpl_v = D_0PVOLT+50;
	// }
	if (tcpl_v <= (t_com33 + 50))
	{
		tcpl_v = t_com33+50;
	}
	else if (tcpl_v >= 3638) // data come from data cph table
	{
		tcpl_v = 3638 ;
	}

	/*******************************IdeaRC******************************************************/
	if (aidx >= 10 && awork1 > awork2) // > C-Rate4 ?
	{
		// Calculate by coefficient
		twork1 = QCAP_TBL[aidx + 5] - // Coefficient/((C-rate4 - C-rate3)*10
				 (uint16_t)((((long)QCAP_TBL[aidx] - QCAP_TBL[aidx + 5]) * (awork1 - awork2) * D_FCCCOE / ((uint16_t)awork2 * 10)));

		twork2 = QCAP_TBL[aidx + 6] -
				 (uint16_t)((((long)QCAP_TBL[aidx + 1] - QCAP_TBL[aidx + 6]) * (awork1 - awork2) * D_FCCCOE / ((uint16_t)awork2 * 10)));
	}
	else
	{ // <= C-Rate4
		twork1 = QCAP_TBL[aidx] -
				 (uint16_t)((((long)QCAP_TBL[aidx] - QCAP_TBL[aidx + 5]) * awork1 / awork2));

		twork2 = QCAP_TBL[aidx + 1] -
				 (uint16_t)((((long)QCAP_TBL[aidx + 1] - QCAP_TBL[aidx + 6]) * awork1 / awork2));
	}

	Dischargefactor = twork1 + (uint16_t)((((long)twork2 - twork1) * awork3 / awork4)); // discharge Q

	if (Dischargefactor)
	{
		ccwork = (int32_t)tabsc * 1000 / Dischargefactor; // discharge Current Q
		dcwork = ccwork - tabsc;						  //	discharge Q Cap
		Ilrc_w -= ccwork;								  //  IdeaRC
		Del_lrc += dcwork;								  //  DelDischargeCapacity
	}
	else
	{
		Ilrc_w -= tabsc; //  IdeaRC
		Del_lrc += 0;	 //  DelDischargeCapacity
	}

	if (Ilrc_w < 0)
	{
		Ilrc_w = 0;
	}

	if (t_com10 != t_com0f)
	{
		if (Del_lrc > 0)
		{
			// Chargefactor = (long)(ABS(Del_lrc) + (long)(t_com10 - t_com0f)*3600)*1000/((long)(t_com10 - t_com0f)*3600);
			Chargefactor = (uint16_t)((long)ABS(Del_lrc) * 10 / (long)((t_com10 - t_com0f) * 36)) + 1000;
		}
		else
		{
			Chargefactor = (long)(t_com10 - t_com0f) * 36000 / ((long)(t_com10 - t_com0f) * 36 + ABS(Del_lrc) / 100);
		}
	}
	else
	{
		if (Del_lrc > 0)
		{
			// Chargefactor = (long)(ABS(Del_lrc) + 3600)*1000/3600;
			Chargefactor = (uint16_t)((long)ABS(Del_lrc) * 10 / 36 + 1000);
		}
		else
		{
			Chargefactor = (uint16_t)(3600000 / ((long)3600 + ABS(Del_lrc)));
		}
	}
	/***********************************************************************************************/

	tinreg = Calc_InRegFcc();

	if (t_com17 > 10)
	{
		t_com2e = ((uint32_t)D_DCAP * (10000 - tinreg) / 100 + D_DCAP / 2) / D_DCAP;
		if (t_com2e > 100)
		{
			t_com2e = 100;
		}
	}
	tcph_v_out = tcph_v;		
	tcpl_v_out = tcpl_v;		
}

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: RemainingCapacity() Calculation Function
 *--------------------------------------------------------------------------
 * Include			:
 *--------------------------------------------------------------------------
 * Declaration		: void Make_RC(void)
 *--------------------------------------------------------------------------
 * Function			: Calculate RemainingCapacity() from RC integration work.
 *					:
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: None
 *--------------------------------------------------------------------------
 * Input			: lrc_w		: RC integration work
 *					:
 * Output			: t_com0fc	: RemainingCapacity() [mAh]
 *					:
 *--------------------------------------------------------------------------
 * Used function	:
 *					:
 *--------------------------------------------------------------------------
 * Caution			:
 *--------------------------------------------------------------------------
 *""FUNC COMMENT END""*****************************************************/
void Make_RC(void) // RC more than fcc , from full charge will go down
{
	uint16_t twork;
	twork = (uint16_t)(lrc_w / (60 * 60)); // RC = RC_W / (60min*60sec) FCC * aresult / 100 * 3600
	if (twork > t_com10)				   // RC > FCC ?
	{
		lrc_w = t_com10 * 60 * 60;
		t_com0f = t_com10; // RC = FCC
	}
	else
	{
		t_com0f = twork; // RC <= FCC
	}
}

void Make_iRC(void)
{
	uint16_t twork;

	twork = (uint16_t)(Ilrc_w / (60 * 60)); // RC = RC_W / (60min*60sec)

	if (twork > IdealFcc) // RC > FCC ?
	{
		IdealRc = IdealFcc; // RC = FCC
	}
	else
	{
		IdealRc = twork; // RC <= FCC
	}
}

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: Function of capacity calculation while
 * 					: discharging and voltage is higher than CP_H.
 *--------------------------------------------------------------------------
 * Include			:
 *--------------------------------------------------------------------------
 * Declaration		: void Calc_NormalRC(DWORD lrc)
 *--------------------------------------------------------------------------
 * Function			: It calculates capacity while discharging and
 *					:  the voltage is higher than CP_H.
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: None
 *--------------------------------------------------------------------------
 * Input			: None
 *					:
 * Output			: lrc_w		: RC integration work
 *					:
 *--------------------------------------------------------------------------
 * Used function	:
 *					:
 *--------------------------------------------------------------------------
 * Caution			:
 *--------------------------------------------------------------------------
 *""FUNC COMMENT END""*****************************************************/
static void Calc_NormalRC(uint32_t lrc)
{
	uint32_t lwork;

	if (f_study_d == ON) // Now discharge relearning ?
	{
		lrcdr_w += lrc; // Integrate discharge rel.cap
	}
	// CP_x capacity = FCC*60*60*(D_CP_x/100)
	//               = FCC*D_CP_x*36
	// lwork = (uint32_t)t_com10 * D_CP_H * 36; // Calculate CP_H capacity
	// if (lrc_w < lwork)						 // Correction cap < CP_H cap ?
	// {
	// 	// lrc /= 2; // Correction coefficient = 0.5  . to solve the problem of when FCC cph , hold much time .
	// 	// 1% percent 5minutes , err 1% , lower time/2 .
	// 	lrc /= 1; // Correction coefficient = 0.5
	// }
	lrc_w -= lrc; // Substruct correction value

	if (lrc_w <= 0)
	{
		lrc_w = 0; // Set 0
	}
	if (lrc_w_last <= 0)
	{
		lrc_w_last = 0; // 40 is right number ,since t_com10*36/3600 ,maybe rsoc == 0 ;
	}

	// lwork = (uint32_t)t_com10 * D_CP_L * 36; // Calculate CP_L capacity
	// if (lrc_w < lwork)						 // Correction cap < CP_L cap ?
	// {
	// 	lrc_w = lwork; // Correction cap hold to CP_H cap
	// }

	// if(f_relax == ON && f_init_first_time==0)  //如何保证不复位的情况。
	// if (!f_charge)  // at frist time come in .   can not use f_charge ,
}

//  clear  full charge update flag  in function void Calc_RSOC(void)

void clr_flg_fulchg_update(void)
{
	keep_rc_rsoc20 = 0;
	cap_accmu_chg_update = 0;
	f_20rc_cap_detected = 0;
	f_chg_update_20 = 0;
	voltage_new = 0;
	current_dsg_keep = 0;
	// save_volta = 0; // 动态变化  // save voltage   should not zhushi ,want to see the data
	// save_soc = 0;	// save soc at this moment
	for (int k_clear = 0; k_clear < 3; k_clear++)
	{
		volt_keep[k_clear] = 0;
		curr_keep[k_clear] = 0;
	}

	f_bat_init = 0;
}

void Dsg_Update_FCC(void)
{
	uint8_t aidx;
	uint8_t awork1, awork2, awork3, awork4;
	uint16_t twork1, twork2;
	int32_t ccwork;
	int32_t dcwork;

	uint16_t dsg_upd_facd32_inner;		 // this time dsg update factor   , use outer last time .
	uint16_t dsg_upd_factor32_last;		 // dsg factor of last time
	uint16_t FCC_up_dsg_last32bit_inner; // 	FCC  of last time for update .
	uint16_t FCC_dsg_up;				 // FCC data of this time .   use these 32 bits temperary datas for caculate .
	uint16_t temp_result;

	twork1 = (uint16_t)((long)dsg_upfcc_keep_current *100 / D_DCAP); // eg :   3600 mA.h  = 3600mA * 1h

	if (twork1 <= D_CRATE_TBL[1]) // <= C-rate2 ?
	{
		aidx = 0;					  // Table index = 0
		if (twork1 <= D_CRATE_TBL[0]) // <= C-rate1 ?
		{
			awork1 = 0; // SetC-rate1
		}
		else
		{ // > C-rate1
			// Calculate value index
			awork1 = (uint8_t)(twork1 - D_CRATE_TBL[0]);
		}

		// Data area is within C-rate1 to C-rate2
		awork2 = D_CRATE_TBL[1] - D_CRATE_TBL[0];
	}
	else
	{								  // > C-rate2
		if (twork1 <= D_CRATE_TBL[2]) // <= C-rate3 ?
		{
			aidx = 5; // Table index = 5
			// Calculate value index
			awork1 = (uint8_t)(twork1 - D_CRATE_TBL[1]);
			// Data area is within C-rate2 to C-rate3
			awork2 = D_CRATE_TBL[2] - D_CRATE_TBL[1];
		}
		else
		{									  // > C-rate3
			aidx = 10;						  // Table index = 10
			twork1 = twork1 - D_CRATE_TBL[2]; // twork1 means crate:  current / designs apaity
			if (twork1 > 255)				  // bigger than 1byte value ?  twork u16 1.25
			{
				awork1 = 255; // Set max value
			}
			else
			{
				awork1 = (uint8_t)twork1; // store rate difference
			}
			// Data area is within C-rate3 to C-rate4
			awork2 = D_CRATE_TBL[3] - D_CRATE_TBL[2]; // store range difference
		}
	}

	// - Make Temperature index -
	awork3 = dsg_upfcc_keep_temp - D_TRATE_TBL[0]; // Make the value of T-rate1 base
	
	if (dsg_upfcc_keep_temp >= D_TRATE_TBL[1])	   // >= T-rate2 ?
	{
		aidx++;									   // Increment table index
		if (dsg_upfcc_keep_temp >= D_TRATE_TBL[2]) // >= T-rate3 ?
		{
			aidx++;									   // Increment table index
			if (dsg_upfcc_keep_temp >= D_TRATE_TBL[3]) // >= T-rate4 ?
			{
				aidx++; // Increment table index
						// Data area is within T-rate4 to T-rate5
				awork4 = D_TRATE_TBL[4] - D_TRATE_TBL[3];
				if (dsg_upfcc_keep_temp >= D_TRATE_TBL[4]) // >= T-rate5 ?
				{
					awork3 = awork4; // Value index is max value
				}
				else
				{ // T-rate4 <= Temp. < T-rate5
				  // Calculate value index
					awork3 = dsg_upfcc_keep_temp - D_TRATE_TBL[3];
				}
			}
			else
			{ // T-rate3 <= Temp. < T-rate4
			  // Data area is within T-rate3 to T-rate4
				awork4 = D_TRATE_TBL[3] - D_TRATE_TBL[2];
				// Calculate value index
				awork3 = dsg_upfcc_keep_temp - D_TRATE_TBL[2];
			}
		}
		else
		{ // T-rate2 <= Temp. < T-rate3
			// Data area is within T-rate2 to T-rate3
			awork4 = D_TRATE_TBL[2] - D_TRATE_TBL[1];
			awork3 = dsg_upfcc_keep_temp - D_TRATE_TBL[1]; // Calculate value index
		}
	}
	else
	{ // < T-rate2
		// Data area is within T-rate1 to T-rate2
		awork4 = D_TRATE_TBL[1] - D_TRATE_TBL[0];

		if (dsg_upfcc_keep_temp <= D_TRATE_TBL[0]) // <= T-rate1 ?
		{
			awork3 = 0; // Value index = 0
		}
	}

	if (aidx >= 10 && awork1 > awork2) // > C-Rate4 ?
	{
		// Calculate by coefficient
		// twork1 = QCAP_TBL[aidx+5] -				// Coefficient/((C-rate4 - C-rate3)*10) = 0.6(awork1-awork2)/awork2
		// 	(uint16_t)((((long)QCAP_TBL[aidx]-QCAP_TBL[aidx+5])*(awork1-awork2)*D_FCCCOE/((uint16_t)awork2*10)));
		twork1 = QCAP_TBL[aidx + 5] - // Coefficient/((C-rate4 - C-rate3)*10) = 0.6(awork1-awork2)/awork2
				 (uint16_t)((((long)QCAP_TBL[aidx] - QCAP_TBL[aidx + 5]) * (awork1 - awork2) * 6 / ((uint16_t)awork2 * 10)));

		// 0.6 (awork1 - awork2 , aworkd1 = )
		// awork1 =  twork1-D_CRATE_TBL[2] ;
		// awork2 =  D_CRATE_TBL[3]-D_CRATE_TBL[2] ;
		// awork2 - awork1 = twork1 - D_CRATE_TBL[3] ;  when high rates , change a lot ?
		// twork2 = QCAP_TBL[aidx+6] -
		// 	(uint16_t)((((long)QCAP_TBL[aidx+1]-QCAP_TBL[aidx+6])*(awork1-awork2)*D_FCCCOE/((uint16_t)awork2*10)));
		twork2 = QCAP_TBL[aidx + 6] -
				 (uint16_t)((((long)QCAP_TBL[aidx + 1] - QCAP_TBL[aidx + 6]) * (awork1 - awork2) * 6 / ((uint16_t)awork2 * 10)));
	}
	else
	{ // <= C-Rate4
		twork1 = QCAP_TBL[aidx] -
				 (uint16_t)((((long)QCAP_TBL[aidx] - QCAP_TBL[aidx + 5]) * awork1 / awork2));

		twork2 = QCAP_TBL[aidx + 1] -
				 (uint16_t)((((long)QCAP_TBL[aidx + 1] - QCAP_TBL[aidx + 6]) * awork1 / awork2));
	}
	dsg_upd_facd32_inner = twork1 + (uint16_t)((((long)twork2 - twork1) * awork3 / awork4)); // new fcc factor

	// twrok1_out = twork1 ;
	// twrok2_out = twork2 ;
	// awrok3_out = awork3 ;
	// awrok4_out = awork4 ;

	// dsg_upd_facd32_inner = (dsg_upd_facd32_inner+1000)/ 2 ;  // new = (0ld + new ) / 2 ; 
	dsg_upd_facd32_inner = (dsg_upd_facd32_inner+save_fac_dsg_upd)/ 2 ;  // new = (0ld + new ) / 2 ; 

	old_factor = save_fac_dsg_upd;		  // to show out information   old factor
	new_factor = dsg_upd_facd32_inner;	  // new factor
	old_fcc = FCC_up_dsg_last32bit_inner; // to show out information    old fcc

	temp_result = (dsg_upd_facd32_inner * 10) / (save_fac_dsg_upd / 10);

	FCC_dsg_up = temp_result * (save_dsg_upd_fcc / 100) + temp_result * (save_dsg_upd_fcc % 100 / 10) / 10 + temp_result * (save_dsg_upd_fcc % 10) / 100;

	
	if (FCC_dsg_up > D_FCCMAXLIMIT)
	{
		FCC_dsg_up = D_FCCMAXLIMIT;
	}

	if (FCC_dsg_up < D_FCCMINLIMIT)
	{
		FCC_dsg_up = D_FCCMINLIMIT;
	}
	
	save_fac_dsg_upd = dsg_upd_facd32_inner; // save old fcc factor
											 // save updated fcc factor to a global parameter  .    new fcc far
											 // 用函数内部变量临时计算
	save_dsg_upd_fcc = FCC_dsg_up;			 // save new  updated FCC  // save fcc
	new_fcc = FCC_dsg_up;					 //
	t_com0f = FCC_dsg_up * t_com0d / 100;	 // RC = fcc * soc /100 ;
	lrc_w = t_com0f * 3600;					 // lrc_w = RC *3600 ;
	t_com10 = FCC_dsg_up;
	leiji = 0;
	count_3s = 0;
	f_count3s_en = 0;
	f_count3s_en_b = 0;
	f_ful_chg_once = 0;
	lrc_w_last= lrc_w ;
	t_com0dlast = t_com0d;
	fcc_last_cpl_pinghua = t_com10  ; 
	//}
	// out parameter only   save_dsg_upd_fcc ;  save_fac_dsg_upd ;
}

void Dsg_Update_work(void)
{
	if (f_chg_last2 == 0 && f_charge == 1) // 在任何温度 ？
	{
		f_start_add_chg = 1;
	}
	if (f_start_add_chg == 1 && f_charge == 1)
	{
		leiji += tabsc;
	}

	// 充着断了， 清除哪些标志位 。
	// 1. 温度设置为多少
	// 2. tabsc 设置值

	// if (CellTemp < 15)
	// {
	// f_ful_chg_once == 1 ) //(f_fullchg == ON && t_com0d == 100) // f_have_ever_fulchg

	if(t_com0d!=100)
	{
		f_ful_chg_once =0;
		// f_count3s_en = 0;
		if(!f_charge)
		{
			leiji = 0 ;
		}
	}
	// weiyi loudong  100 not real full 
	if ((f_ful_chg_once == 1) && (leiji/3600 > t_com10/2) && (f_relax == OFF && f_discharge == ON)&&(t_com0d==100))
	{
		f_count3s_en = 1; // global parameter ;
	}

	if (((f_relax_last_dsgupdate_use== ON || f_charge_last_dsgupdate_use == ON )&& f_discharge == ON)\
	&&((CellTemp_last_time_update-CellTemp >=10)||(CellTemp-CellTemp_last_time_update>=10)))
	{
		f_count3s_en_b = 1 ;
		// temperature condition ,no need rsoc  = 100 .
	}
	
	// f_discharge_last2 = f_discharge;  // put this outer if sentece will be better  ?

	if ((f_count3s_en == 1 || f_count3s_en_b == 1 ) && f_discharge == ON && tabsc> 300)
	{
		count_3s++;

		if((f_count3s_en_b == 1 )&&(count_3s <= 5) )  // temperature keep 5s  change > 10 degree 
		{
			if(!((CellTemp_last_time_update-CellTemp >= 10)||(CellTemp-CellTemp_last_time_update>=10)))
			{
				f_count3s_en_b = 0 ;
				count_3s = 0;
			}
		}

		if (count_3s == 5)
		{
			// save data :
			count_3s = 0;
			f_count3s_en = 0;
			f_count3s_en_b = 0;
			dsg_upfcc_keep_current = tabsc; // this time should be        save current
			dsg_upfcc_keep_temp = CellTemp; // save temperature

			if (f_bigger_than_zero != 1) // if have dischg relearn updated ,use that conditon ,if not , use 25du condition
			{
				f_bigger_than_zero = 1;
				save_dsg_upd_fcc = t_com10;
				save_fac_dsg_upd = 1000;
			}
			Dsg_Update_FCC();
			CellTemp_last_time_update= CellTemp ;
			// to do function work .
			// save data  ?
		}
		// function start to work
	}
	else
	{
		count_3s = 0;
	}
	//
	f_discharge_last2 = f_discharge;
	f_relax_last_dsgupdate_use = f_relax ; 
	f_charge_last_dsgupdate_use = f_charge ;

}

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: RelativeStateOfCharge() Calculation Function
 *--------------------------------------------------------------------------
 * Include			:
 *--------------------------------------------------------------------------
 * Declaration		: void Calc_RSOC(void)
 *--------------------------------------------------------------------------
 * Function			: Calculate RelativeStateOfCharge()
 *					:
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: None
 *--------------------------------------------------------------------------
 * Input			: None
 *					:
 * Output			: t_com0d	: RelativeStateOfCharge()
 *					:
 *--------------------------------------------------------------------------
 * Used function	:
 *					:
 *--------------------------------------------------------------------------
 * Caution			:
 *--------------------------------------------------------------------------
 *""FUNC COMMENT END""*****************************************************/

void Calc_RSOC(void)
{
	uint16_t twork;
	uint8_t aidx_initsoc;

	uint8_t a;
	uint8_t b;
	uint8_t c;
	uint8_t Res_inner_chgupdate; // chg update .
	uint32_t soc_new1;			 // chg update .

	// twork1 = (uint16_t)((long)tabsc *100/D_DCAP); // eg :   3600 mAh  = 3600mA * 1h
	//>0.5C (5-10 degree 3100 )  (<5degree ,300)

	// twrok1_out  =   t_com33  ; // 0x2b
	// twrok2_out   =  CellTemp_use_rsoc; // 0x2c

	if ((uint16_t)((long)tabsc * 100 / D_DCAP) >= 50)
	{
		if (CellTemp_use_rsoc >= 10)
		{
			t_com33 = D_0PVOLT;
		}
		if ((CellTemp_use_rsoc >= 5) && (CellTemp_use_rsoc < 10))
		{
			t_com33 = D_0PVOLT5_Tempera_10;
		}
		else if (CellTemp_use_rsoc < 5)
		{
			t_com33 = D_0PVOLT_Tempera_less_than_5;
		}
	}
	else
	{
		t_com33 = D_0PVOLT;
	}

	// awrok3_out =   t_com33  ; // 0x2d
	// awrok4_out =   CellTemp_use_rsoc  ;   // 0x2e
    twork = (uint16_t)(((((uint32_t)t_com0f * 200) * 10 / t_com10) ) / 2); // already sishewuru .

	// if(twork >990)  // more than 99 , sishewuru   -- less than 99 , use exact rc /fcc .
	// {
	// 	twork = (uint16_t)(((((uint32_t)t_com0f * 200) * 10 / t_com10) + 10) / 2);
	// }
	

	if (twork > 995) // More than 99% ?
	{
		if (F_100TOFCC == ON)
		{
			if (f_fullchg == OFF) // FullCharge is not detected ?
			{
				twork = 99; // Set to 99%
			}
			else
			{
				twork = 100; // Set to 100% (Don't make >100)
			}
		}
		else
		{
			twork = 100;
		}
	}
	else if (twork < 10)  // else if (twork < 10 && F_0TOFD) 
	{

		if (t_com0a < (-D_DCDET))
		{
			if (t_com09 > t_com33)  // t_com09 voltage   sochold1
			{
				twork /= 10;
				if (F_0TOFD)
				{
					twork = 1;
				}
				// Count_0Vlt_soctimehold0 = 0;
			}
			else
			{
				// if(Count_0Vlt_soctimehold0 >= 5)
				// {
					twork /= 10;
				// // }
				// else
				// {
					// if (F_0TOFD)
					// {
					// 	twork = 1;
					// }else
					// {
					// 	twork /= 10;
					// }
				// }	
			}
		}
		else
		{
			twork /= 10;
		}
	}
	else
	{
		twork /= 10;
	}

	t_com0d = twork; // Set to RSOC

	if (CellTemp > 20 && CellTemp < 30)
	{
		Calc_inner_3res(); //
	}

	Dsg_Update_work();
	if (F_CAPUINT == ON)
	{
		t_com84_cwh = (uint32_t)t_com84 * D_DVOLT / 10000;
		t_com0f_cwh = (uint32_t)t_com0f * D_DVOLT / 10000; // cWh
		t_com10_cwh = (uint32_t)t_com10 * D_DVOLT / 10000; // cWh
		t_com23 = (uint32_t)IdealRc * D_DVOLT / 10000;	   // cWh
		t_com1c = (uint32_t)IdealFcc * D_DVOLT / 10000;	   // cWh

	}
	else
	{
		t_com84_cwh = t_com84;
		t_com0f_cwh = t_com0f; // mAh
		t_com10_cwh = t_com10; // mAh
		t_com23 = IdealRc;	   // mAh
		t_com1c = IdealFcc;	   // mAh
	}

}

/*""FUNC COMMENT""***************************************************
 * ID			: 1.0
 * module outline: Function of relearn capacity calculation while
 *				:  discharging and voltage is lower than CP_H.
 *-------------------------------------------------------------------
 * Include		:
 *-------------------------------------------------------------------
 * Declaration	: void Calc_CP1RelRC(DWORD lrc)
 *-------------------------------------------------------------------
 * Function		: CP_H,CP_L
 *				: It calculates relearn capacity while discharging
 *				:  and the voltage is smaller than CP_H and higher
 *				:  than CP_L.
 *-------------------------------------------------------------------
 * Argument		: DWORD	: Decrease capacity
 *-------------------------------------------------------------------
 * Return		: None
 *-------------------------------------------------------------------
 * Input			: None
 * Output		: lrccr_w : Charge relearning integration work
 *				: lrcdr_w : Discahrge relearning integration work
 *-------------------------------------------------------------------
 * Used function 	:
 *-------------------------------------------------------------------
 * Caution		:
 *-------------------------------------------------------------------
 * History		: 2012.08.01 Ver 0.01
 * 				: New create
 *""FUNC COMMENT END""**********************************************/
void Calc_CP1RelRC(uint32_t lrc)
{
	uint32_t lwork;

	lrccr_w -= lrc;	 // Integrate chg relearn cap.
	if (lrccr_w < 0) // Underflow ?
	{
		lrccr_w = 0; // Set 0
	}

	lwork = (uint32_t)t_com10 * D_CP_L * 36; // Calculate CP_L capacity

	if (lrccr_w < lwork) // Chg relearn cap. < CPL cap ?
	{
		lrccr_w = lwork; // Chg relearn cap = CPL cap
	}

	if (f_study_d == ON) // Now discharge relarning ?
	{
		lrcdr_w += lrc; // Integrate discharge rel.cap.
	}
}

/*""FUNC COMMENT""***************************************************
 * ID				: 1.0
 * module outline	: Function of capacity calculation while
 *					:  discharging and voltage is lower than CP_H.
 *-------------------------------------------------------------------
 * Include			:
 *-------------------------------------------------------------------
 * Declaration		: void Calc_HoseiRC(DWORD lrc)
 *-------------------------------------------------------------------
 * Function			: CP_H
 *					: It calculates capacity while discharging and
 *					: the voltage is lower than CP_H.
 *-------------------------------------------------------------------
 * Argument			: DWORD	: Decrease capacity
 *-------------------------------------------------------------------
 * Return			: None
 *-------------------------------------------------------------------
 * Input				: None
 * Output			: lrc_w		: RC integration work
 *-------------------------------------------------------------------
 * Used function 	:
 *-------------------------------------------------------------------
 * Caution			:
 *-------------------------------------------------------------------
 * History			: 2012.08.01 Ver 0.01
 * 					: New create
 *a
 *""FUNC COMMENT END""**********************************************/
void Calc_HoseiRC(uint32_t lrc)
{
	uint32_t lwork;
	// int16_t dis_fac_cpl = 100  ; // discharge factor when reach cpl voltage . 

	//if (f_study_d == ON && f_cp_l == ON)
	//{
	// 	if (lrc_w != lrccr_w) // Correction cap. != Chg rel.cap ?
	// 	{
	// 		if (lrccr_w < 16) // Charge rel.cap = 0 ?
	// 		{
	// 			lrc *= 2; // Correction coefficient = 2
	// 		}
	// 		// else
	// 		// { // Calc correction coefficient
	// 		// 	lrc = (uint16_t)(((lrc_w / (lrccr_w / 16)) * lrc) / 16);
	// 		// }
	// 	}
	//}

	if (f_cp_l == OFF) // CP_L not detected ?
	{
		// lwork = (long)t_com10 * D_CP_L * 36; // Calculation the CP_L capacity
		// if (lrc_w < lwork)					 // less than CP_L ?
		// {
		// 	lrc_w = lwork; // hold on CP_L capacity
		// }
		if(t_com0d <= D_CP_L)
		{
			lrc_w -= lrc/2;	   // Subtruct correction value  18*3600
		}else{
			lrc_w -= lrc;	   // Subtruct correction value  18*3600
		}


		if (lrc_w <= t_com10 * 36) // t_com10/36 / 10 * 2 =  0.2 rsoc  FCC *3600 * /100/2
		{
			lrc_w = t_com10 * 36; // 40 is right number ,since t_com10*36/3600 ,maybe rsoc == 0 ;
		}
		if (lrc_w_last <= t_com10 * 36)
		{
			lrc_w_last = t_com10 * 36; // 40 is right number ,since t_com10*36/3600 ,maybe rsoc == 0 ;
		}
		// 
	}
	else   			   // cpl ==ON ;
	{				   // CP_L detected ?
		if( f_cp_l_last == OFF)  // to do clear 0 . / can come here , must means this time cpl ON . 
		{
			// dis_fcc = t_com0d / 5.5;    // enlarge 100 times .  100/5.5*t_com0d  = 18.2 about 18 
			// dis_fac_cpl = t_com0d*18 +t_com0d/5  ;              // discharge factor when reach cpl .
			dis_fac_cpl = t_com0d*D_DSG_PINGHUA_MUL +t_com0d*6/D_DSG_PINGHUA_DIV ;              // discharge factor when reach cpl .

			// if (t_com0d < D_CP_L)
			// {
			// 	dis_fac_cpl+=8 ;
			// }

			if (t_com0d < D_CP_L) // t_com0d = rsoc  D_CP_L = 6 ;
			{
				if (dis_fac_cpl < 30)
				{
					dis_fac_cpl = 30 ; // Subtruct correction value
				}
				else if( dis_fac_cpl >= 109 ) // 5---92
				{
					dis_fac_cpl= 100 ;
				}
			}
			else if (t_com0d > D_CP_L)
			{

				// if(cpl gengxin ) // if not update ?  // no need to judge update . 
				// if(t_com10  < fcc_last_cpl_pinghua ) 
				// {
				// 	dis_fac_cpl = (lrc_w/3600 - t_com10/50)*100 / (t_com10*3/50)  ;

				// // (new RC  - 0.01 newFCC )/(fcc*0.06)    // 0.06 cpl 
				// }else if(t_com10 > fcc_last_cpl_pinghua )
				// {
				// 	dis_fac_cpl = (lrc_w/3600 - t_com10/100)*100 / (t_com10*3/50)  ;
				// }
				if (f_cp_l_fccupdated)  
				{
					if (t_com10 < fcc_last_cpl_pinghua)
					{
						// (new RC  - 0.01 newFCC )/(fcc*0.06)    // 0.06 cpl 
						dis_fac_cpl = (lrc_w / 36 - t_com10 * 2) / (t_com10 * D_CP_L / 100);
					}
					else if (t_com10 >= fcc_last_cpl_pinghua)
					{
						dis_fac_cpl = (lrc_w / 36 - t_com10) / (t_com10 * D_CP_L / 100);
					}
					fcc_last_cpl_pinghua =  t_com10  ;
				}
				

				if (dis_fac_cpl <= 109)
				{
					dis_fac_cpl = 100 ; // Subtruct correction value
				}
				else if (dis_fac_cpl >= 400) // 5---92
				{
					dis_fac_cpl = 400;
				}
			}else
			{
				dis_fac_cpl = 100 ;
			}
		}

		lrc_w -= dis_fac_cpl*lrc/100;
		if(t_com0d!=0)
		{
			if (lrc_w / 36 <= t_com10)
			{
				lrc_w = t_com10 * 36; // Set 0
			}
			if (lrc_w_last <= t_com10 * 36)
			{
				lrc_w_last = t_com10 * 36; // 40 is right number ,since t_com10*36/3600 ,maybe rsoc == 0 ;
			}
		}

		if (t_com09 > t_com33) // D_0PVOLT =t_com33
		{
			if (t_com0d != 0)
			{
				if (lrc_w / 36 <= t_com10)
				{
					lrc_w = t_com10 * 36; // Set 0
				}
				if (lrc_w_last <= t_com10 * 36)
				{
					lrc_w_last = t_com10 * 36; // 40 is right number ,since t_com10*36/3600 ,maybe rsoc == 0 ;
				}
			}
		}
		else 
		{
			if (lrc_w <= 0)
			{
				lrc_w = 0; // Set 0
			}
			if(lrc_w_last  <= 0)
			{
				lrc_w_last = 0; // 40 is right number ,since t_com10*36/3600 ,maybe rsoc == 0 ;
			}
		}
	}
	// f_cp_h_fccupdated = 0 ;
	// f_cp_l_fccupdated = 0 ;
	// lrc_w_last= lrc_w ;
	// t_com0dlast = t_com0d;
	// f_init_first_time = 0;

	// if ((t_com09 <= t_com33 + 70) && (t_com0d > 2))
	// {
	// 	// Record_lrc_w = t_com10*0.02* 3600*;    // rc
	// 	if (CellTemp < 10)
	// 	{
	// 		if (t_com09 <= t_com33 + 40)
	// 		{
	// 			t_com0d = 2;		  // soc = 2
	// 			lrc_w = t_com10 * 72; // rc
	// 			lrc_w_last = lrc_w;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		t_com0d = 2;		  // soc = 2
	// 		lrc_w = t_com10 * 72; // rc
	// 		lrc_w_last = lrc_w;
	// 	}
	// }
	if ((t_com09 <= t_com33 + 10) && (t_com0d > 1))
	{
		t_com0d = 1; // soc = 1
		// Record_lrc_w = t_com10*0.01* 3600;    // rc
		lrc_w = t_com10 * 36; // rc
		lrc_w_last = lrc_w;
	}

	// if (t_com09 > t_com33) // t_com09 voltage  sochold1
	// {
	// 	Count_0Vlt_soctimehold0 = 0;
	// }
	// else // dsg   ,  voltage <= D_0pvolt
	// {
	// 	Count_0Vlt_soctimehold0++;
	// 	if (Count_0Vlt_soctimehold0 >= 5)
	// 	{
	// 		lrc_w = 0 ;
	// 		lrc_w_last = 0;
	// 		Count_0Vlt_soctimehold0 = 0;
	// 	}
	// }

	if (lrc_w <= 0)
	{
		lrc_w = 0; // Set 0
	}
	if (lrc_w_last <= 0)
	{
		lrc_w_last = 0; // 40 is right number ,since t_com10*36/3600 ,maybe rsoc == 0 ;
	}
}

/*""FUNC COMMENT""***************************************************
 * ID			: 1.0
 * module outline: FCC up/down limit check function
 *-------------------------------------------------------------------
 * Include		:
 *-------------------------------------------------------------------
 * Declaration	: void FCC_Limit_Chk(void)
 *-------------------------------------------------------------------
 * Function		: FCC Limit
 *				: Check the limit of FCC up/down
 *-------------------------------------------------------------------
 * Argument		: None
 *-------------------------------------------------------------------
 * Return		: None
 *-------------------------------------------------------------------
 * Input			: None
 * Output		: tcom25c_w : FCC temporary
 *-------------------------------------------------------------------
 * Used function :
 *-------------------------------------------------------------------
 * Caution		:
 *-------------------------------------------------------------------
 * History		: 2012.08.01 Ver 0.01
 * 				: New create
 *
 *""FUNC COMMENT END""**********************************************/
void FCC_Limit_Chk(void)
{
	uint16_t twork;	 // Calculate FCC limi	
	// uint16_t fccmaxlimit_new ;												// Normal spec
	// uint16_t IdealFcclimit_new ;	
	twork = D_RCLMT; // D_RCLMT [mAh]
    
	Calc_factor_of_fcc(); // update fcc , fcc factor and save into  save_fac_dsg_upd

    // fccmaxlimit_new  = D_FCCMAXLIMIT *(Dischargefactor/1000)
	// + D_FCCMAXLIMIT/10 *(Dischargefactor%1000/100)
	// + D_FCCMAXLIMIT/100*(Dischargefactor%100/10)
	// + D_FCCMAXLIMIT/1000*(Dischargefactor%10/1) ;

	// IdealFcclimit_new  = IdealFcc*(Dischargefactor/1000)
	// + IdealFcc/10 *(Dischargefactor%1000/100)
	// + IdealFcc/100*(Dischargefactor%100/10)
	// + IdealFcc/1000*(Dischargefactor%10/1) ;

	// if ( IdealFcclimit_new != 0)
	// {
	// 	if (tcom10c_w > IdealFcclimit_new) // IdealFcclimit_new  (normal value )<  fccmaxlimit_new (big value )
	// 	{
	// 		tcom10c_w = IdealFcclimit_new;
	// 	}
	// }

	if (tcom10c_w < t_com10) // relearn cap < FCC ?
	{
		if ((t_com10 - tcom10c_w) > twork) // Is diff larger than limit ?
		{
			tcom10c_w = t_com10 - twork; // FCC = FCC - limit
		}
	}
	else
	{									   // relearn cap >= FCC
										   // Normal spec
		if ((tcom10c_w - t_com10) > twork) // Is diff larger than limit ?
		{
			tcom10c_w = t_com10 + twork; // FCC = FCC + limit
		}
	}
	
	if (tcom10c_w > D_FCCMAXLIMIT) // 限制FCC
	{
		tcom10c_w = D_FCCMAXLIMIT;
	}

	if (tcom10c_w < D_FCCMINLIMIT)
	{
		tcom10c_w = D_FCCMINLIMIT;
	}
}

/*""FUNC COMMENT""***************************************************
 * ID				: 1.0
 * module outline	: Discharge relearning function
 *-------------------------------------------------------------------
 * Include			:
 *-------------------------------------------------------------------
 * Declaration		: void Make_Relearning(BYTE acp)
 *-------------------------------------------------------------------
 * Function			:
 *					: Function of discharge relearning.
 *-------------------------------------------------------------------
 * Argument			: BYTE	: Correction point
 *-------------------------------------------------------------------
 * Return			: None
 *-------------------------------------------------------------------
 * Input				: None
 * Output			: tcom25c_w : FCC temporary
 *-------------------------------------------------------------------
 * Used function 	: FCC_Limit_Chk()
 *-------------------------------------------------------------------
 * Caution			:
 *-------------------------------------------------------------------
 * History			: 2012.08.01 Ver 0.01
 * 					: New create
 *
 *""FUNC COMMENT END""**********************************************/
void Make_Relearning(uint8_t acp)
{
	uint16_t twork;
	uint16_t Fccfar;

	lrlstp_cnt = 0; // Clear relearn stop time counter

	if (f_study_d == ON && f_study_d1 == ON && CellTemp >= D_STUDYT) // GAo zong add need <15 update cph		// Discharge relearning = ON
																	 // & Temp >= Relearn temp ?

	{
		f_relearn = OFF;  // Clear Relearn flag
		arelearn_cnt = 0; // Clear Relearn counter
						  // Calc FCC by discharge relearn capacity
		// newFCC = relearn capcity * (100 / (100-CP_x)) / 60*60
		//		  = relearn capacity / ( (100-CP_x) * 36 )
		// tcom10c_w = (uint16_t)(lrcdr_w / (((uint16_t)100 - acp) * 36));
		tcom10c_w = (uint16_t)(lrcdr_w/ 3600 +(t_com10 / 10 * acp / 10));  // leiji + fcc*rsoc
		FCC_Limit_Chk(); // FCC Limit check

		if (F_FCCUPDATADEL == OFF) // Update FCC at CP detect ?
		{
			t_com10 = tcom10c_w; // Set FCC
		}
		else
		{					// Update FCC at start chg.
			f_studied = ON; // Set studied flag
		}

		tcom2a_w = t_com17; // Set CycleCount
							// Save CycleCount at relearn
		// Fccfar = (uint32_t)tcom10c_w * 10000 / Dischargefactor * 10 / IdealFcc;
		// IdealRc = (uint32_t)IdealRc * Fccfar / 100;
		// Ilrc_w = (uint32_t)IdealRc * (60 * 60);
		// IdealFcc = (uint32_t)tcom10c_w * 1000 / Dischargefactor;
		f_cp_h_fccupdated = 1;
		//lrc_w_last  = lrc_w ;
		clr_flg_fulchg_update();
		save_dsg_upd_fcc = tcom10c_w;
		f_bigger_than_zero = 1;
		Calc_factor_of_fcc(); // update fcc , fcc factor and save into  save_fac_dsg_upd
		CellTemp_last_time_update= CellTemp ;

		// save_fac_dsg_upd = Dischargefactor ;
		// save_dsg_upd_fcc = t_com10 ;
	}
	else
	{									   // Discharge relearning = OFF
										   // FCC update when not relearn
										   // Calculate degradation cap
		if (trek_cnt != 0 && D_REKKA != 0) // degradation cnt is not 0 ?
		{
			twork = (uint16_t)(((uint32_t)trek_cnt * D_REKKA) / 100);
			if (t_com10 > twork) // Under flow ?
			{
				tcom10c_w = t_com10 - twork;
			}
			else
			{ // Under flow
				tcom10c_w = 0;
			}

			f_studied = ON; // Set studied flag
		}
	}
	//	Fccfar =   (uint32_t)tcom10c_w * 10000/Dischargefactor*10/IdealFcc;
	//	IdealRc =  (uint32_t)IdealRc * Fccfar / 100;
	//	IdealFcc = (uint32_t)tcom10c_w * 1000/Dischargefactor;
	fcc_last_cpl_pinghua = t_com10  ; 
	trek_cnt = 0; // Clear degradation counter
	// f_study_d = OFF;							// Clear discharge relearn flag
	f_study_d1 = OFF; // Clear discharge relearn flag  change into both update
}

void Make_Relearning_cpl(uint8_t acp)
{
	uint16_t twork;
	uint16_t Fccfar;

	lrlstp_cnt = 0; // Clear relearn stop time counter

	if ((f_study_d == ON && f_study_d2 == ON) // Discharge relearning = ON
		&& (CellTemp >= D_STUDYT))			  // & Temp >= Relearn temp ?
	{
		f_relearn = OFF;  // Clear Relearn flag
		arelearn_cnt = 0; // Clear Relearn counter
						  // Calc FCC by discharge relearn capacity
		// newFCC = relearn capcity * (100 / (100-CP_x)) / 60*60
		//		  = relearn capacity / ( (100-CP_x) * 36 )

		rsoc_enlarge_1000= (uint16_t)(((((uint32_t)t_com0f * 200) * 10 / t_com10) ) / 2); // already sishewuru .
		tcom10c_w = (uint16_t)(lrcdr_w/ (((uint16_t)100 - acp) * 36));
		FCC_Limit_Chk(); // FCC Limit check

		if (F_FCCUPDATADEL == OFF) // Update FCC at CP detect ?
		{
			t_com10 = tcom10c_w; // Set FCC
		}
		else
		{					// Update FCC at start chg.
			f_studied = ON; // Set studied flag
		}
		tcom2a_w = t_com17; // Set CycleCount
							// Save CycleCount at relearn
		Fccfar = (uint32_t)tcom10c_w * 10000 / Dischargefactor *10 / IdealFcc;
		IdealRc = (uint32_t)IdealRc * Fccfar / 100;
		Ilrc_w = (uint32_t)IdealRc * (60 * 60);

		IdealFcc_last = IdealFcc ;
		IdealFcc = (uint32_t)tcom10c_w * 1000 / Dischargefactor;

		if (IdealFcc != 0)
		{
			IdealFcc_last = IdealFcc;
		}
		IdealFcc = (uint32_t)tcom10c_w * 1000/Dischargefactor;

		if(IdealFcc==0)
		{
			IdealFcc = IdealFcc_last ;
		}

		if (IdealFcc_last!= 0 )
		{
			if (IdealFcc < IdealFcc - IdealFcc / 100) // （new < 1.01 old ）
			{
				IdealFcc = IdealFcc_last - IdealFcc_last/ 100;
			}
			if (IdealFcc - IdealFcc_last > IdealFcc_last / 100)
			{
				IdealFcc = IdealFcc_last + IdealFcc_last / 100;
			}
		}
		IdealFcc_last = IdealFcc;
		//NCCLimit();
		//Calc_Dischargefactor();
		clr_flg_fulchg_update();

		// dsg_upfcc_keep_temp = CellTemp  ;
		// dsg_upfcc_keep_current = tabsc ;  // this time should be
		// rsoc_enlarge_1000  = t_com0d *10  ;
		lrccr_w = (long)t_com10* rsoc_enlarge_1000 *18/5;
		lrc_w = lrccr_w;
		lrc_w_last = lrc_w;
		f_cp_l_fccupdated = 1 ;
		save_dsg_upd_fcc = tcom10c_w;
		Calc_factor_of_fcc(); // update fcc , fcc factor and save into  save_fac_dsg_upd
		f_bigger_than_zero = 1;
		CellTemp_last_time_update= CellTemp ;
	}

	//**************************delete for update both cph and cpl ***************** //
	else
	{									   // Discharge relearning = OFF
										   // FCC update when not relearn
										   // Calculate degradation cap
		if (trek_cnt != 0 && D_REKKA != 0) // degradation cnt is not 0 ?
		{
			twork = (uint16_t)(((uint32_t)trek_cnt * D_REKKA) / 100);
			if (t_com10 > twork) // Under flow ?
			{
				tcom10c_w = t_com10 - twork;
			}
			else
			{ // Under flow
				tcom10c_w = 0;
			}

			f_studied = ON; // Set studied flag
		}
		
	}
	// Fccfar = (uint32_t)tcom10c_w * 10000 / Dischargefactor * 10 / IdealFcc;
	// IdealRc = (uint32_t)IdealRc * Fccfar / 100;
	// IdealFcc = (uint32_t)tcom10c_w * 1000 / Dischargefactor;
    
	
	
	//Calc_Dischargefactor();
	trek_cnt = 0; // Clear degradation counter

	// Cause update cph will use it

	//**************************delete for update both cph and cpl ***************** //
	f_study_d = OFF;  // Clear discharge relearn flag
	f_study_d2 = OFF; // Clear discharge relearn flag
}

void Calc_iRSOC(void)
{
	uint16_t twork;

	twork = (uint16_t)(((((uint32_t)IdealRc * 200) * 10 / IdealFcc) + 10) / 2);

	if (twork > 995) // More than 99% ?
	{
		if (F_100TOFCC == ON)
		{
			if (f_fullchg == OFF) // FullCharge is not detected ?
			{
				twork = 99; // Set to 99%
			}
			else
			{
				twork = 100; // Set to 100% (Don't make >100)
			}
		}
		else
		{
			twork = 100;
		}
	}
	else if (twork < 10 && F_0TOFD)
	{
		if (t_com0a < (-D_DCDET))
		{
			if (t_com09 >= t_com33)
			{
				//				lrc_w = t_com0f * 3600;
				twork /= 10;
				if (F_0TOFD)
				{
					twork = 1;
				}
				
			}
			else
			{
				twork /= 10;
			}
		}
		else
		{
			twork /= 10;
		}
	}
	else
	{
		twork /= 10;
	}

	// if (t_com0a > 0 && isochold1)
	// {
	// 	isochold1 = 0;
	// }
	IRsoc = twork; // Set to RSOC
}

/*
//  chg pinghua
 // chg pinghua

*/

void chg_pinghua(void)
{
	if (f_charge == ON)
	{
		// if ((t_com09 >= (g_ChargingVoltage - FULLCHG_TV)) && (t_com0a <= 350 ))
		if ((t_com09 >= (g_ChargingVoltage - D_PINGHUA_CHGVOL_THRESH)) && (t_com0a >= D_PINGHUA_CHGCUR_LOW && t_com0a <= D_PINGHUA_CHGCUR_HIGH))
		{
			if (f_pinghua_conditon == 0)
			{
				temp_Current = t_com0a;
				f_pinghua_conditon = 1;
				pinghua_soc_start = t_com0d;
			}
			if (f_pinghua_conditon == 1 && buchang_conditon_cnt < D_PINGHUA_TIME) // must have this , or the next circle will not come in .
			{
				buchang_conditon_cnt++; // condition reach  + 1
			}
			if (f_pinghua_work == 0 && f_pinghua_conditon == 1 && buchang_conditon_cnt == 40 && (temp_Current - t_com0a >= D_PINGHUA_CUR_RANGE ))
			// use conditon == 1 , in case come into again when condition reach
			{
				// about  100-t_com0d) * FCC /39
				f_pinghua_work = 1;
			}
			if (t_com0d < 100 && f_pinghua_work == 1)
			{
				chg_pinghua_current = (uint32_t)(100 - pinghua_soc_start) * t_com10 / D_PINGHUA_CAP; // chg_buchang_value = (100-t_com0d) * FCC /100 *3600 /1400;
																						  // can not use 100 -t_com0d , it will make the real less .
			//  /D_PINGHUA_CAP = /100 *3600 /1400 = /(100/3600*1400)= 30 
			}
			else
			{
				f_pinghua_work = 0; // control rsoc = 100  // use this control outer function ,can not delete
			}
		}
		else
		{
			f_pinghua_conditon = 0;
			f_pinghua_work = 0;
			buchang_conditon_cnt = 0;
		}
	}
	else
	{
		f_pinghua_conditon = 0;
		f_pinghua_work = 0;
		buchang_conditon_cnt = 0;
	}
}

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: RemainingCapacity() calculation function
 *--------------------------------------------------------------------------
 * Include			:
 *--------------------------------------------------------------------------
 * Declaration		: void Calc_RC(void)
 *--------------------------------------------------------------------------
 * Function			: It calculates RemainingCapacity()
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: None
 *--------------------------------------------------------------------------
 * Input			: None
 *					:
 * Output			: t_com0fc	: RemainingCapacity() [mAh]
 *					:
 *--------------------------------------------------------------------------
 * Used function	: Calc_NormalRC(), Make_RC()
 *					:
 *--------------------------------------------------------------------------
 * Caution			:
 *--------------------------------------------------------------------------
 *""FUNC COMMENT END""*****************************************************/
void Calc_RC(void)
{
	static uint8_t acpl_cnt;
	static uint8_t acph_cnt;
	static uint8_t adlogc; // Power consumption 10times counter
	int32_t x;
	int32_t y;

	uint32_t lwork;
	uint8_t divi_by_1k;

	if (t_com0a > 0) // Charging ?
	{
		if (f_charge == ON) // Charging ?
		{
			if (f_studied == ON) // Studied flag = ON ?
			{
				f_studied = OFF;	 // Clear studied flag
				t_com10 = tcom10c_w; // Store relearn value to FCC
			}

			if (f_fullchg == OFF) // No OVER_CHARGED_ALARM ?
			{
				f_study_d = OFF;  // Clear discharge relearn flag
				f_study_d1 = OFF; // Clear discharge relearn flag
				f_study_d2 = OFF; // Clear discharge relearn flag
			}

			if ((f_cp_h == ON)		   // CP_H detected ?
				&& (t_com0d > D_CP_H)) // & RSOC > CP_H ?
			{
				f_cp_h = OFF; // Clear CP_H detection flag
			}

			if ((f_cp_l == ON)&& (t_com0d > D_CP_L)) // & RSOC > CP_L ?  // CP_L detected ?
			{
				f_cp_l_off_delay_count++ ;
				if(f_cp_l_off_delay_count==2)
				{
					f_cp_l = OFF; // Clear CP_L detection flag
					f_cp_l_off_delay_count = 0 ;
				}
			}
			else
			{
				f_cp_l_off_delay_count = 0;
			}
		}

		if (f_study_c == ON) // Now charge relarning ?
		{
			lrccr_w += tabsc;	// Calculate chg relearn cap.
			if (f_rcsame == ON) // Correction cap = chg relearn cap ?
			{
				lrc_w = lrccr_w; // Set same value to RC
			}
			else
			{						 // Not same
				if (lrc_w < lrccr_w) // Chg relearn cap is bigger ?
				{
					lrc_w += (tabsc << 1); // Correction coefficient = 2
					if (lrc_w >= lrccr_w)  // Inverted ?
					{
						f_rcsame = ON; // Set same RC flag
					}
				}
				else
				{						   // Correction cap is bigger
					lrc_w += (tabsc >> 1); // Correction coefficient = 0.5
					if (lrc_w < lrccr_w)   // Inverted ?
					{
						f_rcsame = ON; // Set same RC flag
					}
				}
			}
		}
		else
		{				   // Not charge relarning
			chg_pinghua(); // must put here to use tabsc , in this function , use change tabsc
			// when chg cur >= 250 && cur  chg cur <= 350
			if (f_pinghua_work == 1)
			{
				lrc_w += chg_pinghua_current - divi_by_1k * 3;
			}
			else
			{
				// the following for charging volume and discharge capacity not same
				if (accu_chg_cap < 1000)
				{
					accu_chg_cap += tabsc;
					divi_by_1k = 0; // must use , or will be used in lrc_w += tabsc - divi_by_1k *3 ;
				}
				else
				{
					divi_by_1k = accu_chg_cap / 1000;
					accu_chg_cap %= 1000;
				}
				lrc_w = lrc_w + tabsc - divi_by_1k * 5; // Calc RC without correction
														// the following for charging volume and discharge capacity not same
			}

			// CPx detected ?
			if ((f_cp_h == ON) || (f_cp_l == ON)&& f_study_d==ON )
			{
				lrccr_w += tabsc; // Integrate chg rel.cap.
			}
		}

		if (tabsc > D_RCCMIN)
		{
			Ilrc_w += (int32_t)tabsc * Chargefactor / 1000; // IdealRc
			x = (int32_t)tabsc;
			y = x * Chargefactor / 1000 - tabsc;
			Del_lrc -= y; //
		}
	}
	else						// current <= 0
	{							// Discahrging or No current
		if (t_com09 <= t_com33) // lower than 0% voltage ?
		{
			if (Count_0volt >= 5)
			{	
				Count_0volt = 0; // when decetc voltage for zero soc, keep 5 seconds .					
					// Detect more than 4 times ?
				if (F_DISRELCHG == OFF) // Charge relearn not disable ?
				{
					f_study_c = ON; // Set charge relearn flag
				}

				f_cp_h = ON; // Set CP_H detection flag
				f_cp_l = ON; // Set CP_L detection flag
				lrc_w = 0;	 // Correction capacity = 0
				lrccr_w = 0; // Charge relearn capacity = 0
				f_FD = ON;
				t_com0f = 0;	 // RC[mAh] = 0
				lmaxerr_cnt = 0; // Clear MaxErr integ. counter
				// t_com0c = 0;					// Clear MaxError
				//  (Process to prevent fluctuation when jumping CC.)
				Ilrc_w = 0; // IdealRc
				IdealRc = 0;
				toldrc = 0;		 // Set last RC to 0
				t_com0d = 0 ;
				
				// sochold1 = 1;	 // 20240627kpf
				isochold1 = 1;	 // 20240627kpf
				
				return;
			}
			else
			{
				Count_0volt++;
			}
		}

		if (tabsc <= D_RCCMIN) // Current < not count curr ?
		{
			if (adlogc == 9) // Consumption current piles up 10 times ?
			{
				lrc_w -= D_DLOGC; // Take dischg consumption curr
				if (lrc_w < 0)	  // Underflow ?
				{
					lrc_w = 0; // Sst 0
				}

				if (f_study_c == ON) // Now charge relarning ?
				{
					lrccr_w -= D_DLOGC; // Take dischg consumption curr
					if (lrccr_w < 0)	// Underflow ?
					{
						lrccr_w = 0; // Set 0
					}
				}

				if (f_study_d == ON) // Now discharge relearning ?
				{
					lrcdr_w += D_DLOGC; // Add dischg consumption curr
				}
			}
		}
		else
		{				   // Now discharging
			Calc_CPVolt(); // Calculate CP_x voltage
			// V6 更改cpl点的电压
			// 更改内阻计算方式， 不用查表。
			// 1.cycle 大于 200
			// 2.温度范围 20-30 度  :计算范围，不是补偿范围。
			// 3. 原来电压+I（R测 - Rnew）
			// 4. 这个范围内， 内阻不能再变小 ，因为每跑一圈内阻应该变大，而且20-30度范围内容量变化小。
			// 全温度范围补偿
			// - degC interpolation -
			// tcpl_v = twork1 + (uint16_t)((((long)twork2 - twork1) * awork3 / awork4)) - tinreg;
			// f_calc_inner_3res_work = 1 ; to make sure calc_inner_3res_work have worked .
			if (t_com17 > 10000 && f_calc_inner_3res_work == 1) // 温度加到计算内阻的函数
			{
				// tcpl_v =  tcpl_v + tinreg + tabsc * (R1 - R2);//
				if (inner_res_dsg_100 > 75)
				{
					// inner_res_buchang_vol = tabsc/10 * ((inner_res_dsg_100 -  75) /2)/ 50;  // - innder resistance
					// become + inner resistance
					inner_res_buchang_vol = tabsc / 10 * ((inner_res_dsg_100 + 75) / 2) / 50;
				}
				if (inner_res_old_buchang_vol > inner_res_buchang_vol)
				{
					inner_res_buchang_vol = inner_res_old_buchang_vol;
				}
				inner_res_old_buchang_vol = inner_res_buchang_vol;
				// tcpl_v = (tcpl_v + outer_tinreg + inner_res);

				tabsc_out = tabsc; // t_com2e
				// inner_res_dsg_100   // t_com2c
				tcpl_v_start1 = tcpl_v;				   // t_com2a
				inner_res_out = inner_res_buchang_vol; // t_com2b
				tcpl_v -= inner_res_buchang_vol;
				tcpl_v_end_out = tcpl_v;
			}

			lwork = tabsc;	 // Make data for RC integration
			if (adlogc == 9) // Consumption current piles up 10 times ?
			{
				lwork += D_DLOGC; // Add dischg consumption curr
			}

			if (f_cp_h == OFF) // Not detect CP_H voltage ?
			{
				if (f_discharge == OFF) // Not discharging ?
				{
					Calc_NormalRC(lwork); // Calculate normal RC
				}
				else
				{						  // Discharging
					if (t_com09 < tcph_v) // MinV < CP_H voltage ?
					{
						acph_cnt++;		   // Increment CP_H det.counter
						if (acph_cnt >= 4) // Detect 4 times ?
						{
							acph_cnt = 0; // Clear the counter
							f_cp_h = ON;  // Set CP_H detect flag
										  // Charge relearn not disable ?
							if (F_DISRELCHG == OFF)
							{
								// Set charge relearn flag
								f_study_c = ON;
							}
							// Relearn point is CP_H ?
							if (F_DHGRELPOINT == ON)
							{
								// Relarning process
								Make_Relearning(D_CP_H);
							}
							
							// Set CP_H capacity to RC work
							// CP_H capacity = FCC*60*60*(D_CP_H/100)
							//               = FCC*D_CP_H*36
							// lrccr_w = (uint32_t)t_com10 * D_CP_H * 36;
							lrccr_w = (uint32_t)t_com10 * t_com0d * 36;   // fcc*rsoc   // here soc never changed , so can be put here .
							lrc_w = lrccr_w;
							lrc_w_last  = lrc_w ;
							f_rcsame = OFF; // Clear RC same flag
							Calc_HoseiRC(lwork);

							// if (F_CORRRCTRCL == ON && D_CP_H < t_com0d)
							// {
							// 	// Set CP_L capacity to RC
							// 	lrc_w = lrccr_w;
							// }
							// else
							// {
							// 	f_rcsame = OFF; // Clear RC same flag
							// 	Calc_HoseiRC(lwork);
							// }
							// Calculate RC correction
						}
						else
						{ // Less than 4 times
						  // Calculate normal RC
							Calc_NormalRC(lwork);
						}
					}
					else
					{					 // MinV >= CP_H voltage
						acph_cnt = 0;	 // Clear CP_H detection counter
						f_study_c = OFF; // Clear charge relearn flag
										 // Calculate normal RC
						Calc_NormalRC(lwork);
					}
				}
			}
			else
			{					   // Already CP_H is detected
				if (f_cp_l == OFF) // Not detect CP_L ?
				{
					if (t_com09 < tcpl_v) // MinV < CP_L voltage ?
					{
						acpl_cnt++;		   // Increment CP_L det. counter
						if (acpl_cnt == 4) // Detect 4 times ?
						{
							acpl_cnt = 0; // Clear CP_L detection counter
							f_cp_l = ON;  // Set CP_L detect flag
										  // Relearn point is CP_H ?
							if (F_DHGRELPOINT == ON)
							{
								// 	f_study_d = ON; // in function make_relearning ,
								// f_study_d closedwhen finishend updated on 20231113
								// Relearning process
								// can not use this way add f_study_d = ON to add update cph and cpl ,
								// cause no matter cph update , cpl will update even from 35% down
								Make_Relearning_cpl(D_CP_L);
							}
							// CP_L capacity = FCC*60*60*(D_CP_L/100)
							//               = FCC*D_CP_L*36
							//lrccr_w = (long)t_com10 * D_CP_L * 36;
							// lrccr_w = (long)t_com10 * t_com0d * 36;

							// rsoc_enlarge_1000= (uint16_t)(((((uint32_t)t_com0f * 200) * 10 / t_com10) ) / 2); // already sishewuru .
							// lrccr_w = (long)t_com10 * rsoc_enlarge_1000 * 36 /10 ;
							// lrccr_w = (long)t_com10*rsoc_enlarge_1000*18/5;
							// lrc_w = lrccr_w;
							// lrc_w_last  = lrc_w ;
							// Make drop at detect CP_L ?
							// & Current cap > CP_L cap ?
							//  if (F_CORRRCTRCL == ON && D_CP_L < t_com0d)  // 6<10  rc/fcc 
							//  {
							//  	// Set CP_L capacity to RC
							//  	// lrc_w = lrccr_w;
							//  }
							//  else
							//  {
								// Clear RC same flag
								f_rcsame = OFF;
								// Calculate RC correction
								Calc_HoseiRC(lwork);
							 //}
						}
						else
						{ // Less than 4 times
						  // Calc RC at less than CP_H
							Calc_CP1RelRC(lwork);
							// Calculate RC correction
							Calc_HoseiRC(lwork);
						}
					}
					else
					{				  // MinV >= CP_L voltage
						acpl_cnt = 0; // Clear CP_L detection counter
									  // Calc RC at less than CP_H
						Calc_CP1RelRC(lwork);
						Calc_HoseiRC(lwork); // Calculate RC correction
					}
				}
				else
				{					  // Already CP_L is detected
					lrccr_w -= lwork; // Take it from Chg rel.cap.
					if (lrccr_w < 0)  // Underflow ?
					{
						lrccr_w = 0; // Set 0
					}
					Calc_HoseiRC(lwork); // Calculate RC correction
				}
			}
		}

		adlogc++;		  // Inc consumption curr counter
		if (adlogc == 10) // Count 10 ?
		{
			adlogc = 0; // Clear the counter
		}
	}

	if (f_discharge == ON || f_relax == ON)
	{
		if (f_init_first_time == 0 && f_cp_h_fccupdated == 0 && f_cp_l_fccupdated == 0)
		{
			if (lrc_w > lrc_w_last)
			{
				lrc_w = lrc_w_last;
			}
			if (t_com0d > t_com0dlast) // t_com0d : rsoc
			{
				t_com0d = t_com0dlast;
			}
		}
	}
	f_cp_h_fccupdated = 0;
	f_cp_l_fccupdated = 0;
	lrc_w_last = lrc_w;
	t_com0dlast = t_com0d;
	f_init_first_time = 0;

	f_cp_l_last  = f_cp_l ;
	Make_RC(); // Calculate RemainingCapacity
	Make_iRC();

}

/*""FUNC COMMENT""***************************************************
 * ID 			: 1.0
 * module outline: MaxError() calculation function
 *-------------------------------------------------------------------
 * Include		:
 *-------------------------------------------------------------------
 * Declaration	: void Calc_MaxErr(void)
 *-------------------------------------------------------------------
 * Function		: Calculate MaxError()
 *-------------------------------------------------------------------
 * Argument		: None
 *-------------------------------------------------------------------
 * Return		: None
 *-------------------------------------------------------------------
 * Input			: None
 * Output		: t_com0c	: MaxError()
 *-------------------------------------------------------------------
 * Used function	:
 *-------------------------------------------------------------------
 * Caution		:
 *-------------------------------------------------------------------
 * History		: 2012.08.01 Ver 0.01
 * 				: New create
 *
 *""FUNC COMMENT END""**********************************************/
// void Calc_MaxErr(void)
// {
// 	uint16_t	twork;

// 	// MaxError = (Total integration cap x 0.05) / (FCC / 100)
// 	//          = Total integration cap x 5 / FCC
// 	twork = (uint16_t)(lmaxerr_cnt * 5 / t_com10 );

// 	if( twork >= 100 )							// MaxError > 100% ?
// 	{
// 		t_com0c = 100;
// 	}
// 	else
// 	{
// 		t_com0c = twork;
// 	}
// }

// Function of counting capacity of MaxError and DataFlash updating request
//  after calculating CycleCount.
void MEDF_Count(uint16_t tdata)
{
	lmaxerr_cnt += tdata; // Add MaxError integ. counter
	// Calc_MaxErr();								// Calculate MaxError()
	tdfup_cnt += tdata;	  // Add DF update counter
	if (tdfup_cnt >= 500) // reached 500mAh ?
	{
		f_dfreq = ON;  // Set DataFlash update req.
		tdfup_cnt = 0; // Clear the counter
	}
}

// Function of counting CycleCount
void CC_Count(uint16_t tdata)
{
	tcc_cnt += tdata;	  // Add CC counter
	if (tcc_cnt >= tccup) // reached CC count value ?
	{
		t_com17++;				// Increment CycleCount
		trek_cnt++;				// Increment degradation cnt
		arelearn_cnt++;			// Increment conditioning cnt
		if (arelearn_cnt == 50) // reached 50 cycle ?
		{
			f_relearn = ON; // Set RELEARN_FLAG
		}
		tcc_cnt = 0; // Clear the counter
	}
}

/*""FUNC COMMENT""***************************************************
 * ID			: 1.0
 * module outline: CycleCount() calculation function
 *-------------------------------------------------------------------
 * Include		:
 *-------------------------------------------------------------------
 * Declaration	: void Calc_CC(void)
 *-------------------------------------------------------------------
 * Function		: Calculate CycleCount()
 *-------------------------------------------------------------------
 * Argument		: None
 *-------------------------------------------------------------------
 * Return		: None
 *-------------------------------------------------------------------
 * Input			: None
 * Output		: t_com17	: CycleCount()
 *-------------------------------------------------------------------
 * Used function : CC_Count(), MEDF_Count()
 *-------------------------------------------------------------------
 * Caution		:
 *-------------------------------------------------------------------
 * History		: 2012.08.01 Ver 0.01
 * 			: New create
 *
 *""FUNC COMMENT END""**********************************************/
void Calc_CC(void)
{
	uint16_t twork;

	if (D_CCCPER < 0) // CCCC counts discharging ?
	{
		if (t_com0a < 0) // Now discharging ?
		{
			if (t_com0f < toldrc) // RC reduces ?
			{
				twork = toldrc - t_com0f;
				CC_Count(twork);   // Counting CycleCount
				MEDF_Count(twork); // Counting MaxError/DF
			}
		}
		else
		{						  // Not discharging
			if (t_com0f > toldrc) // RC increasing ?
			{
				MEDF_Count(t_com0f - toldrc); // Counting MaxError/DF
			}
		}
	}
	else
	{					 // CC counts charging
		if (t_com0a > 0) // Now charging ?
		{
			if (t_com0f > toldrc) // RC increasing ?
			{
				twork = t_com0f - toldrc;
				CC_Count(twork);   // Counting CycleCount
				MEDF_Count(twork); // Counting MaxError/DF
			}
		}
		else
		{						  // Not charging
			if (t_com0f < toldrc) // RC reducing ?
			{
				MEDF_Count(toldrc - t_com0f); // Counting MaxError/DF
			}
		}
	}

	toldrc = t_com0f; // Update last RC
}

/*""FUNC COMMENT""***************************************************
 * module outline	: Initial capacity setting function
 *-------------------------------------------------------------------
 * Include			:
 *-------------------------------------------------------------------
 * Declaration		: void Init_Cap(void)
 *-------------------------------------------------------------------
 * Function			: Calculate and set the initial capacity from
 *					: Voltage-Capacity table.
 *-------------------------------------------------------------------
 * Return			: None
 *-------------------------------------------------------------------
 * Input				: None
 * Output			: None
 *-------------------------------------------------------------------
 * Used function		: ReadVolt(), Make_RC()
 *-------------------------------------------------------------------
 * Caution			:
 *					:
 *""FUNC COMMENT END""**********************************************/
void Init_Cap(void)
{
	uint8_t aidx;
	uint8_t aresult;

	f_init_first_time = 1; // in case discharge update , when less it 0 , it will always be  0 .
						   // Search using table
	
	for (aidx = 0; t_com09 >= OCV_SOC[aidx + 1] && aidx < 19; aidx++)
		;

	if (t_com09 <= OCV_SOC[0]) // Smaller than 0% voltage ?
	{
		lrc_w = 0; // Set capacity to 0%
		Ilrc_w = 0;
	}
	else
	{
		if (t_com09 >= OCV_SOC[20]) // Bigger than 100% voltage ?
		{
			if (F_100TOFCC == ON)
			{
				// Set capacity to 100%
				lrc_w = (long)t_com10 * 3564;	// (100/100*3600=3600)
				Ilrc_w = (long)IdealFcc * 3564; // (100/100*3600=3600)
			}
			else
			{
				lrc_w = (long)t_com10 * 3600;	// Set capacity to 100%
				Ilrc_w = (long)IdealFcc * 3600; // (100/100*3600=3600)
			}
		}
		else
		{ // Not 0% and Not 99%
			// aresult = (BYTE)((long)(INITCAP_TBL[aidx+1] - 5*aidx)
			// 			* (tminv - INITV_TBL[aidx])
			// 			/ (INITV_TBL[aidx+1] - INITV_TBL[aidx])
			// 			+ 5*aidx);
			aresult = (uint8_t)((t_com09 - OCV_SOC[aidx]) * 5 / (OCV_SOC[aidx + 1] - OCV_SOC[aidx])) + (5 * aidx);
			// RC_w = FCC * aresult / 100 * 3600
			//		= FCC * aresult * 36
			lrc_w = (uint32_t)t_com10 * aresult * 36;
			Ilrc_w = (long)IdealFcc * aresult * 36;
			
		}
	}

	
	lrc_w_last = lrc_w ;
	t_com0dlast = t_com0d ;
	fcc_last_cpl_pinghua = t_com10  ; 
	CellTemp_last_time_update= CellTemp ;
	Make_RC();	 // Calculate RemainingCapacity
	Calc_RSOC(); // Calculate RSOC
	Make_iRC();
	Calc_iRSOC();
	

	if (t_com0d <= D_CP_H) // RSOC <= CP ?
	{
		f_cp_h = ON; // Set CCP detect flag
	}

	if (t_com0d <= D_CP_L) // RSOC <= CP ?
	{
		f_cp_l = ON; // Set CCP detect flag
	}
}

void ClearStudey(void)
{
	lrlstp_cnt++;	   // Increment relearn stop counter
	if (D_RLSTPT != 0) // Relearn stop time is enable?
	{
		// Relearn stop time has passed?
		if (lrlstp_cnt >= D_RLSTPT * 60 * 60)
		{
			f_study_d = OFF; // Clear discharge relearn flag
		}
	}
}

// void ful_chg_acc_cap_updated(void)
// {
// 	// uint32_t after_full_cap_accmu ;
// 	if (t_com0d == 20 && t_com0a > 0 && f_charge == ON) // t_com10 FCC   t_com0d = RSOC
// 	{
// 		f_chg_update_20 = 1; // 20% to  open , in the following will be used .
// 		if(t_com0d == 20 && f_20rc_cap_detected == 0)  // when rsoc == 20 , only keep one time .
// 		{
// 			keep_rc_rsoc20  = lrc_w  ;
// 			f_20rc_cap_detected = 1 ;
// 		}
// 	}

// 	if (f_chg_update_20 == 1)  // can not combine ,with last conditon , becasue if conbine , not 20 , will cap_accmu_chg_update = 0;
// 	{
// 		cap_accmu_chg_update += t_com0a;
// 		// this time ! chg , last time rsoc== 100 && f_fullchg
// 		// use it
// 		// 20% fcc + 20---》100% ， + over 100%
// 		if (f_charge == OFF && f_chg_last_state == ON && t_com0d == 100 && f_fullchg == ON) // t_com10 FCC   t_com0d = RSOC
// 		{
// 			t_com10 = (keep_rc_rsoc20 + cap_accmu_chg_update)/60/60 ;
// 			// rc is controled by make_() , parameter lrc_w
// 			lrc_w = keep_rc_rsoc20 + cap_accmu_chg_update  ;
// 			t_com0f = t_com10 ;  // rc = fcc   in fact , no need this ,only last step is okay .
// 			t_com0d = 100 ;
// 			keep_rc_rsoc20 = 0 ;
// 			cap_accmu_chg_update = 0;
// 			f_20rc_cap_detected = 0 ;
// 		}
// 	}
// 	else
// 	{
// 		cap_accmu_chg_update = 0;
// 	}
// 	// after use  f_chg_update_20 , then close
// 	if (f_charge == OFF && t_com0a <= 0 && t_com10 != 100)
// 	{
// 		f_chg_update_20 = 0;
// 	}

// 	f_chg_last_state = f_charge;
// }

/*""FUNC COMMENT""***************************************************
 * ID			: 1.0
 * module outline: Internal resistance calculation function
 *-------------------------------------------------------------------
 * Include		:
 *-------------------------------------------------------------------
 * Declaration	: WORD Calc_InReg(void)
 *-------------------------------------------------------------------
 * Function		:
 *				: Calculate capacity correction voltage adjusting value
 *				: by increasing the internal resistance.
 *-------------------------------------------------------------------
 * Argument		: None
 *-------------------------------------------------------------------
 * Return		: WORD	: Correction voltage
 *-------------------------------------------------------------------
 * Input			: None
 * Output		: None
 *-------------------------------------------------------------------
 * Used function :
 *-------------------------------------------------------------------
 * Caution		:
 *-------------------------------------------------------------------
 * History		: 2012.08.01 Ver 0.01
 * 				: New create
 *
 *""FUNC COMMENT END""**********************************************/
// uint16_t Calc_InReg(void)
// {
// 	uint8_t	awork1,awork2;
// 	uint16_t	twork1,twork2;
// 	uint8_t	al1;
// 												// Search the index
// 	for( al1=0; t_com17>=INREG_CYCLE[al1] && al1<5; al1++ );
// 												// Set each correction data
// 	if( al1 == 0 )								// First index ?
// 	{
// 		awork1 = 0;
// 		awork2 = INREG_TBL[0];
// 		twork1 = t_com17;
// 		twork2 = INREG_CYCLE[0];
// 	}
// 	else
// 	{									// 2nd or more
// 		al1--;
// 		awork1 = INREG_TBL[al1];
// 		awork2 = INREG_TBL[al1+1] - INREG_TBL[al1];
// 		twork1 = t_com17 - INREG_CYCLE[al1];
// 		twork2 = INREG_CYCLE[al1+1] - INREG_CYCLE[al1];
// 	}
// 	// Correction voltage[mV] = Internal resistance x Current / 1000
// 	return ((((uint32_t)awork2*twork1/twork2)+awork1)*tabsc/1000);
// }

// uint16_t Calc_InRegFcc(void)
// {
// 	uint16_t	awork1,awork2;
// 	uint16_t	twork1,twork2;
// 	uint8_t	al1;
// 												// Search the index
// 	for( al1=0; t_com17>=INREG_CYCLE[al1] && al1<5; al1++ );
// 												// Set each correction data
// 	if( al1 == 0 )								// First index ?
// 	{
// 		awork1 = 0;
// 		awork2 = INREG_FCC[0];
// 		twork1 = t_com17;
// 		twork2 = INREG_CYCLE[0];
// 	}
// 	else
// 	{									// 2nd or more
// 		al1--;
// 		awork1 = INREG_FCC[al1];
// 		awork2 = INREG_FCC[al1+1] - INREG_FCC[al1];
// 		twork1 = t_com17 - INREG_CYCLE[al1];
// 		twork2 = INREG_CYCLE[al1+1] - INREG_CYCLE[al1];
// 	}
// 	return (((uint32_t)awork2*twork1*100/twork2)+awork1*100);
// }

/*""FUNC COMMENT""***************************************************
 * ID			: 1.0
 * module outline: Correction voltage calculation function
 *-------------------------------------------------------------------
 * Include		:
 *-------------------------------------------------------------------
 * Declaration	: void Calc_CPVolt(void)
 *-------------------------------------------------------------------
 * Function		: CP_H,CP_L
 *				: Calculate correction voltage CP_H and CP_L.
 *-------------------------------------------------------------------
 * Argument		: None
 *-------------------------------------------------------------------
 * Return		: None
 *-------------------------------------------------------------------
 * Input			: None
 * Output		: CP_H : Voltage of correction point high
 *				: CP_L : Voltage of correction point low
 *-------------------------------------------------------------------
 *Used function 	: Calc_InReg()
 *-------------------------------------------------------------------
 * Caution		:
 *-------------------------------------------------------------------
 * History		: 2012.08.01 Ver 0.01
 * 				: New create
 *
 *""FUNC COMMENT END""**********************************************/

// void Dsg_Update_work(void)
// 	{
// 		if(f_chg_last2 == 0 && f_charge==1 )   // 在任何温度 ？
// 			{  f_start_add_chg = 1 ;   }
// 		if( f_start_add_chg==1 && f_charge==1)
// 			{
// 				leiji += tabsc ;
// 			}

// 		// 充着断了， 清除哪些标志位 。
// 		//1. 温度设置为多少
// 		//2. tabsc 设置值

// 			if (CellTemp < 15)
// 			{
// 				// f_ful_chg_once == 1 ) //(f_fullchg == ON && t_com0d == 100) // f_have_ever_fulchg
// 				if ((f_ful_chg_once == 1) || (leiji / 3600 > t_com10 / 2) && (f_discharge_last2 == OFF && f_discharge == ON))
// 				{
// 					f_count3s_en = 1; // global parameter ;
// 				}

// 				// f_discharge_last2 = f_discharge;  // put this outer if sentece will be better  ?

// 				if (f_count3s_en == 1 && f_discharge == ON && tabsc > 20)
// 				{
// 					count_3s++;
// 					if (count_3s == 3)
// 					{
// 						// save data :
// 						count_3s = 0;
// 						f_count3s_en = 0;
// 						dsg_upfcc_keep_current = tabsc; // this time should be        save current
// 						dsg_upfcc_keep_temp = CellTemp; // save temperature

// 						if (f_bigger_than_zero != 1) // if have dischg relearn updated ,use that conditon ,if not , use 25du condition
// 						{
// 							save_dsg_upd_fcc = t_com10;
// 							save_fac_dsg_upd = 1000;
// 						}
// 						Dsg_Update_FCC();
// 						// to do function work .
// 						// save data  ?
// 					}
// 					// function start to work
// 				}
// 				else
// 				{
// 					count_3s = 0;
// 				}
// 			}
// 		f_discharge_last2 = f_discharge ;

// 	}
