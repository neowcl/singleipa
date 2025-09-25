#ifndef __MODE_H__
#define __MODE_H__

#include "stdint.h"
#include "base_types.h"


extern uint16_t CS_Cnt;
extern uint16_t CS_Cnt1;
extern uint8_t CellVoltRange;
extern uint16_t CCS_Cnt;
extern uint16_t CCS_Cnt1;
#define CV_PV	    0x10
#define	CV_LV  		0x80
#define	CV_MV  		0x40
#define	CV_HV  		0x20
#define	CV_CVRALL	0xF0



extern uint8_t norelax;
extern uint16_t t_com66_FC_cnt;

void TemperatureRangeJudge(void);
void VoltageRangeJudge(void);
void TFStatus(void);
void Alarm_Chk(void);
void Set_CCCV(void);


void FlagStatus(void);
void FlagStatus1(void);










#endif
