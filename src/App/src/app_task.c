/***************************************************************************/ /**
                                                                               * @file     app_task.c
                                                                               * @version  V1.0.0
                                                                               * @author   sz414
                                                                               * @date     2022-06-06 PM
                                                                               * @brief    该文件实现APP层需要导出的API和通用帮助函数。
                                                                               *
                                                                               * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
                                                                               *****************************************************************************/

#include "app_inc.h"
#include "bi2cs_interface.h"
#include "datcalc_spl.h"
#include "task.h"
#include "modules_pmu.h"

/**
 * @brief
 * @param  None
 * @retval None
 */
void app_init(void)
{
  // update_soc_input_param;//初始化采样一次
  // fmc_calibration_data_init();     //校准参数初始化
  // bms_algorithm_initialize();      //算法参数初始化
  // init_EEP_data();                 //读取flash里面的参数，作为算法的输入
  tccup = (uint16_t)((long)D_DCAP * ABS(D_CCCPER) / 100);
  if (F_USEDFDAT == ON) // Initialize with Flexible data?
  {
    DF_Read(); // Read DataFlash data
    Reset_cnt++;
  }
  LifeTime_Read();
 // block_delay_ms(4000);
  while (1)
  {
    if (fristsample() == 0)
    {
      break;
    }
  }

  init_soc_input_state(); // SOC输入状态初始化
  get_chip_uid();         // 获取芯片ID
  
  //readIPAmessage();

  bi2cs_dataCmd_init(); // 寄存器初始化 // 读版本信息
  
  Make_RC(); // rc 、fcc 算法  采集
  Make_iRC();
  toldrc = t_com0f;
  t_coma0 = IdealFcc;
  //oldNcc=IdealFcc;
  f_relax = ON;
  //ResetIPA_flag=1;
}

/**
 * @brief  命令处理函数
 * @param  None
 * @retval None
 */
void app_handle_task(void)
{
  // 定时扫描并处理寄存器命令.
  timer_reg_command();
}
