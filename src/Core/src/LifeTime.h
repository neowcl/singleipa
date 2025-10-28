#ifndef __LIFETIME_H__
#define __LIFETIME_H__

#include "stdint.h"
#include "base_types.h"



#pragma pack(1)


typedef struct
{
    uint16_t   lt_Erase_cnt;
    uint16_t   lt_FirstUseTime;
    uint16_t   lt_CellMaxVolt;
    uint16_t   lt_CellMinVolt;
    uint16_t   lt_ChgMaxCurrent;
    uint16_t   lt_ChgMinCurrent;
    uint16_t   lt_DsgMaxCurrent;
    uint16_t   lt_DsgMinCurrent;
    uint16_t   lt_AvgDsgMaxCurrent;
    uint16_t   lt_AvgDsgMaxPower;
    int8_t     lt_CellMaxTemp;
    int8_t     lt_CellMinTemp;
    int8_t     lt_IntMaxTemp;
    int8_t     lt_IntMinTemp;
    uint16_t   lt_PowerDownCnt;
    uint16_t   lt_QMaxUpdataCnt;
    uint16_t   lt_LastQMaxUpdataCycle;
    uint16_t   lt_LastQMaxUpdataValue;
    uint16_t   lt_VailChargeTermCnt;
    uint16_t   lt_LastVailChargeTermCycle;
    uint32_t   lt_FwTotalRunTime;
    uint32_t   lt_HighTempTime;
    uint32_t   lt_HighVoltTime;
    uint32_t   lt_HighTVTime;
    int16_t     lt_MinChargeVoltage;
}_LifTimes;

#pragma pack()

#define LTSIZE    sizeof(_LifTimes)
typedef union
{
	_LifTimes	  sltdat;								// Flexible data
	uint8_t	      uc[LTSIZE];							// Byte alignment
}_LTDF;

extern uint16_t altflg;								// Flags for DataFlash
#define f_ltreq     DEF_BIT0(&altflg)			// LifeTime req
#define f_lt_W      DEF_BIT1(&altflg)
#define f_lt_areq	DEF_BIT2(&altflg)			// BlockA
#define f_lt_breq	DEF_BIT3(&altflg)			// BlockB
#define f_lt_erase	DEF_BIT4(&altflg)	        //
#define f_reset_mcu DEF_BIT5(&altflg)		    //
#define f_updata_en DEF_BIT6(&altflg)
#define f_df_erase  DEF_BIT7(&altflg)
#define f_df_eraseflg  DEF_BIT8(&altflg)

// #define f_lftestw  DEF_BIT8(&altflg)


extern  _LTDF     DF_LifeTime;
#define altdat   DF_LifeTime.uc


#define     lterase_cnt          DF_LifeTime.sltdat.lt_Erase_cnt
#define     FirstUseTime         DF_LifeTime.sltdat.lt_FirstUseTime
#define     CellMaxVolt          DF_LifeTime.sltdat.lt_CellMaxVolt
#define     CellMinVolt          DF_LifeTime.sltdat.lt_CellMinVolt
#define     ChgMaxCurrent        DF_LifeTime.sltdat.lt_ChgMaxCurrent
#define     ChgMinCurrent        DF_LifeTime.sltdat.lt_ChgMinCurrent
#define     DsgMaxCurrent        DF_LifeTime.sltdat.lt_DsgMaxCurrent
#define     DsgMinCurrent        DF_LifeTime.sltdat.lt_DsgMinCurrent
#define     AvgDsgMaxCurrent     DF_LifeTime.sltdat.lt_AvgDsgMaxCurrent
#define     AvgDsgMaxPower       DF_LifeTime.sltdat.lt_AvgDsgMaxPower
#define     CellMaxTemp          DF_LifeTime.sltdat.lt_CellMaxTemp
#define     CellMinTemp          DF_LifeTime.sltdat.lt_CellMinTemp
#define     IntMaxTemp           DF_LifeTime.sltdat.lt_IntMaxTemp
#define     IntMinTemp           DF_LifeTime.sltdat.lt_IntMinTemp
#define     PowerDownCnt         DF_LifeTime.sltdat.lt_PowerDownCnt
#define     QMaxUpdataCnt        DF_LifeTime.sltdat.lt_QMaxUpdataCnt
#define     LastQMaxUpdataCycle  DF_LifeTime.sltdat.lt_LastQMaxUpdataCycle
#define     LastQMaxUpdataValue  DF_LifeTime.sltdat.lt_LastQMaxUpdataValue
#define     VailChargeTermCnt    DF_LifeTime.sltdat.lt_VailChargeTermCnt
#define     LastVailChargeTermCycle  DF_LifeTime.sltdat.lt_LastVailChargeTermCycle
#define     FwTotalRunTime       DF_LifeTime.sltdat.lt_FwTotalRunTime
#define     HT_TIME              DF_LifeTime.sltdat.lt_HighTempTime
#define     HV_TIME              DF_LifeTime.sltdat.lt_HighVoltTime
#define     HTV_TIME             DF_LifeTime.sltdat.lt_HighTVTime

#define     MinChargeVoltage     DF_LifeTime.sltdat.lt_MinChargeVoltage


												
#define     LIFETIME_ST_OFF                   16
#define     LIFETIME_LEN                      480
#define     LIFETIME_BLOCK                    0x01
#define     LIFETIME_FLASH_BLOCK_A            0xEC00
#define     LIFETIME_FLASH_BLOCK_B            0xEE00

extern uint16_t Fwrun_Cnt;
extern uint16_t HT_Cnt;
extern uint16_t HV_Cnt;
extern uint16_t HTV_Cnt;
extern uint16_t lt_test;


extern int16_t CurrentPower;
//extern int16_t Power;

extern uint32_t  LtW_CntW;
extern void Timestamp(void);

void LT_Erase_A(void);
void LT_Erase_B(void);
void LifeTime_Calc(void);
uint8_t LifeTime_Write(void);
void LifeTime_Read(void);
void LifeTime_IndexW(uint8_t adata);
//void Calc_Res(void);




#endif


