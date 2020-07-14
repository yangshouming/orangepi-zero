#!/usr/bin/env python
# coding=utf-8
'''
@Description: Description
@Author: Stream
@Version: V0.0.1
@Date: 2020-07-03 14:57:05
@LastEditors: Stream
@LastEditTime: 2020-07-03 15:31:44
@FilePath: \code\python\key-input.py
@ChangeLog: ChangeLog
'''
import OPi.GPIO as GPIO
import time

pin_number = 7

GPIO.setmode(GPIO.BOARD)
GPIO.setup(pin_number, GPIO.IN, pull_up_down=GPIO.PUD_UP)


def my_callback(channel):

    print('my_callback', channel)


# GPIO.add_event_detect(pin_number, GPIO.FALLING,
#                       callback=my_callback, bouncetime=200)
try:
    while True:
        time.sleep(0.5)
        print("pin value", GPIO.input(pin_number))
except KeyboardInterrupt:
    GPIO.cleanup()
