/*
问题：如何将I2C默认通信速率从100kbps提高到标准的400kbps
硬件：香橙派Orange Pi Zero LTS电脑开发板512MB
系统： Armbian buster with Linux 5.4.20-sunxi
通信接口：I2C0 I2C1
解决步骤：首先，先去网上该板子以及该系列板子的i2c相关内容，但是网上研究的人不多，
			而且更多的是在这个板子上做应用开发，不涉及底层驱动，所以找不到这个板子关于修改i2c的相关信息。
			
			接着就是去找厂家，但是厂家无法提供对应的技术支持，只提供了一个买家技术交流群。
			
			在买家技术交流群，把需要解决的问题，当前软硬件版本发出后，未得到回复。
			
			最后决定自己修改底层，分两个方向，一个是修改设备树，另一个是修改驱动源码：
			修改设备树需要找到处理器的dtb文件并进行反编译为dts文件，修改dts后再重新编译为dtb文件，最后覆盖到内核里。
			修改驱动源码需要找到处理器的i2c源码，根据芯片手册修改寄存器参数，然后在系统源码里编译成ko文件，最后覆盖到内核里。
			对于单片机工程师来时，修改寄存器是最简单的，但是出于维护底层驱动一致性和通用性，决定采用修改设备树的办法。
			
修改设备树： 1.先去Armbian官网找参考文档，得知系统配置文件是/boot/armbianEnv.txt，根据指示修改配置文件，完成i2c开机启动。
			2.找到Armbian系统源码，阅读i2c驱动源码，得知i2c参数的传入方式
			3.在系统里找到dtb文件，使用dtc工具进行反编译，获取dts文件
			3.在dts文件里，增加 clock-frequency=<400000>; 参数，然后使用dtc工具编译成dtb文件。
			4.将新得到的dtb文件覆盖到系统内核里








配置系统启动参数,两种
sudo vi /boot/armbianEnv.txt
sudo armbian-config
开启i2c


设备树覆盖 dtb
/boot/dtb/overlay/sun8i-h3-i2c0.dtbo



设备树编译
clock-frequency = <400000>;
dtc -I dts -O dtb -o /home/pi/temp.dtb /home/pi/temp.dts

设备树反编译
sudo cp /boot/dtb/overlay/sun8i-h3-i2c0.dtbo /home/pi/
dtc -I dtb -O dts -o /home/pi/temp.dts /home/pi/sun8i-h3-i2c0.dtbo



sudo cp /boot/dtb/overlay/sun8i-h3-i2c0.dtbo /boot/dtb/overlay/sun8i-h3-i2c0.dtbo.bak



香橙派已经搭建好，相应的驱动已经集成到系统里

传感器通信驱动源码修改点：
MLX90640_SWI2C_Driver.c
60行 注释以下两条语句
// ioctl(fd, I2C_TIMEOUT, 5); //设置超时时间
// ioctl(fd, I2C_RETRIES, 2); //设置重试次数

参考板子上的 /home/pi/mlx/code/drive 目录

注意点：WiFi上电2分钟后才连接

#自动获取ip
dhclient

1 首先 手动添加dns服务器

vi /etc/resolv.conf

在文件中添加如下两行：

nameserver 8.8.8.8
nameserver 114.114.114.114

ping www.baidu.com
ping 14.215.177.38



/etc/network/interfaces
#DNS配置
dns-nameservers 8.8.8.8 223.5.5.5


//开机后启动------------------------------------------OK
sudo service network-manager start
sudo service network-manager stop


dhclient

readelf -d libmlx.so|grep TEXTREL
readelf -r libmlx.so|grep R_ARM_REL32

cp libmlx.so /usr/lib/


GPIO控制
https://www.cnblogs.com/liangwode/p/5803350.html

echo 7 > /sys/class/gpio/export

echo out > /sys/class/gpio/gpio7/direction

echo 1 >/sys/class/gpio/gpio7/value

echo 0 >/sys/class/gpio/gpio7/value

echo 7 > /sys/class/gpio/unexport





拷机指令
s,m,h,d,y (time)
stress -c 4 --timeout 2d

stress -c 4 --timeout 4h

查看系统状态
armbianmonitor -m

armbianmonitor -m >> armbianmonitor_log.txt

查看每个CPU状态 每5秒更新
mpstat -P ALL 5




https://blog.csdn.net/xiekaikaibing/article/details/97244493

扩展SD卡空间 扩容
resize_part


https://blog.csdn.net/lixiaoxin1989/article/details/90476307/




使能SPI
armbian-config 打开spi-dev

echo "param_spidev_spi_bus=1">>/boot/armbianEnv.txt




pip3 install setuptools
pip3 install wheel
apt-get install python3-dev
pip3 install spidev





systemctl status network-manager.service





//传感器驱动编译
cd /root/orangepi-zero/code/drive/source
make
cp libmlx.so /usr/lib/

//传感器测试
cd /root/orangepi-zero/code/drive/test
make
./mlx.bin
ls


WiFi配置 关闭 network-manager

sed -i 's/TimeoutStartSec=5min/TimeoutStartSec=30sec/g' /etc/systemd/system/network-online.target.wants/networking.service
systemctl status network-manager.service
systemctl stop network-manager.service
systemctl disable network-manager.service
ls

reboot

//网速测试
git clone https://github.com/sivel/speedtest-cli.git
./speedtest-cli/speedtest.py --bytes



//查看历史开机时间
cat armbian-hardware-monitor.log |grep "Orange Pi Zero | 20.02.1"


//WiFi驱动编译
https://docs.armbian.com/User-Guide_Advanced-Features/#how-to-build-a-wireless-driver


//部署应用程序
cd ~
mkdir het && cd het && wget http://uuxia.top:8123/file/pi/orpi/installheto.sh && chmod +x installheto.sh && ./installheto.sh

//删除应用程序
rm -rf /etc/het/
rm -rf /root/het/



FEL USB下载模式
http://sunxi.org/FEL#Through_a_special_SD_card_image


镜像打包
https://blog.csdn.net/u013451404/article/details/80552765
https://blog.csdn.net/lixiaoxin1989/article/details/90476307
https://www.osyunwei.com/archives/9368.html
*/
