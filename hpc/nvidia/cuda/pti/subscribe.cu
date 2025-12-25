#include "cuda_compat.h"
#include "cuda_helpers.h"

static void callbackFunc(void *userData, CUpti_CallbackDomain domain,
			 CUpti_CallbackId callbackId,
			 const void *_callbackData)
{
	const CUpti_CallbackData *callbackData = (const CUpti_CallbackData *)_callbackData;

#ifdef DEBUG
	const char *name;
	cuptiGetCallbackName(domain, callbackId, &name);
	printf("userData %p, domain %d, callbackId %d, name %s, callbackData %p\n",
		userData, domain, callbackId, name, callbackData);
#endif

	switch (domain) {
	case CUPTI_CB_DOMAIN_RUNTIME_API:
		if (callbackData->callbackSite == CUPTI_API_ENTER) {
			/* access parameters passed to cudaMemcpy */
			if (callbackId == CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy_v3020) {
				printf("cudaMemcpy(size=%zu, kind=%d)\n",
					((cudaMemcpy_v3020_params *)(callbackData->functionParams))->count,
					((cudaMemcpy_v3020_params *)(callbackData->functionParams))->kind);
			}
			/* access parameters passed to cudaMalloc */
			if (callbackId == CUPTI_RUNTIME_TRACE_CBID_cudaMalloc_v3020) {
#ifdef __LUCA__
# define devPtr	ptr
# define size	bytesize
#endif
				printf("cudaMalloc(devPtr=%p, size=%ld)\n",
					((cudaMalloc_v3020_params *)(callbackData->functionParams))->devPtr,
					((cudaMalloc_v3020_params *)(callbackData->functionParams))->size);
			}
		}
		break;
	default:
		break;
	}
}

__global__ void kernel_1(void)
{
	printf("kernel\n");
}

int main(void)
{
	void *mem;
	CUpti_SubscriberHandle subscriber;

	CUPTI_CHECK_EXIT(cuptiSubscribe(&subscriber, callbackFunc, NULL));
	CUPTI_CHECK_EXIT(cuptiEnableDomain(true, subscriber, CUPTI_CB_DOMAIN_RUNTIME_API));
	CUPTI_CHECK_EXIT(cuptiEnableDomain(true, subscriber, CUPTI_CB_DOMAIN_DRIVER_API));
#ifndef __LUCA__
	CUPTI_CHECK_EXIT(cuptiEnableAllDomains(true, subscriber));
#endif

	cudaMalloc(&mem, 1024);

	kernel_1<<<1, 1>>>();

	CUPTI_CHECK_EXIT(cuptiEnableDomain(false, subscriber, CUPTI_CB_DOMAIN_RUNTIME_API));
	CUPTI_CHECK_EXIT(cuptiEnableDomain(false, subscriber, CUPTI_CB_DOMAIN_DRIVER_API));
#ifndef __LUCA__
	CUPTI_CHECK_EXIT(cuptiEnableAllDomains(false, subscriber));
#endif
	CUPTI_CHECK_EXIT(cuptiUnsubscribe(subscriber));

	cudaFree(mem);
	cudaDeviceSynchronize();
	return 0;
}
