/*******************************************************************************
 * @Description: Description
 * @Author: Stream
 * @Version: V0.0.1
 * @Date: 2020-07-06 16:23:43
 * @LastEditors: Stream
 * @LastEditTime: 2020-09-25 10:58:59
 * @FilePath: \code\led\source\gpio\main.c
 * @ChangeLog: ChangeLog
*******************************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include "led.h"
/*
/sys/class/gpio
*/

int main(int argc, char **argv)
{
    led_init();
    while (1)
    {
        for (int i = 0; i < 8; i++)
        {
            /* code */
            led_set_color(i);
            sleep(3);
            printf("blink color %d\r\n", i);
        }

        break;
    }
    return 0;
}
