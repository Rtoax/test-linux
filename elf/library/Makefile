# SPDX-License-Identifier: GPL-3.0
TARGETS :=
TARGETS += libc
TARGETS += main
TARGETS += main-a
TARGETS += main-a-ctors
TARGETS += latency
TARGETS += latency-got latency-got-llc
TARGETS += latency-a latency-a-llc

TARGETS_LIBSO :=
TARGETS_LIBSO += libfoo.so
TARGETS_LIBSO += libadd.so
TARGETS_LIBSO += libcall0.so

TARGETS_LIBA :=
TARGETS_LIBA += libfoo.a
TARGETS_LIBA += libadd.a
TARGETS_LIBA += libcall0.a

CC := gcc

CFLAGS :=
LDFLAGS :=

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

# FIXME: HygonGenuine not support x86-64
ifneq ($(CPU_VENDOR_ID),HygonGenuine)
  CFLAGS += -march=native
else
  $(warning CPU Vendor ID: ${CPU_VENDOR_ID})
endif

include ../../template/main.mk

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
libfoo.a: foo.a.o ctors.a.o
libadd.so: add.so.o
libadd.a: add.a.o
libcall0.so: call0.so.o
libcall0.a: call0.a.o
