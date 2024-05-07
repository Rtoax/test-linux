#include <stdio.h>
#include <malloc.h>

int snprintf_hex(char *buf, size_t size, char *data, size_t len)
{
	int ret = 0;
	size_t i;

	for (i = 0; i < len; i++)
		ret += snprintf(buf + ret, size - ret, "%02x", data[i]);
	return ret;
}

int main(void)
{
	char buf[1024] = {0};
	char data[] = {"hello world.\n"};

	snprintf_hex(buf, 1024, data, sizeof(data));

	printf("%s\n", buf);
	return 0;
}
