#include "cuda_compat.h"
#include "cuda_helpers.h"

static void callbackFunc(void *userData, CUpti_CallbackDomain domain,
			 CUpti_CallbackId callbackId,
			 const void *callbackData)
{
	const char *name;
	cuptiGetCallbackName(domain, callbackId, &name);
	printf("userData %p, domain %d, callbackId %d, name %s, callbackData %p\n",
		userData, domain, callbackId, name, callbackData);
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
	CUPTI_CHECK_EXIT(cuptiEnableDomain(true, subscriber, CUPTI_CB_DOMAIN_DRIVER_API));
	CUPTI_CHECK_EXIT(cuptiEnableAllDomains(true, subscriber));

	kernel_1<<<1, 1>>>();

	CUPTI_CHECK_EXIT(cuptiUnsubscribe(subscriber));

	cudaDeviceSynchronize();
	return 0;
}
