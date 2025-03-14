include ../../../tlbuild.mk


LIBSECCOMP_HDR = /usr/include/seccomp.h

TARGETS :=

ifneq ($(wildcard $(LIBSECCOMP_HDR)),)
TARGETS += seccomp_arch_resolve_name
TARGETS += seccomp_rule_add
TARGETS += seccomp_syscall_resolve_name
else
$(warning "ERROR: Must install libseccomp header")
endif


LDFLAGS := -lseccomp

build: ${TARGETS}

seccomp_rule_add: seccomp_rule_add.o
seccomp_syscall_resolve_name: seccomp_syscall_resolve_name.o
seccomp_arch_resolve_name: seccomp_arch_resolve_name.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
