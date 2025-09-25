/**
 *****************************************************************************
 * @brief   Base data types defination.
 *
 * @file   base_types.h
 * @author
 * @date   28/JUN/2020
 *****************************************************************************
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <b>&copy; Copyright (c) 2020 Tinychip Microelectronics Co.,Ltd.</b>
 *
 *****************************************************************************
 */

#ifndef __BASE_TYPES_H__
#define __BASE_TYPES_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

/*****************************************************************************/    

#define         W_OK		0xA0						// Write OK
#define         W_NG		0x07						// Write NG
#define         AREA_NG		0x08						// 

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
#ifndef TRUE
  /** Value is true (boolean_t type) */
  #define TRUE        ((boolean_t) 1u)
#endif

#ifndef FALSE
  /** Value is false (boolean_t type) */
  #define FALSE       ((boolean_t) 0u)
#endif  


#ifndef ON
  /** Value is true (boolean_t type) */
  #define ON        ((boolean_t) 1u)
#endif

#ifndef OFF
  /** Value is false (boolean_t type) */
  #define OFF       ((boolean_t) 0u)
#endif 


/** Returns the minimum value out of two values */
#define min( X, Y )  ((X) < (Y) ? (X) : (Y))

/** Returns the maximum value out of two values */
#define max( X, Y )  ((X) > (Y) ? (X) : (Y))

/** Returns the dimension of an array */
#define ARRAY_SZ( X )  (sizeof(X) / sizeof((X)[0]))


/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/** logical datatype (only values are TRUE and FALSE) */
typedef uint8_t      boolean_t;
  
/** single precision floating point number (4 byte) */
typedef float        float32_t;

/** double precision floating point number (8 byte) */
typedef double       float64_t;

/** ASCCI character for string generation (8 bit) */
typedef char         char_t;

/** function pointer type to void/void function */
typedef void         (*func_ptr_t)(void);

/** function pointer type to void/uint8_t function */
typedef void         (*func_ptr_arg1_t)(uint8_t u8Param);




typedef struct
{
	unsigned char bit0			:1;	
	unsigned char bit1			:1;
	unsigned char bit2			:1;
	unsigned char bit3			:1;
	unsigned char bit4			:1;
	unsigned char bit5			:1;
	unsigned char bit6			:1;
	unsigned char bit7			:1;
  unsigned char bit8			:1;
  unsigned char bit9			:1;
  unsigned char bitA			:1;
  unsigned char bitB			:1;
  unsigned char bitC			:1;
  unsigned char bitD			:1;
  unsigned char bitE			:1;
  unsigned char bitF			:1;

}_STC_BIT;

#define DEF_BITF(pdata)	((volatile _STC_BIT*)(pdata))->bitF
#define DEF_BITE(pdata)	((volatile _STC_BIT*)(pdata))->bitE
#define DEF_BITD(pdata)	((volatile _STC_BIT*)(pdata))->bitD
#define DEF_BITC(pdata)	((volatile _STC_BIT*)(pdata))->bitC
#define DEF_BITB(pdata)	((volatile _STC_BIT*)(pdata))->bitB
#define DEF_BITA(pdata)	((volatile _STC_BIT*)(pdata))->bitA
#define DEF_BIT9(pdata)	((volatile _STC_BIT*)(pdata))->bit9
#define DEF_BIT8(pdata)	((volatile _STC_BIT*)(pdata))->bit8
#define DEF_BIT7(pdata)	((volatile _STC_BIT*)(pdata))->bit7
#define DEF_BIT6(pdata)	((volatile _STC_BIT*)(pdata))->bit6
#define DEF_BIT5(pdata)	((volatile _STC_BIT*)(pdata))->bit5
#define DEF_BIT4(pdata)	((volatile _STC_BIT*)(pdata))->bit4
#define DEF_BIT3(pdata)	((volatile _STC_BIT*)(pdata))->bit3
#define DEF_BIT2(pdata)	((volatile _STC_BIT*)(pdata))->bit2
#define DEF_BIT1(pdata)	((volatile _STC_BIT*)(pdata))->bit1
#define DEF_BIT0(pdata)	((volatile _STC_BIT*)(pdata))->bit0

#define ABS(a)	((a)>0 ?(a) : -(a))				// Macro of calc absolute value


#endif /* __BASE_TYPES_H__ */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
