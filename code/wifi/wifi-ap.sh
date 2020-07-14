#!/bin/bash
###
 # @Description: Description
 # @Author: Stream
 # @Version: V0.0.1
 # @Date: 2020-07-13 17:49:13
 # @LastEditors: Stream
 # @LastEditTime: 2020-07-13 17:50:07
 # @FilePath: \code\wifi\wifi-ap.sh
 # @ChangeLog: ChangeLog
### 
#!/usr/bin/env bash
killall -q wpa_supplicant
killall -q udhcpc
killall -q udhcpd
killall -q hostapd
# 以上清除当前网络相关进程是必须的，不然WiFi还有可能工作在sta模式下
echo "start switch to AP mode..."
ifconfig wlan0 down

# 设置当前网卡IP为192.168.43.1，和udhcpd 里面IP要相同
ifconfig wlan0 192.168.43.1 up  
#启动hostap 工具，记得-B表示后台运行
hostapd -B hostapd.cfg
# 启动udhcpd 设置ip地址范围，dns等
udhcpd udhcpd.conf
