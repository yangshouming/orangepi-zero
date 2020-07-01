#!/usr/bin/env python
# coding=utf-8
'''
@Author: Stream
@Date: 2020-04-07 16:01:46
@LastEditTime: 2020-04-09 10:22:45
@LastEditors: Stream
@Description: 
@FilePath: \mlx_raspibeery\code\gpio_buzzer\gpio_buzzer.py
@version: v0.0.1
'''

import RPi.GPIO as GPIO
import time


class buzzer:
    """
    无源蜂鸣器 模块
    """

    __buzzer_pwm = 0

    def buzzuer_init(self, pin_number=27):
        """
        蜂鸣器初始化
        pin_number:BCM 引脚号
        """
        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(pin_number, GPIO.OUT)
        self.__buzzer_pwm = GPIO.PWM(pin_number, 4000)
        self.__buzzer_pwm.ChangeDutyCycle(0)
        self.__buzzer_pwm.start(0)
        print("buzzuer_init")

    def buzzuer_cmd(self, cmd):
        """
        蜂鸣器连续长鸣
        cmd:1-开始，2-停止
        """
        if(cmd):
            self.__buzzer_pwm.start(50)
        else:
            self.__buzzer_pwm.start(0)

    def buzzuer_beep(self, count=5):
        """
        蜂鸣器按次数响
        count:次数
        """
        i = 0
        for i in range(count):
            self.buzzuer_cmd(1)
            print("on")
            time.sleep(0.5)  # delay 0.5s
            self.buzzuer_cmd(0)
            print("off")
            time.sleep(0.5)  # delay 0.5s


# 使用方法
beep = buzzer()
beep.buzzuer_init(27)
beep.buzzuer_beep(5)
