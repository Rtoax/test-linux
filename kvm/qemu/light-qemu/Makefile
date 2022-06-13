
ARCH=$(shell uname -m)

ifeq (${ARCH},x86_64)
TEST_SRC=test-x86_64.S
AS_FLAGS=-32
endif

ifeq (${ARCH},aarch64)
TEST_SRC=test-aarch64.S
AS_FLAGS=
endif

QEMU_SRC=qemu.c

all:
	as ${AS_FLAGS} ${TEST_SRC} -o test.o
	objcopy -O binary test.o test.bin
	gcc ${QEMU_SRC} -o light-qemu.out

test:
	$(shell test -f ./light-qemu.out && echo ./light-qemu.out)

clean:
	rm -f test.o test.bin light-qemu.out
