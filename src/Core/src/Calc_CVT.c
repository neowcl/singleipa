#include "Calc_CVT.h"
#include "bi2cs_interface.h"
#include "Cell.h"
#include "LifeTime.h"
#include "Ram.h"
#include "datcalc_spl.h" // datcalc_spl.c

#include "Mode.h"
int16_t CalcCur[4]; // Calc Current
uint8_t AveCurNum;	// Aveage Current Num
int16_t LastCur;	// Last Current
int32_t AverageCurSum;
uint8_t aaveragecur_cnt;
uint32_t MinFCCCap;

int8_t SOC_Init;
int8_t SOC_End;
int32_t at_startqmax_cnt; // Start Count
int32_t at_endqmax_cnt;	  // End  Count
int8_t f_Qmax_ctrl;		  // QMax control
int32_t QmaxCapcity_Calc; // QMax Capcity

uint8_t relaxing = 0;
// uint8_t cp_updated ;
uint16_t relaxingCnt = 0;

uint16_t tfc_cnt; // Full Charge check count

uint16_t t_com84_cwh;

void Calc_AvgCur(void)
{
	uint8_t aidx;
	if (((int16_t)LastCur <= (int16_t)D_CCDET && (int16_t)t_com0a > (int16_t)D_CCDET) ||
		((int16_t)LastCur >= (int16_t)(-D_DCDET) && (int16_t)t_com0a < (int16_t)(-D_DCDET)))
	{
		for (aidx = 0; aidx < 4; aidx++)
		{
			CalcCur[aidx] = 0;
		}
		AveCurNum = 0;
		t_com89 = 0;
	}
	else
	{
		CalcCur[AveCurNum++] = t_com0a;
		if (AveCurNum >= 4)
		{
			AveCurNum = 0;
		}

		for (aidx = 0; aidx < 4; aidx++)
		{
			AverageCurSum += CalcCur[aidx];
		}

		tcom89_new = AverageCurSum * 2 + tcom89_new * 98 / 100;
		AverageCurSum = 0;
		if (ABS(tabsc - ABS(t_com89)) <= 1)
		{
			aaveragecur_cnt++;
			if (aaveragecur_cnt >= 40)
			{
				aaveragecur_cnt = 0;
				t_com89 = t_com0a;
			}
		}
		else
		{
			t_com89 = tcom89_new / 400;
			aaveragecur_cnt = 0;
		}
	}
	LastCur = t_com0a;
}

void Calc_ATTE(void)
{
	if (t_com89 < 0)
	{
		t_com11 = (long)t_com0f * 60 / ABS(t_com89); // AverageTimeToEmpty
	}
	else
	{
		t_com11 = 0xFFFF;
	}

	if (t_com02 >= 0)
	{
		t_com04 = 0xFFFF;
	}
	else
	{
		t_com04 = (int32_t)t_com0f * 60 / ABS(t_com02); // At Rate TO TimeToEmpty
	}

	if (f_dsg)
	{
		if (t_com0a < t_com1e)
		{
			t_com1e = t_com0a;
		}

		t_com1d = (int32_t)t_com0f * 60 / ABS(t_com1e);
	}
	else
	{
		t_com1d = 0xFFFF;
	}
}

void Calc_ATTF(void)
{
	if (t_com89 > 0 && f_charge)
	{
		t_com13 = (long)(t_com10 - t_com0f) * 60 / ABS(t_com89);
	}
	else
	{
		t_com13 = 0xFFFF;
	}

	t_com1f = (int32_t)t_com89 * t_com09 / 1000;		   // cW
	CurrentPower = (int32_t)ABS(t_com0a) * t_com09 / 1000; // cW
	//	Power = (int32_t)t_com0c*t_com08/1000;
}

void Calc_FullCharge(void)
{
	if (f_charge == ON && t_com0a > 50) // Charging current detection ?
	{
		if (f_fullchg == ON) // FULLY_CHARGED = ON ?
		{
			if (t_com0f >= t_com10) // RC >= FCC ?
			{
				FullCharge(); // Full Charge Processing
			}
		}
		else
		{
			// MaxV >= Single cell CV-FCtaperV
			// & Full Charge Current less than ?
			if ((t_com09 >= (g_ChargingVoltage - FULLCHG_TV))&&  (tabsc < FULLCHG_CURR))
			{
				tfc_cnt++; // Full Charge check count + 1
						   // Full charge determination time elapsed ?
				MinFCCCap += tabsc;
				if (tfc_cnt == FULLCHG_T / 2)
				{
					if (MinFCCCap / 360 < D_MINFULLCAP)
					{
						tfc_cnt = 0;
						MinFCCCap = 0;
					}
					else
					{
						MinFCCCap = 0;
					}
				}
				if (tfc_cnt >= FULLCHG_T) //
				{
					if (MinFCCCap / 360 >= D_MINFULLCAP)
					{
						tfc_cnt = 0; // Clear Full Charge check count
						VailChargeTermCnt++;
						LastVailChargeTermCycle = t_com17;
						f_ltreq = ON;
						FullCharge(); // Full Charge Processing
					}
					else
					{
						tfc_cnt = 0;
						MinFCCCap = 0;
					}
				}
			}
			else
			{
				if (tfc_cnt != 0) // Full Charge check count = 0 ?
				{
					tfc_cnt--; // Full Charge check count - 1
				}
			}
		}
	}
	else
	{				 // Charging current undetected
		tfc_cnt = 0; // Clear Full Charge check count
	}
}

void FullCharge(void)
{
	uint16_t twork;
	if (F_DISRELDHG == OFF) // Dischg relearn not disable ?
	{
		f_study_d = ON;	 // Set discharge relearn flag
		f_study_d1 = ON; // Set discharge relearn flag
		f_study_d2 = ON; // Set discharge relearn flag
	}
	if (CellTemp < D_STUDYT	 // Less than relearn limit temp
		|| f_study_c == OFF) // or Charge relearn flag=OFF ?
	{
		if (trek_cnt != 0 && D_REKKA != 0) // Degradation cnt is not 0 ?
		{
			// FCC = FCC - (Degradation counter * Degradation capacity)
			twork = (uint16_t)(((long)trek_cnt * D_REKKA) / 100);
			if (t_com10 > twork) // Not Under flow ?
			{
				t_com10 = t_com10 - twork;
			}
			else
			{ // Under flow
				t_com10 = 10;
			}
		}
	}
	else
	{											// Make relearning
		arelearn_cnt = 0;						// Clear Relearning counter
		f_relearn = OFF;						// Clear Relearning flag
		tcom10c_w = (uint16_t)(lrccr_w / 3600); // Calc new FCC
		FCC_Limit_Chk();						// FCC inc/dec limit check
		t_com10 = tcom10c_w;					// Set FullChargeCapacity()
	}
	trek_cnt = 0; // Clear degradation counter
	lrlstp_cnt = 0;
	f_study_c = OFF;

	if (f_fullchg == OFF) // FULLY_CHARGED == OFF ?
	{
		lrc_w = (long)t_com10 * 3600;	// Calc RC integration work
		// lrc_w_last = lrc_w  ;
		Ilrc_w = (long)IdealFcc * 3600; // Calc RC integration work
		IdealRc = IdealFcc;
		Del_lrc = 0;
		IRsoc = 100;
		if (f_study_d == ON) // Start discharge relearn ?
		{
			lrcdr_w = 0; // Clear discharge relarn cap.
		}
		t_com0f = t_com10; // Update RemainingCapacity()
		t_com0d = 100;	   // RSOC=100%
		// (To prevent changing CC when capacity is jumped.)
		toldrc = t_com10; // Update to RemCap value last time
						  // Update last RemCap
	}

	f_fullchg = ON; // Set FULLY_CHARGED
	f_ful_chg_once = ON;
	f_VCT = ON;
	// f_FC1 = 1;
}

void DCR_Mode(void)
{
	// CHG\DSG\RELAX三态判断,其中只有进入RELAX状态需要计时
	// DSG
	if (t_com0a < (-D_DCDET))
	{
		f_discharge = ON;
		f_t_com66_OCVTAKEN=ON;
		f_charge = OFF;
		f_relax = OFF;
		f_dsg = 1;
		f_DSG1 = ON;
		relaxing = 0;
		relaxingCnt = 0;

		// f_DSG = 1;
	}
	// CHG
	else if (t_com0a > D_CCDET)
	{
		f_discharge = OFF;
		f_charge = ON;
		f_t_com66_OCVTAKEN=ON;
		f_relax = OFF;
		f_dsg = 0;
		relaxing = 0;
		relaxingCnt = 0;
		f_DSG1 = OFF;

		// f_DSG = 0;
	}

	// Relax
	if ((t_com0a <= D_CCDET) && (t_com0a >= (-D_DCDET)))
	{
		if (relaxingCnt != 0xffff)
		{
			relaxingCnt++;
		}
	}

	if (!relaxing)
	{
		// DSG->Relax
		if ((f_dsg == 1) && (relaxingCnt >= D_DRELAXJT))
		{
			f_dsg = 0;
			relaxing = 1;
			f_discharge = OFF;
			f_charge = OFF;
			f_t_com66_OCVTAKEN=OFF;
			f_relax = ON;
			relaxingCnt = 0;
			f_DSG1 = ON;
			// f_DSG = 1;
		}
		// CHG->Relax
		if ((f_dsg == 0) && (relaxingCnt >= D_CRELAXJT))
		{
			relaxing = 1;
			f_dsg = 0;
			f_DSG1 = ON;
			f_discharge = OFF;
			f_charge = OFF;
			f_t_com66_OCVTAKEN=OFF;
			f_relax = ON;
			relaxingCnt = 0;

			// f_DSG = 1;
		}
	}
}

void Calc_QMax(void)
{
	uint8_t aidx = 0;
	uint8_t dropSoc;

	if (CellTemp >= TEMPLIMIT_L && CellTemp <= TEMPLIMIT_H && t_com17 > CYCLELIMIT)
	{
		if (f_relax == ON)
		{
			if (f_Qmax_start == OFF)
			{
				if (f_DP_SLP)
				{
					at_startqmax_cnt += D_DSLPVOLTTIME;
				}
				else if (f_SLEEP)
				{
					at_startqmax_cnt += D_VOLTTIME;
				}
				else
				{
					at_startqmax_cnt += 1;
				}
				// at_startqmax_cnt++;
				if (at_startqmax_cnt >= 18000) // Calc SOC init
				{
					for (aidx = 0; (aidx < 19) && (t_com09 > OCV_SOC[aidx + 1]); aidx++);
					SOC_Init = (int8_t)aidx * 5 + (int16_t)((int16_t)(t_com09 - OCV_SOC[aidx]) * 5) / (int16_t)(OCV_SOC[aidx + 1] - OCV_SOC[aidx]);
					f_Qmax_start = ON;
					f_Qmax_end = OFF;
					at_startqmax_cnt = 0;
					at_endqmax_cnt = 0;
					QmaxCapcity_Calc = 0;
				}
			}
			else
			{
				if (f_DP_SLP)
				{
					at_endqmax_cnt += D_DSLPVOLTTIME;
				}
				else if (f_SLEEP)
				{
					at_endqmax_cnt += D_VOLTTIME;
				}
				else
				{
					at_endqmax_cnt += 1;
				}
				// at_endqmax_cnt++;
				if (at_endqmax_cnt >= 18000) // Calc SOC end
				{
					for (aidx = 0; (aidx < 19) && (t_com09 > OCV_SOC[aidx + 1]); aidx++)
						;
					SOC_End = (int8_t)aidx * 5 + (int16_t)((int16_t)(t_com09 - OCV_SOC[aidx]) * 5) / (int16_t)(OCV_SOC[aidx + 1] - OCV_SOC[aidx]);
					f_Qmax_end = ON;
					f_Qmax_start = OFF;
					at_endqmax_cnt = 0;
					at_startqmax_cnt = 0;
				}
			}

			if (f_Qmax_end == ON)
			{
				if (SOC_Init <= SOC_L || SOC_Init >= SOC_H)
				{
					if (SOC_End <= SOC_L || SOC_End >= SOC_H)
					{
						dropSoc = ABS(SOC_Init - SOC_End);
						if (dropSoc > VARSOC)
						{
							t_com84 = QmaxCapcity_Calc / 36 / dropSoc;
							QMaxUpdataCnt++;
							LastQMaxUpdataCycle = t_com17;
							LastQMaxUpdataValue = t_com84;
							f_ltreq = ON;
							f_Qmax_start = OFF;
							f_Qmax_end = OFF;
							at_endqmax_cnt = 0;
							at_startqmax_cnt = 0;
							QmaxCapcity_Calc = 0;
						}
						else
						{
							f_Qmax_start = OFF;
							f_Qmax_end = OFF;
							at_endqmax_cnt = 0;
							at_startqmax_cnt = 0;
							QmaxCapcity_Calc = 0;
						}
					}
					else
					{
						f_Qmax_start = OFF;
						f_Qmax_end = OFF;
						at_endqmax_cnt = 0;
						at_startqmax_cnt = 0;
						QmaxCapcity_Calc = 0;
					}
				}
				else
				{
					f_Qmax_start = OFF;
					f_Qmax_end = OFF;
					at_endqmax_cnt = 0;
					at_startqmax_cnt = 0;
					QmaxCapcity_Calc = 0;
				}
			}
		}
		else
		{
			if (tabsc >= (long)C_RATE_L * D_DCAP / 10 && tabsc <= (long)C_RATE_H * D_DCAP / 10 && f_Qmax_start == ON) // 0.1C
			{
				if (F_QMAXDSGUPDATA == ON)
				{
					if (f_charge == ON)
					{
						f_Qmax_start = OFF;
						f_Qmax_end = OFF;
						at_startqmax_cnt = 0;
						QmaxCapcity_Calc = 0;
					}
					else
					{
						QmaxCapcity_Calc += tabsc;
					}
				}

				if (F_QMAXCHGUPDATA == ON)
				{
					if (f_discharge == ON)
					{
						f_Qmax_start = OFF;
						f_Qmax_end = OFF;
						at_startqmax_cnt = 0;
						QmaxCapcity_Calc = 0;
					}
					else
					{
						QmaxCapcity_Calc += tabsc;
					}
				}
			}
			else
			{
				//				f_Qmax_start = OFF;
				f_Qmax_end = OFF;
				at_startqmax_cnt = 0;
				//				QmaxCapcity_Calc = 0;
			}
			at_endqmax_cnt = 0;
		}
	}
	else
	{
		f_Qmax_start = OFF;
		f_Qmax_end = OFF;
		at_endqmax_cnt = 0;
		at_startqmax_cnt = 0;
		QmaxCapcity_Calc = 0;
	}
}
