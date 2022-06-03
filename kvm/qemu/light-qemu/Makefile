
all:
	as -32 test.S -o test.o
	objcopy -O binary test.o test.bin
	gcc qemu.c -o light-qemu.out

clean:
	rm -f test.o test.bin light-qemu.out
