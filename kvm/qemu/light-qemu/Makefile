TARGET=light-qemu
ARCH=$(shell uname -m)

QEMU_SRC :=
QEMU_SRC += qemu.c

ifeq (${ARCH},x86_64)
TEST_SRC=test-x86_64.S
AS_FLAGS=-32
endif

ifeq (${ARCH},aarch64)
TEST_SRC=test-aarch64.S
AS_FLAGS=
endif


all:
	as ${AS_FLAGS} ${TEST_SRC} -o test.o
	objcopy -O binary test.o test.bin
	gcc ${QEMU_SRC} -o $(TARGET)

test:
	$(shell test -f ./$(TARGET) && echo ./$(TARGET))

clean:
	rm -f test.o test.bin $(TARGET)
