#include <uuid/uuid.h>
#include <stdio.h>

void uuid_print(uuid_t u)
{
	for (int i = 0; i < sizeof(uuid_t); i++) {
		printf("%02x", u[i]);
		if (i == 3 || i == 5 || i == 7 || i == 9)
			printf("-");
	}
	printf("\n");
}

int main(void)
{
	uuid_t u1;
	uuid_generate(u1);
	uuid_print(u1);
	return 0;
}
