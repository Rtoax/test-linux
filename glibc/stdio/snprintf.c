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

int test0(void)
{
	char buf[1024] = {0};
	char data[] = {"hello world.\n"};

	snprintf_hex(buf, 1024, data, sizeof(data));

	printf("%s\n", buf);
	return 0;
}

int test1_overflow(void)
{
	int err;
	char buffer[8];

	/**
	 * snprintf not set errno, should return -ERANGE here;
	 */
	err = snprintf(buffer, sizeof(buffer), "%s", "1234567890");
	if (err >= sizeof(buffer))
		fprintf(stderr, "ERANGE.\n");

	printf("%d %s\n", err, buffer);
	return 0;
}

int main(void)
{
	test0();
	test1_overflow();
	return 0;
}
