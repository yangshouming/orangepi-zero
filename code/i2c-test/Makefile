src  :=$(shell ls *.c)
objs :=$(patsubst %.c,%.o,$(src))
mlx.bin: $(objs)
	arm-linux-gnueabihf-gcc  -o $@  $^  -lm -lwiringPi
%.o:%.c
	arm-linux-gnueabihf-gcc  -c -o $@  $< -lm 

