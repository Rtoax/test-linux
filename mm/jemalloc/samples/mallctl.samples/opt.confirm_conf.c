#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.confirm_conf (bool) r-
//	Confirm-runtime-options-when-program-starts enabled/disabled. If true, the string specified via --with-malloc-conf,
//	the string pointed to by the global variable malloc_conf, the “name” of the file referenced by the symbolic link
//	named /etc/malloc.conf, and the value of the environment variable MALLOC_CONF, will be printed in order. Then, each
//	option being set will be individually printed. This option is disabled by default.
//	确认运行时选项，当程序运行时候。
//	如果为真，--with-malloc-conf 配置的字符串 /etc/malloc.conf MALLOC_CONF

void get_jemalloc_opt_confirm_conf(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.confirm_conf", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_confirm_conf(&enable);
	printf("enable = %d\n", enable);
}




