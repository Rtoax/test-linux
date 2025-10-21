# SPDX-License-Identifier: GPL-3.0
target-y := libc
target-y += main
target-y += main-a
target-y += main-a-ctors
target-y += latency
target-y += latency-got latency-got-llc
target-y += latency-a latency-a-llc

target-libso-y := libfoo.so.1.10
target-libso-y += libadd.so
target-libso-y += libcall0.so

target-libso-cpp-y := libadd_cpp.so.0.1

target-liba-y := libfoo.a
target-liba-y += libadd.a
target-liba-y += libcall0.a

ifdef VERBOSE
  CFLAGS += -Q
  LDFLAGS += -Q
endif

CFLAGS_main := -lfoo
LDFLAGS_main := libfoo.so
# Note: Add a directory to the runtime library search path.
# $ readelf -d main
# 0x000000000000000f (RPATH)              Library rpath: [/home/rongtao/Git/tst-linux/elf/library]
LDFLAGS_main += -Wl,-rpath,$(shell pwd)

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
main: main.o libfoo.so.1.10
main-a: main-a.o libfoo.a
main-a-ctors: main-a-ctors.o libfoo.a
latency: latency.o libcall0.so
latency-got: latency-got.o libcall0.so
latency-got-llc: latency-got-llc.o libcall0.so
latency-a: latency-a.o libcall0.a
latency-a-llc: latency-a-llc.o libcall0.a

libfoo.so.1.10: foo.so.o ctors.so.o
libfoo.a: foo.a.o ctors.a.o
libadd.so: add.so.o
libadd_cpp.so.0.1: add.cpp.so.o
libadd.a: add.a.o
libcall0.so: call0.so.o
libcall0.a: call0.a.o
