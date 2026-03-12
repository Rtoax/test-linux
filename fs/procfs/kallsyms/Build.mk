# SPDX-License-Identifier: GPL-3.0
target-y := ksym_examples
target-libso-y := libksym_helpers.so
target-liba-y := libksym_helpers.a

libksym_helpers.a-objs := ${OUTPUT}ksym_helpers.a.o
libksym_helpers.so-objs := ${OUTPUT}ksym_helpers.so.o
ksym_examples-objs := libksym_helpers.a
