#include "cuda_compat.h"

static void callbackFunc(void *userData, CUpti_CallbackDomain domain,
			 CUpti_CallbackId callbackId,
			 const void *callbackData)
{
	/* TODO */
	printf("callbackId %d\n", callbackId);
}

__global__ void kernel_1(void)
{
	printf("kernel\n");
}

int main(void)
{
	CUpti_SubscriberHandle subscriber;

	cuptiSubscribe(&subscriber, callbackFunc, NULL);
	cuptiEnableDomain(CUPTI_CB_DOMAIN_RUNTIME_API, subscriber, CUPTI_CB_DOMAIN_FORCE_INT);

	kernel_1<<<1, 1>>>();

	cuptiUnsubscribe(subscriber);

	cudaDeviceSynchronize();
	return 0;
}
