/**************************************************************************//**
 * @file     
 * @version  V0.1.0
 * @author   
 * @date     2022-07-29 AM
 * @brief
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

#include "main.h"

#include "modules_pmu.h"
#include "bms_register_inc.h"
#include "calibration_handle.h"
#include "bit_register.h"

/**
  * @brief  power up init 
  * @param  None
  * @retval None
  */

//cal_data_t cal_data;


uint8_t get_calibration_enable_flag(void)
{
    return cal_data._CalEn;
}

void write_calibration_enable_flag(uint8_t flag)
{
   // ManufacturingStatus_CAL_EN_bit_reg(flag);
    cal_data._CalEn = flag;
    clear_cali_timeout_cnt();
}
/**
* @fn void fmc_calibration_data_init(void)
* @brief 校准参数上电初始化                                
* @param None
* @return None
*/
void fmc_calibration_data_init(void)
{
    //fmc_read_flash(FMC_CALIBRATION_DATA - FMC_DATA_FLASH_BASE_ADDR, (uint8_t *)&cal_data, sizeof(Calibdata_t));
    cal_data._CalEn = 0;
    if(cal_data._CalMagicNumber != 0xAA55)                       //magic不为0xAA55说明没有校准数据
    {
        cal_data._CellGain = CELL_GAIN_DEFAULT;
        cal_data._BoardOffset = 0;
        cal_data._CChighGain = CC_GAIN_DEFAULT;
        cal_data._CCLowGain = CC_GAIN_DEFAULT;
        cal_data._CCOffset = CC_OFFSET_DEFAULT;
        cal_data._HP_CCOffset = 0;
        cal_data._Deadband = DEADBAND_DEFAULT;
        cal_data._CCDeadband = CC_DEADBAND_DEFAULT;
        cal_data._InterTempOffset = 0;
        cal_data._ExterTempOffset = 0;
        cal_data._VolCaliInterTemp = 250;
        cal_data._Reference_value_Voltage = 3800;
        cal_data._Reference_value_DsgHighCurrent = -1000;
        cal_data._Reference_value_DsgLowCurrent = -100;
        cal_data._Reference_value_resistence = 1000;
        cal_data._CalMagicNumber = 0xAA55;
        //fmc_write_flash(FMC_CALIBRATION_DATA - FMC_DATA_FLASH_BASE_ADDR, (uint8_t *)&cal_data, sizeof(Calibdata_t));
        cal_data._CalMagicNumber = 0;
    }
    cal_data._CalMagicNumber = 0;
}

/**
* @fn fmc_calibration_data_write
* @brief 校准参数写进flash
* @param None
* @return None
*/
void fmc_calibration_data_write(CALI_TYPE_t cali_type, int16_t val)
{
    if(!cal_data._CalEn){ //不在校准状态不可写入参数
        return ;
    }
    switch(cali_type)
    {
    case CAL_CELL_GAIN://1
        cal_data._CellGain = val;
        cal_data._VolCaliInterTemp = get_temperatureIn();
        //set_reg_value_i16(REGTYPE_MEMORY, regCellGain, 0, val);
        break;
    case CAL_CELL_REF: //2
        cal_data._Reference_value_Voltage = val;
        break;
    case CAL_CC_OFFSET: //3
        cal_data._CCOffset = val;
        //set_reg_value_i16(REGTYPE_MEMORY, regCCOffset, 0, val);
        break;
    case CAL_CC_HPOFFSET://4
        cal_data._HP_CCOffset = val;
        //set_reg_value_i16(REGTYPE_MEMORY, regHP_CCOffset, 0, val);
        break;
    case CAL_CELL_TS: //5
        //cal_data._VolCaliInterTemp = val;
        //set_reg_value_i16(REGTYPE_MEMORY, regVolCaliInterTemp, 0, val);
        break;
    case CAL_CC_HIGH_GAIN://7
        cal_data._CChighGain = val;
        //set_reg_value_i16(REGTYPE_MEMORY, regCChighGain, 0, val);
        break;
    case CAL_CC_HIGH_REF: //6
        cal_data._Reference_value_DsgHighCurrent = val;
        break;
    case CAL_CC_LOW_GAIN://9
        cal_data._CCLowGain = val;
        //set_reg_value_i16(REGTYPE_MEMORY, regCCLowGain, 0, val);
        break;
    case CAL_CC_LOW_REF: //8
        cal_data._Reference_value_DsgLowCurrent = val;
        break;
    case CAL_CC_WRITE_EN: //A
        cal_data._CalMagicNumber = 0xAA55;
        break;
    default:
        return;
        //break;
    }
    if(cal_data._CalMagicNumber == 0xAA55)
    {
        cal_data._CalEn = 0;
        //fmc_write_flash(FMC_CALIBRATION_DATA - FMC_DATA_FLASH_BASE_ADDR, (uint8_t *)&cal_data, sizeof(Calibdata_t));
        //fmc_write_flash((uint32_t)&Calibdata - FMC_DATA_FLASH_BASE_ADDR, (uint8_t *)&cal_data, sizeof(calibdata_para_t)); //待起用
        cal_data._CalMagicNumber = 0;
    }
}
