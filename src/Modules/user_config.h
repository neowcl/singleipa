/***************************************************************************//**
 * @file     .h
 * @version  
 * @author   
 * @date    
 * @brief    
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/


#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

// Include external header file.
#include "cbmx56x_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UPDATE_FLAG_ENABLE         0x01 //1 jlink

#define SEAL_ENABLE                0x00
#define SLEEP_ENABLE               0x01

#define FW_VERSION                 0x020204

#define FW_SUB_VERSION             0x0501
#define HW_VERSION                 0x333150

#define NTC_TEMPERATURE_REDUCE     0x00


//#define FLASH_AUTH_KEY_ADDRESS 

//#define  HMAC_SHA256_KEY_BUF {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,\
//                              0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10}

//#define UNSEAL_PASSWORD      {0x12,0x34,0x56,0x78}
//#define FULL_UNSEAL_PASSWORD {0x12,0x34,0x56,0x78}

//#define UNSEAL_PASSWORD      {0x01,0x02,0x03,0x04}
//#define FULL_UNSEAL_PASSWORD {0x05,0x06,0x07,0x08}
    
 /****************************
 V1.1.5

0x00010103
 lib -- SHA256
******************************/
#ifdef __cplusplus
}
#endif

#endif  //__MODULES_TEMP_H__

/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
