src  :=$(shell ls *.c)
objs :=$(patsubst %.c,%.o,$(src))
mlx.bin: $(objs)
	arm-linux-gnueabihf-gcc  -o $@  $^ -lm -lmlx
%.o:%.c
	arm-linux-gnueabihf-gcc  -c -o $@  $< -lm -lmlx

clean:
	rm *.o  *.bin
