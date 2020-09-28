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
#include "buzzer.h"

int main(int argc, char **argv)
{
    buzzer_init();
    while (1)
    {
        for (int i = 0; i < 8; i++)
        {
            /* code */
            buzzer_set(1);
            sleep(1);
            buzzer_set(0);
            sleep(1);
            printf("blink color %d\r\n", i);
        }

        break;
    }
    return 0;
}
