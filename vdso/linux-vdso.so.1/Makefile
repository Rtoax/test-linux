# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

KVDSO64 := /lib/modules/$(shell uname -r)/vdso/vdso64.so

# Test vDSO linux-vdso.so.1
#
# See linux:/arch/x86/entry/vdso/Makefile
#VDSO_LDFLAGS_vdso.lds = -m elf_x86_64 -soname linux-vdso.so.1 --no-undefined \
#		-z max-page-size=4096 

TARGETS :=
TARGETS += main-custom

ifneq ($(wildcard $(KVDSO64)),)
  TARGETS += main-kernel
else
  $(warning "WARNING: Not found ${KVDSO64}")
endif

all: ${TARGETS}

#-Wl,-soname=linux-vdso.so.custom
libvdso_custom.so:
	@echo -e "  CC  \033[1m$(@)\033[m"
	$(Q)gcc vdso.c \
		-P -C \
		-fpic --share \
		-Wl,-melf_x86_64 \
		-Wl,-soname=linux-vdso.so.custom \
		-Wl,--no-undefined \
		-Wl,-zmax-page-size=4096 \
		-o libvdso_custom.so
	$(Q)ln -s libvdso_custom.so linux-vdso.so.custom

# Copy vdso64.so from installed kernel.
libvdso64_1.so:
	@echo -e "  GEN  \033[1m$(@)\033[m"
	$(Q)sudo cp /lib/modules/$(shell uname -r)/vdso/vdso64.so libvdso64.so
	$(Q)cat libvdso64.so | sed 's/linux-vdso.so.1/linux-vdso.so.2/g' > libvdso64_1.so
	$(Q)chmod +x libvdso64_1.so
	$(Q)ln -s libvdso64_1.so linux-vdso.so.2

main-custom: libvdso_custom.so
	@echo -e "  CC  \033[1m$(@)\033[m"
	$(Q)gcc main.c -o main-custom -L. -lvdso_custom -DCUSTOM_VDSO

main-kernel: libvdso64_1.so
	@echo -e "  CC  \033[1m$(@)\033[m"
	$(Q)gcc main.c -o main-kernel -L. -lvdso64_1 -DKERNEL_VDSO64

clean:
	@echo -e "  CLEAN  \033[1m$(TARGETS)\033[m"
	$(Q)rm -f ${TARGETS} *.so linux-vdso.so*

