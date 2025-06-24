#include <stdio.h>
#include <string.h>
#include <malloc.h>

#ifdef DEBUG
# define debug(fmt...) do { \
		printf("%s:%d ", __func__, __LINE__); \
		printf(fmt); \
	} while (0)
#else
# define debug(fmt...)
#endif

char icmp_pkg[] = {
"286ed488c72c286ed488c79a08004500006a177d4000400101690aaa06420aaa0618080000003d9500012405725d0000000038390a0000000000101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f303132333435363700000000000000000000000000000000000000000000"
};

int ch2hex(char ch)
{
	switch (ch) {
	case '0':case '1':case '2':case '3':case '4':
	case '5':case '6':case '7':case '8':case '9':
		return (int)(ch - '0');
	case 'a':case 'A': return 10;
	case 'b':case 'B': return 11;
	case 'c':case 'C': return 12;
	case 'd':case 'D': return 13;
	case 'e':case 'E': return 14;
	case 'f':case 'F': return 15;
	default:
		printf("wrong char: %c\n", ch);
		return -1;
	}
}

unsigned char str2hex(char ch2[2])
{
	char c1 = ch2[0];
	char c2 = ch2[1];
	int i1 = ch2hex(c1);
	int i2 = ch2hex(c2);

	return i1 * 16 + i2;
}

unsigned short icmp_pkg_chksum(void *pkg, int len)
{
	int pkg_size = len;
	int sum = 0;
	unsigned short *chkword = pkg, chksum = 0;

	while (pkg_size > 1) {
		sum += *chkword;
		chkword++;
		pkg_size-=2;
		debug("sum = 0x%x, ~sum = 0x%x\n", sum, ~sum);
	}

	if (pkg_size == 1) {
		*(unsigned char *)(&chksum) = *(unsigned char *)chkword;
		sum += chksum;
		debug("sum = 0x%x\n", sum);
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	debug("sum = 0x%x\n", sum);
	chksum = ~sum;
	debug("chksum = 0x%x\n", chksum);
	return chksum;
}

int main(void)
{
	int icmp_pkg_size = strlen(icmp_pkg) / 2;

	int i;
	unsigned char v;
	char *const pc = icmp_pkg;
	char icmp_pkg_[icmp_pkg_size];

	printf("icmp_pkg_size	:	%d\n", icmp_pkg_size);

	for (i = 0; i < icmp_pkg_size; i++) {
		v = str2hex(pc + i * 2);
		icmp_pkg_[i] = v;
	}

	for (i = 0; i < icmp_pkg_size; i++) {
		printf("%02x ", icmp_pkg_[i]);
		if ((i + 1) % 8 == 0) printf(" ");
		if ((i + 1) % 16 == 0) printf("\n");
	}
	printf("\n");

	printf("icmp_pkg_chksum	:	0x%x [0x%x], i=%d\n",
		icmp_pkg_chksum(icmp_pkg_ + 13, 85), *(icmp_pkg_ + 13), i);

	for (i = 13; i < icmp_pkg_size; i++) {
		printf("%02x ", *(icmp_pkg_ + i));
		if ((i + 1) % 8 == 0) printf(" ");
		if ((i + 1) % 16 == 0) printf("\n");
	}
	printf("\n");
	return 0;
}
