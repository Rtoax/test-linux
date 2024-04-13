#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <err.h>

int print_err(char *fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	vwarn("vwarn:", arg);
	vwarnx("vwarnx:", arg);
	verr(1, "verr:", arg);
	verrx(1, "verrx:", arg);
	va_end(arg);
}

int main(void)
{
	warn("warn: %d\n", __LINE__);
	warnx("warnx: %s\n", __func__);
	err(1, "err: %s\n", __func__);
	errx(1, "errx: %d\n", __LINE__);

	print_err("v: %s\n", "err+warn");

	return 0;
}
