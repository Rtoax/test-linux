// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
/******************************************************************************\
 *             NCCL: NVIDIA Collective Communication Library                  *
\******************************************************************************/
#ifndef __CUDA_ADAPTER_NCCL_H
#define __CUDA_ADAPTER_NCCL_H 1

#ifdef NCCL_H_
#error "CudaAdapter not allow include origin CUDA nccl.h"
#endif

#include "wrapper_defs.h"

/* /usr/include/nccl.h, /opt/luca/include/hccl.h */
/**
 * HPCC 3.0.0
 * LUCA 3.2.1
 *   struct {
 *     // attributes that users should never touch.
 *     size_t size;
 *     unsigned int magic;
 *     unsigned int version;
 *     // attributes that users are able to customize.
 *     int blocking;
 *   };
 *
 * NCCL 2.27.7
 *   struct ncclConfig_v22700 {
 *     // attributes that users should never touch.
 *     size_t size;
 *     unsigned int magic;
 *     unsigned int version;
 *     // attributes that users are able to customize.
 *     int blocking;
 *     int cgaClusterSize;
 *     int minCTAs;
 *     int maxCTAs;
 *     const char *netName;
 *     int splitShare;
 *     int trafficClass;
 *     const char *commName;
 *     int collnetEnable;
 *     int CTAPolicy;
 *     int shrinkShare;
 *     int nvlsCTAs;
 *   } ncclConfig_t;
 */
#define ncclConfig_t ncclX(Config_t)
/**
 * ROCm rccl already define this in /usr/include/rccl/rccl.h
 */
#ifndef NCCL_CONFIG_INITIALIZER
#define NCCL_CONFIG_INITIALIZER NCCLX(_CONFIG_INITIALIZER)
#endif
#define ncclResult_t ncclX(Result_t)
#define ncclSuccess ncclX(Success) /* 0 */
#ifdef __USE_HPCC__
#define ncclUnhandledCudaError ncclX(UnhandledHpccError) /* 1 */
#elif defined(__USE_LUCA__)
#define ncclUnhandledCudaError ncclX(UnhandledLucaError) /* 1 */
#else /* for HIP and CUDA */
#define ncclUnhandledCudaError ncclX(UnhandledCudaError) /* 1 */
#endif
#define ncclSystemError ncclX(SystemError) /* 2 */
#define ncclInternalError ncclX(InternalError)
#define ncclInvalidArgument ncclX(InvalidArgument)
#define ncclInvalidUsage ncclX(InvalidUsage)
#define ncclRemoteError ncclX(RemoteError)
#define ncclInProgress ncclX(InProgress)
#define ncclNumResults ncclX(NumResults) /* 8 */

/* const char*  ncclGetErrorString(ncclResult_t result); */
#define ncclGetErrorString(result) ncclX(GetErrorString(result))

#define ncclGetVersion(version) ncclX(GetVersion(version))
#define pncclGetVersion(version) pncclX(GetVersion(version))

/**
 * typedef struct {
 *   char internal[128];
 * } ncclUniqueId;
 */
#define ncclUniqueId ncclX(UniqueId)
/**
 * ncclResult_t ncclGetUniqueId(ncclUniqueId* uniqueId);
 */
#define ncclGetUniqueId(id) ncclX(GetUniqueId(id))

/* Communicator */
#define ncclComm_t ncclX(Comm_t)

/**
 * ncclResult_t ncclCommInitRank(ncclComm_t* comm, int nranks, ncclUniqueId commId, int rank);
 */
#define ncclCommInitRank ncclX(CommInitRank)

/**
 * ncclResult_t ncclCommInitRankConfig(ncclComm_t* comm, int nranks,
 *                                     ncclUniqueId commId, int rank,
 *                                     ncclConfig_t* config);
 */
#define ncclCommInitRankConfig ncclX(CommInitRankConfig)

/**
 * ncclResult_t ncclCommInitAll(ncclComm_t* comms, int ndev, const int* devlist);
 */
#define ncclCommInitAll(comm, ndev, devlist) \
	ncclX(CommInitAll(comm, ndev, devlist))
#define ncclCommDestroy ncclX(CommDestroy)

#define ncclGroupStart ncclX(GroupStart)
#define ncclGroupEnd ncclX(GroupEnd)

#define ncclRedOp_t ncclX(RedOp_t)
#define ncclSum ncclX(Sum)
#define ncclProd ncclX(Prod)
#define ncclMax ncclX(Max)
#define ncclMin ncclX(Min)
#define ncclAvg ncclX(Avg)
#define ncclNumOps ncclX(NumOps)
#define ncclMaxRedOp ncclX(MaxRedOp)

#define ncclDataType_t ncclX(DataType_t)
#define ncclInt8 ncclX(Int8)
#define ncclChar ncclX(Char)
#define ncclUint8 ncclX(Uint8)
#define ncclInt32 ncclX(Int32)
#define ncclInt ncclX(Int)
#define ncclUint32 ncclX(Uint32)
#define ncclInt64 ncclX(Int64)
#define ncclUint64 ncclX(Uint64)
#define ncclFloat16 ncclX(Float16)
#define ncclHalf ncclX(Half)
#define ncclFloat32 ncclX(Float32)
#define ncclFloat ncclX(Float)
#define ncclFloat64 ncclX(Float64)
#define ncclDouble ncclX(Double)
#define ncclBfloat16 ncclX(Bfloat16)
#define ncclNumTypes ncclX(NumTypes)

/**
 * ncclResult_t  ncclAllReduce(const void* sendbuff, void* recvbuff, size_t count,
 *                             ncclDataType_t datatype, ncclRedOp_t op,
 *                             ncclComm_t comm, cudaStream_t stream);
 */
#define ncclAllReduce ncclX(AllReduce)

#ifdef __USE_HPCC__
# include <hccl.h>
#elif defined(__USE_LUCA__)
# include <lccl.h>
#elif defined(__USE_HIP__)
# include <rccl/rccl.h>
#endif

#endif
