src  :=$(shell ls *.c)
objs :=$(patsubst %.c,%.o,$(src))
mlx.bin: $(objs)
	arm-linux-gnueabihf-gcc  -o $@  $^  -lm
%.o:%.c
	arm-linux-gnueabihf-gcc  -c -o $@  $<

clean:
	rm *.o *.bin
