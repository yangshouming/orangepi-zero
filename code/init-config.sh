#!/bin/bash
#linux

#use color
#echo -e "\033[36m "userstring" \033[0m"
# 30m black
# 31m red
# 32m green
# 33m yellow
# 34m blue
# 35m purple
# 36m sky blue
# 37m white

#printf info
date
echo -e "\033[32m"hello world"\033[0m"
echo -e "\033[32m"author:stream"\033[0m"

#check user
if [ "root" != $(whoami) ]; then
    echo -e "\033[31m "error" \033[0m"
    echo -e "\033[31m "please run with root" \033[0m"
    echo -e "\033[31m "exit" \033[0m"
    exit 0
fi

#check Linux version
str_current_version=$(lsb_release -c)
str_match_version="buster"

if [[ "$str_current_version" = *$str_match_version* ]]; then
    echo -e "\033[32m"right"\033[0m"
    echo -e "\033[32m"the current Linux version is match"\033[0m"
    echo -e "\033[32m"run"\033[0m"
else
    echo -e "\033[31m"error"\033[0m"
    echo -e "\033[31m"the current Linux version is not match"\033[0m"
    echo -e "\033[31m"exit"\033[0m"
    exit 0
fi

#get top dir
CURRENT_TOP_DIR=$(cd $(dirname $0); pwd)
echo $CURRENT_TOP_DIR

#creat log file
touch config_log.txt
echo -e "start" >> "${CURRENT_TOP_DIR}"/config_log.conf
echo -e "$(date)" >> "${CURRENT_TOP_DIR}"/config_log.conf

#set apt source 

cp /etc/apt/sources.list /etc/apt/sources.list.bak
cat>/etc/apt/sources.list <<EOF
deb https://mirrors.tuna.tsinghua.edu.cn/debian/ buster main contrib non-free
# deb-src https://mirrors.tuna.tsinghua.edu.cn/debian/ buster main contrib non-free
deb https://mirrors.tuna.tsinghua.edu.cn/debian/ buster-updates main contrib non-free
# deb-src https://mirrors.tuna.tsinghua.edu.cn/debian/ buster-updates main contrib non-free
deb https://mirrors.tuna.tsinghua.edu.cn/debian/ buster-backports main contrib non-free
# deb-src https://mirrors.tuna.tsinghua.edu.cn/debian/ buster-backports main contrib non-free
deb https://mirrors.tuna.tsinghua.edu.cn/debian-security buster/updates main contrib non-free
# deb-src https://mirrors.tuna.tsinghua.edu.cn/debian-security buster/updates main contrib non-free
EOF

# cp /etc/apt/sources.list.d/armbian.list  /etc/apt/sources.list.d/armbian.list.bak
# cat>/etc/apt/sources.list.d/armbian.list <<EOF
# deb https://mirrors.tuna.tsinghua.edu.cn/armbian/ buster main buster-utils buster-desktop
# EOF

apt-get update -y
apt-get upgrade -y

echo -e "\033[36m "source update suceess" \033[0m"

#tools install
apt install i2c-tools -y
apt install git -y

echo -e "\033[36m "tools install suceess" \033[0m"

#config vim
cd /home/pi
apt install  vim -y
cp /etc/vim/vimrc /home/pi/.vimrc
cat>>/home/pi/.vimrc <<EOF
set nocompatible
set number
set backspace=2
set tabstop=4
set shiftwidth=4
set ignorecase
set hlsearch
EOF
echo -e "\033[36m "config vim" \033[0m"

timedatectl set-timezone Asia/Shanghai

echo -e "alias date='date \"+%a %b %d %H:%M:%S %Z %Y\"'" >> /home/pi/.bashrc
echo -e "alias date='date \"+%a %b %d %H:%M:%S %Z %Y\"'" >> /root/.bashrc
date


#wiringOP
git clone https://github.com/orangepi-xunlong/wiringOP.git
cd wiringOP
chmod 777 build
./build
gpio -v
echo -e "\033[36m "wiringOP" \033[0m"

#python
ln -s /usr/bin/python3 /usr/bin/python
sudo apt-get install python3-pip -y
pip3 config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
sudo apt-get install python3-opencv python3-numpy python3-pandas python3-sklearn python3-skimage -y


#copy config file

echo "copy config files"

cp /etc/wpa_supplicant/wpa_supplicant.conf /etc/wpa_supplicant/wpa_supplicant.conf.bak
cp "${CURRENT_TOP_DIR}"/wpa_supplicant.conf /etc/wpa_supplicant/
cp /etc/network/interfaces /etc/network/interfaces.bak
cp "${CURRENT_TOP_DIR}"/interfaces /etc/network/

cp /boot/dtb/overlay/sun8i-h3-i2c0.dtbo /boot/dtb/overlay/sun8i-h3-i2c0.dtbo.bak
cp "${CURRENT_TOP_DIR}"/sun8i-h3-i2c0.dtbo /boot/dtb/overlay/

cp /boot/dtb/overlay/sun8i-h3-i2c1.dtbo /boot/dtb/overlay/sun8i-h3-i2c1.dtbo.bak
cp "${CURRENT_TOP_DIR}"/sun8i-h3-i2c1.dtbo /boot/dtb/overlay/

cp "${CURRENT_TOP_DIR}"/libmlx.so /usr/lib/


#open i2c
sed -i 's/overlays=usbhost2 usbhost3/overlays=i2c0 i2c1 usbhost2 usbhost3/g' /boot/armbianEnv.txt

echo -e "end" >> "${CURRENT_TOP_DIR}"/config_log.conf
echo -e "$(date)" >> "${CURRENT_TOP_DIR}"/config_log.conf
echo -e "\033[36m "config finish,please reboot" \033[0m"
exit 0
