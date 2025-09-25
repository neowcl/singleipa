/****************************************************

****************************************************/
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdint.h>  

typedef union FilterValue_u 
{
	struct 
	{
		int16_t i;
		uint16_t fract;
	} i;
	int32_t l;
} FilterValue_t;
int16_t InterpolateTable(int16_t* tableX, int16_t* tableY, uint8_t len, int16_t xvalue);
int16_t InterpolateTableXlong(int32_t* tableX, int16_t* tableY, uint8_t len, int32_t xvalue);
void seed_and_filter(FilterValue_t *y, int16_t x, uint16_t a);
void filter(FilterValue_t *y, int16_t x, uint16_t a);
int16_t filter_result(const FilterValue_t *y);
int32_t A_Div_B(int32_t a,int32_t b);
int32_t A_Mult_B_Div_C(int32_t a,int32_t b,int32_t c);
uint8_t delayXs16bit(uint32_t *cnt,uint32_t x,uint8_t y);
uint8_t delayXs_NoRuntime(uint16_t *cnt,uint16_t x,uint8_t reset);
void Authentication_Calculate(uint8_t *Calculate_Data,uint8_t *Random_Data,const void *Key);
uint32_t Fabs(int32_t data);

#endif


