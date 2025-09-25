/****************************************************

****************************************************/
#include "utility.h"
#include <math.h> 
#include <stdlib.h> 

#include "cbmx56x_sha256.h"
#include "cbmx56x_hdiv.h"
#include "cbmx56x_rcc.h"

//int16_t InterpolateTableXlong(int32_t* tableX, int16_t* tableY, uint8_t len, int32_t xvalue)
//{
//    int32_t yvalue,y1,x1,x2;
//    float k;
//    int16_t i = 1;
//    while ((tableX[i] < xvalue) && (i < (len-1)))
//        i++;
//    y1 = (tableY[i] - tableY[i-1]);
//    x1 = (xvalue - tableX[i-1]);
//    x2 = (tableX[i] - tableX[i-1]);
//    if(x2 != 0)
//    {
//      k = (float)x1/x2;
//      yvalue =  (int32_t)(y1 * k + tableY[i-1]); 
//    }
//    else
//      yvalue = tableY[i-1];
//    return(yvalue);
//}
/**
  * @brief  Division operation
  * @param  a: dividend 
  * @param  b: divisor
  * @retval return a/b
  */
int32_t A_Div_B(int32_t a,int32_t b)
{
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_HDIV, ENABLE);
    int32_t quotient;
    int32_t dividend;
    int32_t divisor;

    dividend = (int32_t)a;
    divisor = (int32_t)b;
    quotient=hdiv_quotient_int(dividend, divisor);
    return quotient;
}

/**
  * @brief  Division operation
  * @param  a:  
  * @param  b: 
  * @param  c: divisor
  * @retval return a*b/c
  */
int32_t A_Mult_B_Div_C(int32_t a,int32_t b,int32_t c)
{
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_HDIV, ENABLE);
    int32_t product;
    int32_t quotient;
    int32_t divisor;  

    divisor = (int32_t)c;
    product = (int32_t)a * (int32_t)b;
    quotient = hdiv_quotient_int(product, divisor);
    return quotient;
}


uint32_t Fabs(int32_t data)
{
    if(data<0)
    {
        return (-data);
    }
    else
    {
        return data;
    }
}
//uint32_t result[8];
//uint8_t aa[32];
void Authentication_Calculate(uint8_t *Calculate_Data,uint8_t *Random_Data,const void *Key)
{
    sha256_hmac_calc(Random_Data,32,(uint8_t *)Key,32,Calculate_Data);
}

