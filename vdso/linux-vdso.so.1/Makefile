# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

KVDSO64 := /lib/modules/$(shell uname -r)/vdso/vdso64.so

# Test vDSO linux-vdso.so.1
#
# See linux:/arch/x86/entry/vdso/Makefile
#VDSO_LDFLAGS_vdso.lds = -m elf_x86_64 -soname linux-vdso.so.1 --no-undefined \
#		-z max-page-size=4096 

TARGETS :=
TARGETS += main-custom
TARGETS += main-kernel

ifeq ($(wildcard $(KVDSO64)),)
  $(warning "WARNING: Not found ${KVDSO64}, use dump")
  KVDSO64 := vdso64.so
endif

.PHONY: all
all: ${TARGETS}

VDSO_CFLAGS :=

ifeq ($(shell uname -m),x86_64)
  VDSO_CFLAGS += -P -C -fpic --share -Wl,-melf_x86_64 \
                 -Wl,-soname=linux-vdso.so.custom \
                 -Wl,--no-undefined -Wl,-zmax-page-size=4096
endif
ifeq ($(shell uname -m),aarch64)
  # TODO: Update to upstream linux
  VDSO_CFLAGS += -P -C -fpic --share
endif


#-Wl,-soname=linux-vdso.so.custom
libvdso_custom.so:
	@echo -e "  CC  \033[1m$(@)\033[m"
	$(Q)gcc vdso.c ${VDSO_CFLAGS} -o libvdso_custom.so
	$(Q)ln -s libvdso_custom.so linux-vdso.so.custom

vdso64.so:
	$(Q)../dump.sh

# Copy vdso64.so from installed kernel.
libvdso64_1.so: ${KVDSO64}
	@echo -e "  GEN  \033[1m$(@)\033[m"
	$(Q)sudo cp ${KVDSO64} libvdso64.so
	$(Q)cat libvdso64.so | sed 's/linux-vdso.so.1/linux-vdso.so.2/g' > libvdso64_1.so
	$(Q)chmod +x libvdso64_1.so
	$(Q)ln -s libvdso64_1.so linux-vdso.so.2

main-custom: libvdso_custom.so
	@echo -e "  CC  \033[1m$(@)\033[m"
	$(Q)gcc main.c -o main-custom -L. -lvdso_custom -DCUSTOM_VDSO
	$(Q)LD_LIBRARY_PATH=./ ldd $(@)

main-kernel: libvdso64_1.so
	@echo -e "  CC  \033[1m$(@)\033[m"
	$(Q)gcc main.c -o main-kernel -L. -lvdso64_1 -DKERNEL_VDSO64
	$(Q)LD_LIBRARY_PATH=./ ldd $(@)

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1m$(TARGETS)\033[m"
	$(Q)rm -f ${TARGETS} *.so linux-vdso.so*

