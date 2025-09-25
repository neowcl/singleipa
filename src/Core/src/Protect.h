#ifndef __PROTECT_H__
#define __PROTECT_H__

#include "stdint.h"
#include "base_types.h"



extern boolean_t bOV;
extern boolean_t bUV;
extern boolean_t bOT;
extern boolean_t bUT;
extern boolean_t bORSOC;
extern boolean_t bURSOC;
extern boolean_t bSDSOC;
extern boolean_t bSOC;

extern boolean_t bTempSOC;

extern boolean_t bIO_Alarm;


extern void ProtectProcess(void);
extern void BatteryTripPoint(void);
//void Calc_Dischargefactor(void);



#endif
