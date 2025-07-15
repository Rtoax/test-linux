#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main(void)
{
	int num = acc_get_num_devices(acc_device_default);
	printf("num = %d\n", num);
	return 0;
}
