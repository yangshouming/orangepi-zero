#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include "button.h"

/******************************************************************************/
/*
* 函数名称 : button_init
* 功能描述 : button初始化
* 参    数 : 无
* 返回值   : @-1	错误
             @0		正常
* 示    例 : button_init();
*/
/******************************************************************************/
int button_init(void)
{
    KEY_Init();
    return 0;
}

/******************************************************************************/
/*
* 函数名称 : button_loop
* 功能描述 : 按键定时循环扫描
* 参    数 : 无
* 返回值   : 0-无按键 1-短按 2-长按
* 示    例 : key_value=button_loop();
*/
/******************************************************************************/
int button_loop(void)
{
    int value=0;

    KEY_Drv();

    if (IsKey(KEY_1,KEY_EVT_PRESSED))
    {
        /* code */
        value=1;
    }
    else if ( IsKey(KEY_1,KEY_EVT_DOWN))
    {
        /* code */
        value=2;
    }

    return value;
}
