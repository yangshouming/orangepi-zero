/*******************************************************************************
 * @Description: RGB七色LED
 * @Author: Stream
 * @Version: V0.0.1
 * @Date: 2020-09-25 10:03:12
 * @LastEditors: Stream
 * @LastEditTime: 2020-09-25 14:56:00
 * @FilePath: \code\led\source\gpio\led.c
 * @ChangeLog: ChangeLog
*******************************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include "led.h"

#define PIN_RED 19
#define PIN_GREEN 21
#define PIN_BLUE 23

/******************************************************************************/
/*
* 函数名称 : led_init
* 功能描述 : led初始化
* 参    数 : 无
* 返回值   : @-1	错误
             @0		正常
* 示    例 : led_init();
*/
/******************************************************************************/
int led_init(void)
{
    wiringPiSetupPhys();
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    return 0;
}

/******************************************************************************/
/*
* 函数名称 : led_set_color
* 功能描述 : 设置led颜色
* 参    数 : @int color 0x00=熄灭 0x01=红色 0x02=绿色 0x03=黄色 0x04=蓝色 0x05=紫色 0x06=青色 0x07=白色。
                闪烁样式的实现方式为：定时翻转熄灭&其他颜色。
                比如：红色1HZ闪烁，则为启动500ms的定时器，在翻转“熄灭”&“红色”两种状态。
* 返回值   :无
* 示    例 : led_set_color(&rate);
*/
/******************************************************************************/
void led_set_color(int color)
{
    digitalWrite(PIN_RED, color & 0X01);
    digitalWrite(PIN_GREEN, color & 0X02);
    digitalWrite(PIN_BLUE, color & 0X04);
}
