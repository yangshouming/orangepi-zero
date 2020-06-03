src  :=$(shell ls *.c)
objs :=$(patsubst %.c,%.o,$(src))
mlx.bin: $(objs)
	arm-linux-gnueabihf-gcc  -o $@  $^ -lwiringPi -lm 
%.o:%.c
	arm-linux-gnueabihf-gcc  -c -o $@  $< -lm 

