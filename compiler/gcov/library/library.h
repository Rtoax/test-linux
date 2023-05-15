#pragma once

#define __noinline__	__attribute__ ((noinline))

#define DECLARE_FN1(fname)	\
unsigned long __attribute__((noinline)) fn1_##fname(unsigned long a);

#define DEFINE_FN1(fname)	\
unsigned long __attribute__((noinline)) fn1_##fname(unsigned long a) {	\
	return a + 3;	\
}

DECLARE_FN1(branch_1st)
DECLARE_FN1(branch_2nd)
DECLARE_FN1(branch_3rd)
DECLARE_FN1(branch_4th)
DECLARE_FN1(branch_5th)
DECLARE_FN1(branch_6th)
DECLARE_FN1(branch_7th)

int lib_f1(void);

void bubble_sort(int *a, int n);

