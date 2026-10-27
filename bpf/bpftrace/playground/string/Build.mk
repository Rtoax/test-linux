include bpf/bpftrace.mk
include os.mk

subdir-y += error

bpftrace-y += strcat.bt

target-bpf-y += str_concat.bpf.o

# fatal error: 'asm/errno.h' file not found
ifeq ($(call is_os_any_of,ubuntu debian),y)
  CFLAGS_BPF += -I/usr/include/${CPU_ARCH}-linux-gnu
endif
