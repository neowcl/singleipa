/***************************************************************************//**
 * @file     
 * @version  V1.0.0
 * @author   
 * @date     
 * @brief    
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 *****************************************************************************/


#ifndef __BIT_REGISTER_H__
#define __BIT_REGISTER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void interrupt_status_init(void);

void interrupt_status_of_vol(uint16_t bat_vol);
void interrupt_status_of_temperature(int16_t temperature);
void battery_status_of_FC_FD(uint16_t soc_val);
void battery_status_of_DSG_BIT(uint8_t DSG_bit);

void operation_status_sleep_bit_reg(uint8_t sleep_mode);

void ManufacturingStatus_CAL_EN_bit_reg(uint8_t val);
uint8_t read_ManufacturingStatus_CAL_EN_bit_reg(void);

void ManufacturingStatus_LF_EN_bit_reg(uint8_t val);
uint8_t read_ManufacturingStatus_LF_EN_bit_reg(void );

void operation_status_SEC_bit_reg(uint8_t seal_type);

typedef struct _Gauge_Group
{
    union{
        struct{
            uint8_t VOLT_HI    :1;
            uint8_t VOLT_LO    :1;
            uint8_t TEMP_HI    :1;
            uint8_t TEMP_LO    :1;
            uint8_t SOC_DELTA  :1;
            uint8_t RSV0       :3;
        }Bit;
        uint8_t Byte;
    } interrupt_status;

    union{
        struct{
            uint16_t CC_EN  :1;  //������ʹ��
            uint16_t PB     :1;  //���ص��
            uint16_t RSV0   :3;  
            uint16_t AM     :1;
            uint16_t ChgM   :1;//�㲥����ѹ����ʹ��
            uint16_t CapM   :1;//�������ʼ���ѡ��
            uint16_t ICC    :1;//֧�ֳ�����
            uint16_t PBS    :1;//֧�����ӿ���ģʽ
            uint16_t RSV1   :5;
            uint16_t CF     :1;
        }Bit;
        uint16_t Byte;
    }BatteryMode;

    union
    {
        struct
        {
            uint16_t RSV0   :4;
            uint16_t F_D     :1;  //�ѷŸ�
            uint16_t F_C     :1;  //�ѳ���
            uint16_t DSING    :1; //���ڷŵ�
            uint16_t INITI    :1; //��ʼ��
            uint16_t RTALARM    :1;//ʣ��ʱ�䱨��
            uint16_t RCALARM    :1;//ʣ����������
            uint16_t RSVD   :1;
            uint16_t TDALARM    :1; //��ֹ�ŵ籨��
            uint16_t OTALARM    :1; //���±���
            uint16_t RSV1   :1;
            uint16_t TCALARM    :1;//��ֹ��籨��
            uint16_t OCA    :1;
        }Bit;
        uint16_t Byte;
    }BatteryStatus;

    union
    {
        struct
        {
            uint16_t RSV0       :6;
            uint16_t DP_SLP     :1;
            uint16_t RSV1       :1;
            uint16_t SEC1       :1;  //SECURITY Mode��ȫģʽ
            uint16_t SEC0       :1;  //SECURITY Mode��ȫģʽ
            uint16_t RSV5       :5;
            uint16_t SLEEP      :1;
        }Bit;
        uint16_t Byte;
    }OperationStatus;

    union
    {
        struct
        {
            uint8_t UT          :1;  //T<T1(0��)
            uint8_t UL          :1;  //T1+1<T<T2(10��)
            uint8_t STL         :1;  //T2+1<T<T5(20��)
            uint8_t RT          :1;  //T5+1<T<T6(25��)
            uint8_t STH         :1;  //T6<T<T3(45��)
            uint8_t HT          :1;  //T3<T<T4(55��)
            uint8_t OT          :1;  //T4<T
            uint8_t RSV         :1;  
        }Bit;
        uint8_t Byte;
    }TempRange;

    union
    {
        struct
        {
            uint16_t PV         :1;  //Precharge voltage ����
            uint16_t LV         :1;  //Low voltage ����
            uint16_t MV         :1;  //Mid voltage ����
            uint16_t HV         :1;  //High voltage ����
            uint16_t RSV0       :9;  
            uint16_t FST_CHG    :1;  
            uint16_t RSV1       :2;  
        }Bit;
        uint16_t Byte;
    }ChargingStatus;

    union
    {
        struct
        {
            uint8_t F_D          :1;  //Fully discharged
            uint8_t F_C          :1;  //Fully chargedͬ���״̬
            uint8_t TER_D        :1;  //Terminate discharge
            uint8_t TER_C        :1;  //Terminate charge
            uint8_t RSV0         :1;
            uint8_t ED_VOL       :1;  //End-of-discharge termination voltage
            uint8_t DSG1         :1;  //Discharge/relax 0:charging
            uint8_t RSV1         :1;
        }Bit;
        uint8_t Byte;
    }GaugingStatus;

    union
    {
        struct
        {
            uint16_t REST       :1;  //��RELAXģʽ��ʹ����OCV
            uint16_t RSV0       :1;  
            uint16_t RDIS       :1;  //Ra update is disabled
            uint16_t VOK        :1;  //Voltage OK for QMax update
            uint16_t QEN        :1;  //Impedance Track gauging (Ra and QMax updates are enabled.)
            uint16_t QmaxUpdate :1;  
            uint16_t Rx         :1;  
            uint16_t RSV1       :5;
            uint16_t OCVFR      :1;
            uint16_t RSV2       :3;
        }Bit;
        uint16_t Byte;
    }ITStatus; 

    union
    {
        struct
        {
            uint16_t RSV0       :3;
            uint16_t GAUGE_EN   :1;  //Gauging�������迹���ٲ������Ƿ�ʹ��
            uint16_t RSV1       :1;
            uint16_t LF_EN      :1;  //Lifetime data�ռ�ʹ��
            uint16_t RSV2       :9;
            uint16_t CAL_EN     :1;  //CALIBRATION mode�Ƿ�ʹ��
        }Bit;
        uint16_t Byte;
    }ManufacturingStatus; 

}Gauge_Reg_t;


#ifdef __cplusplus
}
#endif

#endif


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
