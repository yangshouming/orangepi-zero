# src  :=$(shell ls *.c)
# objs :=$(patsubst %.c,%.o,$(src))
# libmlx.so: $(objs)
# 	arm-linux-gnueabihf-gcc  -o $@  $^  -lm  -shared -fPIC
# %.o:%.c
# 	arm-linux-gnueabihf-gcc  -c -o $@  $< -lm -fPIC

src  :=$(shell ls *.c)
objs :=$(patsubst %.c,%.o,$(src))
mlx.bin: $(objs)
	arm-linux-gnueabihf-gcc  -o $@  $^ -lwiringPi
%.o:%.c
	arm-linux-gnueabihf-gcc  -c -o $@  $<

clean:
	rm *.o *.so