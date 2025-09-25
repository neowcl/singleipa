#include "cell.h"
//#include "crc.h"
//#include "DataFlash.h"
//_ST_FIXED_DATA  *u_fd_rom = (_ST_FIXED_DATA *)u_fd;


const _ST_FIXED_DATA u_fd_rom __attribute__((used)) __attribute__((section(".ARM.__at_0x0000E400")))=
{
    2800,         //d_Valid update voltage
    15,         //d_Sleep Current
    10,         //d_Deep Sleep Current
    5,         //d_Voltage Time
    20,         //d_Deep Sleep Voltage Time
    1,         //d_Wake Check Time
    2,         //d_Auto Time
    33660,         //d_-40°C NTC Impedance
    24280,         //d_-35°C NTC Impedance
    17700,         //d_-30°C NTC Impedance
    13040,         //d_-25°C NTC Impedance
    9712,         //d_-20°C NTC Impedance
    7298,         //d_-15°C NTC Impedance
    5534,         //d_-10°C NTC Impedance
    4234,         //d_-5°C NTC Impedance
    3266,         //d_0°C NTC Impedance
    2540,         //d_5°C NTC Impedance
    1990,         //d_10°C NTC Impedance
    1571,         //d_15°C NTC Impedance
    1249,         //d_20°C NTC Impedance
    1000,         //d_25°C NTC Impedance
    806,         //d_30°C NTC Impedance
    653,         //d_35°C NTC Impedance
    533,         //d_40°C NTC Impedance
    437,         //d_45°C NTC Impedance
    360,         //d_50°C NTC Impedance
    297,         //d_55°C NTC Impedance
    240,         //d_60°C NTC Impedance
    208,         //d_65°C NTC Impedance
    175,         //d_70°C NTC Impedance
    148,         //d_75°C NTC Impedance
    126,         //d_80°C NTC Impedance
    107,         //d_85°C NTC Impedance
    92,         //d_90°C NTC Impedance
    79,         //d_95°C NTC Impedance
    68,         //d_100°C NTC Impedance
    59,         //d_105°C NTC Impedance
    51,         //d_110°C NTC Impedance
    44,         //d_115°C NTC Impedance
    39,         //d_120°C NTC Impedance
    34,         //d_125°C NTC Impedance
    30,         //d_130°C NTC Impedance
    26,         //d_135°C NTC Impedance
    24,         //d_140°C NTC Impedance
    21,         //d_145°C NTC Impedance
    18,         //d_150°C NTC Impedance    
    3200,         //d_SOC-OCV Table 0%
    3649,         //d_SOC-OCV Table 5%
    3676,         //d_SOC-OCV Table 10%
    3703,         //d_SOC-OCV Table 15%
    3730,         //d_SOC-OCV Table 20%
    3753,         //d_SOC-OCV Table 25%
    3774,         //d_SOC-OCV Table 30%
    3795,         //d_SOC-OCV Table 35%
    3818,         //d_SOC-OCV Table 40%
    3845,         //d_SOC-OCV Table 45%
    3877,         //d_SOC-OCV Table 50%
    3916,         //d_SOC-OCV Table 55%
    3970,         //d_SOC-OCV Table 60%
    4031,         //d_SOC-OCV Table 65%
    4089,         //d_SOC-OCV Table 70%
    4149,         //d_SOC-OCV Table 75%
    4211,         //d_SOC-OCV Table 80%
    4273,         //d_SOC-OCV Table 85%
    4330,         //d_SOC-OCV Table 90%
    4379,         //d_SOC-OCV Table 95%
    4439,         //d_SOC-OCV Table 100%
    3895,         //d_CPH voltage table (C1/T1)
    3962,         //d_CPH voltage table (C1/T2)
    3967,         //d_CPH voltage table (C1/T3)
    4012,         //d_CPH voltage table (C1/T4)
    4013,         //d_CPH voltage table (C1/T5)
    3767,         //d_CPH voltage table (C2/T1)
    3901,         //d_CPH voltage table (C2/T2)
    3923,         //d_CPH voltage table (C2/T3)
    3979,         //d_CPH voltage table (C2/T4)
    3981,         //d_CPH voltage table (C2/T5)
    3670,         //d_CPH voltage table (C3/T1)
    3837,         //d_CPH voltage table (C3/T2)
    3877,         //d_CPH voltage table (C3/T3)
    3946,         //d_CPH voltage table (C3/T4)
    3948,         //d_CPH voltage table (C3/T5)
    3593,         //d_CPH voltage table (C4/T1)
    3778,         //d_CPH voltage table (C4/T2)
    3829,         //d_CPH voltage table (C4/T3)
    3907,         //d_CPH voltage table (C4/T4)
    3909,         //d_CPH voltage table (C4/T5)
    3544,         //d_CPL voltage table (C1/T1)
    3632,         //d_CPL voltage table (C1/T2)
    3646,         //d_CPL voltage table (C1/T3)
    3660,         //d_CPL voltage table (C1/T4)
    3661,         //d_CPL voltage table (C1/T5)
    3285,         //d_CPL voltage table (C2/T1)
    3519,         //d_CPL voltage table (C2/T2)
    3562,         //d_CPL voltage table (C2/T3)
    3626,         //d_CPL voltage table (C2/T4)
    3628,         //d_CPL voltage table (C2/T5)
    3187,         //d_CPL voltage table (C3/T1)
    3398,         //d_CPL voltage table (C3/T2)
    3465,         //d_CPL voltage table (C3/T3)
    3570,         //d_CPL voltage table (C3/T4)
    3572,         //d_CPL voltage table (C3/T5)
    3236,         //d_CPL voltage table (C4/T1)
    3317,         //d_CPL voltage table (C4/T2)
    3387,         //d_CPL voltage table (C4/T3)
    3523,         //d_CPL voltage table (C4/T4)
    3525,         //d_CPL voltage table (C4/T5)
    928,         //d_QCap Capcity table (C1/T1)
    967,         //d_QCap Capcity table (C1/T2)
    1010,         //d_QCap Capcity table (C1/T3)
    1010,         //d_QCap Capcity table (C1/T4)
    1010,         //d_QCap Capcity table (C1/T5)
    914,         //d_QCap Capcity table (C2/T1)
    951,         //d_QCap Capcity table (C2/T2)
    1000,         //d_QCap Capcity table (C2/T3)
    1000,         //d_QCap Capcity table (C2/T4)
    1000,         //d_QCap Capcity table (C2/T5)
    855,         //d_QCap Capcity table (C3/T1)
    925,         //d_QCap Capcity table (C3/T2)
    981,         //d_QCap Capcity table (C3/T3)
    981,         //d_QCap Capcity table (C3/T4)
    981,         //d_QCap Capcity table (C3/T5)
    820,         //d_QCap Capcity table (C4/T1)
    890,         //d_QCap Capcity table (C4/T2)
    959,         //d_QCap Capcity table (C4/T3)
    959,         //d_QCap Capcity table (C4/T4)
    959,         //d_QCap Capcity table (C4/T5)    
    0,         //d_Temp Threshold
    5,         //d_Dead Band
    3200,         //d_RSOC 0% voltage
    100,         //d_Charge Term Voltage
    120,         //d_Charge Term Taper Current
    40,         //d_Full Charge Judgement time 
    1,         //d_Charge Term Taper Capacity
    10,         //d_DSG Current Thershold
    10,         //d_CHG Current Thershold
    10,         //d_DSG Relax Time
    10,         //d_CHG Relax Time
    72,         //d_Relearn stop time
    60,         //d_CPH
    6,         //d_CPL
    7,         //d_CPH coefficient
    6,         //d_CPL coefficient
    6,         //d_FCC coefficient
    10,         //d_CP table C-rate 1
    30,         //d_CP table C-rate 2
    50,         //d_CP table C-rate 3
    70,         //d_CP table C-rate 4
    5,         //d_CP table T-rate 1
    15,         //d_CP table T-rate 2
    25,         //d_CP table T-rate 3
    40,         //d_CP table T-rate 4
    60,         //d_CP table T-rate 5
    50,         //d_Internal impedance cycle1
    100,         //d_Internal impedance cycle2
    200,         //d_Internal impedance cycle3
    500,         //d_Internal impedance cycle4
    800,         //d_Internal impedance cycle5
    1000,         //d_Internal impedance cycle6
    0,         //d_Internal impedance table1
    0,         //d_Internal impedance table2
    0,         //d_Internal impedance table3
    0,         //d_Internal impedance table4
    0,         //d_Internal impedance table5
    0,         //d_Internal impedance table6
    1,         //d_Internal FCC table1
    5,         //d_Internal FCC table2
    10,         //d_Internal FCC table3
    20,         //d_Internal FCC table4
    30,         //d_Internal FCC table5
    40,         //d_Internal FCC table6
    4470,         //d_Set Voltage Threshold
    4370,         //d_Clear Voltage Threshold
    100,         //d_Set % RSOC Threshold
    94,         //d_Clear % RSOC Threshold
    3200,         //d_Set Voltage Threshold
    3600,         //d_Clear Voltage Threshold
    0,         //d_Set % RSOC Threshold
    7,         //d_Clear % RSOC Threshold
    4470,         //d_Set Voltage Threshold
    4370,         //d_Clear Voltage Threshold
    100,         //d_Set % RSOC Threshold
    94,         //d_Clear % RSOC Threshold
    3300,         //d_Set Voltage Threshold
    3700,         //d_Clear Voltage Threshold
    3,         //d_Set % RSOC Threshold
    10,         //d_Clear % RSOC Threshold
    3227,         //d_Design Capacity
    3840,         //d_Design Voltage
    4470,         //d_Charge  Voltage
    3701,         //d_Full Charge Capacity
    3724,         //d_NORMAL_CC
    -10,         //d_UT
    0,         //d_LT
    15,         //d_ST
    25,         //d_SHT
    45,         //d_HT
    60,         //d_OT
    3,         //d_Temp Hysteresis
    4470,         //d_LT CV
    1024,         //d_LT CCL
    1024,         //d_LT CCM
    1024,         //d_LT CCH
    4470,         //d_STL CV
    1920,         //d_STL CCL
    1920,         //d_STL CCM
    1920,         //d_STL CCH
    4470,         //d_RT CV
    2048,         //d_RT CCL
    2048,         //d_RT CCM
    2048,         //d_RT CCH
    4470,         //d_STH CV
    1024,         //d_STH CCL
    1024,         //d_STH CCM
    1024,         //d_STH CCH
    4470,         //d_HT CV
    1024,         //d_HT CCL
    1024,         //d_HT CCM
    1024,         //d_HT CCH    
    0,         //d_Maintenance CC
    618,         //d_Pre-Charge CC
    3000,         //d_PrechargeStartVoltage
    3200,         //d_LV
    3800,         //d_MV
    4250,         //d_HV
    10,         //d_Voltage Hysteresis
    4350,         //d_High Voltage  Threshold
    40,         //d_High Temp  Threshold
    65535,         //d_Degrade Start Cycle
    199,         //d_Cycle Threshold1
    0,         //d_SOH Threshold1
    65535,         //d_Runtime Threshold1
    65535,         //d_HTHV Threshold1
    0,         //d_CV Degradation1
    0,         //d_CC Degradation1
    299,         //d_Cycle Threshold2
    0,         //d_SOH Threshold2
    65535,         //d_Runtime Threshold2
    65535,         //d_HTHV Threshold2
    20,         //d_CV Degradation2
    0,         //d_CC Degradation2
    1000,         //d_Cycle Threshold3
    0,         //d_SOH Threshold3
    65535,         //d_Runtime Threshold3
    65535,         //d_HTHV Threshold3
    60,         //d_CV Degradation3
    0,         //d_CC Degradation3
    0,         //d_R_BMU
    0,         //d_R_System
    60,         //d_Temp Threshold
    4450,         //d_Voltage Threshold
    65535,         //d_Time interval
    10,         //d_Delta Voltage
    50,         //d_Min CV
    2500,         //d_FastStepCC1
    4200,         //d_FastStepCV2
    2000,         //d_FastStepCC2
    4400,         //d_FastStepCV3
    1500,         //d_FastStepCC3
    100,         //d_CCStepDelta
    200,         //d_CCStepDown
    5,         //d_CCStepDelay
    1000,         //d_MinStepCC
    0x19ac,         //d_System Config
    0x0003,         //d_Algorithm Config
    0x0,         //d_I2C Config
    0x0,         //d_Auth Config
    0x0,         //d_Power Config
    0x0,         //d_IO Config
    0x0ccc,         //d_SOC Config A
    0x8c,         //d_SOC Config B
    0x0010,         //d_DA Config
    0x0000,         //d_Charging Config
    0x0000,         //d_LifeTime Config
    29,         //d_Initialization RSOC
    1000,         //d_InitMaxLoadCurrut
    -90,         //d_CycleCount couting percent
    3,         //d_Min Current for RC calculation
    9,         //d_Consumption current of discharge
    10,         //d_Deterioration capacity
    256,         //d_FCC update limit
    0,         //d_FCC update temp limit
    30,         //d_Qmax update min delta SOC
    5,         //d_Temp Low limit 
    45,         //d_Temp High limit 
    5,         //d_Creat Low limit
    200,         //d_Creat High limit
    0,         //d_SOC Low Limit
    100,         //d_SOC High Limit
    5,         //d_Cycle Limit
    384,         //d_Init Discharge Set
    768,         //d_Init Charge Set
    10,         //d_Init Discharge Set RSOC
    20,         //d_Init Charge Set RSOC
    95,         //d_Time RSOC Threshold 1
    90,         //d_Time RSOC Threshold 2
    70,         //d_Time RSOC Threshold 3
    50,         //d_Time RSOC Threshold 4
    30,         //d_Time RSOC Threshold 5
    10,         //d_Time RSOC Threshold 6
    5,         //d_Time RSOC Threshold 7
    245,         //d_SOCFSetThreshold
    367,         //d_SOCFClearThreshold
    74,         //d_SOC1SetThreshold
    184,         //d_SOC1ClearThreshold
    -6000,         //d_ODCDetection
    -500,         //d_ODCRecovery
    2,         //d_ODCDelay
    6000,         //d_OCCDetection
    500,         //d_OCCRecovery
    2,         //d_OCCDelay
    2950,         //d_BATLOWDetection
    3100,         //d_BATLOWRecovery
    2,         //d_BATLOWDelay
    4400,         //d_BATHIDetection
    4300,         //d_BATHIRecovery
    2,         //d_BAITHIDelay
    -10,         //d_DsgCurrent
    10,         //d_ChgCurrent
    600,         //d_OTCDetection
    500,         //d_OTCRecovery
    2,         //d_OTCDelay
    700,         //d_OTDDetection
    600,         //d_OTDRecovery
    2,         //d_OTDDelay
    4250,         //d_Init Voltage High Set
    4150,         //d_Init Voltage High Clear
    3500,         //d_Init Voltage Low Set
    3600,         //d_Init Voltage Low Clear
    60,         //d_Init Temperature High Set
    50,         //d_Init Temperature High Clear
    0,         //d_Init Temperature Low Set
    3,         //d_Init Temperature Low Clear
    5,         //d_SOC Delta
    80,         //d_GPIO Pulse Width
    0x0028,         //d_MfgStatusinit Config
    16409,         //d_Cell Gain
    5510,         //d_CC Gain
    -28,         //d_CC_Offset
    -3,         //d_Cell Temp Offset
    0,         //d_Ex Temp Offset    
    21172,         //d_Manufacture Date
    0x0abc,         //d_Serial Number
    {10,'a','b','c','d','e','f','g','h','i','j'},         //d_Manufacturer Name
    {8,'V','e','r','i','d','i','a','n'},         //d_Device Name
    {4,'L','I','O','N'},         //d_Device Chemistry
    0x47,         //d_Manufacturer Info Block A01
    0x57,         //d_Manufacturer Info Block A02
    0x33,         //d_Manufacturer Info Block A03
    0x4c,         //d_Manufacturer Info Block A04
    0x30,         //d_Manufacturer Info Block A05
    0x31,         //d_Manufacturer Info Block A06
    0x33,         //d_Manufacturer Info Block A07
    0x35,         //d_Manufacturer Info Block A08
    0x34,         //d_Manufacturer Info Block A09
    0x36,         //d_Manufacturer Info Block A10
    0x4e,         //d_Manufacturer Info Block A11
    0x44,         //d_Manufacturer Info Block A12
    0x37,         //d_Manufacturer Info Block A13
    0x31,         //d_Manufacturer Info Block A14
    0x46,         //d_Manufacturer Info Block A15
    0x52,         //d_Manufacturer Info Block A16
    0x58,         //d_Manufacturer Info Block A17
    0x31,         //d_Manufacturer Info Block A18
    0x44,         //d_Manufacturer Info Block A19
    0x45,         //d_Manufacturer Info Block A20
    0x46,         //d_Manufacturer Info Block A21
    0x47,         //d_Manufacturer Info Block A22
    0x48,         //d_Manufacturer Info Block A23
    0x49,         //d_Manufacturer Info Block A24
    0x4a,         //d_Manufacturer Info Block A25
    0x4b,         //d_Manufacturer Info Block A26
    0x4c,         //d_Manufacturer Info Block A27
    0x4e,         //d_Manufacturer Info Block A28
    0x4f,         //d_Manufacturer Info Block A29
    0x50,         //d_Manufacturer Info Block A30
    0x51,         //d_Manufacturer Info Block A31
    0x30,         //d_Manufacturer Info Block A32
    0x46,         //d_Manufacturer Info Block B01
    0x38,         //d_Manufacturer Info Block B02
    0x59,         //d_Manufacturer Info Block B03
    0x31,         //d_Manufacturer Info Block B04
    0x33,         //d_Manufacturer Info Block B05
    0x37,         //d_Manufacturer Info Block B06
    0x35,         //d_Manufacturer Info Block B07
    0x31,         //d_Manufacturer Info Block B08
    0x50,         //d_Manufacturer Info Block B09
    0x30,         //d_Manufacturer Info Block B10
    0x52,         //d_Manufacturer Info Block B11
    0x31,         //d_Manufacturer Info Block B12
    0x33,         //d_Manufacturer Info Block B13
    0x58,         //d_Manufacturer Info Block B14
    0x43,         //d_Manufacturer Info Block B15
    0x38,         //d_Manufacturer Info Block B16
    0x48,         //d_Manufacturer Info Block B17
    0x43,         //d_Manufacturer Info Block B18
    0x44,         //d_Manufacturer Info Block B19
    0x45,         //d_Manufacturer Info Block B20
    0x46,         //d_Manufacturer Info Block B21
    0x47,         //d_Manufacturer Info Block B22
    0x48,         //d_Manufacturer Info Block B23
    0x49,         //d_Manufacturer Info Block B24
    0x4a,         //d_Manufacturer Info Block B25
    0x4b,         //d_Manufacturer Info Block B26
    0x4c,         //d_Manufacturer Info Block B27
    0x4e,         //d_Manufacturer Info Block B28
    0x4f,         //d_Manufacturer Info Block B29
    0x50,         //d_Manufacturer Info Block B30
    0x51,         //d_Manufacturer Info Block B31
    0x30,         //d_Manufacturer Info Block B32
    0x0c64,         //d_StaticDFSignature
    0xcb9e,         //d_DynamicDFSignature
    0x10,         //d_Key1
    0x12,         //d_Key2
    0x22,         //d_Key3
    0x20,         //d_Key4
    0xff,         //d_Key1
    0xff,         //d_Key2
    0xff,         //d_Key3
    0xff,         //d_Key4
    3600,         //d_FCC Max Limit
    1500,         //d_FCC Min Limit
    100,         //d_Current Limit
    5,         //d_Current Limit Time    
100,  // #define D_PINGHUA_CHGVOL_THRESH	u_fd_rom.d_pinghua_chgvol_thresh  //100
230,//#define D_PINGHUA_CHGCUR_LOW   u_fd_rom.d_d_pinghua_chgcur_low    // 230
350,// #define D_PINGHUA_CHGCUR_HIGH u_fd_rom.d_pinghua_chgcur_high      // 350 
40,// #define D_PINGHUA_TIME	u_fd_rom.d_pinghua_time                   // 40
3,// #define D_PINGHUA_CUR_RANGE   u_fd_rom.d_pinghua_cur_range        // 3
30,// #define D_PINGHUA_CAP  u_fd_rom.d_pinghua_cap                     // 30  *3600/100/1400

-4,// #define D_SPL_TEMP  u_fd_rom.d_spl_Tmep
{0x74, 0x33, 0x48, 0x00, 0xEB, 0x93, 0xEC, 0x5F, 0xBB, 0x0C, 0xA6, 0x94, 0x17, 0x27, 0xF3, 0x42,
    0x67, 0xDE, 0xDD, 0xA3, 0x31, 0xEF, 0x92, 0x0F, 0xAE, 0xF8, 0x65, 0xD0, 0x7A, 0xD3, 0x66, 0xCC},  
{0x37, 0x34, 0x31, 0x2D, 0x30, 0x31, 0x30, 0x36, 0x36}, 
{0xed,0x7c,0x3d,0x3c},
{0xee,0x82,0x01,0x00},
{0xd9,0x82,0x01,0x00},
{0xbb,0x82,0x01,0x00},
{0x01,0xe1,0x00,0x00},
{0xd4,0x1f,0x80,0x06},
{0xE7, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x36,0x00,0x00,0x00,0x2f,0x00,0x00,0x20,0x15,0x00,0x00,0x40},
{0x36,0x00,0x00,0x00,0x23,0x00,0x00,0x20,0x15,0x00,0x00,0x40},
18,  // DSG_PINGHUA_MUL
10,  // DSG_PINGHUA_DIV
3100, 
3000,
0x2240,
};














