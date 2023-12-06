
CC = gcc
CFLAGS :=
RUN_PFX :=

ifneq ($(shell uname -m),aarch64)
	CC = aarch64-linux-gnu-gcc
	AS = aarch64-linux-gnu-as
	LD = aarch64-linux-gnu-ld
	# This root could be created by Docker Image Tar Archive
	# see: aarch64-linux-gnu-gcc -print-sysroot
	CFLAGS += --sysroot=$(shell pwd)/sysroot
	RUN_PFX = qemu-aarch64 --sysroot=$(shell pwd)/sysroot
endif

TARGETS :=
TARGETS += sve-width

CFLAGS += -march=armv9-a+sve2

all: $(TARGETS)

sve-width-asm: sve-width-asm.o
sve-width-intrinsics: sve-width-intrinsics.o

test:
	$(RUN_PFX) ./sve-width

clean:
	rm -f $(TARGETS) *.o
