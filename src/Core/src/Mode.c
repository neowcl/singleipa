#include "Mode.h"
#include "Cell.h"
#include "bi2cs_interface.h"
#include "LifeTime.h"
#include "Ram.h"

uint8_t CellVoltRange;
uint16_t CS_Cnt = 0;
uint16_t CS_Cnt1 = 0;
// uint16_t CCS_Cnt = 0;
// uint16_t CCS_Cnt1 = 0;

uint16_t FVoltage = 0;

// uint8_t ODC_Cnt;
// uint8_t OCC_Cnt;
// uint8_t BATHI_Cnt;
// uint8_t BATLOW_Cnt;
// uint8_t OTC_Cnt;
// uint8_t OTD_Cnt;

void TemperatureRangeJudge(void)
{
    if (CellTemp < D_JT1)
    {
        TempRange.data = TR_UT;
    }
    else if (CellTemp < D_JT2)
    {
        if (TempRange.data & TR_UT)
        {
        TempRange_LT:
            if (CellTemp > (D_JT1 + D_HYSTEMP))
            {
                TempRange.data = TR_LT;
            }
        }
        else
        {
            TempRange.data = TR_LT;
        }
    }
    else if (CellTemp < D_JT5)
    {
        if (TempRange.data & (TR_UT | TR_LT))
        {
        TempRange_STL:
            if (CellTemp > (D_JT2 + D_HYSTEMP))
            {
                TempRange.data = TR_STL;
            }
            else
            {
                goto TempRange_LT;
            }
        }
        else
        {
            TempRange.data = TR_STL;
        }
    }
    else if (CellTemp <= D_JT6)
    {
        if (TempRange.data & (TR_UT | TR_LT | TR_STL))
        {
            if (CellTemp > (D_JT5 + D_HYSTEMP))
            {
                TempRange.data = TR_RT;
            }
            else
            {
                goto TempRange_STL;
            }
        }
        else if (TempRange.data & (TR_STH | TR_HT | TR_OT))
        {
            if (CellTemp < (D_JT6 - D_HYSTEMP))
            {
                TempRange.data = TR_RT;
            }
            else
            {
                goto TempRange_STH;
            }
        }
        else
        {
            TempRange.data = TR_RT;
        }
    }
    else if (CellTemp <= D_JT3)
    {
        if (TempRange.data & (TR_HT | TR_OT))
        {
        TempRange_STH:
            if (CellTemp < (D_JT3 - D_HYSTEMP))
            {
                TempRange.data = TR_STH;
            }
            else
            {
                goto TempRange_HT;
            }
        }
        else
        {
            TempRange.data = TR_STH;
        }
    }
    else if (CellTemp <= D_JT4)
    {
        if (TempRange.data & TR_OT)
        {
        TempRange_HT:
            if (CellTemp < (D_JT4 - D_HYSTEMP))
            {
                TempRange.data = TR_HT;
            }
        }
        else
        {
            TempRange.data = TR_HT;
        }
    }
    else
    {
        TempRange.data = TR_OT;
    }
}

void VoltageRangeJudge(void)
{
    int8_t F0;
    int8_t F1;
    if (t_com09 <= D_PRESVOLT)
    {
        // EA = 0;
        ChargingStatus.data &= 0xfff0;
        f_PV = 1;
        // EA = 1;
    }
    else
    {
        F1 = 0;
        F0 = 0;
        if (t_com09 <= D_CVLOW)
        {
            if (CellVoltRange & (CV_LV | CV_MV | CV_HV))
            {
                if (t_com09 < (D_CVLOW - D_CVHYS))
                {
                    CellVoltRange = (CellVoltRange & ~CV_CVRALL) | CV_PV;
                    F1 = 1;
                }
                else
                    goto CVRange_LV;
            }
            else
            {
                CellVoltRange = (CellVoltRange & ~CV_CVRALL) | CV_PV;
                F1 = 1;
            }
            if (F1)
            {
                if (f_LV || f_MV || f_HV)
                {
                    if (f_dsg || f_relax)
                    {
                        F0 = 1;
                    }
                }
                else
                {
                    F0 = 1;
                }
                if (F0)
                {
                    // EA = 0;
                    ChargingStatus.data &= 0xfff0;
                    f_PV = 1;
                    // EA = 1;
                }
            }
        }
        else if (t_com09 <= D_CVMED)
        {
        CVRange_LV:
            if (CellVoltRange & (CV_MV | CV_HV))
            {
                if (t_com09 < (D_CVMED - D_CVHYS))
                {
                    CellVoltRange = (CellVoltRange & ~CV_CVRALL) | CV_LV;
                    F1 = 1;
                }
                else
                    goto CVRange_MV;
            }
            else
            {
                CellVoltRange = (CellVoltRange & ~CV_CVRALL) | CV_LV;
                F1 = 1;
            }
            if (F1)
            {
                if (f_MV || f_HV)
                {
                    if (f_dsg || f_relax)
                    {
                        F0 = 1;
                    }
                }
                else if (f_PV)
                {
                    if (t_com09 > D_CVLOW)
                        F0 = 1;
                }
                else
                    F0 = 1;
                if (F0)
                {
                    // EA = 0;
                    ChargingStatus.data &= 0xfff0;
                    f_LV = 1;
                    // EA = 1;
                }
            }
        }
        else if (t_com09 <= D_CVHIGH)
        {
        CVRange_MV:
            if (CellVoltRange & CV_HV)
            {
                if (t_com09 < (D_CVHIGH - D_CVHYS))
                {
                    CellVoltRange = (CellVoltRange & ~CV_CVRALL) | CV_MV;
                    F1 = 1;
                }
            }
            else
            {
                CellVoltRange = (CellVoltRange & ~CV_CVRALL) | CV_MV;
                F1 = 1;
            }
            if (F1)
            {
                if (f_HV)
                {
                    if (f_dsg || f_relax)
                    {
                        F0 = 1;
                    }
                }
                else if (f_PV)
                {
                    if (t_com09 > D_CVLOW)
                        F0 = 1;
                }
                else
                    F0 = 1;
                if (F0)
                {
                    // EA = 0;

                    ChargingStatus.data &= 0xfff0;
                    f_MV = 1;
                    // EA = 1;
                }
            }
        }
        else
        {
            CellVoltRange = (CellVoltRange & ~CV_CVRALL) | CV_HV;
            if (f_PV)
            {
                if (t_com09 > D_CVLOW)
                    F0 = 1;
            }
            else
                F0 = 1;
            if (F0)
            {
                // EA = 0;
                ChargingStatus.data &= 0xfff0;
                f_HV = 1;
                // EA = 1;
            }
        }
    }
}

void Alarm_Chk(void)
{
}

void TFStatus(void)
{
    if (f_TC)
    {
        // Condition: CLEAR V
        if (f_TCCLV)
        {
            if (t_com09 <= D_TCCLVOLTTHR)
            {
                f_TC = OFF;
            }
        }
        // Condition: CLEAR RSOC
        if (f_TCCLRSOC)
        {
            if (t_com0d <= D_TCCLRSOCTHR)
            {
                f_TC = OFF;
            }
        }
    }
    else
    {
        // Condition: SET V
        if (f_TCSETV)
        {
            if (t_com09 > D_TCVOLTTHR)
            {
                f_TC = ON;
            }
        }
        // Condition: SET RSOC
        if (f_TCSETRSOC)
        {
            if (t_com0d >= D_TCRSOCTHR)
            {
                f_TC = ON;
            }
        }
        // Condition: SET VCT
        if (f_TCSETVCT)
        {
            if (f_VCT)
            {
                f_TC = ON;
            }
        }
    }

    if (t_com66_FC_cnt >= 120)
    {
        t_com66_FC_cnt = 120;

        f_t_com66_FC = 1;
    }

    if (f_FC)
    {
        // Condition: CLEAR V
        if (f_FCCLV)
        {
            if (t_com09 <= D_FCCLVOLTTHR)
            {
                f_FC = OFF;
                f_t_com66_FC = 0;
            }
        }
        // Condition: CLEAR RSOC
        if (f_FCCLRSOC)
        {
            if (t_com0d <= D_FCCLRSOCTHR)
            {
                f_FC = OFF;
                f_t_com66_FC = 0;
            }
        }
    }
    else
    {
        // Condition: SET V
        if (f_FCSETV)
        {
            if (t_com09 > D_FCVOLTTHR)
            {
                f_FC = ON;
            }
        }
        // Condition: SET RSOC
        if (f_FCSETRSOC)
        {
            if (t_com0d >= D_FCRSOCTHR)
            {
                f_FC = ON;
            }
        }
        // Condition: SET VCT
        if (f_FCSETVCT)
        {
            if (f_VCT)
            {
                f_FC = ON;
            }
        }
    }

    if (f_TD)
    {
        // Condition: CLEAR V
        if (f_TDCLV)
        {
            if (t_com09 >= D_TDCLVOLTTHR)
            {
                f_TD = OFF;
            }
        }
        // Condition: CLEAR RSOC
        if (f_TDCLRSOC)
        {
            if (t_com0d >= D_TDCLRSOCTHR)
            {
                f_TD = OFF;
            }
        }
    }
    else
    {
        // Condition: SET V
        if (f_TDSETV)
        {
            if (t_com09 < D_TDVOLTTHR)
            {
                f_TD = ON;
            }
        }
        // Condition: SET RSOC
        if (f_TDSETRSOC)
        {
            if (t_com0d < D_TDRSOCTHR)
            {
                f_TD = ON;
            }
        }
    }

    if (f_FD)
    {
        // Condition: CLEAR V
        if (f_FDCLV)
        {
            if (t_com09 >= D_FDCLVOLTTHR)
            {
                f_FD = OFF;
            }
        }
        // Condition: CLEAR RSOC
        if (f_FDCLRSOC)
        {
            if (t_com0d >= D_FDCLRSOCTHR)
            {
                f_FD = OFF;
            }
        }
    }
    else
    {
        // Condition: SET V
        if (f_FDSETV)
        {
            if (9 < D_FDVOLTTHR)
            {
                f_FD = ON;
            }
        }
        // Condition: SET RSOC
        if (f_FDSETRSOC)
        {
            if (t_com0d <= D_FDRSOCTHR)
            {
                f_FD = ON;
            }
        }
    }
    // BatteryStatus
    if (f_TC && f_charge)
    {
        f_tca = ON;
    }
    else
    {
        f_tca = OFF;
    }

    if (f_FC)
    {
        f_full = ON;
    }
    else
    {
        f_full = OFF;
        f_VCT = OFF;
        f_fullchg = OFF;
        // f_FC1 = 0;
    }

    if (f_TD && f_dsg)
    {
        f_tda = ON;
    }
    else
    {
        f_tda = OFF;
    }

    if (f_FD)
    {
        f_fd = ON;
    }
    else
    {
        f_fd = OFF;
    }
}

void FlagStatus(void)
{
    // if (IdealRc <= D_SOCFSetThreshold)
    // {
    //     f_SOCF1 = 1;
    // }

    // if (IdealRc >= D_SOCFClearThreshold)
    // {
    //     f_SOCF1 = 0;
    // }

    // if (IdealRc <= D_SOC1SetThreshold)
    // {
    //     f_SOC1 = 1;
    // }

    // if (IdealRc >= D_SOC1ClearThreshold)
    // {
    //     f_SOC1 = 0;
    // }

    // if (f_relax)
    // {
    //     f_OCVTAKEN1 = 1;
    // }
    // else
    // {
    //     f_OCVTAKEN1 = 0;
    // }

    if (ABS(FVoltage - t_com09) < 10)
    {
        f_VOK1 = 1;
    }
    else
    {
        f_VOK1 = 0;
    }
    if (t_com09 < 2900)
    {
        f_t_com66_LOWV = 1;
    }
    else
    {
        f_t_com66_LOWV = 0;
    }
    if (t_com0d < 1)
    {
        f_t_com66_SOC1 = 1;
        f_t_com66_SOCF = 1;
    }
    else
    {
        f_t_com66_SOC1 = 0;
        f_t_com66_SOCF = 0;
    }
    if (t_com0a < -25)
    {
        f_t_com66_DSG = 1;
    }
    else
    {
        f_t_com66_DSG = 0;
    }

    FVoltage = 9;

    if (F_IGENABLE)
    {
        f_QEN1 = 1;

        if (!f_HIB)
        {
            f_DNR1 = 1;
        }
        else
        {
            f_DNR1 = 0;
        }
    }
    else
    {
        f_QEN1 = 0;
    }

    
}

// void FlagStatus1(void)
// {
//     if (f_discharge)
//     {
//         if (t_com0a <= D_ODCDetection)
//         {
//             ODC_Cnt++;
//             if (ODC_Cnt >= D_ODCDelay)
//             {
//                 ODC_Cnt = 0;
//                 f_ODC1 = 1;
//             }
//         }
//         else
//         {
//             ODC_Cnt = 0;
//         }

//         if (t_com0a >= D_ODCRecovery)
//         {
//             ODC_Cnt = 0;
//             f_ODC1 = 0;
//         }

//         if (t_com09 <= D_BATLOWDetection)
//         {
//             BATLOW_Cnt++;
//             if (BATLOW_Cnt >= D_BATLOWDelay)
//             {
//                 BATLOW_Cnt = 0;
//                 f_BATLOW1 = 1;
//             }
//         }
//         else
//         {
//             BATLOW_Cnt = 0;
//         }

//         if (t_com09 >= D_BATLOWRecovery)
//         {
//             BATLOW_Cnt = 0;
//             f_BATLOW1 = 0;
//         }
//     }
//     else
//     {
//         f_BATLOW1 = 0;
//         f_ODC1 = 0;
//     }

//     if (f_charge)
//     {
//         if (t_com0a >= D_OCCDetection)
//         {
//             OCC_Cnt++;
//             if (OCC_Cnt >= D_OCCDelay)
//             {
//                 OCC_Cnt = 0;
//                 f_OCC1 = 1;
//             }
//         }
//         else
//         {
//             OCC_Cnt = 0;
//         }

//         if (t_com0a <= D_OCCRecovery)
//         {
//             OCC_Cnt = 0;
//             f_OCC1 = 0;
//         }

//         if (t_com09 >= D_BATHIDetection)
//         {
//             BATHI_Cnt++;
//             if (BATHI_Cnt >= D_BAITHIDelay)
//             {
//                 BATHI_Cnt = 0;
//                 f_BATHI1 = 1;
//             }
//         }
//         else
//         {
//             BATHI_Cnt = 0;
//         }

//         if (t_com09 <= D_BATHIRecovery)
//         {
//             BATHI_Cnt = 0;
//             f_BATHI1 = 0;
//         }
//     }
//     else
//     {
//         f_OCC1 = 0;
//         f_BATHI1 = 0;
//     }

//     if (t_com0a >= D_ChgCurrent)
//     {
//         if (t_com08 >= (D_OTCDetection + 2731))
//         {
//             OTC_Cnt++;
//             if (OTC_Cnt >= D_OTCDelay)
//             {
//                 OTC_Cnt = 0;
//                 f_OTC1 = 1;
//             }
//         }
//         else
//         {
//             OTC_Cnt = 0;
//         }

//         if (t_com08 <= (D_OTCRecovery + 2731))
//         {
//             OTC_Cnt = 0;
//             f_OTC1 = 0;
//         }
//     }
//     else
//     {
//         f_OTC1 = 0;
//     }

//     if (t_com0a <= D_DsgCurrent)
//     {
//         if (t_com08 >= (D_OTDDetection + 2731))
//         {
//             OTD_Cnt++;
//             if (OTC_Cnt >= D_OTDDelay)
//             {
//                 OTD_Cnt = 0;
//                 f_OTD1 = 1;
//             }
//         }
//         else
//         {
//             OTD_Cnt = 0;
//         }

//         if (t_com08 <= (D_OTDRecovery + 2731))
//         {
//             OTD_Cnt = 0;
//             f_OTD1 = 0;
//         }
//     }
//     else
//     {
//         f_OTD1 = 0;
//     }

//     if (f_TD || f_CHG_INH1 == 0)
//     {
//         f_CHG1 = 1;
//     }

//     if (f_TC && f_CHG_INH1 == 1)
//     {
//         f_CHG1 = 0;
//     }
// }

void Set_CCCV(void)
{
    //*******************************************************************************************
    // Charging Configuration
    // RSVD	    RSVD	TAPER_VOLT	SLEEPCHG	HIBAT_CHG	CHGV_DEGRADE	DEGRADE_CC	COMP_IR
    // 15        14      13          12          11          10              9           8
    // CS_CV	    RSVD	RSVD	    RSVD	    RSVD	    SOC_CHARGE	    RSVD	    CRATE
    // 7         6       5           4           3           2               1           0
    //*******************************************************************************************

    int16_t ChargingVoltage;
    int16_t ChargingCurrent;
    uint16_t dg_cc;
    uint16_t dg_cv;
    // 1.JEITA
    switch (TempRange.data)
    {
    case TR_UT:
    {
        f_SU = ON;
        ChargingCurrent = 0;
        ChargingVoltage = 0;
        break;
    }
    case TR_LT:
    {
        f_SU = OFF;
        if (f_HV)
        {
            ChargingCurrent = LT_CCH;
        }
        else if (f_MV)
        {
            ChargingCurrent = LT_CCM;
        }
        else if (f_LV)
        {
            ChargingCurrent = LT_CCL;
        }
        // else
        // {
        //     ChargingCurrent = PRE_CC;
        // }
        ChargingVoltage = LT_CV;
        break;
    }
    case TR_STL:
    {
        f_SU = OFF;
        if (f_HV)
        {
            ChargingCurrent = STL_CCH;
        }
        else if (f_MV)
        {
            ChargingCurrent = STL_CCM;
        }
        else if (f_LV)
        {
            ChargingCurrent = STL_CCL;
        }
        // else
        // {
        //     ChargingCurrent = PRE_CC;
        // }
        ChargingVoltage = STL_CV;
        break;
    }
    case TR_RT:
    {
        f_SU = OFF;
        if (f_HV)
        {
            ChargingCurrent = RT_CCH;
        }
        else if (f_MV)
        {
            ChargingCurrent = RT_CCM;
        }
        else if (f_LV)
        {
            ChargingCurrent = RT_CCL;
        }
        // else
        // {
        //     ChargingCurrent = PRE_CC;
        // }
        ChargingVoltage = RT_CV;
        break;
    }
    case TR_STH:
    {
        f_SU = OFF;
        if (f_HV)
        {
            ChargingCurrent = STH_CCH;
        }
        else if (f_MV)
        {
            ChargingCurrent = STH_CCM;
        }
        else if (f_LV)
        {
            ChargingCurrent = STH_CCL;
        }
        // else
        // {
        //     ChargingCurrent = PRE_CC;
        // }
        ChargingVoltage = STH_CV;
        break;
    }
    case TR_HT:
    {
        f_SU = OFF;
        if (f_HV)
        {
            ChargingCurrent = HT_CCH;
        }
        else if (f_MV)
        {
            ChargingCurrent = HT_CCM;
        }
        else if (f_LV)
        {
            ChargingCurrent = HT_CCL;
        }
        // else
        // {
        //     ChargingCurrent = PRE_CC;
        // }
        ChargingVoltage = HT_CV;
        break;
    }
    case TR_OT:
    {
        f_SU = ON;
        ChargingCurrent = 0;
        ChargingVoltage = 0;
        break;
    }
    }
    // 2. CRATE
    //***************************************************************************************************
    // The Charging Configuration[CRATE] bit provides an option to adjust the ChargingCurrent based on SOH
    //***************************************************************************************************
    if (D_CRATE)
    {
        ChargingCurrent = (uint32_t)ChargingCurrent * t_com2e / 100;
    }

    // 3. Degradation Modes
    // 4. Cell Swelling Control
    // 5. Charge Inhibit
    /*理解：
    如果先CHG，再HT，没有任何动作
    如果先DSG，再HT，IN = 1
    由于没有MOS控制，IN = 1后可进入CHG，此时IN不变
    退出高温，IN清除
    */
    if (!f_charge && f_HT)
    {
        f_IN = 1;
        ChargingCurrent = 0;
        ChargingVoltage = 0;
    }
    else if (!f_HT)
    {
        f_IN = 0;
    }

    if (D_DEGRADE_En)
    {
        if (t_com17 > D_DGSTARTCYCLECNT)
        {
            if (t_com17 > D_DGCYCLECNT3 || t_com2e < D_DGSOH3 || FwTotalRunTime > D_DGRUNTIME3 )//|| HTV_TIME > D_DGHIGH_TV3)
            {
                dg_cc = D_DG_CC3;
                dg_cv = D_DG_CV3;
                f_CV_DGRD = 0x3;
            }
            else if (t_com17 > D_DGCYCLECNT2 || t_com2e < D_DGSOH2 || FwTotalRunTime > D_DGRUNTIME2 || HTV_TIME > D_DGHIGH_TV2)
            {
                dg_cc = D_DG_CC2;
                dg_cv = D_DG_CV2;
                f_CV_DGRD = 0x2;
            }
            else if (t_com17 > D_DGCYCLECNT1 || t_com2e < D_DGSOH1 || FwTotalRunTime > D_DGRUNTIME1 || HTV_TIME > D_DGHIGH_TV1)
            {
                dg_cc = D_DG_CC1;
                dg_cv = D_DG_CV1;
                f_CV_DGRD = 0x1;
            }
            else
            {
                dg_cc = 0;
                dg_cv = 0;
                f_CV_DGRD = 0x0;
            }

            if (D_DEGRADE_CV)
            {
                ChargingVoltage -= dg_cv;
            }

            if (D_DEGRADE_CC)
            {
                ChargingCurrent = (uint32_t)ChargingCurrent * (100 - dg_cc) / 100;
            }
        }
        else
        {
            f_CV_DGRD = 0x0;
        }
    }
    else
    {
        f_CV_DGRD = 0x0;
    }

    if (D_CS_CV)
    {
        if (ChargingVoltage >= D_CS_MINCV)
        {
            if (t_com08 >= D_CSTEMP_TH && t_com09 >= D_CSVOLT_TH)
            {
                CS_Cnt++;
                if (CS_Cnt >= D_CSTIME_InV)
                {
                    CS_Cnt1++;
                    CS_Cnt = 0;
                }
                ChargingVoltage -= D_CSVOLT_DT * CS_Cnt1;
            }
            else
            {
                CS_Cnt1 = 0;
                CS_Cnt = 0;
            }

            if (ChargingVoltage < D_CS_MINCV)
            {
                ChargingVoltage = D_CS_MINCV;
            }
        }
        else
        {
            CS_Cnt1 = 0;
            CS_Cnt = 0;
        }
    }
    else
    {
        CS_Cnt1 = 0;
        CS_Cnt = 0;
    }

    if (D_COMP_IR && f_charge)
    {
        ChargingVoltage += (uint32_t)tabsc * (D_R_BMU + D_R_SYSTEM) / 1000;
    }

   

    t_com32 = ChargingCurrent;
    g_ChargingVoltage = ChargingVoltage;
}
