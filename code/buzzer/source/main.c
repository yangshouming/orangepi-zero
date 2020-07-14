/*******************************************************************************
 * @Description: Description
 * @Author: Stream
 * @Version: V0.0.1
 * @Date: 2020-07-06 16:23:43
 * @LastEditors: Stream
 * @LastEditTime: 2020-07-06 17:35:20
 * @FilePath: \code\buzzer\source\main.c
 * @ChangeLog: ChangeLog
*******************************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

int pin_number = 8;

int buzzer_init(void)
{
    wiringPiSetupPhys();
    pinMode(pin_number, OUTPUT);
    return 0;
}

int buzzer_on(void)
{
    digitalWrite(pin_number, HIGH);
    return 0;
}

int buzzer_off(void)
{
    digitalWrite(pin_number, LOW);
    return 0;
}

int main(int argc, char **argv)
{
    buzzer_init();
    while (1)
    {
        for (int i = 0; i < 3; i++)
        {
            /* code */
            buzzer_on();
            usleep(500 * 1000);
            buzzer_off();
            usleep(500 * 1000);
            printf("blink\r\n");
        }

        break;
    }
    return 0;
}
