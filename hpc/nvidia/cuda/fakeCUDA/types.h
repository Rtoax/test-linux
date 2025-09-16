#pragma once

typedef struct cudaDeviceProp cudaDeviceProp;
typedef enum cudaDeviceAttr cudaDeviceAttr;
typedef enum cudaMemcpyKind cudaMemcpyKind;
typedef enum cudaMemoryAdvise cudaMemoryAdvise;
typedef struct cudaMemLocation cudaMemLocation;

/* TODO: _Float32 may not supported */
typedef _Float32 __half;
