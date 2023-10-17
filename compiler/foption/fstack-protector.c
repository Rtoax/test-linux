#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdarg.h>

void __stack_chk_fail(void)
{
	printf("Stack Overflow.\n");
}

int my_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list args;
	int i;

	va_start(args, format);
	i = vsnprintf(str, size, format, args);
	va_end(args);

	return i;
}

int main(void)
{
	char array[10 + 1];
	pid_t tgid = -1;

	/* overflow, __stack_chk_fail() will be called */
	my_snprintf(array, sizeof(array) + 10, "This is tgid overflow %u", tgid);

	return 0;
}
