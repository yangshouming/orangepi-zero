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

/******************************************************************************\
                                 Includes
\******************************************************************************/

#include "HET_RGB2HSL.h"
/******************************************************************************\
                             Variables definitions
\******************************************************************************/
#define HET_RGB2HSL_MAX(a, b, c) ((a > ((b > c) ? b : c)) ? a : ((b > c) ? b : c))
#define HET_RGB2HSL_MIN(a, b, c) ((a < ((b < c) ? b : c)) ? a : ((b < c) ? b : c))
/******************************************************************************\
                             Functions definitions
\******************************************************************************/
//TS_RGB s_RGB;
//TS_HSL s_HSL;

/*
* 函数名称 : RGB_To_HSL
* 功能描述 : RGB转HSL  RGB from 0 to 255; HSL from 0 to 240
* 参    数 : RGB值    HSL指针
* 返回值   : 无
* 示    例 : RGB_To_HSL(r,g,b,*h,*s,*l);
*/
/******************************************************************************/
static void RGB_To_HSL(float r, float g, float b, float *h, float *s, float *l)
{
    //转到RGB(1, 1, 1)的空间
    float var_R = r / 255;
    float var_G = g / 255;
    float var_B = b / 255;

    float vmin = HET_RGB2HSL_MIN(var_R, var_G, var_B);
    float vmax = HET_RGB2HSL_MAX(var_R, var_G, var_B);
    float delta = vmax - vmin;

    float dr, dg, db;

    *l = (vmax + vmin) / 2;

    if (0 == delta)
    {
        *h = 0;
        *s = 0;
    }
    else
    {
        if (*l < 0.5)
            *s = delta / (vmax + vmin);
        else
            *s = delta / (2 - vmax - vmin);

        dr = (((vmax - var_R) / 6) + (delta / 2)) / delta;
        dg = (((vmax - var_G) / 6) + (delta / 2)) / delta;
        db = (((vmax - var_B) / 6) + (delta / 2)) / delta;

        if (var_R == vmax)
            *h = db - dg;
        else if (var_G == vmax)
            *h = (1.0 / 3.0) + dr - db;
        else if (var_B == vmax)
            *h = (2.0 / 3.0) + dg - dr;

        if (*h < 0)
            *h += 1;
        if (*h > 1)
            *h -= 1;
    }
    //转回到HSL(240, 240, 240)的空间

    *h *= 240;
    *s *= 240;
    *l *= 240;
}

/*
* 函数名称 : Hue_To_RGB
* 功能描述 : 色彩转换子函数，HSL_To_RGB调用
* 参    数 :
* 返回值   : 无
* 示    例 : RGB_To_HSL(v1,v2,vH);
*/
/******************************************************************************/
static float Hue_To_RGB(float v1, float v2, float vH)
{
    if (vH < 0)
        vH += 1;
    if (vH > 1)
        vH -= 1;
    if ((6 * vH) < 1)
        return (v1 + (v2 - v1) * 6 * vH);
    if ((2 * vH) < 1)
        return v2;
    if ((3 * vH) < 2)
        return (v1 + (v2 - v1) * ((2.0 / 3.0) - vH) * 6);

    return v1;
}

/*
* 函数名称 : HSL_To_RGB
* 功能描述 : HSL转RGB  RGB from 0 to 255; HSL from 0 to 240
* 参    数 : HSL值 RGB指针
* 返回值   : 无
* 示    例 : HSL_To_RGB(h,s,l,*R,*G,*B);
*/
/******************************************************************************/
static void HSL_To_RGB(float h, float s, float l, float *R, float *G, float *B)
{
    float v1, v2;
    //转到HSL(1, 1, 1)的空间
    float H = h / 240;
    float S = s / 240;
    float L = l / 240;

    if (0 == S)
    {
        //转回到RGB(255, 255, 255)的空间
        *R = L * 255;
        *G = L * 255;
        *B = L * 255;
    }
    else
    {
        if (L < 0.5)
            v2 = L * (1 + S);
        else
            v2 = (L + S) - (L * S);

        v1 = 2 * L - v2;

        //转回到RGB(255, 255, 255)的空间
        *R = 255 * Hue_To_RGB(v1, v2, H + (1.0 / 3.0));
        *G = 255 * Hue_To_RGB(v1, v2, H);
        *B = 255 * Hue_To_RGB(v1, v2, H - (1.0 / 3.0));
    }
}

/*
* 函数名称 : User_HSL_To_RGB
* 功能描述 : HSL转RGB  RGB from 0 to 255; HSL from 0 to 240
* 参    数 : *rgb RGB指针
			 *hsl HSL指针
* 返回值   : 无
* 示    例 : User_HSL_To_RGB( *rgb, *hsl);
*/
/******************************************************************************/
void User_HSL_To_RGB(TS_RGB *rgb, TS_HSL *hsl)
{

    float r, g, b;
    float h, s, l;

    h = hsl->Hue;
    s = hsl->Saturation;
    l = hsl->Lightness;

    HSL_To_RGB(h, s, l, &r, &g, &b);

    rgb->Red = r;
    rgb->Green = g;
    rgb->Blue = b;
}

/*
* 函数名称 : User_HSL_To_RGB
* 功能描述 : RGB转HSL  RGB from 0 to 255; HSL from 0 to 240
* 参    数 : *rgb RGB指针
			 *hsl HSL指针
* 返回值   : 无
* 示    例 : User_HSL_To_RGB( *rgb, *hsl);
*/
/******************************************************************************/
void User_RGB_To_HSL(TS_RGB *rgb, TS_HSL *hsl)
{

    float r, g, b;
    float h, s, l;

    r = rgb->Red;
    g = rgb->Green;
    b = rgb->Blue;

    RGB_To_HSL(r, g, b, &h, &s, &l);

    hsl->Hue = h;
    hsl->Saturation = s;
    hsl->Lightness = l;
}
