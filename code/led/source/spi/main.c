/*******************************************************************************
 * @Description: Description
 * @Author: Stream
 * @Version: V0.0.1
 * @Date: 2020-07-06 16:23:43
 * @LastEditors: Stream
 * @LastEditTime: 2020-08-03 18:58:20
 * @FilePath: \code\led\source\spi\main.c
 * @ChangeLog: ChangeLog
*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_CHAN 1

static int myFd;

unsigned char spi_pixl[] = {
    0x88,
    0x8c,
    0xc8,
    0xcc,
};

void rgb2spidata(unsigned long rgb, unsigned char *spi_rgb_data)
{

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    unsigned char spi_rgb_data_index = 0;

    unsigned char temp_bit = 0;

    //W2812B 是GRB接口

    green = (rgb) >> 16;
    red = (rgb) >> 8;
    blue = (rgb) >> 0;

    printf("red %02x,green %02x,blue %02x,\n", red, green, blue);

    spi_rgb_data[spi_rgb_data_index++] = 0x00;

    for (char i = 0; i < 4; i++)
    {
        /* code */
        temp_bit = (red & 0xc0) >> 6;
        red = red << 2;
        printf("temp_bit %d ", temp_bit);
        spi_rgb_data[spi_rgb_data_index++] = spi_pixl[temp_bit];
    }
    printf("\r\n");

    for (char i = 0; i < 4; i++)
    {
        /* code */
        temp_bit = (green & 0xc0) >> 6;
        green = green << 2;
        printf("temp_bit %d ", temp_bit);
        spi_rgb_data[spi_rgb_data_index++] = spi_pixl[temp_bit];
    }
    printf("\r\n");

    for (char i = 0; i < 4; i++)
    {
        /* code */
        temp_bit = (blue & 0xc0) >> 6;
        blue = blue << 2;
        printf("temp_bit %d ", temp_bit);
        spi_rgb_data[spi_rgb_data_index++] = spi_pixl[temp_bit];
    }
    printf("\r\n");

    for (char i = 0; i < 13; i++)
    {
        printf("%02x ", spi_rgb_data[i]);
    }

    printf("\r\n");
}

int led_spi_init(void)
{
    wiringPiSetupPhys();

    // myFd = wiringPiSPISetup(SPI_CHAN, 2 * 1000000);
    wiringPiSPISetupMode(SPI_CHAN, 0, 3 * 1000000, 1);
}

//0 ：成功    -1 ：出错
int led_set_color(unsigned long rgb_color)
{
    unsigned char spi_data[13];

    rgb2spidata(rgb_color, spi_data);
    return wiringPiSPIDataRW(SPI_CHAN, spi_data, sizeof(spi_data));
}

//0 ：成功    -1 ：出错
int led_set_color_rgb(unsigned char red, unsigned char green, unsigned char blue)
{

    unsigned long rgb_color;
    unsigned char spi_data[13];
    rgb_color = red << 16 | green << 8 | blue;

    rgb2spidata(rgb_color, spi_data);
    return wiringPiSPIDataRW(SPI_CHAN, spi_data, sizeof(spi_data));
}

int led_spi_on(void)
{
    led_set_color(0xffffff);
}

int led_spi_off(void)
{
    led_set_color(0x000000);
}

int main(int argc, char **argv)
{
    led_spi_init();

    unsigned char red;
    unsigned char green;
    unsigned char blue;
    srand(time(NULL));
    while (1)
    {

        // led_set_color(0xff00ff);
        // sleep(5);

        // led_set_color(0x452314);
        // sleep(5);

        // led_set_color(0x45413);
        // sleep(5);

        red = rand() % 255;
        green = rand() % 255;
        blue = rand() % 255;
        led_set_color_rgb(red, green, blue);
        sleep(1);

        // led_spi_on();
        // sleep(1);
        // led_spi_off();
        // sleep(1);

        // led_spi_on();
        // sleep(1);
        // led_spi_off();
        // sleep(1);

        // led_spi_on();
        // sleep(1);
        // led_spi_off();
        // sleep(1);

        // break;
    }
    return 0;
}
