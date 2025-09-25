#include "LifeTime.h"
#include "bi2cs_interface.h"
#include "Cell.h"
#include "Ram.h"
#include "modules_fmc.h"
#include "ic_config.h"
_LTDF     DF_LifeTime ;//__attribute__((used)) __attribute__((section(".ARM.__at_0x0000EC00")));

#define CHECK_CNT   3
#define LTW_DELAY   36000    //10Hour

uint16_t altflg;
int16_t CurrentPower;
//int16_t Power;

//uint16_t T1_Cnt[8] = {0};
//uint16_t T2_Cnt[8] = {0};
//uint16_t T3_Cnt[8] = {0};
//uint16_t T4_Cnt[8] = {0};
//uint16_t T5_Cnt[8] = {0};
//uint16_t T6_Cnt[8] = {0};
//uint16_t T7_Cnt[8] = {0};

static    uint8_t   LtW_Cnt[16];
//    uint32_t  LtW_CntW;
static    uint8_t   *apltadr;
static    uint8_t   altidx;
uint16_t lt_test = 1;
uint16_t Fwrun_Cnt = 0;
uint16_t HT_Cnt = 0;
uint16_t HV_Cnt = 0;
uint16_t HTV_Cnt = 0;

uint32_t  LtW_CntW;

uint8_t SocCnt,TempCnt;
uint16_t T_Cnt[7][8] = {0};
//uint16_t Run_Cnt[4] = {0};


static void LTW_Index(void);
static void LTR_Index(void);

void SocTime(uint8_t TempCnt,uint8_t SocCnt) //TempCnt = temp , SocCnt = soc range 
{
	if(f_DP_SLP)
	{
			T_Cnt[TempCnt][SocCnt] += D_DSLPVOLTTIME;
	}
	else if(f_SLEEP)
	{
			T_Cnt[TempCnt][SocCnt] += D_VOLTTIME;
	}
	else
	{
			T_Cnt[TempCnt][SocCnt] += 1;
	}
    if (T_Cnt[TempCnt][SocCnt] >= (3600 / lt_test))
    {
        T_Cnt[TempCnt][SocCnt] = 0;
        f_ltreq = ON;
        if (TempCnt == 0)
        {
            T1_RSOC[SocCnt] += 1;
        }
        else if (TempCnt == 1)
        {
            T2_RSOC[SocCnt] += 1;
        }
        else if (TempCnt == 2)
        {
            T3_RSOC[SocCnt] += 1;
        }
        else if (TempCnt == 3)
        {
            T4_RSOC[SocCnt] += 1;
        }
        else if (TempCnt == 4)
        {
            T5_RSOC[SocCnt] += 1;
        }
        else if (TempCnt == 5)
        {
            T6_RSOC[SocCnt] += 1;
        }
        else if (TempCnt == 6)
        {
            T7_RSOC[SocCnt] += 1;
        }
    }
}

//static void RunTime(uint32_t* Run_time,uint16_t* Run_Cnt)
//{
//	if(f_DP_SLP)
//	{
//			*Run_Cnt += D_DSLPVOLTTIME;
//	}
//	else if(f_SLEEP)
//	{
//			*Run_Cnt += D_VOLTTIME;
//	}
//	else
//	{
//			*Run_Cnt += 1;
//	}

//	if(*Run_Cnt  >= (3600/lt_test))
//	{
//			*Run_Cnt = 0;
//			(*Run_time)++;
//			f_ltreq = ON;
//	}
//}

void LifeTime_Calc(void)
{
    if (f_LF_EN)
    {
        if (f_LT_TEST)
        {
            lt_test = 3600;
        }
        else
        {
            lt_test = 1;
        }

        if(t_com09 > CellMaxVolt)
        {
            LtW_Cnt[0]++;
            if(LtW_Cnt[0] >= CHECK_CNT)
            {
                CellMaxVolt = t_com09;
                LtW_Cnt[0] = 0;
                f_ltreq = ON;
            }
        }
        else
        {
            LtW_Cnt[0] = 0;
        }

        if(t_com09 < CellMinVolt)
        {
            LtW_Cnt[1]++;
            if(LtW_Cnt[1] >= CHECK_CNT)
            {
                CellMinVolt = t_com09;
                LtW_Cnt[1] = 0;
                f_ltreq = ON;
            }
        }
        else
        {
            LtW_Cnt[1] = 0;
        }

        if(f_charge)
        {
            if(t_com0a > ChgMaxCurrent)
            {
                LtW_Cnt[2]++;
                if(LtW_Cnt[2] >= CHECK_CNT)
                {
                    ChgMaxCurrent = t_com0a;
                    LtW_Cnt[2] = 0;
                    f_ltreq = ON;
                }
            }
            else
            {
                LtW_Cnt[2] = 0;
            }

            if(t_com0a < ChgMinCurrent)
            {
                LtW_Cnt[3]++;
                if(LtW_Cnt[3] >= CHECK_CNT)
                {
                    ChgMinCurrent = t_com0a;
                    LtW_Cnt[3] = 0;
                    f_ltreq = ON;
                }
            }
            else
            {
                LtW_Cnt[3] = 0;
            }
        }

        if(f_discharge)
        {
            if(tabsc > DsgMaxCurrent)
            {
                LtW_Cnt[4]++;
                if(LtW_Cnt[4] >= CHECK_CNT)
                {
                    DsgMaxCurrent = tabsc;
                    LtW_Cnt[4] = 0;
                    f_ltreq = ON;
                }
            }
            else
            {
                LtW_Cnt[4] = 0;
            }

            if(tabsc < DsgMinCurrent)
            {
                LtW_Cnt[5]++;
                if(LtW_Cnt[5] >= CHECK_CNT)
                {
                    DsgMinCurrent = tabsc;
                    LtW_Cnt[5] = 0;
                    f_ltreq = ON;
                }
            }
            else
            {
                LtW_Cnt[5] = 0;
            }

            if(ABS(t_com89) > ABS(AvgDsgMaxCurrent) && t_com89 < 0)
            {
                LtW_Cnt[6]++;
                if(LtW_Cnt[6] >= CHECK_CNT)
                {
                    LtW_Cnt[6] = 0;
                    AvgDsgMaxCurrent = ABS(t_com89);
                    f_ltreq = ON;
                }
            }
            else
            {
                LtW_Cnt[6] = 0;
            }

            if(ABS(t_com1f) > AvgDsgMaxPower)
            {
                LtW_Cnt[7]++;
                if(LtW_Cnt[7] >= CHECK_CNT)
                {
                    AvgDsgMaxPower = ABS(t_com1f) ;
                    LtW_Cnt[7] = 0;
                    f_ltreq = ON;
                }
            }
            else
            {
                LtW_Cnt[7] = 0;
            } 
        }

        if(CellTemp > CellMaxTemp)
        {
            LtW_Cnt[8]++;
            if(LtW_Cnt[8] >= CHECK_CNT)
            {
                CellMaxTemp = CellTemp;
                LtW_Cnt[8] = 0;
                f_ltreq = ON;
            }
        }
        else
        {
            LtW_Cnt[8] = 0;
        }

        if(CellTemp < CellMinTemp)
        {
            LtW_Cnt[9]++;
            if(LtW_Cnt[9] >= CHECK_CNT)
            {
                CellMinTemp = CellTemp;
                LtW_Cnt[9] = 0;
                f_ltreq = ON;
            }
        }
        else
        {
            LtW_Cnt[9] = 0;
        }

        if(IntTemp > IntMaxTemp)
        {
            LtW_Cnt[10]++;
            if(LtW_Cnt[10] >= CHECK_CNT)
            {
                IntMaxTemp = IntTemp;
                LtW_Cnt[10] = 0;
                f_ltreq = ON;
            }
        }
        else
        {
            LtW_Cnt[10] = 0;
        }

        if(IntTemp < IntMinTemp)
        {
            LtW_Cnt[11]++;
            if(LtW_Cnt[11] >= CHECK_CNT)
            {
                IntMinTemp = IntTemp;
                LtW_Cnt[11] = 0;
                f_ltreq = ON;
            }
        }
        else
        {
            LtW_Cnt[11] = 0;
        }
				
        if(g_ChargingVoltage < MinChargeVoltage)
        {
            LtW_Cnt[12]++;
            if(LtW_Cnt[12] >= CHECK_CNT)
            {
                MinChargeVoltage = g_ChargingVoltage;
                LtW_Cnt[12] = 0;
                f_ltreq = ON;
            }
        }
        else
        {
            LtW_Cnt[12] = 0;
        }				


        if(f_DP_SLP)
        {
            Fwrun_Cnt += D_DSLPVOLTTIME;
        }
        else if(f_SLEEP)
        {
            Fwrun_Cnt += D_VOLTTIME;
        }
        else
        {
            Fwrun_Cnt += 1;
        }

        if(Fwrun_Cnt  >= (3600/lt_test))
        {
            Fwrun_Cnt = 0;
            FwTotalRunTime++;
            f_ltreq = ON;
        }

        if(t_com09 > D_HIGHVOLT)
        {
            if(f_DP_SLP)
            {
                HV_Cnt += D_DSLPVOLTTIME;
            }
            else if(f_SLEEP)
            {
                HV_Cnt += D_VOLTTIME;
            }
            else
            {
                HV_Cnt += 1;
            }

            if(HV_Cnt  >= (3600/lt_test))
            {
                HV_Cnt = 0;
                HV_TIME++;
                f_ltreq = ON;
            }
        }

        if(CellTemp > D_HIGHTEMP)
        {
            if(f_DP_SLP)
            {
                HT_Cnt += D_DSLPVOLTTIME;
            }
            else if(f_SLEEP)
            {
                HT_Cnt += D_VOLTTIME;
            }
            else
            {
                HT_Cnt += 1;
            }

            if(HT_Cnt  >= (3600/lt_test))
            {
                HT_Cnt = 0;
                HT_TIME++;
                f_ltreq = ON;
            }
        }

        if(t_com09 > D_HIGHVOLT && CellTemp > D_HIGHTEMP)
        {
            if(f_DP_SLP)
            {
                HTV_Cnt += D_DSLPVOLTTIME;
            }
            else if(f_SLEEP)
            {
                HTV_Cnt += D_VOLTTIME;
            }
            else
            {
                HTV_Cnt += 1;
            }

            if(HTV_Cnt  >= (3600/lt_test))
            {
                HTV_Cnt = 0;
                HTV_TIME++;
                f_ltreq = ON;
            }
        }

        if (t_com0d <= D_LFRSOCG)
        {
            SocCnt = 0;
        }
        else if (t_com0d <= D_LFRSOCF)
        {
            SocCnt = 1;
        }
        else if (t_com0d <= D_LFRSOCE)
        {
            SocCnt = 2;
        }
        else if (t_com0d <= D_LFRSOCD)
        {
            SocCnt = 3;
        }
        else if (t_com0d <= D_LFRSOCC)
        {
            SocCnt = 4;
        }
        else if (t_com0d <= D_LFRSOCB)
        {
            SocCnt = 5;
        }
        else if (t_com0d <= D_LFRSOCA)
        {
            SocCnt = 6;
        }
        else
        {
            SocCnt = 7;
        }

        switch (TempRange.data)
        {
        case TR_UT:
						TempCnt = 0;
						SocTime(TempCnt,SocCnt);
						break;
        case TR_LT:
						TempCnt = 1;
						SocTime(TempCnt,SocCnt);
						break;				
        case TR_STL:
						TempCnt = 2; 
						SocTime(TempCnt,SocCnt);
						break;				
        case TR_RT:
            TempCnt = 3;
						SocTime(TempCnt,SocCnt);
						break;
        case TR_STH:
						TempCnt = 4;
						SocTime(TempCnt,SocCnt);
						break;				
				case TR_HT:
						TempCnt = 5;
						SocTime(TempCnt,SocCnt);
						break;				
        case TR_OT:
						TempCnt = 6;
						SocTime(TempCnt,SocCnt);
						break;
        default:   
						break;
        }

        if(f_ltreq)
        {
            if(f_DP_SLP)
            {
                LtW_CntW += D_DSLPVOLTTIME;
            }
            else if(f_SLEEP)
            {
                LtW_CntW += D_VOLTTIME;
            }
            else
            {
                LtW_CntW += 1;
            }

						
            if(LtW_CntW >= (LTW_DELAY/lt_test))
            {
                f_lt_W = ON;
                f_ltreq = OFF;
                LtW_CntW = 0;
            }
        }
        else
        {
            LtW_CntW = 0;
        }
    }
}


void LT_Erase_A(void)
{
    fmc_page_erase(118);
}

void LT_Erase_B(void)
{
    fmc_page_erase(119);
}

void LTW_Index(void)
{
    apltadr = (uint8_t*)LIFETIME_FLASH_BLOCK_A;				// Search BlockA
    if(apltadr[0] != 0xFF)
    {
        apltadr = (uint8_t*)LIFETIME_FLASH_BLOCK_B;				// Search BlockB
        LifeTimeprt=LIFETIME_FLASH_BLOCK_B;
        if(apltadr[0] != 0xFF)
        {
            LT_Erase_A();
            if( lterase_cnt != 0xFFFF )
            {
                lterase_cnt++;		// Increment DF erase times
            } 
            
            f_lt_breq = ON;
            if( lterase_cnt != 0xFFFF )
            {
                lterase_cnt++;		// Increment DF erase times
            }
            apltadr = (uint8_t*)LIFETIME_FLASH_BLOCK_A;				// Search BlockB 
            LifeTimeprt=LIFETIME_FLASH_BLOCK_A;
        } 
        altidx = 0;      
    }
    else
    {
        apltadr = (uint8_t*)LIFETIME_FLASH_BLOCK_A;				// Search BlockA
        LifeTimeprt=LIFETIME_FLASH_BLOCK_A;
        altidx = 0;
    } 
}

void LTR_Index(void)
{
    apltadr = (uint8_t*)LIFETIME_FLASH_BLOCK_B;				// Search from BlockB
    LifeTimeprt= LIFETIME_FLASH_BLOCK_B;
    if(apltadr[0] != 0xFF)
    {
        apltadr = (uint8_t*)(LIFETIME_FLASH_BLOCK_B + LIFETIME_ST_OFF);
        LifeTimeprt= LIFETIME_FLASH_BLOCK_B;
    }
    else
    {
        apltadr = (uint8_t*)LIFETIME_FLASH_BLOCK_A;
        LifeTimeprt= LIFETIME_FLASH_BLOCK_A;
        if(apltadr[0] != 0xFF)
        {
            apltadr = (uint8_t*)(LIFETIME_FLASH_BLOCK_A + LIFETIME_ST_OFF);
            LifeTimeprt= LIFETIME_FLASH_BLOCK_A;
        }
        else
        {
            apltadr = (uint8_t*)0xFFFF;
            //LifeTimeprt=0xFFFF;
        }
    }
}

void LifeTime_Read(void)
{
    uint16_t al1;
    LTR_Index();
						// Search read area
	if( apltadr != (uint8_t*)0xFFFF )				// DataFlash is not empty ?
	{
												// Data read loop
		for( al1=0; al1 < LTSIZE; al1++,apltadr++ )
		{
			altdat[al1] = *apltadr;
		}
	} 
	else 
	{									// DataFlash is empty
		for( al1=0; al1< LTSIZE; al1++ )			// Set default data
		{
			altdat[al1] = 0;
		}

        IntMinTemp = 30;
        CellMinTemp = 30;
        CellMinVolt = 4000;
        ChgMinCurrent = 10000;
        DsgMinCurrent = 10000;
	}
}

uint8_t LifeTime_Write(void)
{
    uint16_t	al1;
	uint8_t	*apwork1, *apwork2;

    LTW_Index();
    

    if( altidx >= LIFETIME_BLOCK )						// Index Abnormal?
	{
		return FALSE;							// Abort
	}

    apwork1 = (uint8_t*)(apltadr + LIFETIME_ST_OFF + ((uint16_t)altidx * LIFETIME_LEN));

	apwork2 = apwork1;

    for( al1=0; al1 < LTSIZE; al1++ )				// Write area empty check
	{
		if( *apwork1 != 0xFF )					// Not empty ?
		{
			LifeTime_IndexW(AREA_NG);					// Write index(area NG)
			return FALSE;						// Abort
		}
		apwork1++;								// To next data
	}

    fmc_write_flash( (uint32_t)apwork2-FMC_DATA_FLASH_BASE_ADDR, altdat, LTSIZE );

	LifeTime_IndexW(W_OK);						// Write index(Write OK)
	
    if( f_lt_breq == ON )						// BlockB Erase request exist ?
	{
		LT_Erase_B();							// BlockB erase
		f_lt_breq = OFF;						// Clear BlockB erase request
	} 
	else 
	{
		if( f_lt_areq == ON )					// BlockA Erase request exist ?
		{
			LT_Erase_A();						// BlockA erase
			f_lt_areq = OFF;					// Clear BlockA erase request
		}
	}
	return TRUE;
}

void LifeTime_IndexW(uint8_t adata)
{
    if( apltadr[altidx] == 0xFF )
	{
		fmc_write_flash( (uint32_t)&apltadr[altidx]-FMC_DATA_FLASH_BASE_ADDR, &adata, 1);
	}
}

void Timestamp()
{
      if(f_DP_SLP)
      {
        TimesTamp += D_DSLPVOLTTIME;
      }
      else if(f_SLEEP)
      {
        TimesTamp += D_VOLTTIME;
      }
      else
      {
        TimesTamp += 1;
      }	
			t_com36 = TimesTamp;
			t_com38 = TimesTamp >> 16;	
			DF_RUNTIME = TimesTamp;
}

