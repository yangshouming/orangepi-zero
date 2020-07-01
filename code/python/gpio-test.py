#!/usr/bin/env python3
# coding=utf-8
'''
@Description: Description
@Author: Stream
@Version: V0.0.1
@Date: 2020-06-30 15:17:07
@LastEditors: Stream
@LastEditTime: 2020-06-30 15:54:24
@FilePath: \code\python\gpio-test.py
@ChangeLog: ChangeLog
'''
import OPi.GPIO as GPIO  # ******************
import time
# sudo pip3 install --upgrade OPi.GPIO
pin_number = 7  # buzzuer pin number, global value

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)  # ******************
GPIO.setup(pin_number, GPIO.OUT)

GPIO.output(pin_number, GPIO.HIGH)
time.sleep(0.5)  # delay 0.5s
GPIO.output(pin_number, GPIO.LOW)
time.sleep(0.5)  # delay 0.5s

GPIO.output(pin_number, GPIO.HIGH)
time.sleep(0.5)  # delay 0.5s
GPIO.output(pin_number, GPIO.LOW)
time.sleep(0.5)  # delay 0.5s

GPIO.output(pin_number, GPIO.HIGH)
time.sleep(0.5)  # delay 0.5s
GPIO.output(pin_number, GPIO.LOW)
time.sleep(0.5)  # delay 0.5s
