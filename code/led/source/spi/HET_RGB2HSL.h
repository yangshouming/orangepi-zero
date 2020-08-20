/******************************************************************************\
**  版    权: 深圳市和而泰智能控制股份有限公司所有（2020）
**  文件名称: HET_RGB2HSL
**  功能描述: 色彩表示方法转换算法，实现RGB与HSL的互转
              RGB：Red(红色)、Green(绿色)、Blue(蓝色) 是一种便于硬件操作的色彩表示方法
              HSL：Hue(色相)、Saturation(饱和度)、Lightness(亮度) 是一种非常直观的色彩表示方法，比RGB更具人性化
**  作    者: 杨守明
**  日    期: 2019-5-28
**  版    本: V0.0.1
**  变更记录: V0.0.1/2019-5-28
              1.首次创建
\******************************************************************************/

#ifndef _HET_RGB2HSL_H_
#define _HET_RGB2HSL_H_
/******************************************************************************\
                             Includes
\******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/******************************************************************************\
                          Macro definitions
\******************************************************************************/

/******************************************************************************\
                         Typedef definitions
\******************************************************************************/
typedef struct rgb_data
{
    unsigned char Red;   //Red(红色)
    unsigned char Green; //Green(绿色)
    unsigned char Blue;  //Blue(蓝色)

} TS_RGB;

typedef struct
{
    unsigned char Hue;        //Hue(色相)
    unsigned char Saturation; //Saturation(饱和度)
    unsigned char Lightness;  //Lightness(亮度)

} TS_HSL;
/******************************************************************************\
                    Global variables and functions
\******************************************************************************/
/*
* 函数名称 : User_HSL_To_RGB
* 功能描述 : HSL转RGB  RGB from 0 to 255; HSL from 0 to 240
* 参    数 : *rgb RGB指针
			 *hsl HSL指针
* 返回值   : 无
* 示    例 : User_HSL_To_RGB( *rgb, *hsl);
*/
/******************************************************************************/
extern void User_HSL_To_RGB(TS_RGB *rgb, TS_HSL *hsl);

/*
* 函数名称 : User_RGB_To_HSL
* 功能描述 : RGB转HSL  RGB from 0 to 255; HSL from 0 to 240
* 参    数 : *rgb RGB指针
			 *hsl HSL指针
* 返回值   : 无
* 示    例 : User_RGB_To_HSL( *rgb, *hsl);
*/
/******************************************************************************/

extern void User_RGB_To_HSL(TS_RGB *rgb, TS_HSL *hsl);

#endif
