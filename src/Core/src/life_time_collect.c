/**************************************************************************//**
 * @file     main.c
 * @version  V0.2.0
 * @author   
 * @date     2022-07-29 AM
 * @brief
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/

#include "main.h"
#include "modules_pmu.h"
#include "bms_register_inc.h"

uint16_t life_period_run_time = 0;

/**
  * @brief  power up init 
  * @param  None
  * @retval None
  */
void life_time_init(void)
{
    //life_period_run_time = LifeTime._worktime;
}


/**
  * @brief  unit day 
  * @param  None
  * @retval None
  */
void life_time_work_time_collect(void)
{
    static uint32_t sys_run_sec = 0;
    uint16_t sys_run_day;
    sys_run_sec += get_pmu_period_time();
    if(sys_run_sec > (24*60*60UL)){
        sys_run_sec = 0;
        //sys_run_day = LifeTime._worktime + 1;
        //set_reg_value_u16(REGTYPE_MEMORY, regworktime, 0, sys_run_day);
        /*need stop condition*/
        //sys_run_day = LifeTime._spantime + 1;
        //set_reg_value_u16(REGTYPE_MEMORY, regspantime, 0, sys_run_day);
    }
}

/**
  * @brief  record min max voltage
  * @param  None
  * @retval None
  */
void life_time_max_min_voltage_collect(uint16_t bat_vol)
{
    static uint8_t cnt = 0;
    // if(bat_vol > LifeTime._max_voltage){
    //     cnt++;
    //     if(cnt > 2){
    //         cnt = 0;
    //         //set_reg_value_u16(REGTYPE_MEMORY, regmax_voltage, 0, bat_vol);
    //     }
    // }else if(bat_vol < LifeTime._min_voltage){
    //     cnt++;
    //     if(cnt > 2){
    //         cnt = 0;
    //         //set_reg_value_u16(REGTYPE_MEMORY, regmin_voltage, 0, bat_vol);
    //     }
    // }else{
    //     cnt = 0;
    // }
}

/**
  * @brief  record min max current
  * @param  None
  * @retval None
  */
void life_time_max_min_current_collect(int16_t current)
{
    static uint8_t cnt = 0;
    // if(current > LifeTime._max_charge_current){
    //     cnt++;
    //     if(cnt > 2){
    //         cnt = 0;
    //         //set_reg_value_i16(REGTYPE_MEMORY, regmax_charge_current, 0, current);
    //     }
    // }else if(current < LifeTime._max_discharge_current){
    //     cnt++;
    //     if(cnt > 2){
    //         cnt = 0;
    //         //set_reg_value_i16(REGTYPE_MEMORY, regmax_discharge_current, 0, current);
    //     }
    // }else{
    //     cnt = 0;
    // }
}


/**
  * @brief  record min max average current
  * @param  None
  * @retval None
  */
void life_time_max_min_average_current_collect(int16_t current)
{
    static uint8_t cnt = 0;
    // if(current > LifeTime._max_ave_charge_current){
    //     cnt++;
    //     if(cnt > 2){
    //         cnt = 0;
    //         //set_reg_value_u16(REGTYPE_MEMORY, regmax_ave_charge_current, 0, current);
    //     }
    // }else if(current < LifeTime._max_ave_discharge_current){
    //     cnt++;
    //     if(cnt > 2){
    //         cnt = 0;
    //         //set_reg_value_u16(REGTYPE_MEMORY, regmax_ave_discharge_current, 0, current);
    //     }
    // }else{
    //     cnt = 0;
    // }
}


/**
  * @brief  record min max temprature  0.degc
  * @param  None
  * @retval None
  */
void life_time_max_min_temprature_collect(int16_t temprature)
{
    static uint8_t cnt = 0;
    // if(temprature > LifeTime._max_T){
    //     cnt++;
    //     if(cnt > 2){
    //         cnt = 0;
    //         //set_reg_value_u16(REGTYPE_MEMORY, regmax_T, 0, temprature);
    //     }
    // }else if(temprature < LifeTime._min_T){
    //     cnt++;
    //     if(cnt > 2){
    //         cnt = 0;
    //         //set_reg_value_u16(REGTYPE_MEMORY, regmin_T, 0, temprature);
    //     }
    // }else{
    //     cnt = 0;
    // }
}

LifeTime_t life_time_data;

#define CNT_MAX    2

void life_time_collection(uint16_t voltage, int16_t current, int16_t avg_current, int16_t temp_ex)
{
    static uint8_t max_voltage_cnt = 0;
    static uint8_t min_voltage_cnt = 0;

    static uint8_t max_charge_current_cnt = 0;
    static uint8_t max_discharge_current_cnt = 0;

    static uint8_t max_ave_charge_current_cnt = 0;
    static uint8_t max_ave_discharge_current_cnt = 0;
    static uint32_t sys_run_sec = 0;

    static uint8_t temp_ex_cnt = 0;

    if(voltage > life_time_data._max_voltage)
    {
        max_voltage_cnt++;
        min_voltage_cnt = 0;
        if(max_voltage_cnt > CNT_MAX)
        {
            life_time_data._max_voltage = voltage;
            max_voltage_cnt = 0;
        }

    }else if(voltage < life_time_data._min_voltage){
        max_voltage_cnt = 0;
        min_voltage_cnt++;
        if(min_voltage_cnt > CNT_MAX)
        {
            life_time_data._min_voltage = voltage;
            min_voltage_cnt = 0;
        }

    }else{
        max_voltage_cnt = 0;
        min_voltage_cnt = 0;
    }

    if(current > life_time_data._max_charge_current)
    {
        max_charge_current_cnt++;
        max_discharge_current_cnt = 0;
        if(max_charge_current_cnt > CNT_MAX)
        {
            life_time_data._max_charge_current = current;
            max_charge_current_cnt = 0;
        }
    }else if(current < life_time_data._max_discharge_current){
        max_charge_current_cnt = 0;
        max_discharge_current_cnt++;
        if(max_discharge_current_cnt > CNT_MAX)
        {
            life_time_data._max_discharge_current = current;
            max_discharge_current_cnt = 0;
        }

    }else{
        max_charge_current_cnt = 0;
        max_discharge_current_cnt = 0;
    }

    if(avg_current > life_time_data._max_ave_charge_current)
    {
        max_ave_charge_current_cnt++;
        max_ave_discharge_current_cnt = 0;
        if(max_ave_charge_current_cnt > CNT_MAX)
        {
            life_time_data._max_ave_charge_current = avg_current;
            max_ave_charge_current_cnt = 0;
        }
    }else if(avg_current < life_time_data._max_ave_discharge_current){
        max_ave_charge_current_cnt = 0;
        max_ave_discharge_current_cnt++;
        if(max_ave_discharge_current_cnt > CNT_MAX)
        {
            life_time_data._max_ave_discharge_current = avg_current;
            max_ave_discharge_current_cnt = 0;
        }
    }else{
        max_ave_charge_current_cnt = 0;
        max_ave_discharge_current_cnt = 0;
    }

    sys_run_sec += get_pmu_period_time();
    if(sys_run_sec > (24*60*60UL)){
        sys_run_sec = 0;
        life_time_data._worktime += 1;
        life_time_data._spantime += 1;
    }

    if((temp_ex < 1200)&&(temp_ex > -50))
    {
        if(temp_ex > life_time_data._max_T)
        {
            temp_ex_cnt++;
            if(temp_ex_cnt > CNT_MAX)
            {
                life_time_data._max_T = temp_ex;
                temp_ex_cnt = 0;
            }
        }else if(temp_ex < life_time_data._min_T){
            temp_ex_cnt++;
            if(temp_ex_cnt > CNT_MAX)
            {
                life_time_data._min_T = temp_ex;
                temp_ex_cnt = 0;
            }
        } else{
            temp_ex_cnt = 0;
        }
    }
}
