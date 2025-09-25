#ifndef __DATA_FLASH_H__
#define __DATA_FLASH_H__

#include "main.h"

//typedef uint8_t (*fun)(uint8_t *);

#define READ_ONLY  0x01
#define WRITE_ONLY 0x02
#define READ_WRITE 0x03

typedef struct {
    uint16_t id;
    uint8_t id_access;
    uint8_t (*command_fun)(uint8_t *);
} command_id_t;

typedef struct
{
    uint32_t flag				 : 1;          // 1
    uint32_t DataFlash			 : 1;      // 2
    uint32_t Subcmd	  	 		 : 1;      // 3
    uint32_t Lifetime	    	 : 1;      // 4
    uint32_t ManuDate     	     : 1;  //5
    uint32_t SerialNum   	     : 1;    //6
    uint32_t ManuName    		 : 1;      //7
    uint32_t DeviceName          : 1;  //8
    uint32_t DeviceChem          : 1;  //9
    uint32_t ManuA    			 : 1;      //10
    uint32_t ManuB    			 : 1;      //11
    uint32_t ManuC    		 	 : 1;      //12
    uint32_t SealFlag			 : 1;        //13
    uint32_t SecKEY				 : 1;        //14
    uint32_t AFICheck			 : 1;        //15
    uint32_t AFIUPDATE			 : 1;      //16
	  uint32_t MFGSC			 : 1;          //17
	  uint32_t INITHIGHVOLT			 : 1;    //18
	  uint32_t INITHIGHVOLTCL			 : 1;  //19
	  uint32_t INITLOWVOLT			 : 1;    //20
	  uint32_t INITLOWVOLTCL			 : 1;  //21
		uint32_t INITTEMPHIGH			 : 1;    //22
		uint32_t INITTEMPHIGHCL			 : 1;  //23
	  uint32_t INITTEMPLOW			 : 1;    //24
	  uint32_t INITTEMPLOWCL			 : 1;  //25
	  uint32_t SOCDELTA			 : 1;        //26
	  uint32_t DCHECK			 : 1;          //27
		uint32_t TPVOLT       : 1;         //28
		uint32_t DCAP         : 1;         //29
		uint32_t CVOverride    :1;         //30
		uint32_t FUseTime      :1;         //31
	  uint32_t RSVD         : 1;         //32
}DFUpdate_T;
extern DFUpdate_T DFUpdate;

//typedef struct {
//    uint16_t id;
//    uint8_t id_access;
//} command_id_t;
void data_memory_read_fun(uint8_t *data);
void data_memory_write_fun(uint8_t *data);
void DFUdata_Chk(void);
void register_read_fun(uint8_t *data);
void register_write_fun(uint8_t *data);

void test_write(uint8_t reg_addr, uint8_t val);

           extern uint8_t SOCFlagConfig_update_flag ;

#endif
