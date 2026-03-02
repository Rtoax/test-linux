// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
/******************************************************************************\
 *             PTI - CUDA Profiling Tools Interface                           *
\******************************************************************************/
#ifndef __CUDA_ADAPTER_CUPTI_RUNTIME_CBID_H
#define __CUDA_ADAPTER_CUPTI_RUNTIME_CBID_H 1

#ifdef _CUPTI_RUNTIME_CBID_H
#error "CudaAdapter not allow include origin CUDA cupti_runtime_cbid.h"
#endif

#include "wrapper_defs.h"

#ifdef __USE_HPCC__
# define CUXcudaX_v(a, b, v) CUXcudaX(a, b ## v)
#elif defined(__USE_LUCA__)
# define CUXcudaX_v(a, b, v) CUXcudaX(a, b)
#elif defined(__USE_HIP__)
# error "Not support HIP yet!!!"
#endif

#define CUpti_runtime_api_trace_cbid CUX(pti_runtime_api_trace_cbid) /* enum */

#define CUPTI_RUNTIME_TRACE_CBID_INVALID CUX(PTI_RUNTIME_TRACE_CBID_INVALID)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDriverGetVersion_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DriverGetVersion, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaRuntimeGetVersion_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, RuntimeGetVersion, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetDeviceCount_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetDeviceCount, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetDeviceProperties_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetDeviceProperties, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaChooseDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ChooseDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetChannelDesc_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetChannelDesc, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaCreateChannelDesc_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, CreateChannelDesc, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaConfigureCall_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ConfigureCall, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaSetupArgument_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, SetupArgument, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetLastError_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetLastError, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaPeekAtLastError_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, PeekAtLastError, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetErrorString_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetErrorString, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunch_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Launch, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaFuncSetCacheConfig_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, FuncSetCacheConfig, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaFuncGetAttributes_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, FuncGetAttributes, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaSetDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, SetDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaSetValidDevices_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, SetValidDevices, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaSetDeviceFlags_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, SetDeviceFlags, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMalloc_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Malloc, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMallocPitch_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MallocPitch, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaFree_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Free, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMallocArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MallocArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaFreeArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, FreeArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMallocHost_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MallocHost, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaFreeHost_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, FreeHost, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaHostAlloc_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, HostAlloc, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaHostGetDevicePointer_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, HostGetDevicePointer, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaHostGetFlags_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, HostGetFlags, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemGetInfo_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemGetInfo, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2D_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2D, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyToArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DToArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2DToArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyFromArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DFromArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2DFromArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyArrayToArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyArrayToArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DArrayToArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2DArrayToArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToSymbol_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyToSymbol, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromSymbol_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyFromSymbol, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToArrayAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyToArrayAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromArrayAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyFromArrayAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2DAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DToArrayAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2DToArrayAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DFromArrayAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2DFromArrayAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToSymbolAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyToSymbolAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromSymbolAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyFromSymbolAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemset_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memset, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemset2D_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memset2D, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemsetAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemsetAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemset2DAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memset2DAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetSymbolAddress_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetSymbolAddress, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetSymbolSize_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetSymbolSize, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaBindTexture_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, BindTexture, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaBindTexture2D_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, BindTexture2D, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaBindTextureToArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, BindTextureToArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaUnbindTexture_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, UnbindTexture, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetTextureAlignmentOffset_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetTextureAlignmentOffset, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetTextureReference_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetTextureReference, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaBindSurfaceToArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, BindSurfaceToArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetSurfaceReference_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetSurfaceReference, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGLSetGLDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GLSetGLDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGLRegisterBufferObject_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GLRegisterBufferObject, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGLMapBufferObject_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GLMapBufferObject, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGLUnmapBufferObject_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GLUnmapBufferObject, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGLUnregisterBufferObject_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GLUnregisterBufferObject, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGLSetBufferObjectMapFlags_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GLSetBufferObjectMapFlags, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGLMapBufferObjectAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GLMapBufferObjectAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGLUnmapBufferObjectAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GLUnmapBufferObjectAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaWGLGetDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, WGLGetDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsGLRegisterImage_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphicsGLRegisterImage, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsGLRegisterBuffer_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphicsGLRegisterBuffer, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsUnregisterResource_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphicsUnregisterResource, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsResourceSetMapFlags_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphicsResourceSetMapFlags, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsMapResources_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphicsMapResources, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsUnmapResources_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphicsUnmapResources, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsResourceGetMappedPointer_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphicsResourceGetMappedPointer, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsSubResourceGetMappedArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphicsSubResourceGetMappedArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaVDPAUGetDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, VDPAUGetDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaVDPAUSetVDPAUDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, VDPAUSetVDPAUDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsVDPAURegisterVideoSurface_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphicsVDPAURegisterVideoSurface, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsVDPAURegisterOutputSurface_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphicsVDPAURegisterOutputSurface, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D11GetDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D11GetDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D11GetDevices_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D11GetDevices, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D11SetDirect3DDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D11SetDirect3DDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsD3D11RegisterResource_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphicsD3D11RegisterResource, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10GetDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10GetDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10GetDevices_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10GetDevices, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10SetDirect3DDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10SetDirect3DDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsD3D10RegisterResource_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphicsD3D10RegisterResource, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10RegisterResource_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10RegisterResource, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10UnregisterResource_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10UnregisterResource, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10MapResources_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10MapResources, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10UnmapResources_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10UnmapResources, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10ResourceSetMapFlags_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10ResourceSetMapFlags, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10ResourceGetSurfaceDimensions_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10ResourceGetSurfaceDimensions, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10ResourceGetMappedArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10ResourceGetMappedArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10ResourceGetMappedPointer_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10ResourceGetMappedPointer, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10ResourceGetMappedSize_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10ResourceGetMappedSize, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10ResourceGetMappedPitch_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10ResourceGetMappedPitch, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9GetDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9GetDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9GetDevices_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9GetDevices, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9SetDirect3DDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9SetDirect3DDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9GetDirect3DDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9GetDirect3DDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsD3D9RegisterResource_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphicsD3D9RegisterResource, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9RegisterResource_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9RegisterResource, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9UnregisterResource_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9UnregisterResource, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9MapResources_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9MapResources, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9UnmapResources_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9UnmapResources, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9ResourceSetMapFlags_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9ResourceSetMapFlags, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9ResourceGetSurfaceDimensions_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9ResourceGetSurfaceDimensions, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9ResourceGetMappedArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9ResourceGetMappedArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9ResourceGetMappedPointer_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9ResourceGetMappedPointer, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9ResourceGetMappedSize_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9ResourceGetMappedSize, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9ResourceGetMappedPitch_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9ResourceGetMappedPitch, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9Begin_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9Begin, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9End_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9End, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9RegisterVertexBuffer_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9RegisterVertexBuffer, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9UnregisterVertexBuffer_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9UnregisterVertexBuffer, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9MapVertexBuffer_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9MapVertexBuffer, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D9UnmapVertexBuffer_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D9UnmapVertexBuffer, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaThreadExit_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ThreadExit, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaSetDoubleForDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, SetDoubleForDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaSetDoubleForHost_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, SetDoubleForHost, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaThreadSynchronize_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ThreadSynchronize, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaThreadGetLimit_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ThreadGetLimit, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaThreadSetLimit_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ThreadSetLimit, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamCreate_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamCreate, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamDestroy_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamDestroy, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamSynchronize_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamSynchronize, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamQuery_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamQuery, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEventCreate_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EventCreate, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEventCreateWithFlags_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EventCreateWithFlags, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEventRecord_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EventRecord, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEventDestroy_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EventDestroy, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEventSynchronize_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EventSynchronize, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEventQuery_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EventQuery, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEventElapsedTime_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EventElapsedTime, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMalloc3D_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Malloc3D, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMalloc3DArray_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Malloc3DArray, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemset3D_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memset3D, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemset3DAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memset3DAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3D_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy3D, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3DAsync_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy3DAsync, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaThreadSetCacheConfig_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ThreadSetCacheConfig, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamWaitEvent_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamWaitEvent, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D11GetDirect3DDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D11GetDirect3DDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaD3D10GetDirect3DDevice_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, D3D10GetDirect3DDevice, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaThreadGetCacheConfig_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ThreadGetCacheConfig, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaPointerGetAttributes_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, PointerGetAttributes, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaHostRegister_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, HostRegister, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaHostUnregister_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, HostUnregister, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceCanAccessPeer_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceCanAccessPeer, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceEnablePeerAccess_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceEnablePeerAccess, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceDisablePeerAccess_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceDisablePeerAccess, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaPeerRegister_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, PeerRegister, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaPeerUnregister_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, PeerUnregister, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaPeerGetDevicePointer_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, PeerGetDevicePointer, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyPeer_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyPeer, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyPeerAsync_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyPeerAsync, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3DPeer_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy3DPeer, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3DPeerAsync_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy3DPeerAsync, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceReset_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceReset, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceSynchronize_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceSynchronize, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetLimit_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGetLimit, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceSetLimit_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceSetLimit, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetCacheConfig_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGetCacheConfig, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceSetCacheConfig_v3020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceSetCacheConfig, _v3020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaProfilerInitialize_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ProfilerInitialize, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaProfilerStart_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ProfilerStart, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaProfilerStop_v4000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ProfilerStop, _v4000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetByPCIBusId_v4010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGetByPCIBusId, _v4010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetPCIBusId_v4010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGetPCIBusId, _v4010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGLGetDevices_v4010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GLGetDevices, _v4010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaIpcGetEventHandle_v4010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, IpcGetEventHandle, _v4010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaIpcOpenEventHandle_v4010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, IpcOpenEventHandle, _v4010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaIpcGetMemHandle_v4010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, IpcGetMemHandle, _v4010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaIpcOpenMemHandle_v4010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, IpcOpenMemHandle, _v4010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaIpcCloseMemHandle_v4010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, IpcCloseMemHandle, _v4010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaArrayGetInfo_v4010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ArrayGetInfo, _v4010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaFuncSetSharedMemConfig_v4020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, FuncSetSharedMemConfig, _v4020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetSharedMemConfig_v4020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGetSharedMemConfig, _v4020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceSetSharedMemConfig_v4020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceSetSharedMemConfig, _v4020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaCreateTextureObject_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, CreateTextureObject, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDestroyTextureObject_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DestroyTextureObject, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetTextureObjectResourceDesc_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetTextureObjectResourceDesc, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetTextureObjectTextureDesc_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetTextureObjectTextureDesc, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaCreateSurfaceObject_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, CreateSurfaceObject, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDestroySurfaceObject_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DestroySurfaceObject, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetSurfaceObjectResourceDesc_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetSurfaceObjectResourceDesc, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMallocMipmappedArray_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MallocMipmappedArray, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetMipmappedArrayLevel_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetMipmappedArrayLevel, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaFreeMipmappedArray_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, FreeMipmappedArray, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaBindTextureToMipmappedArray_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, BindTextureToMipmappedArray, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsResourceGetMappedMipmappedArray_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphicsResourceGetMappedMipmappedArray, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamAddCallback_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamAddCallback, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamCreateWithFlags_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamCreateWithFlags, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetTextureObjectResourceViewDesc_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetTextureObjectResourceViewDesc, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetAttribute_v5000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGetAttribute, _v5000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamDestroy_v5050 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamDestroy, _v5050)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamCreateWithPriority_v5050 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamCreateWithPriority, _v5050)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetPriority_v5050 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetPriority, _v5050)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetFlags_v5050 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetFlags, _v5050)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetStreamPriorityRange_v5050 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGetStreamPriorityRange, _v5050)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMallocManaged_v6000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MallocManaged, _v6000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaOccupancyMaxActiveBlocksPerMultiprocessor_v6000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 OccupancyMaxActiveBlocksPerMultiprocessor, _v6000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamAttachMemAsync_v6000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamAttachMemAsync, _v6000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetErrorName_v6050 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetErrorName, _v6050)
#define CUPTI_RUNTIME_TRACE_CBID_cudaOccupancyMaxActiveBlocksPerMultiprocessor_v6050 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 OccupancyMaxActiveBlocksPerMultiprocessor, _v6050)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunchKernel_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LaunchKernel, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetDeviceFlags_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetDeviceFlags, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunch_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Launch_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunchKernel_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LaunchKernel_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2D_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2D_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToArray_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyToArray_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DToArray_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2DToArray_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromArray_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyFromArray_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DFromArray_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2DFromArray_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyArrayToArray_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyArrayToArray_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DArrayToArray_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2DArrayToArray_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToSymbol_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyToSymbol_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromSymbol_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyFromSymbol_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToArrayAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyToArrayAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromArrayAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyFromArrayAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2DAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DToArrayAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2DToArrayAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy2DFromArrayAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy2DFromArrayAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyToSymbolAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyToSymbolAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyFromSymbolAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyFromSymbolAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemset_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memset_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemset2D_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memset2D_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemsetAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemsetAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemset2DAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memset2DAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetPriority_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetPriority_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetFlags_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetFlags_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamSynchronize_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamSynchronize_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamQuery_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamQuery_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamAttachMemAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamAttachMemAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEventRecord_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EventRecord_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemset3D_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memset3D_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemset3DAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memset3DAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3D_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy3D_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3DAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy3DAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamWaitEvent_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamWaitEvent_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamAddCallback_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamAddCallback_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3DPeer_ptds_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy3DPeer_ptds, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3DPeerAsync_ptsz_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy3DPeerAsync_ptsz, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 OccupancyMaxActiveBlocksPerMultiprocessorWithFlags, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPrefetchAsync_v8000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPrefetchAsync, _v8000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPrefetchAsync_ptsz_v8000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPrefetchAsync_ptsz, _v8000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemAdvise_v8000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemAdvise, _v8000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetP2PAttribute_v8000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGetP2PAttribute, _v8000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsEGLRegisterImage_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphicsEGLRegisterImage, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEGLStreamConsumerConnect_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EGLStreamConsumerConnect, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEGLStreamConsumerDisconnect_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EGLStreamConsumerDisconnect, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEGLStreamConsumerAcquireFrame_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EGLStreamConsumerAcquireFrame, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEGLStreamConsumerReleaseFrame_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EGLStreamConsumerReleaseFrame, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEGLStreamProducerConnect_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EGLStreamProducerConnect, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEGLStreamProducerDisconnect_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EGLStreamProducerDisconnect, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEGLStreamProducerPresentFrame_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EGLStreamProducerPresentFrame, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEGLStreamProducerReturnFrame_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EGLStreamProducerReturnFrame, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphicsResourceGetMappedEglFrame_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphicsResourceGetMappedEglFrame, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemRangeGetAttribute_v8000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemRangeGetAttribute, _v8000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemRangeGetAttributes_v8000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemRangeGetAttributes, _v8000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEGLStreamConsumerConnectWithFlags_v7000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 EGLStreamConsumerConnectWithFlags, _v7000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunchCooperativeKernel_v9000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LaunchCooperativeKernel, _v9000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunchCooperativeKernel_ptsz_v9000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LaunchCooperativeKernel_ptsz, _v9000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEventCreateFromEGLSync_v9000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EventCreateFromEGLSync, _v9000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunchCooperativeKernelMultiDevice_v9000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 LaunchCooperativeKernelMultiDevice, _v9000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaFuncSetAttribute_v9000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, FuncSetAttribute, _v9000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaImportExternalMemory_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ImportExternalMemory, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaExternalMemoryGetMappedBuffer_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ExternalMemoryGetMappedBuffer, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaExternalMemoryGetMappedMipmappedArray_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 ExternalMemoryGetMappedMipmappedArray, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDestroyExternalMemory_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DestroyExternalMemory, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaImportExternalSemaphore_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ImportExternalSemaphore, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaSignalExternalSemaphoresAsync_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, SignalExternalSemaphoresAsync, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaSignalExternalSemaphoresAsync_ptsz_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 SignalExternalSemaphoresAsync_ptsz, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaWaitExternalSemaphoresAsync_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, WaitExternalSemaphoresAsync, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaWaitExternalSemaphoresAsync_ptsz_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 WaitExternalSemaphoresAsync_ptsz, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDestroyExternalSemaphore_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DestroyExternalSemaphore, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunchHostFunc_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LaunchHostFunc, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunchHostFunc_ptsz_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LaunchHostFunc_ptsz, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphCreate_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphCreate, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphKernelNodeGetParams_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphKernelNodeGetParams, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphKernelNodeSetParams_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphKernelNodeSetParams, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddKernelNode_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddKernelNode, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddMemcpyNode_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddMemcpyNode, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphMemcpyNodeGetParams_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphMemcpyNodeGetParams, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphMemcpyNodeSetParams_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphMemcpyNodeSetParams, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddMemsetNode_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddMemsetNode, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphMemsetNodeGetParams_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphMemsetNodeGetParams, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphMemsetNodeSetParams_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphMemsetNodeSetParams, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddHostNode_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddHostNode, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphHostNodeGetParams_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphHostNodeGetParams, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddChildGraphNode_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddChildGraphNode, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphChildGraphNodeGetGraph_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphChildGraphNodeGetGraph, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddEmptyNode_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddEmptyNode, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphClone_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphClone, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphNodeFindInClone_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphNodeFindInClone, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphNodeGetType_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphNodeGetType, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphGetRootNodes_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphGetRootNodes, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphNodeGetDependencies_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphNodeGetDependencies, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphNodeGetDependentNodes_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphNodeGetDependentNodes, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddDependencies_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddDependencies, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphRemoveDependencies_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphRemoveDependencies, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphDestroyNode_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphDestroyNode, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphInstantiate_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphInstantiate, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphLaunch_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphLaunch, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphLaunch_ptsz_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphLaunch_ptsz, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecDestroy_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphExecDestroy, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphDestroy_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphDestroy, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamBeginCapture_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamBeginCapture, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamBeginCapture_ptsz_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamBeginCapture_ptsz, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamIsCapturing_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamIsCapturing, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamIsCapturing_ptsz_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamIsCapturing_ptsz, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamEndCapture_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamEndCapture, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamEndCapture_ptsz_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamEndCapture_ptsz, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphHostNodeSetParams_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphHostNodeSetParams, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphGetNodes_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphGetNodes, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphGetEdges_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphGetEdges, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetCaptureInfo_v10010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetCaptureInfo_v10010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetCaptureInfo_ptsz_v10010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetCaptureInfo_ptsz_v10010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecKernelNodeSetParams_v10010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphExecKernelNodeSetParams_v10010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaThreadExchangeStreamCaptureMode_v10010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 ThreadExchangeStreamCaptureMode_v10010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetNvSciSyncAttributes_v10020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGetNvSciSyncAttributes_v10020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaOccupancyAvailableDynamicSMemPerBlock_v10200 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 OccupancyAvailableDynamicSMemPerBlock_v10200)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamSetFlags_v10200 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamSetFlags_v10200)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamSetFlags_ptsz_v10200 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamSetFlags_ptsz_v10200)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecMemcpyNodeSetParams_v10020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphExecMemcpyNodeSetParams_v10020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecMemsetNodeSetParams_v10020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphExecMemsetNodeSetParams_v10020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecHostNodeSetParams_v10020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphExecHostNodeSetParams_v10020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecUpdate_v10020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphExecUpdate_v10020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetFuncBySymbol_v11000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetFuncBySymbol_v11000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaCtxResetPersistingL2Cache_v11000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, CtxResetPersistingL2Cache_v11000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphKernelNodeCopyAttributes_v11000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphKernelNodeCopyAttributes_v11000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphKernelNodeGetAttribute_v11000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphKernelNodeGetAttribute_v11000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphKernelNodeSetAttribute_v11000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphKernelNodeSetAttribute_v11000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamCopyAttributes_v11000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamCopyAttributes_v11000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamCopyAttributes_ptsz_v11000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamCopyAttributes_ptsz_v11000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetAttribute_v11000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetAttribute_v11000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetAttribute_ptsz_v11000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetAttribute_ptsz_v11000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamSetAttribute_v11000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamSetAttribute_v11000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamSetAttribute_ptsz_v11000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamSetAttribute_ptsz_v11000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetTexture1DLinearMaxWidth_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 DeviceGetTexture1DLinearMaxWidth, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphUpload_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphUpload, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphUpload_ptsz_v10000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphUpload_ptsz, _v10000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddMemcpyNodeToSymbol_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddMemcpyNodeToSymbol, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddMemcpyNodeFromSymbol_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddMemcpyNodeFromSymbol, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddMemcpyNode1D_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddMemcpyNode1D, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphMemcpyNodeSetParamsToSymbol_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphMemcpyNodeSetParamsToSymbol, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphMemcpyNodeSetParamsFromSymbol_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphMemcpyNodeSetParamsFromSymbol, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphMemcpyNodeSetParams1D_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphMemcpyNodeSetParams1D, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecMemcpyNodeSetParamsToSymbol_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphExecMemcpyNodeSetParamsToSymbol, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecMemcpyNodeSetParamsFromSymbol_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphExecMemcpyNodeSetParamsFromSymbol, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecMemcpyNodeSetParams1D_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphExecMemcpyNodeSetParams1D, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaArrayGetSparseProperties_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ArrayGetSparseProperties, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMipmappedArrayGetSparseProperties_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 MipmappedArrayGetSparseProperties, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecChildGraphNodeSetParams_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphExecChildGraphNodeSetParams, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddEventRecordNode_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddEventRecordNode, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphEventRecordNodeGetEvent_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphEventRecordNodeGetEvent, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphEventRecordNodeSetEvent_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphEventRecordNodeSetEvent, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddEventWaitNode_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddEventWaitNode, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphEventWaitNodeGetEvent_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphEventWaitNodeGetEvent, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphEventWaitNodeSetEvent_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphEventWaitNodeSetEvent, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecEventRecordNodeSetEvent_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphExecEventRecordNodeSetEvent, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecEventWaitNodeSetEvent_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphExecEventWaitNodeSetEvent, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEventRecordWithFlags_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EventRecordWithFlags, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEventRecordWithFlags_ptsz_v11010 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EventRecordWithFlags_ptsz, _v11010)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetDefaultMemPool_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGetDefaultMemPool, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMallocAsync_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MallocAsync, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMallocAsync_ptsz_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MallocAsync_ptsz, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaFreeAsync_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, FreeAsync, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaFreeAsync_ptsz_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, FreeAsync_ptsz, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPoolTrimTo_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPoolTrimTo, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPoolSetAttribute_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPoolSetAttribute, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPoolGetAttribute_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPoolGetAttribute, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPoolSetAccess_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPoolSetAccess, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaArrayGetPlane_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ArrayGetPlane, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPoolGetAccess_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPoolGetAccess, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPoolCreate_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPoolCreate, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPoolDestroy_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPoolDestroy, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceSetMemPool_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceSetMemPool, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetMemPool_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGetMemPool, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPoolExportToShareableHandle_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPoolExportToShareableHandle, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPoolImportFromShareableHandle_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 MemPoolImportFromShareableHandle, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPoolExportPointer_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPoolExportPointer, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPoolImportPointer_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPoolImportPointer, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMallocFromPoolAsync_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MallocFromPoolAsync, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMallocFromPoolAsync_ptsz_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MallocFromPoolAsync_ptsz, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaSignalExternalSemaphoresAsync_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, SignalExternalSemaphoresAsync, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaSignalExternalSemaphoresAsync_ptsz_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 SignalExternalSemaphoresAsync_ptsz, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaWaitExternalSemaphoresAsync_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, WaitExternalSemaphoresAsync, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaWaitExternalSemaphoresAsync_ptsz_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 WaitExternalSemaphoresAsync_ptsz, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddExternalSemaphoresSignalNode_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphAddExternalSemaphoresSignalNode, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExternalSemaphoresSignalNodeGetParams_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphExternalSemaphoresSignalNodeGetParams, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExternalSemaphoresSignalNodeSetParams_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphExternalSemaphoresSignalNodeSetParams, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddExternalSemaphoresWaitNode_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphAddExternalSemaphoresWaitNode, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExternalSemaphoresWaitNodeGetParams_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphExternalSemaphoresWaitNodeGetParams, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExternalSemaphoresWaitNodeSetParams_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphExternalSemaphoresWaitNodeSetParams, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecExternalSemaphoresSignalNodeSetParams_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphExecExternalSemaphoresSignalNodeSetParams, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecExternalSemaphoresWaitNodeSetParams_v11020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphExecExternalSemaphoresWaitNodeSetParams, _v11020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceFlushGPUDirectRDMAWrites_v11030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceFlushGPUDirectRDMAWrites, _v11030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetDriverEntryPoint_v11030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetDriverEntryPoint, _v11030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetDriverEntryPoint_ptsz_v11030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetDriverEntryPoint_ptsz, _v11030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphDebugDotPrint_v11030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphDebugDotPrint, _v11030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetCaptureInfo_v2_v11030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetCaptureInfo_v2, _v11030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetCaptureInfo_v2_ptsz_v11030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetCaptureInfo_v2_ptsz, _v11030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamUpdateCaptureDependencies_v11030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 StreamUpdateCaptureDependencies, _v11030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamUpdateCaptureDependencies_ptsz_v11030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 StreamUpdateCaptureDependencies_ptsz, _v11030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaUserObjectCreate_v11030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, UserObjectCreate, _v11030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaUserObjectRetain_v11030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, UserObjectRetain, _v11030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaUserObjectRelease_v11030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, UserObjectRelease, _v11030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphRetainUserObject_v11030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphRetainUserObject, _v11030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphReleaseUserObject_v11030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphReleaseUserObject, _v11030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphInstantiateWithFlags_v11040 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphInstantiateWithFlags, _v11040)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddMemAllocNode_v11040 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddMemAllocNode, _v11040)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphMemAllocNodeGetParams_v11040 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphMemAllocNodeGetParams, _v11040)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddMemFreeNode_v11040 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddMemFreeNode, _v11040)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphMemFreeNodeGetParams_v11040 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphMemFreeNodeGetParams, _v11040)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGraphMemTrim_v11040 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGraphMemTrim, _v11040)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetGraphMemAttribute_v11040 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGetGraphMemAttribute, _v11040)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceSetGraphMemAttribute_v11040 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceSetGraphMemAttribute, _v11040)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphNodeSetEnabled_v11060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphNodeSetEnabled, _v11060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphNodeGetEnabled_v11060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphNodeGetEnabled, _v11060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaArrayGetMemoryRequirements_v11060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, ArrayGetMemoryRequirements, _v11060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMipmappedArrayGetMemoryRequirements_v11060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 MipmappedArrayGetMemoryRequirements, _v11060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunchKernelExC_v11060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LaunchKernelExC, _v11060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLaunchKernelExC_ptsz_v11060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LaunchKernelExC_ptsz, _v11060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaOccupancyMaxPotentialClusterSize_v11070 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 OccupancyMaxPotentialClusterSize, _v11070)
#define CUPTI_RUNTIME_TRACE_CBID_cudaOccupancyMaxActiveClusters_v11070 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, OccupancyMaxActiveClusters, _v11070)
#define CUPTI_RUNTIME_TRACE_CBID_cudaCreateTextureObject_v2_v11080 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, CreateTextureObject_v2, _v11080)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetTextureObjectTextureDesc_v2_v11080 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetTextureObjectTextureDesc_v2, _v11080)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphInstantiateWithParams_v12000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphInstantiateWithParams, _v12000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphInstantiateWithParams_ptsz_v12000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GraphInstantiateWithParams_ptsz, _v12000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecGetFlags_v12000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphExecGetFlags, _v12000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetKernel_v12000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetKernel, _v12000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetDeviceProperties_v12000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetDeviceProperties, _v12000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetId_v12000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetId, _v12000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetId_ptsz_v12000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetId_ptsz, _v12000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphInstantiate_v12000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphInstantiate, _v12000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaInitDevice_v12000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, InitDevice, _v12000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddNode_v12020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddNode, _v12020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphNodeSetParams_v12020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphNodeSetParams, _v12020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphExecNodeSetParams_v12020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphExecNodeSetParams, _v12020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemAdvise_v12020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemAdvise, _v12020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPrefetchAsync_v12020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPrefetchAsync, _v12020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPrefetchAsync_ptsz_v12020 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPrefetchAsync_ptsz, _v12020)
#define CUPTI_RUNTIME_TRACE_CBID_cudaFuncGetName_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, FuncGetName, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamBeginCaptureToGraph_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamBeginCaptureToGraph, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamBeginCaptureToGraph_ptsz_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamBeginCaptureToGraph_ptsz, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphConditionalHandleCreate_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphConditionalHandleCreate, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphGetEdges_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphGetEdges, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphNodeGetDependencies_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphNodeGetDependencies, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphNodeGetDependentNodes_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphNodeGetDependentNodes, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddDependencies_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddDependencies, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphRemoveDependencies_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphRemoveDependencies, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGraphAddNode_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GraphAddNode, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetCaptureInfo_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetCaptureInfo, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetCaptureInfo_ptsz_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetCaptureInfo_ptsz, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamUpdateCaptureDependencies_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 StreamUpdateCaptureDependencies, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamUpdateCaptureDependencies_ptsz_v12030 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 StreamUpdateCaptureDependencies_ptsz, _v12030)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceRegisterAsyncNotification_v12040 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 DeviceRegisterAsyncNotification, _v12040)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceUnregisterAsyncNotification_v12040 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 DeviceUnregisterAsyncNotification, _v12040)
#define CUPTI_RUNTIME_TRACE_CBID_cudaFuncGetParamInfo_v12040 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, FuncGetParamInfo, _v12040)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetDriverEntryPointByVersion_v12050 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetDriverEntryPointByVersion, _v12050)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetDriverEntryPointByVersion_ptsz_v12050 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 GetDriverEntryPointByVersion_ptsz, _v12050)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLibraryLoadData_v12060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LibraryLoadData, _v12060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLibraryLoadFromFile_v12060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LibraryLoadFromFile, _v12060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLibraryUnload_v12060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LibraryUnload, _v12060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLibraryGetKernel_v12060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LibraryGetKernel, _v12060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLibraryGetGlobal_v12060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LibraryGetGlobal, _v12060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLibraryGetManaged_v12060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LibraryGetManaged, _v12060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLibraryGetUnifiedFunction_v12060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LibraryGetUnifiedFunction, _v12060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLibraryGetKernelCount_v12060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LibraryGetKernelCount, _v12060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLibraryEnumerateKernels_v12060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LibraryEnumerateKernels, _v12060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaKernelSetAttributeForDevice_v12060 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, KernelSetAttributeForDevice, _v12060)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetDevice_v12080 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetDevice, _v12080)
#define CUPTI_RUNTIME_TRACE_CBID_cudaStreamGetDevice_ptsz_v12080 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, StreamGetDevice_ptsz, _v12080)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyBatchAsync_v12080 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyBatchAsync, _v12080)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyBatchAsync_ptsz_v12080 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyBatchAsync_ptsz, _v12080)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3DBatchAsync_v12080 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy3DBatchAsync, _v12080)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3DBatchAsync_ptsz_v12080 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy3DBatchAsync_ptsz, _v12080)
#define CUPTI_RUNTIME_TRACE_CBID_cudaEventElapsedTime_v12080 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, EventElapsedTime, _v12080)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPrefetchBatchAsync_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPrefetchBatchAsync, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemPrefetchBatchAsync_ptsz_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemPrefetchBatchAsync_ptsz, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemDiscardBatchAsync_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemDiscardBatchAsync, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemDiscardBatchAsync_ptsz_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemDiscardBatchAsync_ptsz, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemDiscardAndPrefetchBatchAsync_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 MemDiscardAndPrefetchBatchAsync, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemDiscardAndPrefetchBatchAsync_ptsz_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 MemDiscardAndPrefetchBatchAsync_ptsz, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaGetExportTable_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, GetExportTable, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaRegisterFatBinary_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, RegisterFatBinary, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaRegisterFatBinaryEnd_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, RegisterFatBinaryEnd, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaUnregisterFatBinary_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, UnregisterFatBinary, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaRegisterVar_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, RegisterVar, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaRegisterHostVar_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, RegisterHostVar, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaRegisterFunction_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, RegisterFunction, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaRegisterManagedVar_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, RegisterManagedVar, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaInitModule_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, InitModule, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaPushCallConfiguration_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, PushCallConfiguration, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaPopCallConfiguration_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, PopCallConfiguration, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaGetKernel_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, GetKernel, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaLaunchKernel_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, LaunchKernel, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaLaunchKernel_ptsz_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, LaunchKernel_ptsz, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaRegisterUnifiedTable_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, RegisterUnifiedTable, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID___cudaGetProcAddress_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID___, GetProcAddress, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyBatchAsync_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyBatchAsync, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpyBatchAsync_ptsz_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemcpyBatchAsync_ptsz, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3DBatchAsync_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy3DBatchAsync, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemcpy3DBatchAsync_ptsz_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, Memcpy3DBatchAsync_ptsz, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLogsRegisterCallback_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LogsRegisterCallback, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLogsUnregisterCallback_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LogsUnregisterCallback, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLogsCurrent_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LogsCurrent, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLogsDumpToFile_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LogsDumpToFile, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaLogsDumpToMemory_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, LogsDumpToMemory, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemGetDefaultMemPool_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemGetDefaultMemPool, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemGetMemPool_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemGetMemPool, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaMemSetMemPool_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, MemSetMemPool, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetHostAtomicCapabilities_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, \
		 DeviceGetHostAtomicCapabilities, _v13000)
#define CUPTI_RUNTIME_TRACE_CBID_cudaDeviceGetP2PAtomicCapabilities_v13000 \
	CUXcudaX_v(PTI_RUNTIME_TRACE_CBID_, DeviceGetP2PAtomicCapabilities, _v13000)

#endif
