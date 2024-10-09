#ifndef __INIT_H
#define __INIT_H 1

#define _section(StrName) __attribute__((section(StrName)))

#define INIT_FN_SECTION		".rongtao.init.func"

#define _initfn		_section(INIT_FN_SECTION)

#define INIT(func) init_call __initfn_##func _initfn = func

typedef int (*init_call)(void);

void do_initcalls(void);

#endif /*<__INIT_H>*/
