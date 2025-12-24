#include "cuda_compat.h"
#include "cuda_helpers.h"

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

	CUPTI_CHECK_EXIT(cuptiSubscribe(&subscriber, callbackFunc, NULL));
	CUPTI_CHECK_EXIT(cuptiEnableDomain(true, subscriber, CUPTI_CB_DOMAIN_RUNTIME_API));

	kernel_1<<<1, 1>>>();

	CUPTI_CHECK_EXIT(cuptiUnsubscribe(subscriber));

	cudaDeviceSynchronize();
	return 0;
}
