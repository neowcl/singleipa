/**************************************************************************//**
 * @file     
 * @version  V0.2.0
 * @author   
 * @date     2022-07-29 AM
 * @brief
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

#include "main.h"
#include "bms_register_config.h"
#include "modules_pmu.h"
#include "bms_register_inc.h"
#include "bit_register.h"
#include "block_command.h"
#include "standard_data_cmd.h"

/**
  * @brief  参数初始化
  * @param  None
  * @retval None
  */
void interrupt_status_init(void)
{
    BatteryStatus = 0;  //0x0A/0x0B
    InterruptStatus = 0; //active

    OperationStatus = 0;
    ManufacturingStatus = 0;

    std_bit_register.ControlStatus.Byte = 0;
    std_bit_register.BatteryStatus.Byte = 0;
    std_bit_register.OperationStatus.Byte = 0;
    std_bit_register.ChargingStatus.Byte = 0;
    std_bit_register.GaugingStatus.Byte = 0;
    std_bit_register.ManufacturingStatus.Byte = 0;
    //std_data.BatteryStatus
    //std_data.InterruptStatus
}

/**
  * @brief  电压中断状态判断
  * @param  None
  * @retval None
  */
void interrupt_status_of_vol(uint16_t bat_vol)
{
    if(bat_vol > InitVoltageHighSet){
        //InterruptStatus |= bitInterruptStatus_VOLT_HI;
        std_data.InterruptStatus |= bitInterruptStatus_VOLT_HI;
    }else if(bat_vol < InitVoltageHighClear){
        std_data.InterruptStatus &= ~bitInterruptStatus_VOLT_HI;
    }

    if(bat_vol < InitVoltageLowSet){
        std_data.InterruptStatus |= bitInterruptStatus_VOLT_LO;
    }else if(bat_vol > InitVoltageLowClear){
        std_data.InterruptStatus &= ~bitInterruptStatus_VOLT_LO;
    }
}

/**
  * @brief  温度中断状态判断
  * @param  None
  * @retval None
  */
void interrupt_status_of_temperature(int16_t temperature)
{
    /*temprature*/
    temperature = temperature/10;
    if(temperature > InitTemperatureHighSet){
        std_data.InterruptStatus |= bitInterruptStatus_TEMP_HI;
    }else if(temperature < InitTemperatureHighClear){
        std_data.InterruptStatus &= ~bitInterruptStatus_TEMP_HI;
    }
    
    if(temperature < InitTemperatureLowSet){ //
        std_data.InterruptStatus |= bitInterruptStatus_TEMP_LO;
    }else if(temperature > InitTemperatureLowClear){
        std_data.InterruptStatus &= ~bitInterruptStatus_TEMP_LO;
    }
}

/**
  * @brief  电池状态位寄存器
  * @param  None
  * @retval None
  */
void battery_status_of_FC_FD(uint16_t soc_val )
{
    if(soc_val > 9900){
        //BatteryStatus |= bitBatteryStatus_FC;  //充满
        std_bit_register.BatteryStatus.Bit.FC = 1;
    }else{
        //BatteryStatus &= (~bitBatteryStatus_FC);
        std_bit_register.BatteryStatus.Bit.FC = 0;
    }

    if(soc_val < 100){
        //BatteryStatus |= bitBatteryStatus_FD;  //放干
        std_bit_register.BatteryStatus.Bit.FD = 1;
    }else{
        //BatteryStatus &= (~bitBatteryStatus_FD);
        std_bit_register.BatteryStatus.Bit.FD = 0;
    }
}

void battery_status_of_DSG_BIT(uint8_t DSG_bit)
{
    if(DSG_bit){
        BatteryStatus |= bitBatteryStatus_DSG;
        //std_bit_register.BatteryStatus.Bit.DSG = 1;
    }else{
        BatteryStatus &= (~bitBatteryStatus_DSG);
        //std_bit_register.BatteryStatus.Bit.DSG = 0;
    }
}

/**
  * @brief  工作模式位寄存器
  * @param  None
  * @retval None
  */
void operation_status_sleep_bit_reg(uint8_t sleep_mode)
{
    switch(sleep_mode)
    {
        case PMU_ACTIVE_MODE:
//            OperationStatus &= (~bitOperationStatus_DP_SLP);
//            OperationStatus &= (~bitOperationStatus_SLEEP);
            f_SLEEP = OFF;
            break;
        case PMU_SLEEP_MODE:
            f_SLEEP = ON;
            f_DP_SLP=OFF;
            break;
        case PMU_DEEP_SLEEP_MODE:
            f_DP_SLP=NO;
            break;
    }
}

/*************

FAS  SS
SEC1 SEC0
 0,   0 = Reserved
 0,   1 = Full Access
 1,   0 = Unsealed
 1,   1 = Sealed

FAS  SS
 0,   0 = Full Access
 0,   1 = Reserved
 1,   0 = Unsealed
 1,   1 = Sealed

************************/
/**
  * @brief  安全位寄存器
  * @param  None
  * @retval None
  */
void operation_status_SEC_bit_reg(uint8_t seal_type)
{
    switch(seal_type)
    {
        case SYS_SEALED:
//            OperationStatus |= bitOperationStatus_SEC1;
//            OperationStatus |= bitOperationStatus_SEC0 ;
            std_bit_register.OperationStatus.Bit.SEC0 = 1;
            std_bit_register.OperationStatus.Bit.SEC1 = 1;
        
            std_bit_register.ControlStatus.Bit.SS = 1;
            std_bit_register.ControlStatus.Bit.FAS = 1;
        
            break;
        case SYS_UNSEALED:
//            OperationStatus |= bitOperationStatus_SEC1;
//            OperationStatus &= (~bitOperationStatus_SEC0);
            std_bit_register.OperationStatus.Bit.SEC0 = 0;
            std_bit_register.OperationStatus.Bit.SEC1 = 1;
        
            std_bit_register.ControlStatus.Bit.SS = 0;
            std_bit_register.ControlStatus.Bit.FAS = 1;
        
            break;
        case SYS_FULL_ACCESS:
//            OperationStatus &= (~bitOperationStatus_SEC1);
//            OperationStatus |= bitOperationStatus_SEC0;
            std_bit_register.OperationStatus.Bit.SEC0 = 1;
            std_bit_register.OperationStatus.Bit.SEC1 = 0;
        
            std_bit_register.ControlStatus.Bit.SS = 0;
            std_bit_register.ControlStatus.Bit.FAS = 0;
            break;
        default:
            //sys_seal_type = SYS_SEALED;
            break;
    }
}

/**
  * @brief  校准使用
  * @param  None
  * @retval None
  */
void ManufacturingStatus_CAL_EN_bit_reg(uint8_t val)
{
    if(val){
        ManufacturingStatus |= bitManufacturingStatus_CAL_EN;
    }else{
        ManufacturingStatus &= (~bitManufacturingStatus_CAL_EN);
    }
}

uint8_t read_ManufacturingStatus_CAL_EN_bit_reg(void)
{
    if(ManufacturingStatus &bitManufacturingStatus_CAL_EN){
        return 1;
    }else{
        return 0;
    }
}


/**
  * @brief  life time enable disable
  * @param  None
  * @retval None
  */
void ManufacturingStatus_LF_EN_bit_reg(uint8_t val)
{
    if(val){
        ManufacturingStatus |= bitManufacturingStatus_LF_EN;
    }else{
        ManufacturingStatus &= (~bitManufacturingStatus_LF_EN);
    }
}

uint8_t read_ManufacturingStatus_LF_EN_bit_reg(void )
{
    if(ManufacturingStatus & bitManufacturingStatus_LF_EN){
        return 1;
    }else{
        return 0;
    }
}
