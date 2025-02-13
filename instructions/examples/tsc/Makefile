SHELL = bash
include ../../../tlbuild.mk


TARGETS :=
CFLAGS :=
ARCH_LIB_CPUID :=

TARGETS += rdtsc_user
TARGETS += rdtscp_user
TARGETS += rdtsc_cmp
TARGETS += rdtsc_evil

user: $(TARGETS)

rdtsc_user: rdtsc_user.o
rdtscp_user: rdtscp_user.o
rdtsc_cmp: rdtsc_cmp.o
rdtsc_evil: rdtsc_evil.o

CFLAGS += -g -ggdb
CFLAGS += -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -O3
ifdef STATIC
  CFLAGS += -static
  $(info Defined STATIC)
endif

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test:
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f $(TARGETS) *.o
