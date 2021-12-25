﻿// 转换后的代码如下
//
////////////////////////////////////////////////////////////////
#include <compiler.h>    // 请在本网页下载此头文件(http://keilc51c-to-sdccc.verimake.com/)
/********************************** (C) COPYRIGHT *******************************
* File Name          : Debug.H
* Author             : WCH
* Version            : V1.0
* Date               : 2020/07/03
* Description        : This file contains all the functions prototypes for UART
*                      Printf , Delay functions.									 
*******************************************************************************/
#ifndef	__DEBUG_H__
#define __DEBUG_H__

//#include <absacc.h>
#include <stdio.h>
#include <string.h>
//#include <intrins.h>
#include "CH557X.H"

//定义函数返回值
#ifndef  SUCCESS
#define  SUCCESS    0
#endif
#ifndef  FAIL
#define  FAIL       0xFF
#endif


#define	 FREQ_SYS	                       48000000	          //系统主频48MHz
#define  OSC_EN_XT                       0                    //外部晶振使能，默认开启内部晶振
#ifndef  UART0_BUAD
#define  UART0_BUAD                      115200
#define  UART1_BUAD                      57600
#endif
#ifndef  DE_PRINTF                                            //程序Pirntf输出开启
#define  DE_PRINTF                      1
#endif

#ifndef MIN
#define MIN(a,b)                (((a) <= (b)) ? (a) : (b))
#endif

void CfgFsys(void);                                           //CH557时钟选择和配置
void mDelayuS(UINT16 n);                                 //以uS为单位延时
void mDelaymS(UINT16 n);                                 //以mS为单位延时
void mInitSTDIO(void);                                        //T1作为波特率发生器
void CH557UART0Alter(void);                                    //CH557串口0引脚映射到P0.2/P0.3
void CH557UART0SendByte(UINT8 SendDat);                    //CH557UART0发送一个字节
UINT8 CH557UART0RcvByte(void);                                //CH557UART0查询方式接收一个字节

void CH557WDTModeSelect(UINT8 mode);                       //CH557看门狗模式设置 
void CH557WDTFeed(UINT8 tim);                              //CH557看门狗喂狗
void CH557SoftReset(void);                                    //CH557软复位
  
#endif

