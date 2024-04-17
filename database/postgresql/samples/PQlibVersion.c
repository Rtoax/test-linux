#include <stdio.h>
#include <libpq-fe.h>

int main(void)
{
	int lib_ver = PQlibVersion();
	printf("Version of PostgreSQL: %d\n", lib_ver);
	return 0;
}
