include os.mk

subdir-y += config
subdir-y += map
subdir-y += string

bpftrace-y += $(shell ls *.bt)

bpf-c += $(shell ls *.bpf.c)
target-bpf-y += $(patsubst %.bpf.c,%.bpf.o,${bpf-c})

# fatal error: 'asm/errno.h' file not found
ifeq ($(call is_os_any_of,ubuntu debian),y)
  CFLAGS_BPF += -I/usr/include/${CPU_ARCH}-linux-gnu
endif
