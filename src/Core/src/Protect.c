#include <stdio.h>
#include <string.h>
#include "Protect.h"
#include "Cell.h"
#include "bi2cs_interface.h"
#include "datcalc_spl.h"
// 保护相关的参数

// 保护标志
boolean_t bORSOC;
boolean_t bURSOC;
boolean_t bSDSOC;
boolean_t bSOC;
boolean_t bIO_Alarm;
// IOConfig
// 7							6					5					4				3				2				1				0
// GPIO_LEVEL_EN	GPIO_POL	INT_TYPE	INT_PUP	INT_POL	INT_EN	BTP_SRC	BTP_EN

/*************************************************************************************************
 * 函数名: VoltHiSetThreshold   VoltHiClearThreshold
 * 参  数: 无
 * 返回值: 无
 * 描  述: 电池过压保护检测，过压后置位g_StdCmdData.nInterruptStatus.nInterruptStatus_f.VOLT_HI为1
 *************************************************************************************************/
void VoltHiSetThreshold(void)
{
    if (!f_VOLT_HI)
    {
        if (t_com09 > t_com2f)
        {
            f_VOLT_HI = ON;
        }
    }
}

void VoltHiClearThreshold(void)
{
    if (f_VOLT_HI)
    {
        if (t_com09 < t_com30)
        {
            f_VOLT_HI = OFF;
        }
    }
}

/*************************************************************************************************
 * 函数名: VoltLoSetThreshold   VoltLoClearThreshold
 * 参  数: 无
 * 返回值: 无
 * 描  述: 电芯欠压保护检测，保护后置位g_StdCmdData.nInterruptStatus.nInterruptStatus_f.VOLT_LO为1
 *************************************************************************************************/
void VoltLoSetThreshold(void)
{
    if (!f_VOLT_LO)
    {
        if (t_com09 < t_com67)
        {
            f_VOLT_LO = ON;
        }
    }
}

void VoltLoClearThreshold(void)
{
    if (f_VOLT_LO)
    {
        if (t_com09 > t_com68)
        {
            f_VOLT_LO = OFF;
        }
    }
}

/*************************************************************************************************
 * 函数名: TempHiSetThreshold
 * 参  数: 无
 * 返回值: 无
 * 描  述: 高温保护检测，保护后置位g_StdCmdData.nInterruptStatus.nInterruptStatus_f.TEMP_HI为1
 *************************************************************************************************/
void TempHiSetThreshold(void)
{
    if (!f_TEMP_HI)
    {
        if (t_com08 > (t_com6a * 10 + 2731))
        {
            f_TEMP_HI = ON;
        }
    }
}

void TempHiClearThreshold()
{
    if (f_TEMP_HI)
    {
        if (t_com08 < (t_com6b * 10 + 2731))
        {
            f_TEMP_HI = OFF;
        }
    }
}

/*************************************************************************************************
 * 函数名: ProtectUT
 * 参  数: 无
 * 返回值: 无
 * 描  述: 低温保护检测，保护后置位g_StdCmdData.nInterruptStatus.nInterruptStatus_f.TEMP_LO为1
 *************************************************************************************************/
void TempLoSetThreshold(void)
{
    if (!f_TEMP_LO)
    {
        if (t_com08 < (t_com6c * 10 + 2731))
        {
            f_TEMP_LO = ON;
        }
    }
}
void TempLoClearThreshold(void)
{
    if (f_TEMP_LO)
    {
        if (t_com08 > (t_com6d * 10 + 2731))
        {
            f_TEMP_LO = OFF;
        }
    }
}

/*************************************************************************************************
 * 函数名: ProtectOV
 * 参  数: 无
 * 返回值: 无
 * 描  述: RSOC 100%保护检测，过压后置位bORSOC为1
 *************************************************************************************************/
void ProtectORSOC(void)
{
    if (bORSOC && f_SOC_DELTA)
    {
        bSOC = 0;
        if (t_com0d < 100)
        {
            bORSOC = 0;
            f_SOC_DELTA = OFF;
        }
    }
    else if (!bORSOC)
    {
        if (t_com0d >= 100)
        {
            bSOC = 1;
            bORSOC = 1;
            f_SOC_DELTA = ON;
        }
    }
}

/*************************************************************************************************
 * 函数名: ProtectOV
 * 参  数: 无
 * 返回值: 无
 * 描  述: 配置的RSOC间隔在INT引脚上生成中断的保护检测，过压后置位bSDSOC为1
 *************************************************************************************************/
void ProtectSOCSetDelta(void)
{
    if (bSDSOC && f_SOC_DELTA)
    {
        bSOC = 0;
        if (t_com0d != (100 - 1 * t_com6f))
        {
            bSDSOC = 0;
            f_SOC_DELTA = OFF;
        }
    }
    else if (!bSDSOC)
    {
        if (t_com0d == (100 - 1 * t_com6f))
        {
            bSOC = 1;
            bSDSOC = 1;
            f_SOC_DELTA = ON;
        }
    }
}

/*************************************************************************************************
 * 函数名: ProtectOV
 * 参  数: 无
 * 返回值: 无
 * 描  述: RSOC 0%保护检测，过压后置位bURSOC为1
 *************************************************************************************************/
void ProtectURSOC(void)
{
    if (bURSOC && f_SOC_DELTA)
    {
        bSOC = 0;
        if (t_com0d > 0)
        {
            bURSOC = 0;
            f_SOC_DELTA = OFF;
        }
    }
    else if (!bURSOC)
    {
        if (t_com0d <= 0)
        {
            bSOC = 1;
            bURSOC = 1;
            f_SOC_DELTA = ON;
        }
    }
}

void ProtectIO_Alarm(void)
{
    if (f_VOLT_HI || f_VOLT_LO || f_TEMP_HI || f_TEMP_LO || bSOC)
    {
        bIO_Alarm = 1;
    }
    else
    {
        bIO_Alarm = 0;
    }
}
/*************************************************************************************************
 * 函数名: ProtectProcess
 * 参  数: 无
 * 返回值: 无
 * 描  述: 各种保护检测
 *************************************************************************************************/
void ProtectProcess(void)
{
    VoltHiSetThreshold();   // 检测过压保护
    VoltHiClearThreshold(); // 检测过压保护释放

    VoltLoSetThreshold();   // 检测欠压保护
    VoltLoClearThreshold(); // 检测欠压保护释放
    TempHiSetThreshold();   // 检测高温保护
    TempHiClearThreshold(); // 检测高温保护释放

    TempLoSetThreshold();   // 检测欠温保护
    TempLoClearThreshold(); // 检测低温保护释放

    if (t_com6f)
    {
        ProtectORSOC();       // RSOC 100%保护检测
        ProtectSOCSetDelta(); // 配置的RSOC间隔在INT引脚上生成中断的保护检测
        ProtectURSOC();       // RSOC 0%保护检测
    }
    else
    {
        bSOC = 0;
        f_SOC_DELTA = 0;
        bORSOC = 0;
        bURSOC = 0;
        bSDSOC = 0;
    }

    ProtectIO_Alarm(); // 触发保护后主机中断标志置一
}

void BatteryTripPoint(void)
{
    if (f_BTP_En)
    {
        if (f_BTP_SRC)
        {
            if (t_com0a <= 0)
            {
                if (t_com0d < D_INITDSGRSOC)
                {
                    if (f_BTP_POL)
                    {
                        f_BTP_INT = ON;
                        f_rca = ON;
                        // IOCTRL->INT_CFG_F.INT_POL=1;   //1为高电平（High）
                    }
                }
            }
            else
            {
                if (t_com0d > D_INITCHGRSOC)
                {
                    if (f_BTP_POL)
                    {
                        f_BTP_INT = OFF;
                        f_rca = OFF;
                        // IOCTRL->INT_CFG_F.INT_POL=0;   //0为低电平（High）
                    }
                }
            }
        }
        else
        {
            if (t_com0a <= 0)
            {
                if (t_com0f < D_INITDSGRC)
                {
                    if (f_BTP_POL)
                    {
                        f_BTP_INT = ON;
                        f_rca = ON;
                        // IOCTRL->INT_CFG_F.INT_POL=1;   //1为高电平（High）
                    }
                }
            }
            else
            {
                if (t_com0f > D_INITCHGRC)
                {
                    if (f_BTP_POL)
                    {
                        f_BTP_INT = OFF;
                        f_rca = OFF;
                        // IOCTRL->INT_CFG_F.INT_POL=0;   //0为低电平（High）
                    }
                }
            }
        }
    }
}

// void Calc_Dischargefactor(void)
// {
//     uint8_t aidx;
//     uint16_t twork1;
//     uint16_t Dischargefactor1;
//     uint16_t 	IdealFcc1;

//     twork1 = (uint16_t)((long)tabsc * 100 / D_DCAP); // eg :   3600 mAh  = 3600mA * 1h

//     if (twork1 <= ((D_CRATE_TBL[1] - D_CRATE_TBL[0]) / 2))
//     {
//         aidx = 0;
//     }
//     else if (twork1 <= ((D_CRATE_TBL[2] - D_CRATE_TBL[1]) / 2))
//     {
//         aidx = 5;
//     }
//     else if (twork1 <= ((D_CRATE_TBL[3] - D_CRATE_TBL[2]) / 2))
//     {
//         aidx = 10;
//     }
//     else
//     {
//         aidx = 15;
//     }

//     if (CellTemp < D_TRATE_TBL[0])
//     {
//         Dischargefactor1 = QCAP_TBL[aidx];
//     }
//     else if (CellTemp < D_TRATE_TBL[3])
//     {
//         for (int i = 0; i < 3; i++)
//         {
//             if (CellTemp < D_TRATE_TBL[i + 1])
//             {
//                 Dischargefactor1 = QCAP_TBL[aidx] +
//                                    ((CellTemp - D_TRATE_TBL[i]) * (QCAP_TBL[aidx + 1] - QCAP_TBL[aidx])) /
//                                        (D_TRATE_TBL[i + 1] - D_TRATE_TBL[i]);
//                 break;
//             }
//         }
//     }
//     else
//     {
//         Dischargefactor1 = QCAP_TBL[aidx + 4];
//     }

//     if(Dischargefactor1>1011|| Dischargefactor1<497)
//     {
//         Dischargefactor1=1000;
//     }
//     IdealFcc1 = (uint32_t)tcom10c_w * 1000 / Dischargefactor1;

//     if ((IdealFcc1- 256) > IdealFcc || IdealFcc > (IdealFcc1 + 256))
//     {
//         IIC_ReadReg(0x72, &t_com06);
//         if (t_com06 != 0)
//         {
//             IdealFcc = t_com06;
//         }
//     }

// }

