#ifndef __RAM_H__
#define __RAM_H__

#include "stdint.h"
#include "base_types.h"

#pragma pack(1)
typedef struct
{
    int16_t    df_AtRate;
    uint16_t   df_AtRateTime;
    int16_t    df_MaxLoadCurrent;
    uint16_t   df_MaxLoadTimeToEmpty;
    uint16_t   df_RSOC;
    uint16_t   df_SOH;
    uint16_t   df_RemainingCap;
    uint16_t   df_FullChargeCap;
    uint16_t   df_CycleCount;
    uint16_t   df_QMax;
    int16_t    df_ChargingVolt;
    int16_t    df_ChargingCur;
    int32_t    df_lrc_w;
    uint16_t   df_tcc_cnt;
    uint16_t   df_trek_cnt;
    uint16_t   df_tdferase_cnt;
    uint16_t   df_Reset_flag;
    uint16_t   df_Reset_cnt;
		uint32_t   df_RunTime_Cnt;
		int32_t  	df_Del_lrc;
		int32_t  	df_Ilrc_w;
		uint16_t 	df_IdealRc;
		uint16_t 	df_IdealFcc;
		uint16_t 	df_IRsoc;
		uint16_t   df_Chargefactor;
		uint16_t  	df_Dischargefactor;
}_DFDAT;
#pragma pack()

#define DFSIZE	sizeof(_DFDAT)					// DataFlash size

typedef union
{
	_DFDAT	sdfdat;								// Flexible data
	uint8_t	uc[DFSIZE];							// Byte alignment
}_DF;

extern  _DF	sdf;
#define adfdat		sdf.uc
extern  uint8_t	ReadRecord[DFSIZE];

#define  DF_ATRATE          sdf.sdfdat.df_AtRate
#define  DF_ATRATETIME      sdf.sdfdat.df_AtRateTime
#define  DF_MAXLOADCUR      sdf.sdfdat.df_MaxLoadCurrent
#define  DF_MAXLOADATTE     sdf.sdfdat.df_MaxLoadTimeToEmpty
#define  DF_RSOC            sdf.sdfdat.df_RSOC
#define  DF_SOH             sdf.sdfdat.df_SOH
#define  DF_REMCAP          sdf.sdfdat.df_RemainingCap
#define  DF_FCC             sdf.sdfdat.df_FullChargeCap
#define  DF_CYCLECNT        sdf.sdfdat.df_CycleCount
#define  DF_QMAX            sdf.sdfdat.df_QMax
#define  DF_CV              sdf.sdfdat.df_ChargingVolt
#define  DF_CC              sdf.sdfdat.df_ChargingCur
#define  lrc_w		        sdf.sdfdat.df_lrc_w		// RC correction capacity
#define  tcc_cnt		    sdf.sdfdat.df_tcc_cnt	// CycleCount RC counter
#define  trek_cnt	        sdf.sdfdat.df_trek_cnt	// Degradation counter
#define  tdferase_cnt	    sdf.sdfdat.df_tdferase_cnt
#define  Reset_flag         sdf.sdfdat.df_Reset_flag
#define  Reset_cnt          sdf.sdfdat.df_Reset_cnt
#define  DF_RUNTIME         sdf.sdfdat.df_RunTime_Cnt

#define  Del_lrc         sdf.sdfdat.df_Del_lrc
#define  Ilrc_w         sdf.sdfdat.df_Ilrc_w
#define  IdealRc         sdf.sdfdat.df_IdealRc
#define  IdealFcc         sdf.sdfdat.df_IdealFcc
#define  IRsoc         sdf.sdfdat.df_IRsoc
#define  Chargefactor         sdf.sdfdat.df_Chargefactor
#define  Dischargefactor         sdf.sdfdat.df_Dischargefactor



extern uint16_t adfflg;	
						// Flags for DataFlash
#define f_dfreq     DEF_BIT0(&adfflg)			// LifeTime req
#define f_df_areq	DEF_BIT2(&adfflg)			// BlockA
#define f_df_breq	DEF_BIT3(&adfflg)			// BlockB
// #define f_dftestw     DEF_BIT0(&adfflg)			// DFWtest req


#define     DF_ST_OFF                   16
#define     DF_LEN                      124
#define     DF_BLOCK                    0x04
#define     DF_FLASH_BLOCK_A            0xE800
#define     DF_FLASH_BLOCK_B            0xEA00

void DF_Erase_A(void);
void DF_Erase_B(void);
uint8_t DF_Write(void);
void DF_Read(void);
void DF_IndexW(uint8_t adata);

#endif



