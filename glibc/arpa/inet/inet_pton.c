#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int tl_inet_pton(int family, const char *strptr, void *addrptr)
{
	if (family == AF_INET) {
		struct in_addr in_val;
		if (inet_aton(strptr, &in_val)) {
			memcpy(addrptr, &in_val, sizeof(struct in_addr));
			return 1;
		}
		return 0;
	}
	errno = EAFNOSUPPORT;
	return -1;
}

int test_inet_pton(const char *p)
{
	int err;
	struct sockaddr_in addr;
	err = inet_pton(AF_INET, p, &addr.sin_addr);
	if (err < 0) {
		fprintf(stderr, "inet_pton %s: %m\n", p);
		return -1;
	}

	printf("%-16s : %u (0x%x)\n", p, addr.sin_addr.s_addr,
		addr.sin_addr.s_addr);

	return addr.sin_addr.s_addr;
}

int main(int argc, char *argv[])
{
	int i;

	struct test {
		const char *p;
		uint32_t expect;
	} tests[] = {
		{ "127.0.0.1", 0x100007f },
		{ "192.168.1.9", 0x901a8c0 },
		{ "255.255.255.255", 0xffffffff },
	};

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		uint32_t addr = (uint32_t)test_inet_pton(tests[i].p);
		if (addr != tests[i].expect) {
			fprintf(stderr, "Test address %s fatal.\n", tests[i].p);
			continue;
		}
	}

	return 0;
}
