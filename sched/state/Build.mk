include helpers.mk
include bpf/btf.mk

ifeq (${HAVE_BTF},y)
  CFLAGS += -I. -DHAVE_VMLINUX_H=1
endif

target-y += current
target-y += uninterruptible
target-y += hung
target-y += zombie
target-y += stopped

zombie-objs := ${PROC_HELPERS}
