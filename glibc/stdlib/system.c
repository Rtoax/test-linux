#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int sh_cmd(const char *fmt, ...)
{
	char cmd[1024];
	va_list arg;

	va_start(arg, fmt);
	vsprintf(cmd, fmt, arg);
	printf("DUMP: %s\n", cmd);

	system(cmd);
	va_end(arg);
	return 0;
}

int main(void)
{
	system("mkdir a.dir");

	sh_cmd("cat %s", "/etc/os-release");

	return 0;
}
