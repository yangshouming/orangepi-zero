/*

//安装

1.下载镜像
Armbian镜像
https://www.armbian.com/orange-pi-zero/

2.格式化SD卡
SDFormatterv4

3.写入镜像
Win32DiskImager

4.连接网线，登录SSH，默认账号root 密码1234
修改后
root pi123456
pi pi123456

5.修改更新源，并更新



sudo apt update -y
sudo apt upgrade -y

sudo apt install i2c-tools -y
sudo apt install git -y


6.设置系统时间 时区
timedatectl set-timezone Asia/Shanghai

NTP service


//配置




1.配置系统启动参数,开启i2c,两种
sudo vi /boot/armbianEnv.txt
sudo armbian-config


2.设备树覆盖 当前目录下dtb文件夹
/boot/dtb/overlay/sun8i-h3-i2c0.dtbo
/boot/dtb/overlay/sun8i-h3-i2c1.dtbo


	设备树编译
	clock-frequency = <400000>;
	dtc -I dts -O dtb -o /home/pi/temp.dtb /home/pi/temp.dts

	设备树反编译
	sudo cp /boot/dtb/overlay/sun8i-h3-i2c0.dtbo /home/pi/
	dtc -I dtb -O dts -o /home/pi/temp.dts /home/pi/sun8i-h3-i2c0.dtbo

	sudo cp /boot/dtb/overlay/sun8i-h3-i2c0.dtbo /boot/dtb/overlay/sun8i-h3-i2c0.dtbo.bak

	文件覆盖
	sudo cp /home/pi/orangepi-zero/code/dtb/dts/i2c0/sun8i-h3-i2c0.dtbo /boot/dtb/overlay/sun8i-h3-i2c0.dtbo
	sudo cp /home/pi/orangepi-zero/code/dtb/dts/i2c1/sun8i-h3-i2c1.dtbo /boot/dtb/overlay/sun8i-h3-i2c1.dtbo

3.传感器通信驱动源码修改点：
MLX90640_SWI2C_Driver.c
60行 注释以下两条语句
// ioctl(fd, I2C_TIMEOUT, 5); //设置超时时间
// ioctl(fd, I2C_RETRIES, 2); //设置重试次数

参考板子上的 /home/pi/mlx/code/drive 目录

4.WiFi配置

sudo cp /etc/network/interfaces /etc/network/interfaces.bak
sudo vim /etc/network/interfaces

//内容
auto lo
iface lo inet loopback

auto eth0
allow-hotplug eth0
iface eth0 inet dhcp

allow-hotplug wlan0
iface wlan0 inet manual
iface wlan0 inet dhcp
wpa-roam /etc/wpa_supplicant/wpa_supplicant.conf
iface default inet dhcp


auto lo
iface lo inet loopback

auto eth0
#allow-hotplug eth0
iface eth0 inet dhcp


auto wlan0
#allow-hotplug wlan0
iface wlan0 inet dhcp
wpa-conf /etc/wpa_supplicant/wpa_supplicant.conf

//
/etc/rc.local 添加 dhclient wlan0


注意：WiFi上电2分钟后才连接

//wifi工具
nmtui



4.安装i2c-tools工具


5.查看系统状态
armbianmonitor -m


6.开机启动时间
命令：sudo vim /etc/systemd/system/network-online.target.wants/networking.service

将里面的TimeoutStartSec=5min 修改为TimeoutStartSec=2sec


7.安装wiringOP
git clone https://github.com/orangepi-xunlong/wiringOP.git
cd wiringOP
chmod 777 build
./build

*/
