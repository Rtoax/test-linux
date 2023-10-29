#define __section(section) __attribute__((__section__(section)))

static unsigned int __section(".read.mostly") a = 0xffffffff;

int main(void)
{
	a = 0xff000000;
	return a;
}