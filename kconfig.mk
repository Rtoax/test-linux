# SPDX-License-Identifier: GPL-3.0
SHELL := bash

CONFIG_KERNEL ?= /boot/config-$(shell uname -r)

# If don't have kernel config, enable all CONFIG_=y, otherwise, include config
# file.
ifeq ($(wildcard $(CONFIG_KERNEL)),)
  $(warning "WARNING: Not found ${CONFIG_KERNEL}, config all to =y")
  CONFIG_KPROBES=y
  CONFIG_TRACEPOINTS=y
  CONFIG_PERF_EVENTS=y
  CONFIG_HAVE_FENTRY=y
  CONFIG_BPF_LSM=y
  CONFIG_BPF_SYSCALL=y
  CONFIG_BPF_KPROBE_OVERRIDE=
  CONFIG_ARCH_HAS_SYSCALL_WRAPPER=y
  CONFIG_ANON_VMA_NAME=
  CONFIG_LIVEPATCH=
else
  include $(CONFIG_KERNEL)
endif
