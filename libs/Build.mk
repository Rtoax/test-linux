# SPDX-License-Identifier: GPL-3.0
include kconfig.mk
include bpf/libbpf.mk
include nvidia/cuda.mk
include amd/rocm.mk
include metax/hpcc.mk
include cestc/luca.mk

target-y += byte
target-y += endian
target-y += file
target-y += fd
target-y += gotoxy goprint
target-y += log
target-y += memshow
target-y += mac
target-y += progress
target-y += str
target-y += ipaddr
target-y += ksym_examples
target-y += proc_examples
target-y += cgroup_examples

libtest-linux-c := libtest-linux-c.so.0.1
libproc-helpers := libproc_helpers.so.0.1.0
libpcie-helpers := libpcie_helpers.so.0.0.1

target-liba-y += libtest-linux-c.a
target-liba-y += libproc_helpers.a
target-liba-y += libksym_helpers.a
target-liba-y += libsocket_helpers.a
target-liba-y += libpthread_helpers.a
target-liba-y += libpcie_helpers.a
target-liba-y += libsched_helpers.a
target-liba-y += libmmap_helpers.a
target-liba-${HAVE_LIBBPF_H} += libtrace_helpers.a
target-liba-y += liboom_helpers.a
target-liba-y += libqcow2_helpers.a
target-liba-${HAVE_LIBBPF_H} += libbpf_helpers.a
target-liba-${HAVE_LIBBPF_H} += libbtf_helpers.a
target-liba-y += libreboot_helpers.a
target-liba-y += libcgroup_helpers.a

target-libso-y += ${libpcie-helpers}
target-libso-y += ${libproc-helpers}
target-libso-y += ${libtest-linux-c}
target-libso-y += libksym_helpers.so
target-libso-y += libsocket_helpers.so
target-libso-y += libpthread_helpers.so
target-libso-y += libsched_helpers.so
target-libso-y += libmmap_helpers.so
target-libso-${HAVE_LIBBPF_H} += libtrace_helpers.so
target-libso-y += liboom_helpers.so
target-libso-y += libqcow2_helpers.so
target-libso-${HAVE_LIBBPF_H} += libbpf_helpers.so
target-libso-${HAVE_LIBBPF_H} += libbtf_helpers.so
target-libso-y += libreboot_helpers.so
target-libso-y += libcgroup_helpers.so

target-nvcc-libso-${HAVE_CUDA} := libcuda_helpers.so
target-nvcc-liba-${HAVE_CUDA} := libcuda_helpers.a
target-hipcc-libso-${HAVE_HIP} := libhip_helpers.so
target-hipcc-liba-${HAVE_HIP} := libhip_helpers.a
target-htcc-libso-${HAVE_HPCC} := libhpcc_helpers.so
target-htcc-liba-${HAVE_HPCC} := libhpcc_helpers.a
target-lscc-libso-${HAVE_LUCA} := libluca_helpers.so
target-lscc-liba-${HAVE_LUCA} := libluca_helpers.a

target-test-y += test1

objs-dynamic += ${OUTPUT}byte.so.o
objs-dynamic += ${OUTPUT}endian.so.o
objs-dynamic += ${OUTPUT}fd.so.o
objs-dynamic += ${OUTPUT}file.so.o
objs-dynamic += ${OUTPUT}log.so.o
objs-dynamic += ${OUTPUT}ipaddr.so.o
objs-dynamic += ${OUTPUT}readline.so.o
objs-dynamic += ${OUTPUT}mac.so.o
objs-dynamic += ${OUTPUT}memshow.so.o
objs-dynamic += ${OUTPUT}progress.so.o
objs-dynamic += ${OUTPUT}str.so.o
objs-dynamic += ${OUTPUT}syscall_helpers.so.o
objs-static := $(patsubst %.so.o,%.a.o,${objs-dynamic})

libtest-linux-c.a-objs := ${objs-static}
${libtest-linux-c}-objs := ${objs-dynamic}
libksym_helpers.a-objs := ${OUTPUT}ksym_helpers.a.o
libksym_helpers.so-objs := ${OUTPUT}ksym_helpers.so.o
libproc_helpers.a-objs := ${OUTPUT}proc_helpers.a.o
${libproc-helpers}-objs := ${OUTPUT}proc_helpers.so.o
libsocket_helpers.a-objs := ${OUTPUT}socket_helpers.a.o
libsocket_helpers.so-objs := ${OUTPUT}socket_helpers.so.o
libpthread_helpers.a-objs := ${OUTPUT}pthread_helpers.a.o
libpthread_helpers.so-objs := ${OUTPUT}pthread_helpers.so.o
libpcie_helpers.a-objs := ${OUTPUT}pcie_helpers.a.o
${libpcie-helpers}-objs := ${OUTPUT}pcie_helpers.so.o
libsched_helpers.a-objs := ${OUTPUT}sched_helpers.a.o
libsched_helpers.so-objs := ${OUTPUT}sched_helpers.so.o
libmmap_helpers.a-objs := ${OUTPUT}mmap_helpers.a.o
libmmap_helpers.so-objs := ${OUTPUT}mmap_helpers.so.o
libtrace_helpers.a-objs := ${OUTPUT}trace_helpers.a.o
libtrace_helpers.so-objs := ${OUTPUT}trace_helpers.so.o
liboom_helpers.a-objs := ${OUTPUT}oom_helpers.a.o
liboom_helpers.so-objs := ${OUTPUT}oom_helpers.so.o
libqcow2_helpers.a-objs := ${OUTPUT}qcow2_helpers.a.o
libqcow2_helpers.so-objs := ${OUTPUT}qcow2_helpers.so.o
libbpf_helpers.a-objs := ${OUTPUT}bpf_helpers.a.o
libbpf_helpers.so-objs := ${OUTPUT}bpf_helpers.so.o
libbtf_helpers.a-objs := ${OUTPUT}btf_helpers.a.o
libbtf_helpers.so-objs := ${OUTPUT}btf_helpers.so.o
libcuda_helpers.so-objs := $(OUTPUT)cuda_helpers.cu.so.o
libcuda_helpers.a-objs := $(OUTPUT)cuda_helpers.cu.a.o
libhip_helpers.so-objs := $(OUTPUT)cuda_helpers.hip.so.o
libhip_helpers.a-objs := $(OUTPUT)cuda_helpers.hip.a.o
libluca_helpers.so-objs := $(OUTPUT)cuda_helpers.luca.so.o
libluca_helpers.a-objs := $(OUTPUT)cuda_helpers.luca.a.o
libhpcc_helpers.so-objs := $(OUTPUT)cuda_helpers.hpcc.so.o
libhpcc_helpers.a-objs := $(OUTPUT)cuda_helpers.hpcc.a.o
libreboot_helpers.a-objs := ${OUTPUT}reboot_helpers.a.o
libreboot_helpers.so-objs := ${OUTPUT}reboot_helpers.so.o
libcgroup_helpers.a-objs := ${OUTPUT}cgroup_helpers.a.o
libcgroup_helpers.so-objs := ${OUTPUT}cgroup_helpers.so.o

ksym_examples-objs := ${OUTPUT}ksym_helpers.o
proc_examples-objs := ${OUTPUT}proc_helpers.o
cgroup_examples-objs := ${OUTPUT}cgroup_helpers.o

CFLAGS += -DTEST_MAIN=1
ifeq (${CONFIG_ANON_VMA_NAME},y)
  $(info INFO: Support CONFIG_ANON_VMA_NAME)
  CFLAGS += -DCONFIG_ANON_VMA_NAME=1
endif

ifdef LINK_LIB
  CFLAGS += -ltest-linux-c
  LDFLAGS += ${libtest-linux-c}
endif

LDFLAGS_SO_${libproc-helpers} := -Wl,--version-script=proc_helpers.map
LDFLAGS_SO_${libpcie-helpers} := -Wl,--version-script=pcie_helpers.map
