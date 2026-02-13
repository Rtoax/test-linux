#include <stdio.h>
#include <nccl.h>
#include <cuda_runtime.h>
#include "../nccl_helpers.h"

int main(void)
{
	ncclUniqueId uniqueid;
	int version = 0;

	NCCL_CHECK_EXIT(ncclGetVersion(&version));
	printf("NCCL version %d\n", version);

	NCCL_CHECK_EXIT(ncclGetUniqueId(&uniqueid));
	printf("uniqueid ");
	for (int i = 0; i < sizeof(uniqueid); i++) {
		unsigned char ch = uniqueid.internal[i];
		printf("%02x", ch);
	}
	printf("\n");

	return 0;
}
