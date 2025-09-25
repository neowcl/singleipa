/**
  * @brief   api transform to X58X
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */
#ifndef __API_X58X_H__
#define __API_X58X_H__  
#include <stdint.h>




void algorithm_init(void);
void algorithm_run(void);

void set_alg_cell_voltage(uint8_t ch, float vol_val, uint8_t valid);
void set_alg_pack_voltage(float vol_val);
void set_alg_pack_current( float cur_val, uint8_t valid);
void set_alg_pack_temprature( float temp_val, uint8_t valid);
void set_alg_cell_balance_switch(uint8_t ch, uint8_t val);
void set_alg_BMS_state(uint8_t val);
uint8_t get_alg_BMS_state(void);
void set_alg_BMS_balance_switch(uint8_t val);
void set_alg_SOC_window_H(float val);
void set_alg_SOC_window_L(float val);
void set_alg_SOC_run_out_cmd(uint8_t val);
uint16_t get_alg_pack_SOC_value(void);
uint16_t get_alg_cell_SOC_value(uint8_t ch);
void set_alg_pack_SOC_init_val(uint16_t val);
void set_alg_cell_SOC_init_val(uint8_t ch, uint16_t val);
void set_alg_pack_SOH_init_val(uint16_t val);
void set_alg_pack_CntCC_init_val(uint16_t val);
void set_alg_pack_Qchg_init_val(uint16_t val);
void set_alg_pack_QDischg_init_val(uint16_t val);
void set_alg_FlgEEPpack_val(uint16_t val);
void update_soc_val_to_SOH_alg( void );
void set_SOH_algorithm_dtime(float second);

uint8_t get_battery_state(void);

/*SOC unit % */
float get_bat_soc_val(void);

/*cycle count unit 1 */
float get_soh_cycle_count(void);

/*FCC unit  AH*/
float get_full_charge_capacity(void);

/*RC unit  AH*/
float get_remaining_capacity(void);

#endif
