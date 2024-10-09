#pragma once

#define _section(name) __attribute__((section(name)))

#define INIT_FN_SECTION		".test-linux.init.func"

#define __init		_section(INIT_FN_SECTION)

#define INIT(func) init_call __init_##func __init = func

typedef int (*init_call)(void);

void do_initcalls(void);

extern init_call init_start;
extern init_call init_end;

