/*

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


3.传感器通信驱动源码修改点：
MLX90640_SWI2C_Driver.c
60行 注释以下两条语句
// ioctl(fd, I2C_TIMEOUT, 5); //设置超时时间
// ioctl(fd, I2C_RETRIES, 2); //设置重试次数

参考板子上的 /home/pi/mlx/code/drive 目录

4.注意：WiFi上电2分钟后才连接




*/


