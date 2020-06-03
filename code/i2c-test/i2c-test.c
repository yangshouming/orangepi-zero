/*******************************************************************************
 * @Description: Description
 * @Author: Stream
 * @Version: V0.0.1
 * @Date: 2020-05-27 15:36:04
 * @LastEditors: Stream
 * @LastEditTime: 2020-06-03 14:18:17
 * @FilePath: \code\i2c-test\i2c-test.c
 * @ChangeLog: ChangeLog
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#include "MLX90640_I2C_Driver.h"

#define DEVICE_NAME "/dev/i2c-0"
#define I2C_ADDR 0x33 //EEPROM 0x50 0xA0 |  mlx 0x33 0x66
#define REG_ADDR 0x2400

uint16_t read_buf[1024];
uint16_t write_buf[1024];

#define read_cnt 832

int main(int argc, char **argv)
{

    int ret = 0;
    if (MLX90640_I2CInit() < 0)
    {
        ret = -1;
    }

    // for (uint16_t i = 0; i < 4; i++)
    // {
    //     ret = MLX90640_I2CWrite(I2C_ADDR, REG_ADDR + i * 2, i);
    //     printf("ret %d\n", ret);
    //     printf("%d", i);
    //     sleep(1);
    // }
    // printf("\n ");

    sleep(1);

    ret = MLX90640_I2CRead(I2C_ADDR, REG_ADDR, read_cnt, read_buf);
    printf("ret %d \n", ret);

    for (uint16_t i = 0; i < read_cnt; i++)
    {
        /* code */
        if (i % 32 == 0)
        {
            printf("\n ");
        }

        printf("%04x ", read_buf[i]);
    }
    printf("\n ");

#if 0 
    int fd = -1;
    struct i2c_rdwr_ioctl_data data;

    int return_value = 0;

    data.msgs = (struct i2c_msg *)malloc(2 * sizeof(struct i2c_msg));
    unsigned char sendbuf[1024] = {0};
    unsigned char recvbuf[1024] = {0};

    //0.open
    fd = open(DEVICE_NAME, O_RDWR);
    if (fd < 0)
    {
        printf("Failed to open device %s.\n", DEVICE_NAME);
        return -1;
    }
    printf("open device %s Success.\n", DEVICE_NAME);

#endif

#if 0

    //1.write reg to value
    data.nmsgs = 1;                 //消息的数目
    data.msgs[0].len = 2;           //1个写入目标的reg地址和1个数据
    data.msgs[0].addr = I2C_ADDR;   //i2c设备地址
    data.msgs[0].flags = 0;         //flags为0:表示写;为1:表示读.
    data.msgs[0].buf = sendbuf;     //申请内存为2个Byte
    data.msgs[0].buf[0] = REG_ADDR; //i2c设备要操作的reg地址
    data.msgs[0].buf[1] = 0x40;     //向reg写入的值
    return_value = ioctl(fd, I2C_RDWR, (unsigned long)&data);
    printf("return_value %d\r\n", return_value);

    sleep(1);

    //2.read reg value
    data.nmsgs = 2;
    data.msgs[0].len = 1;           //目标reg的地址的长度
    data.msgs[0].addr = I2C_ADDR;   //i2c设备地址
    data.msgs[0].flags = 0;         //write flag
    data.msgs[0].buf[0] = REG_ADDR; //目标reg地址

    data.msgs[1].len = 1;         //目标reg的地址的长度
    data.msgs[1].addr = I2C_ADDR; //i2c设备地址
    data.msgs[1].flags = 1;       //read flag
    data.msgs[1].buf = recvbuf;   //分配内存

    return_value = ioctl(fd, I2C_RDWR, (unsigned long)&data);
    printf("return_value %d\r\n", return_value);
    printf("buf[0] = %x\n", data.msgs[1].buf[0]);
#endif

#if 0
    //1.write reg to value
    // data.nmsgs = 1;                      //消息的数目
    // data.msgs[0].len = 3;                //1个写入目标的reg地址和1个数据
    // data.msgs[0].addr = I2C_ADDR;        //i2c设备地址
    // data.msgs[0].flags = 0;              //flags为0:表示写;为1:表示读.
    // data.msgs[0].buf = sendbuf;          //申请内存为2个Byte
    // data.msgs[0].buf[0] = REG_ADDR >> 8; //i2c设备要操作的reg地址
    // data.msgs[0].buf[1] = REG_ADDR >> 0; //i2c设备要操作的reg地址
    // data.msgs[0].buf[2] = 0xA6;          //向reg写入的值
    // return_value = ioctl(fd, I2C_RDWR, (unsigned long)&data);
    // printf("return_value %d\r\n", return_value);

    sleep(1);

    //2.read reg value
    data.nmsgs = 2;
    data.msgs[0].len = 2;                //目标reg的地址的长度
    data.msgs[0].addr = I2C_ADDR;        //i2c设备地址
    data.msgs[0].flags = 0;              //write flag
    data.msgs[0].buf[0] = REG_ADDR >> 8; //目标reg地址
    data.msgs[0].buf[1] = REG_ADDR >> 0; //目标reg地址

    data.msgs[1].len = 1;         //目标reg的地址的长度
    data.msgs[1].addr = I2C_ADDR; //i2c设备地址
    data.msgs[1].flags = 1;       //read flag
    data.msgs[1].buf = recvbuf;   //分配内存

    return_value = ioctl(fd, I2C_RDWR, (unsigned long)&data);
    printf("return_value %d\r\n", return_value);
    printf("buf[0] = %x\n", data.msgs[1].buf[0]);

#endif

    // close(fd);

    return 0;
}
