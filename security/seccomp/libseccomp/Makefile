LIBSECCOMP_HDR = /usr/include/seccomp.h

target-y :=
target-y += seccomp_arch_resolve_name
target-y += seccomp_rule_add
target-y += seccomp_syscall_resolve_name

ifeq ($(wildcard $(LIBSECCOMP_HDR)),)
  $(warning "ERROR: Must install libseccomp header")
endif

LDFLAGS := -lseccomp

include ../../../template/main.mk

seccomp_rule_add: seccomp_rule_add.o
seccomp_syscall_resolve_name: seccomp_syscall_resolve_name.o
seccomp_arch_resolve_name: seccomp_arch_resolve_name.o
