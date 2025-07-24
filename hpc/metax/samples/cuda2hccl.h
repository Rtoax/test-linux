#pragma once
/* Metax has CUDA-compatible APIs */
#define cudaMalloc	hcMalloc
#define cudaFree	hcFree
#define cudaMemset	hcMemset
#define cudaMemcpy	hcMemcpy
#define cudaMemcpyHostToDevice	hcMemcpyHostToDevice
#define cudaMemcpyDeviceToHost	hcMemcpyDeviceToHost
#define cudaEvent_t	hcEvent_t
#define cudaEventCreate	hcEventCreate
#define cudaEventRecord	hcEventRecord
#define cudaEventElapsedTime	hcEventElapsedTime
#define cudaEventSynchronize	hcEventSynchronize
