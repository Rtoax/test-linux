#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

int f1(void)
{
	printf("f1\n");
	return 0;
}

#ifdef __cplusplus
}
#endif


int main(void)
{
	f1();
	return 0;
}
