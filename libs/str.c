#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>

void *memcpy_c(void *dest, const void *src, size_t n)
{
	char *d = (char *)dest;
	const char *s = (const char *)src;
	while (n--)
		*d++ = *s++;
	return dest;
}

char *strcaseswap(char *str, ssize_t len)
{
	char *c = str;
	while (*c) {
		*c = (*c)&0xdf;
		c++;
	}
	return str;
}

char *vstrjoint(char *dst, const char *fmt, ...) __attribute__((__format__(printf, 2, 3)));
char *vstrjoint(char *dst, const char *fmt, ...)
{
	if (dst == NULL || fmt == NULL)
		return NULL;
	va_list args;
	va_start(args, fmt);
	vsprintf(dst, fmt, args);
	va_end(args);
	return (char*)dst;
}

const char *vstrcat(int nstr, ...)
{
	int i;
	va_list va;
	static char S[1024] = {0};

	memset(S, 0x00, sizeof(S));

	va_start(va, nstr);
	for (i = 0; i < nstr; i++) {
		char *s = va_arg(va, char*);
		strcat(S, s);
	}
	va_end(va);
	return (char *)S;
}

const char *vstrcat_r(char buf[], int nstr, ...)
{
	int i;
	va_list va;

	va_start(va, nstr);
	for (i = 0; i < nstr; i++) {
		char *s = va_arg(va, char *);
		strcat(buf, s);
	}
	va_end(va);
	return (char *)buf;
}

#ifdef TEST
int main(void)
{
	char buf[1024];
	char str[] = {"AbasdADDadLJ"};
	printf("%s->%s\n", str, strcaseswap(str, strlen(str)));

	char cmd[256];
	memset(cmd, 0, 256);
	vstrjoint(cmd, "rongtao: %d", 123);
	printf("cmd: %s\n", cmd);

	printf("%s\n", vstrcat(3, "rongtao", "is", "me"));
	printf("%s\n", vstrcat_r(buf, 3, "rongtao", "is", "me"));

	return 0;
}
#endif
