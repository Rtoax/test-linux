#include <stdio.h>

int sprint(const char *s)
{
	return printf("%s\n", s);
}

int main(int argc, char *argv[])
{
	const char *name = "Unknown";
	char buf[512];

	if (argc == 0)
		name = "Unknown";
	else
		name = argv[1];

	sprintf(buf, "Hello, %s\n", name);
	sprint(buf);

	return 0;
}
