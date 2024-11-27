# SPDX-License-Identifier: GPL-3.0
SHELL = bash

# Test vDSO linux-vdso.so.1
#
# See linux:/arch/x86/entry/vdso/Makefile
#VDSO_LDFLAGS_vdso.lds = -m elf_x86_64 -soname linux-vdso.so.1 --no-undefined \
#		-z max-page-size=4096 

TARGET :=
TARGET += main-custom
TARGET += main-kernel


all: ${TARGET}

#-Wl,-soname=linux-vdso.so.custom
libvdso_custom.so:
	gcc vdso.c \
		-P -C \
		-fpic --share \
		-Wl,-melf_x86_64 \
		-Wl,-soname=linux-vdso.so.custom \
		-Wl,--no-undefined \
		-Wl,-zmax-page-size=4096 \
		-o libvdso_custom.so
	ln -s libvdso_custom.so linux-vdso.so.custom

# Copy vdso64.so from installed kernel.
libvdso64_1.so:
	sudo cp /lib/modules/$(shell uname -r)/vdso/vdso64.so libvdso64.so
	cat libvdso64.so | sed 's/linux-vdso.so.1/linux-vdso.so.2/g' > libvdso64_1.so
	chmod +x libvdso64_1.so
	ln -s libvdso64_1.so linux-vdso.so.2

main-custom: libvdso_custom.so
	gcc main.c -o main-custom -L. -lvdso_custom -DCUSTOM_VDSO

main-kernel: libvdso64_1.so
	gcc main.c -o main-kernel -L. -lvdso64_1 -DKERNEL_VDSO64

clean:
	rm -f ${TARGET} *.so linux-vdso.so*

