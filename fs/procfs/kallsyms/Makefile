# SPDX-License-Identifier: GPL-3.0
target-y := ksym_examples
target-libso-y := libksym_helpers.so
target-liba-y := libksym_helpers.a

include main.mk

ksym_helpers.o: ksym_helpers.h
ksym_helpers.so.o: ksym_helpers.h
ksym_helpers.a.o: ksym_helpers.h
libksym_helpers.so: ksym_helpers.so.o
libksym_helpers.a: ksym_helpers.a.o

ksym_examples: ksym_examples.o libksym_helpers.a
