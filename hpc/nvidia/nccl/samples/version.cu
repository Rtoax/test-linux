#include <stdio.h>
#include "cuda_compat.h"


int main(void)
{
	ncclResult_t result;
	ncclUniqueId uniqueid;
	int version = 0;

	result = ncclGetVersion(&version);
	printf("version %d, %s\n", version, ncclGetErrorString(result));

	result = ncclGetUniqueId(&uniqueid);
	printf("uniqueid ");
	for (int i = 0; i < sizeof(uniqueid); i++) {
		unsigned char ch = uniqueid.internal[i];
		printf("%02x", ch);
	}
	printf("\n");

	return 0;
}
