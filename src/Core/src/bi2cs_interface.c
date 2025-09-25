#include "bi2cs_interface.h"
#include "base_types.h"


// #include "LifeTime.h"
nGaugingStatus GaugingStatus;
nChargingStatus ChargingStatus;
nOperationStatusA OperationStatusA;
nOperationStatusB OperationStatusB;
nTempRange TempRange;
uint16_t tabsc; // Current absolute value
int8_t CellTemp;
int8_t CellTemp_use_rsoc;
int8_t IntTemp;
int32_t tcom89_new;
BMS_CMD_DATA_T g_StdCmdData;
// BMS_CMD_DATA_T1 g_StdCmdData1;
nManufacturingStatus ManufacturingStatus;
newChargingStatus newChargingStatu;
ut_com66_f ut_com66;
uint16_t oldNcc;
uint8_t readIphCnt=1;
// uint16_t     t_com17_new;
int32_t t_com09_new;
int32_t t_com0a_new;
int32_t t_com08_new;
uint32_t t_com75_new;
int32_t t_com8c_new;
void t_comA0Change();
void t_comA8Change();

void t_com7dChange();
void ECCVerify();
void t_com8cChange();
void t_com43Change();

void t_comA6Init();
void t_com94Init();
void t_com86Change();
void more_init();
//void iphCheck();
void iphMode();


void bi2cs_dataCmd_init(void)
{
  ////////////////////原来的Flash2Ram
  t_com2f = D_INITHIGHVOLT;   // 0x62
  t_com30 = D_INITHIGHVOLTCL; // 0x64
  t_com67 = D_INITLOWVOLT;    // 0x66
  t_com68 = D_INITLOWVOLTCL;  // 0x68
  t_com6a = D_INITTEMPHIGH;   // 0x6A
  t_com6b = D_INITTEMPHIGHCL; // 0x6B
  t_com6c = D_INITTEMPLOW;    // 0x6C
  t_com6d = D_INITTEMPLOWCL;  // 0x6D
  t_com6f = D_SOCDELTA;       // 0x6F
  t_com66_2=0x0000;
  
  f_t_com66_IMAXOK=1;
  t_comc4=0x0000;
  t_com02 = DF_ATRATE;
  t_com04 = DF_ATRATETIME;
  
  t_com1e = DF_MAXLOADCUR;
  t_com2e = DF_SOH;
  t_com1d = DF_MAXLOADATTE;
  t_com0f = DF_REMCAP;

  if (F_CAPUINT == ON)
  {
    t_com18 = (uint32_t)D_DCAP * D_DVOLT / 10000;
    
  }
  else
  {
    t_com18 = D_DCAP;
    
  }
  ////////////////////////////////////////////////

  t_com1a = 0x0031;
  t_comfa[0]=0x41;
  t_comfa[1]=0x4c;
  t_comfa[2]=0x48;
  t_comfa[3]=0x5f;
  t_comfa[4]=0x56;
  t_comfa[5]=0x31;
  t_comfa[6]=0x2e;
  t_comfa[7]=0x31;
  t_comfa[8]=0x5f;
  t_comfa[9]=0x32;
  t_comfa[10]=0x35;
  t_comfa[11]=0x30;
  t_comfa[12]=0x39;
  t_comfa[13]=0x30;
  t_comfa[14]=0x31;


  t_com16 = 0x0080;
  t_com17 = DF_CYCLECNT;
 

  t_com50=0x0000;
/////

/////////////////////////////////////////////////////////////////////
t_combe[0]=0x60;
t_combe[2]=0x66;


///////////////////////////////////////////////////////////////////////

//readIPAmessage();


 t_com19 = D_DVOLT;

  t_coma5[0] = 0x01;
  t_coma5[1] = 0x00;
  t_coma5[2] = 0x00;
  t_coma5[3] = 0x00;

  t_com03 = 0x6301;

  t1_com3d[0] = 0x20;
  t1_com3d[1] = 0x37;
  t1_com3d[2] = 0x70;
  t1_com3d[3] = 0x00;

  
  t1_com88 = 0x0000;


t_combf=D_IPA_MANUFACTURE_DATE;

t1_com85 = 0x9842;

t1_com7a =D_INITVOLTAGEINIT;
t_com4d[0] = 0x00;
t_com4d[1] = 0x00;
t_com4d[2] = 0x00;
t_com4d[3] = 0x00;
t_com19 = D_DVOLT;
g_ChargingVoltage = DF_CV;
t_com84 = DF_QMAX;

t_com79 = 0x0012;

t_com70 = 0x01;
t_com45 = 0x00;
t_com8d = 0x000c;

t_com40 = 0x0190;
//////////////
t_comA6Init();
t_com94Init();
more_init();
iphMode();
t_com1b = 0x04d2; // 待定
///////
t_com60 = 0xbbee;



t_comc3[0]=0x03;
t_comc3[1]=0x01;
t_comc3[2]=0x00;
t_comc3[3]=0x00;
//////////////////////////////////////////////
t_com33 = D_0PVOLT;
t_com3a = LastQMaxUpdataValue;

t_com32 = DF_CC;
f_GAUGE_EN = f_GAUGE;
f_LF_EN = f_LF; // kpfa1
TimesTamp = DF_RUNTIME;
f_FAS = 0;
f_SS = 0;
f_SEC0 = 1;
f_SEC1 = 0;
f_FAS1 = 0;
f_SS1 = 0;


}

void bi2cs_dataCmd_Save(void)
{
  static uint32_t delaycnt = 0;
  // DF_CTRLSTATUS = t_com00;
  DF_ATRATE = t_com02;
  DF_ATRATETIME = t_com04;
  DF_MAXLOADCUR = t_com1e;
  DF_MAXLOADATTE = t_com1d;
  DF_RSOC = t_com0d;
  DF_SOH = t_com2e;
  DF_REMCAP = t_com0f;
  DF_FCC = t_com10;
  DF_CYCLECNT = t_com17;
  DF_QMAX = t_com84;

  DF_CC = t_com32;
  
  f_LDMD1 = OFF;
  f_FULLSLEEP1 = f_DP_SLP;
  f_HIBERNATE1 = f_HIB;
  f_SHUTDOWN1 = OFF;
  f_QMAXUPDATE1 = OFF;
  f_CALMODE1 = f_CAL_EN;
  f_FAS1 = f_FAS;
  f_SS1 = f_SS;


  f_SLEEP1 = f_SLEEP;
  /////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////

  for (int i = 0; i < 21; i++)
  {
    t_com20[i] = D_MF_NAME[i + 1];
  }
  ///////////////////////////////////////
  for (int i = 0; i < 4; i++)
  {
    t_com22[i] = D_DEVCHEM[i + 1];
  }
  for (int i = 0; i < 21; i++)
  {
    t_com21[i] = D_DEVNAME[i + 1];
  }
  DF_CV = g_ChargingVoltage;

  t_coma3 = LastQMaxUpdataCycle;


  t_comA0Change();
  t_comA8Change();

  t_com7dChange();
  t_com8cChange();
  t_com43Change();
t_com86Change();
  t1_com88 = 0x0000;
  t_com0b = t_com89;

  t_com47[0] = 0x61;
  t_com47[1] = 0xa6;
  t_com47[2] = 0x4b;
  t_com47[3] = 0x00;

  t_coma2 = 0x0ba8;
  t_com87 = t_com0a;

  f_CFET = ON;
  f_DFET = ON;
  f_SETC = f_charge;
  f_SOKC = f_charge;
  ECCVerify();




  // for (int i = 0; i < 17; i++)
  // {
  //   t_com90[i] = D_MF_BLOCKA[i];
  // }
  // for (int i = 0; i < 17; i++)
  // {
  //   t_com91[i] = D_MF_BLOCKB[i];
  // }


  

}
void t_comA8Change()
{
  t_com09_new = (t_com09 * 131072) / 1000;
  t_com0a_new = (t_com0a * 131072) / 1000;
  t_com08_new = (t_com08 * 131072) / 10;
  t_com75_new = (t_com75 * 131072) / 10;

  // t_coma8[0]=0x18;
  t_coma8[0] = (uint8_t)t_com09_new;
  t_coma8[1] = (uint8_t)(t_com09_new >> 8);
  t_coma8[2] = (uint8_t)(t_com09_new >> 16);
  t_coma8[3] = (uint8_t)(t_com09_new >> 24);
  t_coma8[4] = (uint8_t)t_com0a_new;
  t_coma8[5] = (uint8_t)(t_com0a_new >> 8);
  t_coma8[6] = (uint8_t)(t_com0a_new >> 16);
  t_coma8[7] = (uint8_t)(t_com0a_new >> 24);
  t_coma8[8] = (uint8_t)t_com0a_new;
  t_coma8[9] = (uint8_t)(t_com0a_new >> 8);
  t_coma8[10] = (uint8_t)(t_com0a_new >> 16);
  t_coma8[11] = (uint8_t)(t_com0a_new >> 24);
  t_coma8[12] = (uint8_t)t_com08_new;
  t_coma8[13] = (uint8_t)(t_com08_new >> 8);
  t_coma8[14] = (uint8_t)(t_com08_new >> 16);
  t_coma8[15] = (uint8_t)(t_com08_new >> 24);
  t_coma8[16] = (uint8_t)t_com75_new;
  t_coma8[17] = (uint8_t)(t_com75_new >> 8);
  t_coma8[18] = (uint8_t)(t_com75_new >> 16);
  t_coma8[19] = (uint8_t)(t_com75_new >> 24);
  t_coma8[20] = (uint8_t)t_com09_new;
  t_coma8[21] = (uint8_t)(t_com09_new >> 8);
  t_coma8[22] = (uint8_t)(t_com09_new >> 16);
  t_coma8[23] = (uint8_t)(t_com09_new >> 24);
}

void t_comA0Change()
{
  t_coma0 = IdealFcc;
  
  if (IdealFcc >= 1.02*D_DCAP)
  {
    t_coma0 =1.02*D_DCAP;
  }
  else if (t_com17 <= 200)
  {
    if (IdealFcc < D_DCAP)
    {
      t_coma0 = D_DCAP;
    }
  }
  else if (t_com17 <= 300)
  {
    if (IdealFcc <0.97*D_DCAP)
    {
      t_coma0 = 0.97*D_DCAP;
    }
  }
  else if (t_com17 <= 500)
  {
    if (IdealFcc < 0.92*D_DCAP)
    {
      t_coma0 = 0.92*D_DCAP;
    }
  }
  else if (t_com17 <= 700)
  {
    if (IdealFcc < 0.86*D_DCAP)
    {
      t_coma0 = 0.86*D_DCAP;
    }
   
  }
  else if (t_com17 <= 900)
  {
    if (IdealFcc <0.8*D_DCAP)
    {
      t_coma0 = 0.8*D_DCAP;
    }
    
  }
  else
  {
    if (IdealFcc <0.79*D_DCAP)
    {
      t_coma0 = 0.79*D_DCAP;
    }
  }
}

void t_com7dChange()
{
  uint32_t t_com7d_new = t_com09*131072*2+200;
  t_com7d[0]= (uint8_t)t_com7d_new;
  t_com7d[1]= (uint8_t)(t_com7d_new >> 8);
  t_com7d[2]= (uint8_t)(t_com7d_new >> 16);
  t_com7d[3]= (uint8_t)(t_com7d_new >> 24);
}
void ECCVerify()
{
  if (t_com62Flg)
  {
    if (t_com62cnt > 2)
    {
      if(!ECCComm(&t_com60,t_com62,t_com63,t_com64))
      {
        t_com62cnt = 0;
        t_com62Flg = 0;
        
      }
    }
  }
}
void t_com8cChange()
{
  t_com8c_new = (t_com09 * 131072) * 2.048;
  t_com8c[0] = (uint8_t)t_com8c_new;
  t_com8c[1] = (uint8_t)(t_com8c_new >> 8);
  t_com8c[2] = (uint8_t)(t_com8c_new >> 16);
  t_com8c[3] = (uint8_t)(t_com8c_new >> 24);
}

void t_com43Change()
{
  if (t_com0a > 10)
  {
    t_com43[0]=f_fullchg ? 0xc9:0x79;
    t_com43[1] = 0x01;
    t_com43[2] = 0x00;
    t_com43[3] = 0x00;
  }
  else
  {
    t_com43[0]=f_fullchg ? 0xc9:0x29;
    t_com43[1] = 0x00;
    t_com43[2] = 0x00;
    t_com43[3] = 0x00;
  }
}

void t_comA6Init()
{
  t_coma6[0] = 0x00;
  t_coma6[1] = 0x00;
  t_coma6[2] = 0x00;
  t_coma6[3] = 0x00;
  t_coma6[4] = 0x55;
  t_coma6[5] = 0xCE;
  t_coma6[6] = 0xAC;
  t_coma6[7] = 0xE0;
  t_coma6[8] = 0xA3;
  t_coma6[9] = 0xEE;
  t_coma6[10] = 0x5C;
  t_coma6[11] = 0x7F;
  t_coma6[12] = 0xFF;
  t_coma6[13] = 0x20;
  t_coma6[14] = 0x45;
  t_coma6[15] = 0x6E;
  t_coma6[16] = 0x90;
  t_coma6[17] = 0x84;
  t_coma6[18] = 0x6C;
  t_coma6[19] = 0x4A;
  t_coma6[20] = 0x37;
  t_coma6[21] = 0xE2;
  t_coma6[22] = 0x23;
  t_coma6[23] = 0xC0;
  t_coma6[24] = 0xA4;
  t_coma6[25] = 0xF4;
  t_coma6[26] = 0xA4;
  t_coma6[27] = 0x93;
  t_coma6[28] = 0x55;
  t_coma6[29] = 0x55;
  t_coma6[30] = 0x55;
  t_coma6[31] = 0x55;
}

void t_com94Init()
{
  t1_com94[0] = 0x42;
  t1_com94[1] = 0x30;
  t1_com94[2] = 0x34;
  t1_com94[3] = 0x37;
  t1_com94[4] = 0x30;
  t1_com94[5] = 0x45;
  t1_com94[6] = 0x32;
  t1_com94[7] = 0x30;
  t1_com94[8] = 0x33;
  t1_com94[9] = 0x30;
  t1_com94[10] = 0x32;
  t1_com94[11] = 0x30;
  t1_com94[12] = 0x30;
  t1_com94[13] = 0x30;
  t1_com94[14] = 0x32;
  t1_com94[15] = 0x38;
  t1_com94[16] = 0x30;
  t1_com94[17] = 0x31;
  t1_com94[18] = 0x31;
  t1_com94[19] = 0x31;
}


void barcode_Init(void)
{
  memcpy(t_com90, D_MF_BLOCKA, 17);
  memcpy(t_com91, D_MF_BLOCKB, 17);

}

void more_init()
{
  t_com9e[0] = 0x0a;
  t_com9e[1] = 0x00;
  t_com9e[2] = 0x00;
  t_com9e[3] = 0x00;
  t_com9e[4] = 0x00;
  t_com9e[5] = 0x00;
  t_com9e[6] = 0x00;
  t_com9e[7] = 0x00;
  t_com9e[8] = 0x00;
  t_com9e[9] = 0x00;
  t_com9e[10] = 0x00;
  ///////////////
  t_com44[0] = 0x00;
  t_com44[1] = 0x00;
  t_com44[2] = 0x00;
  t_com44[3] = 0x00;
  ////////////////////
  t_com4e[0] = 0x00;
  t_com4e[1] = 0x00;
  t_com4e[2] = 0x00;
  t_com4e[3] = 0x00;


  t_com03 = 0x6301;

  

 
  //////////////
  t_com92[0] = 0x39;
  t_com92[1] = 0x31;
  t_com92[2] = 0x36;
  t_com92[3] = 0x43;
  t_com92[4] = 0x30;
  t_com92[5] = 0x39;
  t_com92[6] = 0x33;
  //////////////
  t_com93[0] = 0x55;
  t_com93[1] = 0x41;
  t_com93[2] = 0x4d;
  t_com93[3] = 0x4d;
  t_com93[4] = 0x43;
  t_com93[5] = 0x54;
  t_com93[6] = 0x4d;
  t_com93[7] = 0x41;

  t_com41[0]=0xcf;
  t_com41[1]=0xa3;
  t_com41[2]=0x83;
  t_com41[3]=0x06;
  t_com41[4]=0x06;
  t_com41[5]=0xb9;
  t_com41[6]=0x80;
  t_com41[7]=0x00;
  t_com41[8]=0xa7;
  t_com41[9]=0x0e;
  t_com41[10]=0x08;
  t_com41[11]=0x00;
  t_com41[12]=0xa8;
  t_com41[13]=0x0b;
  t_com41[14]=0xc2;
  t_com41[15]=0x0c;
  t_com41[16]=0x7c;
  t_com41[17]=0x02;
  t_com41[18]=0x13;
  t_com41[19]=0x00;
  t_com41[20]=0xad;
  t_com41[21]=0x0c;
  t_com41[22]=0x35;
  t_com41[23]=0x00;



t_coma4[0] = 0x0b;
t_coma4[1] = 0x00;
t_coma4[2] = 0x00;
t_coma4[3] = 0x00;
t_coma4[4] = 0x00;
t_coma4[5] = 0x00;
t_coma4[6] = 0x00;
t_coma4[7] = 0x00;
t_coma4[8] = 0x00;
t_coma4[9] = 0x00;
t_coma4[10] = 0x00;
t_coma4[11] = 0x00;
t_coma4[12] = 0x00;
t_coma4[13] = 0x00;
t_coma4[14] = 0x00;
t_coma4[15] = 0x00;
t_coma4[16] = 0x00;
t_coma4[17] = 0x00;
t_coma4[18] = 0x00;
t_coma4[19] = 0x00;
t_coma4[20] = 0x00;
t_coma4[21] = 0x00;
t_coma4[22] = 0x00;
t_coma4[23] = 0x00;
t_coma4[24] = 0x00;
t_coma4[25] = 0x00;
t_coma4[26] = 0x00;
t_coma4[27] = 0x00;
t_coma4[28] = 0x00;
t_coma4[29] = 0x00;
t_coma4[30] = 0x00;
t_coma4[31] = 0x00;





  









  


  t_coma1[0]=0xb9;
  t_coma1[1]=0x82;
  t_coma1[2]=0x01;
  t_coma1[3]=0x00;
  t_coma1[4]=0x23;
  t_coma1[5]=0x00;
  t_coma1[6]=0x00;
  t_coma1[7]=0x20;
  t_coma1[8]=0x47;
  t_coma1[9]=0xcc;
  t_coma1[10]=0xdf;
  t_coma1[11]=0xc5;
  t_coma1[12]=0xba;
  t_coma1[13]=0xcb;
  t_coma1[14]=0x0b;
  t_coma1[15]=0x00;
  t_coma1[16]=0xee;
  t_coma1[17]=0x7d;
  t_coma1[18]=0x44;
  t_coma1[19]=0xb0;
  t_coma1[20]=0xa9;
  t_coma1[21]=0xe9;
  t_coma1[22]=0x5d;
  t_coma1[23]=0x00;
  t_coma1[24]=0x00;
  t_coma1[25]=0x00;
  t_coma1[26]=0x00;
  t_coma1[27]=0x00;
  t_coma1[28]=0xb5;
  t_coma1[29]=0xff;
  t_coma1[30]=0xff;
  t_coma1[31]=0xff;

  ////////////////////////////
  t1_com96[0] = 0x54;
  t1_com96[1] = 0x42;
  t1_com96[2] = 0x44;

  t1_com97[0] = 0x54;
  t1_com97[1] = 0x42;
  t1_com97[2] = 0x44;
  t1_com98[0] = 0x54;
  t1_com98[1] = 0x42;
  t1_com98[2] = 0x44;
  t1_com99[0] = 0x54;
  t1_com99[1] = 0x42;
  t1_com99[2] = 0x44;

  /////////
  t_coma7[0] = 0xa2;
  t_coma7[1] = 0x16;
  t_coma7[2] = 0x43;
  t_coma7[3] = 0x06;

  ///////////////

  //////////////
  t_coma5[0] = 0x01;
  t_coma5[1] = 0x00;
  t_coma5[2] = 0x00;
  t_coma5[3] = 0x00;

  
  t1_com3d[0] = 0x20;
  t1_com3d[1] = 0x37;
  t1_com3d[2] = 0x70;
  t1_com3d[3] = 0x00;
}




void t_com86Change()
{
    if (t_com0d < 5)
  {
    t_com86cnt = 5;
  }
  
  if (t_com86cnt > 4)
  {
    t_com86cnt = 0;

    if (t_com0a > D_DEADBAND)
    {
      t_com86[0] = (uint8_t)t_com09;
      t_com86[1] = (uint8_t)(t_com09 >> 8);
      t_com86[2] = (uint8_t)(t_com0a);
      t_com86[3] = (uint8_t)((t_com0a) >> 8);
    }
    else
    {
      t_com86[0] = 0x00;
      t_com86[1] = 0x00;
      t_com86[2] = 0x00;
      t_com86[3] = 0x00;
    }
  }
}
void iphMode()
{
  int i;
  for(i=0;i<0x20;i++)
  {
    t_com53[i]=D_IPA_COM53[i];
  }
  
  for(i=0;i<0x09;i++)
  {
     t1_com76[i]=D_IPA_COM76[i];
  }
  
  for(i=0;i<0x04;i++)
  {
    t_com77[i]=D_IPA_COM77[i];
  }
  
  for(i=0;i<0x04;i++)
  {
     t_comaa[i]=D_IPA_COMAA[i];
  }
  for(i=0;i<0x04;i++)
  {
    t_comab[i]=D_IPA_COMAB[i];
  }
  for(i=0;i<0x04;i++)
  {
     t_comac[i]=D_IPA_COMAC[i];
  }

  for(i=0;i<0x10;i++)
  {
    t_comba[i]=D_IPA_COMBA[i];
  }
  for (i = 0; i < 0x09; i++)
  {
    t1_com76[i] = D_IPA_COM76[i];
  }

  for (i = 0; i < 0x04; i++)
  {
    t1_comad[i] = D_IPA_COMAD[i];
  }

  for (i = 0; i < 0x04; i++)
  {
    t1_comaf[i] = D_IPA_COMAF[i];
  }

}

static inline uint8_t check_array(const uint8_t *arr, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    if (arr[i] != 0x00 && arr[i] != 0xff)
    {
      return 1;
    }
  }
  return 0;
}

void readIPAmessage(void)
{
  int i = 0;
  uint8_t flags[5] = {1, 1, 1, 1, 1};
  uint8_t all_flags_set = 1;
  IPhVerify(t_com91, t_com90, t1_com95, t_com7e, t_comf6);
  IPHSeril(&t_com4c);
  flags[0] = check_array(t_com91, sizeof(t_com91));
  flags[1] = check_array(t_com90, sizeof(t_com90));
  flags[2] = check_array(t1_com95, sizeof(t1_com95));
  flags[3] = check_array(t_com7e, sizeof(t_com7e));
  flags[4] = check_array(t_com4c, 4);

  for (i = 0; i < 5; i++)
  {
    if (!flags[i])
    {
      all_flags_set = 0;
      break;
    }
  }

  if (all_flags_set) 
  {
    readIPAmesCnt=18;
    ts_W_L();
    readIPAmes_flag = 0;
  }
  else
  {
    barcode_Init();    //条码初始化
  }

  memcpy(t1_com52, t_com4c, 4);
  bi2cs_dataCmd_init();
}

