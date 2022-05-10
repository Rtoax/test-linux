# Test vDSO linux-vdso.so.1
# Rong Tao 2022.05.10
#
# See linux:/arch/x86/entry/vdso/Makefile
#VDSO_LDFLAGS_vdso.lds = -m elf_x86_64 -soname linux-vdso.so.1 --no-undefined \
#		-z max-page-size=4096 

TARGET := main-custom.out main-kernel.out

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

main-custom.out: libvdso_custom.so
	gcc main.c -o main-custom.out -L. -lvdso_custom -DCUSTOM_VDSO

main-kernel.out: libvdso64_1.so
	gcc main.c -o main-kernel.out -L. -lvdso64_1 -DKERNEL_VDSO64

clean:
	rm -f ${TARGET} *.so linux-vdso.so*

