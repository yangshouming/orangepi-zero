#!/usr/bin/env python3
import numpy as np
import math
from ctypes import *
import pandas as pd
import time
# import RPi.GPIO as GPIO


# def set_gpio(pin_number):
#     # pin_number = 27  # buzzuer pin number, global value
#     GPIO.cleanup(pin_number)  # reset io  use onece
#     GPIO.setmode(GPIO.BCM)  # set mode use onece
#     GPIO.setup(pin_number, GPIO.OUT)  # set output use onece
#
#
# def gpio_alarm(pin_number):
#     GPIO.output(pin_number, GPIO.HIGH)  # buzzuer on use determine if you need
#     time.sleep(0.1)  # delay 0.5s
#     GPIO.output(pin_number, GPIO.LOW)  # buzzuer off use determine if you need
#     time.sleep(0.1)  # delay 0.5s


def device_init():
    lib = CDLL('libmlx.so')
    print(lib.mlx_init())

    time.sleep(0.5)
    lib.mlx_set_refresh_rate(5)
    # 刷新率 //0x01 – 1Hz //0x02 – 2Hz //0x03 – 4Hz //0x04 – 8Hz //0x05 – 16Hz //0x06 – 32Hz
    time.sleep(0.5)

    x = c_int(0)
    lib.mlx_get_refresh_rate(byref(x))
    print('====>>>> fps is {}'.format(x))
    return lib


if __name__ == '__main__':
    # gpio_pin_number = 27
    lib = device_init()
    worker_sleep = 0.05
    print('====>>>> Getting data worker sleep {}'.format(worker_sleep))
    minitor = []

    for i in range(3000):
        source_array = c_ushort * 834
        calc_array = c_float * 768
        p_source_array = source_array()
        p_calc_array = calc_array()

        if lib.mlx_get_source_data(pointer(p_source_array)) == 0 and lib.mlx_get_calculate_data(pointer(p_calc_array), pointer(p_source_array)) == 0:
            print("====>>>> read ok")
            frame = np.asarray(p_calc_array)
            # image_array = frame.reshape((24, 32))#把数组打印成24*32的点阵数字图
            # print(image_array)
            if frame.max() > 50:
                print('====>>>> T-Erro: {}'.format(frame.max()))
        else:
            print('====>>>> read error')

        time.sleep(worker_sleep)
