LIBSECCOMP_HDR = /usr/include/seccomp.h

TARGETS :=

ifneq ($(wildcard $(LIBSECCOMP_HDR)),)
TARGETS += seccomp_rule_add
else
$(warning "ERROR: Must install libseccomp header")
endif


LDFLAGS := -lseccomp

seccomp_rule_add: seccomp_rule_add.o

build: ${TARGETS}

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o
