#pragma once

#define __noinline__	__attribute__ ((noinline))

#define likely(x)    __builtin_expect(!!(x), 1)
#define unlikely(x)  __builtin_expect(!!(x), 0)

int lib_f1(void);
unsigned long lib_layout_test(void);

void bubble_sort(int *a, int n);

void sort_array(void);
