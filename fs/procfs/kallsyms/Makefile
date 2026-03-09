# SPDX-License-Identifier: GPL-3.0
target-y := ksym_examples
target-libso-y := libksym_helpers.so
target-liba-y := libksym_helpers.a

libksym_helpers.a-objs := ksym_helpers.a.o

include main.mk

ksym_helpers.o: ksym_helpers.h
ksym_helpers.so.o: ksym_helpers.h
ksym_helpers.a.o: ksym_helpers.h
libksym_helpers.so: ksym_helpers.so.o

ksym_examples: ksym_examples.o libksym_helpers.a
