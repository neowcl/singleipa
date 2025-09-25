/***************************************************************************//**
 * @file     protocol.c
 * @version  V1.0.0
 * @author   
 * @date     
 * @brief    
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/
 
#include "main.h"
#include "comm_protocol.h"
#include "data_flash.h"
#include "bi2cs_interface.h"
#include <string.h>
#include "standard_data_cmd.h"
#include "bms_register_inc.h"
#include "block_command.h"
#include "standard_data_cmd.h"

extern uint8_t rcv_random ;
extern uint8_t new_random ;
DFUpdate_T DFUpdate;
uint16_t Accaddress;
uint8_t SOCFlagConfig_update_flag = 0;

typedef struct{
    uint8_t tag;
    uint8_t len;
    uint8_t value[10];
}tag_len_v_t;

/**
  * @brief  寄存器写命令，私有协议
  * @param  None
  * @retval None
  */
void register_write_fun(uint8_t *data)
{
    volatile int8_t err_code = 0;
    tag_len_v_t *ptvl;
    volatile uint8_t reg_id;
    comm_tx_packet_t *tx_packet;

    uint8_t *pdata;
    //const reg_item_t *reg_item;
uint8_t buf[4];
    tx_packet =  (comm_tx_packet_t*)data;

    if(tx_packet->len[0] < 5){
        err_code = -1;
    }

    pdata = data + 5;
    ptvl = (tag_len_v_t*)pdata;
/*
    reg_id = get_regid_by_addr(REGTYPE_REGISTER, ptvl->tag );
    if(reg_id == INVALID_REGID){
        err_code = -1;
    }
    reg_item = get_reg_item(REGTYPE_REGISTER, reg_id);

    //len = get_reg_item_bytes(reg_item);

    if(!(reg_item->flags & REG_ACCESS_WRITE)){
        err_code = -1;
    }

    if(err_code >= 0){
        if(ptvl->len >10){
            ptvl->len = 10;
        }
        set_reg_value(REGTYPE_REGISTER, reg_id, 0, ptvl->value, ptvl->len);
    }
*/
    if((ptvl->tag == 0x72)&&(ptvl->len == 4))//  reg SOCFlagConfig 4bytes
    {
        if(get_sys_seal_type() == SYS_FULL_ACCESS)
        {
            std_data.SOCFlagConfig_bit = *(uint32_t*)ptvl->value;
            SOCFlagConfig_update_flag = 1;
            //buf[0] = ptvl->value[0];
            //fmc_write_flash((uint32_t)&BitConfig._SOCFlagConfig_FLASH - FMC_DATA_FLASH_BASE_ADDR, ptvl->value, 4);
        }
    }

    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd = WRITE_REGISTER_CMD + 0x80;
    tx_packet->len[0]  = 4 + 0;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = RET_OK;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;
    pdata = data + 7;
    *pdata = cal_crc8_check(data, tx_packet->len[0]+3);
}



#if 1
/**
  * @brief  寄存器解析
  * @param  寄存器地址，数据(TLV)
  * @retval 拼装data的长度
  */
uint8_t parse_register_val(uint8_t reg_addr, uint8_t *data)
{
    uint8_t *reg_p = (uint8_t *)&std_data.ContrStatus.Byte.LO;
    uint8_t len = 2;
    uint8_t i;
    
     if(reg_addr > sizeof(std_data_cmd_t)){
        return 0;
     }
    len = 2;

     reg_p = (uint8_t *)&std_data.ContrStatus.Byte.LO + reg_addr;
//    reg_data = get_reg_value_ptr(REGTYPE_REGISTER, reg_id, 0);
    *data = reg_addr; data++;//T
    *data = len; data++;     //L
    for(i = 0; i < len; i++){//V
        *data = *reg_p;
        data++;
        reg_p++;
    }
    return len+2;
     
//    regid_t reg_id = 0;
//    uint8_t len = 2;
//    uint8_t i;
//    uint8_t* reg_data;
//    const reg_item_t *reg_item;
//    
//    reg_id = get_regid_by_addr(REGTYPE_REGISTER, reg_addr);
//    if(reg_id == INVALID_REGID){
//        return 0;
//    }
//    reg_item = get_reg_item(REGTYPE_REGISTER, reg_id);
//    len = get_reg_item_bytes(reg_item);

//    reg_data = get_reg_value_ptr(REGTYPE_REGISTER, reg_id, 0);
//    *data = reg_addr; data++;//T
//    *data = len; data++;     //L
//    for(i = 0; i < len; i++){//V
//        *data = *reg_data;
//        data++;
//        reg_data++;
//    }
//    return len+2;
}
#endif
/**
  * @brief  读寄存器
  * @param  接收到的数据，需要解析
  * @retval NONE
  */
void register_read_fun(uint8_t *data)
{
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;
    uint8_t i;
    uint8_t reg_table[41];
    int8_t  err_code = 0;
    
    uint8_t reg_num = 0;
    uint8_t data_len = 0;
    uint8_t tx_data_len  = 0;
    
    pdata =  data+5;      // data
    data_len = *(data+2); // get len
    if(data_len > 2){
        reg_num = data_len -2;
    }
    if(reg_num > 41){  // 35 to  41
        reg_num = 41 ;//limit 35 registers  ligx adjust at 2022.12.16

    }
    /*get reg id*/
    for(i = 0; i < reg_num; i++){
        reg_table[i] = *pdata;
        pdata++;
    }
    /*filled payload data*/
    pdata =  data+7;
    for(i = 0; i < reg_num; i++){
        data_len = parse_register_val(reg_table[i], pdata);
        pdata += data_len;
        tx_data_len += data_len;
    }
    tx_packet =  (comm_tx_packet_t*)data;
    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd = READ_REGISTER_CMD + 0x80;
    tx_packet->len[0]  = 4 + tx_data_len;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = RET_OK;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;

    *pdata = cal_crc8_check(data, tx_packet->len[0]+3);
}

/**
  * @brief  读data memory 的数据
  * @param  接收到的数据，需要解析
  * @retval NONE
  */
void data_memory_read_fun(uint8_t *data)
{
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;
    volatile int8_t  err_code = RET_OK;
    volatile uint16_t memory_addr = 0;
    volatile uint16_t memory_len = 0;

    //uint8_t tx_data_len  = 0;
    if(data[2] != 0x06){
        err_code = RET_FAIL;
    }

    memory_addr = data[6];
    memory_addr = (memory_addr<<8) + data[5];
    memory_len = data[8];
    memory_len = (memory_len<<8) + data[7];
    if(memory_len > 251){
        memory_len = 251;
    }
    pdata = data + 7;


    if((memory_addr < 0xC00)||(memory_addr > 0x2000)){ //限制datamenory区间(0xC00)
        err_code = RET_FAIL;
    }
    
//    if((uint32_t)&SafetyConfig - FMC_DATA_FLASH_BASE_ADDR )
//    {
//    
//    }
    

    if(get_sys_seal_type() == SYS_SEALED){ //未解锁
        err_code = RET_FAIL;
    }

    if((err_code == RET_OK)){
        os_read_flash(memory_addr, pdata, memory_len);
        pdata += memory_len;
    }else{
        memory_len = 0;
    }

    tx_packet = (comm_tx_packet_t*)data;
    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd = READ_DATA_MEMORY_CMD + 0x80;
    tx_packet->len[0]  = 4 + memory_len;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = err_code;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;

    *pdata = cal_crc8_check(data, tx_packet->len[0]+3);
}

/**
  * @brief  写data memory 的数据
  * @param  接收到的数据，需要解析
  * @retval NONE
  */
void data_memory_write_fun(uint8_t *data)
{
    comm_tx_packet_t *tx_packet;
    uint8_t *pdata;
    volatile int8_t  err_code = RET_OK;
    volatile uint16_t memory_addr = 0;
    volatile uint16_t memory_len = 0;

    //uint8_t tx_data_len  = 0;
    if(data[2] < 5){
        err_code = RET_FAIL;
    }

    memory_addr = data[6];
    memory_addr = (memory_addr<<8) + data[5];

    if((memory_addr < 0xC00)||(memory_addr > 0x2000)){ //限制datamenory区间(0xDC00)
        err_code = RET_FAIL;
    }

    memory_len = data[2] - 4;

    if(memory_len > 251){
        memory_len = 251;
    }

    if(get_sys_seal_type() == SYS_SEALED){ //未解锁
        err_code = RET_FAIL;
    }
    pdata = data + 7;
    if(err_code >= 0){
        os_write_flash(memory_addr, pdata, memory_len);
    }

    tx_packet = (comm_tx_packet_t*)data;
    tx_packet->sync = SYNC_CODE;
    tx_packet->cmd = WRITE_DATA_MEMORY_CMD + 0x80;
    tx_packet->len[0]  = 4 + 0;
    tx_packet->len[1]  = 0;
    tx_packet->errcode = err_code;
    tx_packet->random[0] = rcv_random;
    new_random = get_new_random(rcv_random);
    tx_packet->random[1] = new_random;
    pdata = data + 7;
    *pdata = cal_crc8_check(data, tx_packet->len[0]+3);
}


void DFUdata_Chk(void)
{
    uint8_t MfgSCfg;
    uint16_t offset;
    uint16_t advanceLen, remainLen;
    uint16_t Accaddress;
    if (DFUpdate.flag)
    {
        if (DFUpdate.DataFlash)
        {
            DFUpdate.DataFlash = 0;
            Accaddress = g_StdCmdData.Field.nAltManufacturerAccess;
            if (Accaddress >= 0x4000 && Accaddress < 0x4400)
            {
                fmc_write_flash(Accaddress, (uint8_t *)&g_StdCmdData.Field.nMACData[0], g_StdCmdData.Field.nMACDataLen);
            }
        }
        if (DFUpdate.ManuB)
        {
            DFUpdate.ManuB = 0;
            Accaddress =(uint32_t)&D_MF_BLOCKB-FMC_DATA_FLASH_BASE_ADDR;
            
            fmc_write_flash(Accaddress, (uint8_t *)&g_StdCmdData.Field.nMACData[0], 0x11);
           
        }
         if (DFUpdate.FUseTime)
		{
			FirstUseTime = (*pCMDAddress[0x41] << 8) | *pCMDAddress[0x40];
			f_lt_W = ON;
			DFUpdate.FUseTime = 0;
		}



        if (DFUpdate.MFGSC)
        {
            MfgSCfg = (ManufacturingStatus.data & 0x28) | (u_fd_rom.d_MfgStatusinit & 0xFFD7);
            //						MfgSCfg = MfgSCfg | (u_fd_rom.d_MfgStatusinit & 0xFFD7);
            
            fmc_write_flash((uint32_t)&D_MFGSTATUSINIT-FMC_DATA_FLASH_BASE_ADDR, (uint8_t *)&MfgSCfg, 1);
            DFUpdate.MFGSC = 0;
            DFUpdate.DCHECK = ON;
        }
        if (DFUpdate.TPVOLT)
        {
          
            fmc_write_flash((uint32_t)&D_0PVOLT-FMC_DATA_FLASH_BASE_ADDR, &ssmbdata.aadr[0x33], 2);
            DFUpdate.TPVOLT = 0;
            DFUpdate.DCHECK = ON;
        }

        if (DFUpdate.DCAP)
        {
            fmc_write_flash((uint32_t)&D_DCAP-FMC_DATA_FLASH_BASE_ADDR, &ssmbdata.aadr[0x13], 2);
            DFUpdate.DCAP = 0;
            DFUpdate.DCHECK = ON;
        }

        if (DFUpdate.INITHIGHVOLT)
        {
            fmc_write_flash((uint32_t)&D_INITHIGHVOLT-FMC_DATA_FLASH_BASE_ADDR, &ssmbdata.aadr[0x62], 2);
            DFUpdate.INITHIGHVOLT = 0;
            DFUpdate.DCHECK = ON;
        }

        if (DFUpdate.INITHIGHVOLTCL)
        {
            fmc_write_flash((uint32_t)&D_INITHIGHVOLTCL-FMC_DATA_FLASH_BASE_ADDR, &ssmbdata.aadr[0x64], 2);
            DFUpdate.INITHIGHVOLTCL = 0;
            DFUpdate.DCHECK = ON;
        }

        if (DFUpdate.INITLOWVOLT)
        {
           fmc_write_flash((uint32_t)&D_INITLOWVOLT-FMC_DATA_FLASH_BASE_ADDR, &ssmbdata.aadr[0x67], 2);
            DFUpdate.INITLOWVOLT = 0;
            DFUpdate.DCHECK = ON;
        }

        if (DFUpdate.INITLOWVOLTCL)
        {
            fmc_write_flash((uint32_t)&D_INITLOWVOLTCL-FMC_DATA_FLASH_BASE_ADDR, &ssmbdata.aadr[0x68], 2);
            DFUpdate.INITLOWVOLTCL = 0;
            DFUpdate.DCHECK = ON;
        }

        if (DFUpdate.INITTEMPHIGH)
        {
            fmc_write_flash((uint32_t)&D_INITTEMPHIGH-FMC_DATA_FLASH_BASE_ADDR, &ssmbdata.aadr[0x6A], 1);
            DFUpdate.INITTEMPHIGH = 0;
            DFUpdate.DCHECK = ON;
        }

        if (DFUpdate.INITTEMPHIGHCL)
        {
            fmc_write_flash((uint32_t)&D_INITTEMPHIGHCL-FMC_DATA_FLASH_BASE_ADDR, &ssmbdata.aadr[0x6B], 1);
            DFUpdate.INITTEMPHIGHCL = 0;
            DFUpdate.DCHECK = ON;
        }

        if (DFUpdate.INITTEMPLOW)
        {
            fmc_write_flash((uint32_t)&D_INITTEMPLOW-FMC_DATA_FLASH_BASE_ADDR, &ssmbdata.aadr[0x6C], 1);
            DFUpdate.INITTEMPLOW = 0;
            DFUpdate.DCHECK = ON;
        }

        if (DFUpdate.INITTEMPLOWCL)
        {
            fmc_write_flash((uint32_t)&D_INITTEMPLOWCL-FMC_DATA_FLASH_BASE_ADDR, &ssmbdata.aadr[0x6D], 1);
            DFUpdate.INITTEMPLOWCL = 0;
            DFUpdate.DCHECK = ON;
        }

        if (DFUpdate.SOCDELTA)
        {
           fmc_write_flash((uint32_t)&D_SOCDELTA-FMC_DATA_FLASH_BASE_ADDR, &ssmbdata.aadr[0x6F], 1);
            DFUpdate.SOCDELTA = 0;
            DFUpdate.DCHECK = ON;
        }

        if(DFUpdate.Subcmd)
       {
           DFUpdate.Subcmd = 0;
       }
       if(DFUpdate.ManuDate)
       {
           if (g_StdCmdData.Field.nMACDataLen - 4 > sizeof(D_MF_DATA))
           {
               g_StdCmdData.Field.nMACDataLen = sizeof(D_MF_DATA) + 4;
           }
           fmc_write_flash((uint32_t)&D_MF_DATA-FMC_DATA_FLASH_BASE_ADDR, pCMDAddress[0x40], (g_StdCmdData.Field.nMACDataLen - 4));
           DFUpdate.ManuDate = 0;
           DFUpdate.AFICheck = ON;
       }
       if (DFUpdate.SerialNum)
       {
           if (g_StdCmdData.Field.nMACDataLen - 4 > sizeof(D_SERIES))
           {
               g_StdCmdData.Field.nMACDataLen = sizeof(D_SERIES) + 4;
           }
           fmc_write_flash((uint32_t)&D_SERIES-FMC_DATA_FLASH_BASE_ADDR, pCMDAddress[0x40], (g_StdCmdData.Field.nMACDataLen - 4));
           DFUpdate.SerialNum = 0;
           DFUpdate.AFICheck = ON;
       }

       if (DFUpdate.ManuName)
       {
           if (g_StdCmdData.Field.nMACDataLen - 4 > sizeof(D_MF_NAME))
           {
               g_StdCmdData.Field.nMACDataLen = sizeof(D_MF_NAME) + 4;
           }
           fmc_write_flash((uint32_t)D_MF_NAME-FMC_DATA_FLASH_BASE_ADDR, pCMDAddress[0x40], (g_StdCmdData.Field.nMACDataLen - 4));
           DFUpdate.ManuName = 0;
           DFUpdate.AFICheck = ON;
       }

       if (DFUpdate.DeviceName)
       {
           Accaddress = (uint32_t)&D_DEVNAME - DF_FLASH_OFFSET;
           if (g_StdCmdData.Field.nMACDataLen - 4 > sizeof(D_DEVNAME))
           {
               g_StdCmdData.Field.nMACDataLen = sizeof(D_DEVNAME) + 4;
           }
           fmc_write_flash((uint32_t)D_DEVNAME-FMC_DATA_FLASH_BASE_ADDR, pCMDAddress[0x40], (g_StdCmdData.Field.nMACDataLen - 4));
           DFUpdate.DeviceName = 0;
           DFUpdate.AFICheck = ON;
       }

       if (DFUpdate.DeviceChem)
       {
           if (g_StdCmdData.Field.nMACDataLen - 4 > sizeof(D_DEVCHEM))
           {
               g_StdCmdData.Field.nMACDataLen = sizeof(D_DEVCHEM) + 4;
           }
           fmc_write_flash((uint32_t)D_DEVCHEM-FMC_DATA_FLASH_BASE_ADDR, pCMDAddress[0x40], (g_StdCmdData.Field.nMACDataLen - 4));
           DFUpdate.DeviceChem = 0;
           DFUpdate.AFICheck = ON;
       }

       if (DFUpdate.ManuA)
       {
           if (g_StdCmdData.Field.nMACDataLen - 4 > sizeof(D_MF_BLOCKA))
           {
               g_StdCmdData.Field.nMACDataLen = sizeof(D_MF_BLOCKA) + 4;
           }
           fmc_write_flash((uint32_t)D_MF_BLOCKA-FMC_DATA_FLASH_BASE_ADDR, pCMDAddress[0x40], (g_StdCmdData.Field.nMACDataLen - 4));
           DFUpdate.ManuA = 0;
           DFUpdate.AFICheck = ON;
       }

       if (DFUpdate.ManuB)
       {
           if (g_StdCmdData.Field.nMACDataLen - 4 > sizeof(D_MF_BLOCKB))
           {
               g_StdCmdData.Field.nMACDataLen = sizeof(D_MF_BLOCKB) + 4;
           }
           fmc_write_flash((uint32_t)D_MF_BLOCKB-FMC_DATA_FLASH_BASE_ADDR, pCMDAddress[0x40], (g_StdCmdData.Field.nMACDataLen - 4));
           DFUpdate.ManuB = 0;
           DFUpdate.AFICheck = ON;
       }

    //    if (DFUpdate.SecKEY)
    //    {
    //        if (g_StdCmdData.Field.nMACDataLen - 4 > sizeof(US_KEY1_SW) * 8)
    //        {
    //            g_StdCmdData.Field.nMACDataLen = sizeof(US_KEY1_SW) * 8 + 4;
    //        }
    //        __disable_irq();
    //        DFUpdate.SecKEY = 0;
    //        fmc_write_flash((uint32_t)&US_KEY1_SW, pCMDAddress[0x40], (g_StdCmdData.Field.nMACDataLen - 4));
    //        __enable_irq();
    //        DFUpdate.AFICheck = ON;
    //    }

    //    if (DFUpdate.CVOverride)
    //    {
    //        DFUpdate.CVOverride = 0;
    //        __disable_irq();
    //        Flash00B0_Write((uint32_t)&LT_CV, pCMDAddress[0x40], 10);
    //        __enable_irq();
    //        DFUpdate.DCHECK = ON;
    //    }

    //    if (DFUpdate.AFICheck)
    //    {
    //        DFUpdate.AFICheck = OFF;
    //        StaticDFCrc_Chk();
    //    }

    //    if (DFUpdate.DCHECK)
    //    {
    //        DFUpdate.DCHECK = OFF;
        //  DynamicDFCrc_Chk();
    //    }
    }
}
