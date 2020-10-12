/*******************************************************************************
 * @Description: Description
 * @Author: Stream
 * @Version: V0.0.1
 * @Date: 2020-07-06 16:23:43
 * @LastEditors: Stream
 * @LastEditTime: 2020-09-25 17:35:24
 * @FilePath: \code\buzzer\source\main.c
 * @ChangeLog: ChangeLog
*******************************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

#include "button.h"//头文件包含

int main(int argc, char **argv)
{
    int key_value=0;
    button_init();//初始化
    while (1)
    {

        key_value=button_loop();//扫描，返回键值

        //根据键值做处理
        if (key_value==1)
        {
            /* code */
            //处理短按事件
            printf("short press\n");
        }else if (key_value==2)
        {
            /* code */
            //处理长按事件
            printf("long press\n");
        }
        
        usleep(1000*10);//线程延时 10ms

    }
    return 0;
}
