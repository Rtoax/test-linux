# SPDX-License-Identifier: GPL-3.0
include ../vdso.mk

VDSO_CFLAGS :=
VDSO_CFLAGS += -nolibc

ifeq ($(shell uname -m),x86_64)
  # See linux:/arch/x86/entry/vdso/Makefile
  VDSO_CFLAGS += -P -C --shared -Wl,-melf_x86_64
  VDSO_CFLAGS += -Wl,-soname=${VDSO_NAME}.custom
  VDSO_CFLAGS += -Wl,-shared -Wl,--hash-style=both -Wl,--build-id=sha1 -Wl,--no-undefined
  VDSO_CFLAGS += -Wl,-Bsymbolic -Wl,-znoexecstack
  VDSO_CFLAGS += -Wl,--no-undefined -Wl,-zmax-page-size=4096
  VDSO_CFLAGS += -mcmodel=small -fPIC -O2 -fasynchronous-unwind-tables -m64
  VDSO_CFLAGS += -fno-stack-protector -fno-omit-frame-pointer -foptimize-sibling-calls
else ifeq ($(shell uname -m),aarch64)
  # See linux:/arch/arm64/kernel/vdso/Makefile
  VDSO_CFLAGS += -shared
  VDSO_CFLAGS += -Wl,-soname=${VDSO_NAME}.custom
  VDSO_CFLAGS += -Wl,-Bsymbolic -Wl,--build-id=sha1
  VDSO_CFLAGS += -fno-common -fno-builtin -fno-stack-protector -ffixed-x18
  VDSO_CFLAGS += -O2 -mcmodel=tiny -fasynchronous-unwind-tables
endif

targets-prep := lib${VDSO_NAME}.custom.so
targets-prep += lib${VDSO_NAME}.copy.so
targets-prep += ${VDSO_NAME}
targets-prep += main-custom main-kernel

include ../../template/main.mk

lib${VDSO_NAME}.custom.so:
	$(call log_tgt_exe,VDSO,,$(@))
	$(Q)gcc vdso.c ${VDSO_CFLAGS} -o lib${VDSO_NAME}.custom.so
	$(Q)ln -s lib${VDSO_NAME}.custom.so ${VDSO_NAME}.custom

${VDSO_NAME}:
	$(call log_tgt_exe,VDSO,,$(@))
	$(call gen_vdso_elf)

lib${VDSO_NAME}.copy.so: ${KVDSO64}
	$(call log_tgt_exe,VDSO,,$(@))
	$(Q)cp ${KVDSO64} ${VDSO_NAME}.tmp
	$(Q)cat ${VDSO_NAME}.tmp | sed "s|${VDSO_NAME}|${VDSO_NAME}.copy|g" > lib${VDSO_NAME}.copy.so
	$(Q)chmod +x lib${VDSO_NAME}.copy.so
	$(Q)rm -f ${VDSO_NAME}.tmp
	$(Q)ln -s lib${VDSO_NAME}.copy.so ${VDSO_NAME}.copy

main-custom: lib${VDSO_NAME}.custom.so
	$(call log_tgt_exe,LD,,$(@))
	$(Q)gcc main.c -o $(@) -L. -l${VDSO_NAME}.custom -DCUSTOM_VDSO
	$(Q)LD_LIBRARY_PATH=. ldd $(@)

main-kernel: lib${VDSO_NAME}.copy.so
	$(call log_tgt_exe,LD,,$(@))
	$(Q)gcc main.c -o $(@) -L .${VDSO_NAME}.copy -DKERNEL_VDSO64
	$(Q)LD_LIBRARY_PATH=. ldd $(@)
