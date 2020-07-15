#!/bin/bash
###
 # @Description: Description
 # @Author: Stream
 # @Version: V0.0.1
 # @Date: 2020-07-14 18:00:23
 # @LastEditors: Stream
 # @LastEditTime: 2020-07-14 19:58:30
 # @FilePath: \code\test.sh
 # @ChangeLog: ChangeLog
### 
CURRENT_TOP_DIR=$(cd $(dirname $0); pwd)
echo $CURRENT_TOP_DIR

file_src="${CURRENT_TOP_DIR}"/wpa_supplicant.conf
echo $file_src

file_target="${CURRENT_TOP_DIR}"/wpa_supplicant.conf
echo $file_dest

cp /etc/wpa_supplicant/wpa_supplicant.conf /etc/wpa_supplicant/wpa_supplicant.conf.bak
cp "${CURRENT_TOP_DIR}"/wpa_supplicant.conf /etc/wpa_supplicant/wpa_supplicant.conf

cp /etc/network/interfaces /etc/network/interfaces.bak
cp "${CURRENT_TOP_DIR}"/interfaces /etc/network/interfaces

cp /boot/dtb/overlay/sun8i-h3-i2c0.dtbo /boot/dtb/overlay/sun8i-h3-i2c0.dtbo.bak
cp "${CURRENT_TOP_DIR}"/sun8i-h3-i2c0.dtbo /boot/dtb/overlay/sun8i-h3-i2c0.dtbo

cp /boot/dtb/overlay/sun8i-h3-i2c1.dtbo /boot/dtb/overlay/sun8i-h3-i2c1.dtbo.bak
cp "${CURRENT_TOP_DIR}"/sun8i-h3-i2c1.dtbo /boot/dtb/overlay/sun8i-h3-i2c1.dtbo


