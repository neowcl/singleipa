/***************************************************************************//**
 * @file     main_diagnostic.h
 * @version  V1.0.0
 * @author   sz414
 * @date     2022-06-13 PM
 * @brief    该文件包含了诊断支持接口声明
 * 
 * @copyright Copyright (C) 2020 Chipsea Technologies Corp. All rights reserved.
 ****************************************************************************
 * @attention
 *  硬件平台:  \n
 *  SDK版本： V0.9.0
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date        <th>Version  <th>Author    <th>Description
 * <tr><td>2022/06/08  <td>1.0      <td>SZ404  <td>创建初始版本
 * </table>
 *
 *****************************************************************************/

#ifndef __MAIN_DIAGNOSTIC_H__
#define __MAIN_DIAGNOSTIC_H__

// Include external header file.

#ifdef __cplusplus
extern "C" {
#endif

#if defined(USE_FULL_ASSERT) || defined(_DEBUG)
#ifdef __UVISION_VERSION
    extern void assert_failed(uint8_t* file, uint32_t line);
	#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
#else 
	#include <assert.h>
	#define assert_param(expr) assert(expr)
#endif
	#define trace_msg		printf
	#define ASSERT  assert_param
	#define TRACE0(fmt)  trace_msg(fmt)
	#define TRACE1(fmt,a0)  trace_msg(fmt, a0)
	#define TRACE2(fmt,a0,a1)  trace_msg(fmt,a0,a1)
	#define TRACE3(fmt,a0,a1,a2)  trace_msg(fmt,a0,a1,a2)
	#define TRACE4(fmt,a0,a1,a2,a3)  trace_msg(fmt,a0,a1,a2,a3)
	#define TRACE5(fmt,a0,a1,a2,a3,a4)  trace_msg(fmt,a0,a1,a2,a3,a4)
	#define TRACE6(fmt,a0,a1,a2,a3,a4,a5)  trace_msg(fmt,a0,a1,a2,a3,a4,a5)
#else
  #define assert_param(expr) ((void)0U)
	#define trace_msg	 ((void)0U)
	#define ASSERT(expr) ((void)0)
	#define TRACE0(msg)  ((void)0U)
	#define TRACE1(fmt,a0)  ((void)0U)
	#define TRACE2(fmt,a0,a1)  ((void)0U)
	#define TRACE3(fmt,a0,a1,a2)  ((void)0U)
	#define TRACE4(fmt,a0,a1,a2,a3)  ((void)0U)
	#define TRACE5(fmt,a0,a1,a2,a3,a4)  ((void)0U)
	#define TRACE6(fmt,a0,a1,a2,a3,a4,a5)  ((void)0U)
#endif /* USE_FULL_ASSERT */


#ifdef __cplusplus
}
#endif

#endif  //__MAIN_DIAGNOSTIC_H__


/*** (C) COPYRIGHT 2020 Chipsea Technologies (Shenzhen) Corp. ***/
