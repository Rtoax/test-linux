#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main(void)
{
#define NUM(v)	printf("%s = %d\n", #v, acc_get_num_devices(v));
	NUM(acc_device_default);
	NUM(acc_device_host);
	NUM(acc_device_not_host);
	NUM(acc_device_nvidia);
	NUM(acc_device_radeon);
#undef NUM
	return 0;
}
