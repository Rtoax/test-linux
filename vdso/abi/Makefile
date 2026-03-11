# SPDX-License-Identifier: GPL-3.0
include vdso.mk

target-prep-y := lib${VDSO_NAME}.custom.so
target-prep-y += lib${VDSO_NAME}.copy.so
target-prep-y += ${VDSO_NAME}
target-prep-y += main-custom main-kernel

include main.mk

lib${VDSO_NAME}.custom.so:
	$(call log_tgt,VDSO,$(@))
	$(Q)gcc vdso.c ${VDSO_CFLAGS} -o lib${VDSO_NAME}.custom.so
	$(Q)ln -s lib${VDSO_NAME}.custom.so ${VDSO_NAME}.custom

lib${VDSO_NAME}.copy.so: ${KVDSO64}
	$(call log_tgt,VDSO,$(@))
	$(Q)cp ${KVDSO64} ${VDSO_NAME}.tmp
	$(Q)cat ${VDSO_NAME}.tmp | sed "s|${VDSO_NAME}|${VDSO_NAME}.copy|g" > lib${VDSO_NAME}.copy.so
	$(Q)chmod +x lib${VDSO_NAME}.copy.so
	$(Q)rm -f ${VDSO_NAME}.tmp
	$(Q)ln -s lib${VDSO_NAME}.copy.so ${VDSO_NAME}.copy

main-custom: lib${VDSO_NAME}.custom.so
	$(call log_tgt,LD,$(@))
	$(Q)gcc main.c -o $(@) -L. -l${VDSO_NAME}.custom -DCUSTOM_VDSO
	$(Q)LD_LIBRARY_PATH=. ldd $(@)

main-kernel: lib${VDSO_NAME}.copy.so
	$(call log_tgt,LD,$(@))
	$(Q)gcc main.c -o $(@) -L .${VDSO_NAME}.copy -DKERNEL_VDSO64
	$(Q)LD_LIBRARY_PATH=. ldd $(@)
