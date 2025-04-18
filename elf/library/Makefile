# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

TARGETS :=
TARGETS += libc
TARGETS += main
TARGETS += main-a
TARGETS += main-a-ctors
TARGETS += latency
TARGETS += latency-got latency-got-llc
TARGETS += latency-a latency-a-llc

TARGETS_SO :=
TARGETS_SO += libfoo.so
TARGETS_SO += libadd.so
TARGETS_SO += libcall0.so

TARGETS_A :=
TARGETS_A += libfoo.a
TARGETS_A += libadd.a
TARGETS_A += libcall0.a

CC := gcc

CFLAGS :=
LDFLAGS :=

CFLAGS_SO := -shared -fPIC
LDFLAGS_SO := -shared -fPIC

CFLAGS += -DDEBUG=1 -O0 -g -ggdb

# Debian 12 default compile PIE EXEC, Fedora40 default compile no-PIE EXEC.
# Default no-PIE in my case.
include ../pie.mk

ifdef VERBOSE
  CFLAGS += -Q
  LDFLAGS += -Q
endif

CFLAGS_main := -lfoo
LDFLAGS_main := libfoo.so

CFLAGS_latency := -lcall0
LDFLAGS_latency := libcall0.so

CFLAGS_latency-got := -DDIRECT_USE_GOT=1 -lcall0
LDFLAGS_latency-got := libcall0.so
CFLAGS_latency-got-llc := -DDIRECT_USE_GOT=1 -DONLY_TEST_ONE_LLC_LINESIZE=1 -lcall0
LDFLAGS_latency-got-llc := libcall0.so

CFLAGS_latency-a-llc := -DONLY_TEST_ONE_LLC_LINESIZE=1

CFLAGS_main-a-ctors += -DCALL_FUNC_IN_OBJ=1

.PHONY: build
build: ${TARGETS_SO} ${TARGETS_A} ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# FIXME: HygonGenuine not support x86-64
ifneq ($(CPU_VENDOR_ID),HygonGenuine)
  CFLAGS += -march=native
else
  $(warning CPU Vendor ID: ${CPU_VENDOR_ID})
endif

libc: libc.o
main: main.o libfoo.so
main-a: main-a.o libfoo.a
main-a-ctors: main-a-ctors.o libfoo.a
latency: latency.o libcall0.so
latency-got: latency-got.o libcall0.so
latency-got-llc: latency-got-llc.o libcall0.so
latency-a: latency-a.o libcall0.a
latency-a-llc: latency-a-llc.o libcall0.a

libfoo.so: foo.so.o ctors.so.o
libfoo.a: foo.so.o ctors.so.o
libadd.so: add.so.o
libadd.a: add.so.o
libcall0.so: call0.so.o
libcall0.a: call0.so.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

%.so.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) -c $(<) $(CFLAGS_$(*)) $(CFLAGS_SO)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

$(TARGETS_SO): %:
	@echo -e "  SO  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS_SO) $(LDFLAGS_$(*)) -Wl,-soname=$(@)

$(TARGETS_A): %:
	@echo -e "  AR  \033[1;32m$(^) to $(@)\033[m"
	${Q}ar rcs $(@) $(^)

.PHONY: test
test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	${Q}LD_LIBRARY_PATH=$(shell pwd) ./main

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) $(TARGETS_SO) $(TARGETS_A)\033[m"
	${Q}rm -f ${TARGETS} ${TARGETS_SO} ${TARGETS_A} *.o *.so.o
