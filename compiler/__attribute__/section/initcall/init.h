#pragma once

#define _section(name) __attribute__((section(name)))

#define __init		_section(".test-linux.init.func")
#define __data		_section(".test-linux.init.data")

struct test {
	char name[4];
	int reserve[1];
	int i;
	int j;
} __attribute__((packed));

#define INIT(func) init_call __init_##func __init = func

typedef int (*init_call)(void);

void do_init(void);

extern init_call init_start;
extern init_call init_end;

extern struct test data_start;
extern struct test data_end;
