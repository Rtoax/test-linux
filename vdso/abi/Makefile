# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk
include ../vdso.mk

TARGETS :=
TARGETS += main-custom
TARGETS += main-kernel

.PHONY: all
all: ${TARGETS}

VDSO_CFLAGS :=
VDSO_CFLAGS += -nolibc

ifeq ($(shell uname -m),x86_64)
  # See linux:/arch/x86/entry/vdso/Makefile
  VDSO_CFLAGS += -P -C -fpic --share -Wl,-melf_x86_64
  VDSO_CFLAGS += -Wl,-soname=${VDSO_NAME}.custom
  VDSO_CFLAGS += -Wl,--no-undefined -Wl,-zmax-page-size=4096
else ifeq ($(shell uname -m),aarch64)
  # TODO: Update to upstream linux
  VDSO_CFLAGS += -P -C -fpic --share
endif


lib${VDSO_NAME}.custom.so:
	@echo -e "  CC  \033[1m$(@)\033[m"
	$(Q)gcc vdso.c ${VDSO_CFLAGS} -o lib${VDSO_NAME}.custom.so
	$(Q)ln -s lib${VDSO_NAME}.custom.so ${VDSO_NAME}.custom

${VDSO_NAME}:
	@echo -e "  GEN  \033[1m$(@)\033[m"
	$(call gen_vdso_elf)

lib${VDSO_NAME}.copy.so: ${KVDSO64}
	@echo -e "  GEN  \033[1m$(@)\033[m"
	$(Q)cp ${KVDSO64} ${VDSO_NAME}.tmp
	$(Q)cat ${VDSO_NAME}.tmp | sed "s|${VDSO_NAME}|${VDSO_NAME}.copy|g" > lib${VDSO_NAME}.copy.so
	$(Q)chmod +x lib${VDSO_NAME}.copy.so
	$(Q)rm -f ${VDSO_NAME}.tmp
	$(Q)ln -s lib${VDSO_NAME}.copy.so ${VDSO_NAME}.copy

main-custom: lib${VDSO_NAME}.custom.so
	@echo -e "  CC  \033[1m$(@)\033[m"
	$(Q)gcc main.c -o $(@) -L. -l${VDSO_NAME}.custom -DCUSTOM_VDSO
	$(Q)LD_LIBRARY_PATH=. ldd $(@)

main-kernel: lib${VDSO_NAME}.copy.so
	@echo -e "  CC  \033[1m$(@)\033[m"
	$(Q)gcc main.c -o $(@) -L .${VDSO_NAME}.copy -DKERNEL_VDSO64
	$(Q)LD_LIBRARY_PATH=. ldd $(@)

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1m$(TARGETS)\033[m"
	$(Q)rm -f ${TARGETS} *.so *linux-vdso.so*

