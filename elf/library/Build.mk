# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

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
target-libso-y += libthread.so

target-libso-cpp-y := libadd_cpp.so.0.1

target-liba-y += libfoo.a
target-liba-y += libthread.a
target-liba-y += libadd.a
target-liba-y += libcall0.a

libfoo.a-objs := ${OUTPUT}foo.a.o ${OUTPUT}ctors.a.o
libthread.a-objs := ${OUTPUT}thread.a.o
libadd.a-objs := ${OUTPUT}add.a.o
libcall0.a-objs := ${OUTPUT}call0.a.o

libfoo.so.1.10-objs := ${OUTPUT}foo.so.o ${OUTPUT}ctors.so.o
libadd.so-objs := ${OUTPUT}add.so.o
libadd_cpp.so.0.1-objs := ${OUTPUT}add.cpp.so.o
libthread.so-objs := ${OUTPUT}thread.so.o
libcall0.so-objs := ${OUTPUT}call0.so.o

main-objs := libfoo.so.1.10
main-a-objs := libfoo.a libthread.a
main-a-ctors-objs := libfoo.a libthread.a
latency-objs := libcall0.so
latency-got-objs := libcall0.so
latency-got-llc-objs := libcall0.so
latency-a-objs := libcall0.a
latency-a-llc-objs := libcall0.a

ifdef VERBOSE
  CFLAGS += -Q
  LDFLAGS += -Q
endif

CFLAGS_main := -lfoo -lthread
LDFLAGS_main := libfoo.so libthread.so
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
