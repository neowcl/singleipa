/***************************************************************************//**
 * @file     app_crc.c
 * @version  V1.0.0
 * @author   sz414
 * @date     2022-06-06 PM
 * @brief    该文件实现了芯海通用的CRC算法。
 *           This cs_crc32 function comes from BMS TOOL code. 
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/
 
#include "app_inc.h"

#define POLYNOMIAL_32 0xEDB88320

uint32_t cs_crc32(const uint8_t* pData, int nLen)
{
    uint32_t table[256];
    int i, j;
    uint32_t crc = 0;

    for (i = 0; i < 256; i++)
    {
        for (j = 0, table[i] = i; j < 8; j++)
        {
            table[i] = (table[i] >> 1) ^ ((table[i] & 1) ? POLYNOMIAL_32 : 0);
        }
    }

    crc = ~crc;
    for (i = 0; i < nLen; i++)
    {
        crc = (crc >> 8) ^ table[(crc ^ pData[i]) & 0xff];
    }
    return ~crc;
}


uint16_t cs_crc16(const uint8_t* pData, uint16_t nLen)
{
    // Not implemented
    return 0;
}

