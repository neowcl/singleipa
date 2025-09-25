/**************************************************************************//**
 * @file     modules_temp.c
 * @version  V1.0.0
 * @author   chensj0621
 * @date     2021-01-25 AM
 * @brief    温度检测模块
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

// Include header file.
#include "modules_temp.h"

#if 0
static int16_t  temperature_in_value = 0;
static int16_t  temperature_ex_value = 0;

static int16_t modules_temp_in_calc_value(int32_t reg_data);
static int32_t modules_temp_ex_calc_value(int32_t reg_data);
int16_t modules_check_table(int table_data);
//static void modules_temp_ctrl_enable(void);
//static void modules_temp_ctrl_disable(void);

//温度对应阻值表
const int resistT[146]=
{
/*  -40度     -39      -38      -37      -36      -35      -34      -33      -32      -31   */
    2208889, 2080846, 1961166, 1849244, 1744525, 1646495, 1554682, 1468649, 1387994, 1312344,
/*  -30      -29      -28      -27      -26      -25      -24      -23      -22      -21   */
    1241355, 1174708, 1112110, 1053288, 997989 , 945978 , 897039 , 850971 , 807585 , 766710 , 
/*  -20      -19      -18      -17      -16      -15      -14      -13      -12      -11   */
    728183 , 691854 , 657584 , 625243 , 594711 , 565874 , 538628 , 512875 , 488524 , 465491 ,
/*  -10      -9       -8       -7       -6       -5       -4       -3       -2       -1    */
    443694 , 423062 , 403523 , 385014 , 367474 , 350846 , 335077 , 320118 , 305923 , 292447 ,
/*  0        1        2        3        4        5        6        7        8        9     */
    279650 , 267494 , 255943 , 244962 , 234522 , 224591 , 215143 , 206150 , 197588 , 189435 ,
/*  10       11       12       13       14       15       16       17       18       19    */
    181667 , 174266 , 167210 , 160483 , 154067 , 147946 , 142105 , 136529 , 131205 , 126120 ,
/*  20       21       22       23       24       25       26       27       28       29    */
    121262 , 116620 , 112182 , 107940 , 103882 , 100000 , 96286  , 92731  , 89327  , 86068  ,
/*  30       31       32       33       34       35       36       37       38       39    */
    82946  , 79955  , 77089  , 74342  , 71708  , 69182  , 66759  , 64434  , 62203  , 60061  ,
/*  40       41       42       43       44       45       46       47       48       49    */
    58005  , 56031  , 54135  , 52313  , 50562  , 48879  , 47261  , 45706  , 44210  , 42771  ,
/*  50       51       52       53       54       55       56       57       58       59    */
    41386  , 40054  , 38771  , 37536  , 36347  , 35202  , 34099  , 33036  , 32011  , 31024  , 
/*  60       61       62       63       64       65       66       67       68       69    */
    30072  , 29155  , 28269  , 27416  , 26592  , 25797  , 25030  , 24290  , 23574  , 22885  ,
/*  70       71       72       73       74       75       76       77       78       79    */
    22218  , 21575  , 20952  , 20351  , 19770  , 19209  , 18666  , 18141  , 17634  , 17143  ,
/*  80       81       82       83       84       85       86       87       88       89    */
    16668  , 16208  , 15764  , 15333  , 14917  , 14513  , 14123  , 13745  , 13379  , 13024  ,
/*  90       91       92       93       94       95       96       97       98       99    */
    12680  , 12347  , 12024  , 11711  , 11408  , 11114  , 10829  , 10552  , 10284  , 10024  ,
/*  100      101      102      103      104      105                                       */
    9771   , 9526   , 9288   , 9058   , 8834   , 8616
};        

/**
* @fn void modules_vbat_isr_process(void)
* @brief 温度检测模块中断处理函数  
* @param None
* @return None.
*/
void modules_temp_isr_process(void)
{

}


/**
* @fn void modules_temp_in_updata_value(void)
* @brief 更新内部温度值
* @param None
* @return 0:success  1:error
*/
char modules_temp_in_updata_value(void)
{  
   int32_t temperature_in_value_temp = 0;

   if(vadc_flag_status_get(VADC_FLAG_CHANNEL2_ADCDVF) != SET)
   {
        return 1;
   }
   //modules_temp_ctrl_disable();

   temperature_in_value_temp = vadc_conversion_value_get(VADC_CHANNEL_2);

   temperature_in_value = modules_temp_in_calc_value(temperature_in_value_temp);

   //modules_temp_ctrl_enable();

   return 0;
}

/**
* @fn void modules_temp_ex_updata_value(void)
* @brief 更新外部温度值
* @param None
* @return 0:success  1:error
*/
char modules_temp_ex_updata_value(void)
{  
   int32_t temperature_ex_value_temp = 0;
   int32_t temperature_ex_table = 0;

   if(vadc_flag_status_get(VADC_FLAG_CHANNEL3_ADCDVF) != SET)
   {
        return 1;
   }
   //modules_temp_ctrl_disable();
   
   temperature_ex_value_temp = vadc_conversion_value_get(VADC_CHANNEL_3);
   
   temperature_ex_table = modules_temp_ex_calc_value(temperature_ex_value_temp);

   temperature_ex_value = modules_check_table(temperature_ex_table);

   //modules_temp_ctrl_enable();
  
    return 0;   
}

/**
* @fn void modules_vbat_updata_task(void)
* @brief 从温度检测模块获得内部温度值
* @param None
* @return 内部温度值
*/
int16_t modules_temp_in_get_value()
{
    return temperature_in_value;
}

/**
* @fn void modules_vbat_updata_task(void)
* @brief 从温度检测模块获得内部温度值
* @param None
* @return 内部温度值
*/
int16_t modules_temp_ex_get_value()
{
    return temperature_ex_value;
}

/**
* @fn void modules_vbat_updata_task(void)
* @brief 内部温度计算
* @param None
* @return 内部温度值
*/
static int16_t modules_temp_in_calc_value(int32_t reg_data)  
{
    int64_t value_temp;
    int32_t ts_trim0;
    int32_t ts_trim1;
    double  temp_temp ;
    int32_t dividend[2];
    int32_t divisor;
    int32_t quotient[2];
    int32_t remainder;
    int64_t value_vol;
    int32_t down_sampling_rate;

    down_sampling_rate= (int32_t)vadc_down_sampling_rate_get();
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_HDIV, ENABLE);

    dividend[0]= ((reg_data >> 16)& 0x00FFFFFF);
    dividend[1]= reg_data << 16;

    divisor= down_sampling_rate;
    hdiv_quotient_read(dividend, divisor, quotient, &remainder);  

    dividend[1]= quotient[0];
    dividend[0]= quotient[1];
    
    hdiv_quotient_read(dividend, divisor- 1, quotient, &remainder);
    value_vol= (quotient[0] );
    
    /*!< Internal temperature sensor */
//    ts_trim0 = temp_vadc_tr0_get();
//    ts_trim1 = temp_vadc_tr1_get();
    ts_trim0 = GCR->TEMP_TR0;
    ts_trim1 = GCR->TEMP_TR1;

//    temp_temp = (double)((value_vol )- ts_trim0)* 20.4627514 * (1) + ts_trim1;
//    value_temp= (int32_t)(temp_temp- 27315);
//    value_temp = (value_temp / 10) + 0xAAB;          //0xAAB=2731 加上2731转换成开尔文温度。和TI同步
     temp_temp = (int32_t)((value_vol )- ts_trim0)* 20.4627514 * (1) + ts_trim1;
     value_temp = (int32_t)temp_temp/100;

    return (int16_t)value_temp;
}

/**
* @fn void modules_vbat_updata_task(void)
* @brief 外部温度计算
* @param None
* @return 外部温度值
*/
static int32_t modules_temp_ex_calc_value(int32_t reg_data)  
{
    int64_t value_temp;
    int32_t ts_trim2;
    double temp_temp ;
    int32_t dividend[2];
	int32_t divisor;
	int32_t quotient[2];
	int32_t remainder;
	int64_t value_vol;
    int32_t down_sampling_rate;
    int32_t vadc_offset = 0;

   // vadc_offset = vadc_vadc_offset_get();
    
    down_sampling_rate= (int32_t)vadc_down_sampling_rate_get();
    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_HDIV, ENABLE);

    dividend[0]= ((reg_data>> 8)& 0x00FFFFFF);
    dividend[1]= reg_data<< 24;

    divisor= down_sampling_rate;
    hdiv_quotient_read(dividend, divisor, quotient, &remainder);  

    dividend[1]= quotient[0];
    dividend[0]= quotient[1];
    hdiv_quotient_read(dividend, divisor- 1, quotient, &remainder);

    if(quotient[0]> 0x800000)
    {
        value_vol= quotient[0]- 0x800000;
    }
    else
    {
        value_vol= -(0x800000- quotient[0]); 
    }
    if (vadc_offset != 0)
    {
        if (vadc_offset > 0x8000)
        {
            vadc_offset = vadc_offset - 0x8000;
        }
        else 
        {
            vadc_offset = -(0x8000 - vadc_offset);
        }
        vadc_offset= (2 * vadc_offset * 2 * VADC_VBAT_VREF * 10) >> 16;  
    }
    else 
    {
        vadc_offset = 0;
    }

    value_vol = ((2 * value_vol * 2 * 1900 * 10) >> 24 ) - vadc_offset; 

    rcc_ahb_periph_clock_enable_ctrl(RCC_AHB_PERI_HDIV, DISABLE);

  //  ts_trim2  = temp_vadc_tr2_get();
    if (ts_trim2 == 0)
    {
        ts_trim2 = 18000;
    }
    temp_temp = (double)(value_vol * ts_trim2) * 10/ (19000 - value_vol);
    
    value_temp = (int32_t)(temp_temp);  /*!< External temperature sensor */

    return value_temp;
}

/**
* @fn void modules_check_table(int table_data)
* @brief 外部温度查表
* @param 计算出来的外部温度实际值
* @return 外部温度值.
*/
int16_t modules_check_table(int table_data)
{
    int16_t tempIndex=0;   
   
	while((table_data < resistT[tempIndex]) && (tempIndex < sizeof(resistT)))	
	{
		tempIndex++;
	}

	//return ((tempIndex-40)*10 +0xAAB) ;           //下限为-40度，所以要减去40            0xAAB=2731 加上2731转换成开尔文温度。和TI同步
    return ((tempIndex-40) +0xAAB/10) ;
}
#endif

#if 0
/**
* @fn void modules_vbat_ctrl_enable(void)
* @brief 启动AFE采样
* @param None
* @return None.
*/
static void modules_temp_ctrl_enable(void)                                
{
    vadc_enable_ctrl(ENABLE);
}

/**
* @fn void modules_vbat_ctrl_disable(void)
* @brief 关闭AFE采样
* @param None
* @return None.
*/
static void modules_temp_ctrl_disable(void)                                 
{
    vadc_enable_ctrl(DISABLE);
}
#endif

/****************************************************
* ad value-table vs ntc ;unit 0.1 O
****************************************************/
const int32_t  R_x[140] = 
{
10024, 10284, 10552, 10829, 11114, 11408, 11711, 12024, 12347, 12680,
13024, 13379, 13745, 14123, 14513, 14917, 15333, 15764, 16208, 16668, 
17143, 17634, 18141, 18666, 19209, 19770, 20351, 20952, 21575, 22218,
22885, 23575, 24290, 25030, 25797, 26592, 27416, 28269, 29155, 30072, 
31024, 32011, 33036, 34099, 35202, 36347, 37536, 38771, 40054, 41386, 
42771, 44210, 45706, 47261, 48879, 50562, 52313, 54135, 56031, 58005,
60061, 62203, 64434, 66759, 69182, 71708, 74342, 77089, 79955, 82946,
86068, 89327, 92731, 96286, 100000,103882,107940,112182,116620,121262,
126120,131205,136529,142105,147946,154067,160483,167210,174266,181667,
189435,197588,206150,215143,224591,234522,244962,255943,267494,279650,
292447,305923,320118,335077,350846,367474,385014,403523,423062,443694,//-1 -10
465491,488524,512875,538628,565874,594711,625243,657584,691854,728183,//-11 -20--
766710, 807585, 850971, 897039, 945978, 997989, 1053288,1112110,1174708,1241355,//-21 -30
1312344,1387994,1468649,1554682,1646495,1744525,1849244,1961166,2080846,2208889,//-31 -40
};
/****************************************************
* ntc-table  ;unit 0.1C
****************************************************/
const int16_t T_y[140] =
{
    990, 
    980,
    970, 
    960,
    950, 
    940,
    930, 
    920,
    910, 
    900,
    890, 
    880,
    870, 
    860,
    850, 
    840,
    830,
    820,
    810, 
    800,
    790, 
    780,
    770, 
    760,
    750, 
    740,
    730,
    720,
    710, 
    700,
    690, 
    680,
    670, 
    660,
    650, 
    640,
    630, 
    620,
    610, 
    600,
    590,
    580,
    570, 
    560,
    550, 
    540,
    530, 
    520,
    510, 
    500,
    490, 
    480,
    470, 
    460,
    450, 
    440,
    430, 
    420,
    410, 
    400,
    390, 
    380,
    370, 
    360,
    350,
    340,
    330, 
    320,
    310, 
    300,
    290, 
    280,
    270, 
    260,
    250, 
    240,
    230, 
    220,
    210, 
    200,
    190, 
    180,
    170, 
    160,
    150, 
    140,
    130, 
    120,
    110,
    100,
    90,
    80,  
    70,  
    60,
    50, 
    40,
    30,  
    20,
    10,  
    0, 
    -10,
    -20, 
    -30,
    -40, 
    -50,
    -60, 
    -70,
    -80,
    -90,
    -100,
    -110,
    -120,
    -130,
    -140,
    -150,
    -160,
    -170,
    -180,
    -190,
    -200,
    -210,
    -220,
    -230,
    -240,
    -250,
    -260,
    -270,
    -280,
    -290,
    -300,
    -310,
    -320,
    -330,
    -340,
    -350,
    -360,
    -370,
    -380,
    -390,
    -400
};
int16_t InterpolateTableXlong(int32_t* tableX, int16_t* tableY, uint8_t len, int32_t xvalue)
{
    int32_t yvalue, y1, x1, x2;
    float k;
    int16_t i = 1;
    while ((tableX[i] < xvalue) && (i < (len-1)))
        i++;
    y1 = (tableY[i] - tableY[i-1]);
    x1 = (xvalue - tableX[i-1]);
    x2 = (tableX[i] - tableX[i-1]);
    if(x2 != 0)
    {
        k = (float)x1/x2;
        yvalue =  (int32_t)(y1 * k + tableY[i-1]); 
    }
    else
        yvalue = tableY[i-1];
    return(yvalue);
}

/*小数点一位*/
int16_t Lookup_T(int32_t Rt)
{
    int16_t v;
    v = InterpolateTableXlong((int32_t *)R_x, (int16_t *)T_y, 140, Rt);
    return(v);
}
