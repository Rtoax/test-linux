#define __fc_device__	__attribute__((fakecuda_device))

struct st1 {
	int a;
};

__fc_device__ int a = 0;
__fc_device__ struct st1 st1;

__fc_device__ void kernel1(void)
{
}

int main(void)
{
	return 0;
}
