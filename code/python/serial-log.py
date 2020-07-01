#!/usr/bin/env python
# coding=utf-8
'''
@Description: Description
@Author: Stream
@Version: V0.0.1
@Date: 2020-06-30 17:28:51
@LastEditors: Stream
@LastEditTime: 2020-07-01 10:20:36
@FilePath: \code\python\serial-log.py
@ChangeLog: ChangeLog
'''
import serial
import binascii
com = serial.Serial('/dev/ttyUSB0', 115200)
print(com.isOpen())

com.write(b'hello')
# com.readline()

f = open("foo.txt", "a")

num = f.write("Python\n")
print(num)

num = f.write("yes\n")
print(num)

num = f.write("{0:2x}\n".format(123))
print(num)

# 关闭打开的文件
f.close()


while(com.isOpen()):
    # print(com.read())
    num = com.inWaiting()  # 查询串口接收字节数据，非阻塞
    if num:
        print("\n")
        print("rx start")
        print("hex()")
        data_hex = com.read(num).hex()
        print(data_hex)
        # print('{0:2d} {1:2d} {2:2d}'.format(
        #     data_hex[0], data_hex[1], data_hex[2]))

        print("format")
        line = com.read(num)
        for i in range(num):
            print('{0:2x} '.format(line[i]), end='')
        print("\n")
