
CC = gcc
CFLAGS :=
RUN_PFX :=
TARGETS :=

ifeq ($(shell lscpu | grep -w -e sve -e sve2),)
$(warning Not support SVE/SVE2 on this CPU)
else
TARGETS += sve-width
TARGETS += add_array
TARGETS += svaddlb
TARGETS += neon-sve
endif

# Cross compile
ifneq ($(shell uname -m),aarch64)
	CC = aarch64-linux-gnu-gcc
	AS = aarch64-linux-gnu-as
	LD = aarch64-linux-gnu-ld
	# This root could be created by Docker Image Tar Archive
	# see: aarch64-linux-gnu-gcc -print-sysroot
	CFLAGS += --sysroot=$(shell pwd)/sysroot
	RUN_PFX = qemu-aarch64 --sysroot=$(shell pwd)/sysroot
endif


CFLAGS += -march=armv8-a+sve2

all: $(TARGETS)

sve-width: sve-width.o
add_array: add_array.o
svaddlb: svaddlb.o
neon-sve: neon-sve

test:
	$(RUN_PFX) ./sve-width

clean:
	rm -f $(TARGETS) *.o
