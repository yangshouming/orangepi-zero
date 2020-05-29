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


#set apt source 

cp /etc/apt/sources.list /etc/apt/sources.list.bak
cat>/etc/apt/sources.list <<EOF
deb https://mirrors.tuna.tsinghua.edu.cn/debian/ buster main contrib non-free
deb https://mirrors.tuna.tsinghua.edu.cn/debian/ buster-updates main contrib non-free
deb https://mirrors.tuna.tsinghua.edu.cn/debian/ buster-backports main contrib non-free
deb https://mirrors.tuna.tsinghua.edu.cn/debian-security/ buster/updates main contrib non-free
EOF

cp /etc/apt/sources.list.d/armbian.list  /etc/apt/sources.list.d/armbian.list.bak
cat>/etc/apt/sources.list.d/armbian.list <<EOF
deb https://mirrors.tuna.tsinghua.edu.cn/debian/ main buster-utils buster-desktop
EOF

apt-get update
apt-get upgrade -y
echo -e "\033[36m "source update suceess" \033[0m"


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

echo -e "alias date='date \"+%a %b %d %H:%M:%S %Z %Y\"'" >> /home/pi/.bashrc

exit 0

