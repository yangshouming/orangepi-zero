/*******************************************************************************
 * @Description: 蜂鸣器
 * @Author: Stream
 * @Version: V0.0.1
 * @Date: 2020-09-25 10:03:12
 * @LastEditors: Stream
 * @LastEditTime: 2020-09-25 17:19:54
 * @FilePath: \code\buzzer\source\buzzer.c
 * @ChangeLog: ChangeLog
*******************************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include "buzzer.h"

#define PIN_BUZZER 19

/******************************************************************************/
/*
* 函数名称 : buzzer_init
* 功能描述 : buzzer初始化
* 参    数 : 无
* 返回值   : @-1	错误
             @0		正常
* 示    例 : buzzer_init();
*/
/******************************************************************************/
int buzzer_init(void)
{
    wiringPiSetupPhys();
    pinMode(PIN_BUZZER, OUTPUT);
    return 0;
}

/******************************************************************************/
/*
* 函数名称 : buzzer_set
* 功能描述 : 开关蜂鸣器
* 参    数 : @int onoff 0x00=停止 0x01=鸣叫
* 返回值   :无
* 示    例 : buzzer_set(1);
*/
/******************************************************************************/
void buzzer_set(int onoff)
{
    digitalWrite(PIN_BUZZER, onoff);
}
