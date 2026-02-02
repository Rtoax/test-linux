// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
/******************************************************************************\
 *             NCCL: NVIDIA Collective Communication Library                  *
\******************************************************************************/
#ifndef __CUDA_ADAPTER_NCCL_H
#define __CUDA_ADAPTER_NCCL_H 1

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
#define ncclConfig_t __nccl(Config_t)
/**
 * ROCm rccl already define this in /usr/include/rccl/rccl.h
 */
#ifndef NCCL_CONFIG_INITIALIZER
#define NCCL_CONFIG_INITIALIZER __NCCL(_CONFIG_INITIALIZER)
#endif
#define ncclResult_t __nccl(Result_t)
#define ncclSuccess __nccl(Success) /* 0 */
#ifdef __USE_HPCC__
#define ncclUnhandledCudaError __nccl(UnhandledHpccError) /* 1 */
#elif defined(__USE_LUCA__)
#define ncclUnhandledCudaError __nccl(UnhandledLucaError) /* 1 */
#else /* for HIP and CUDA */
#define ncclUnhandledCudaError __nccl(UnhandledCudaError) /* 1 */
#endif
#define ncclSystemError __nccl(SystemError) /* 2 */
#define ncclInternalError __nccl(InternalError)
#define ncclInvalidArgument __nccl(InvalidArgument)
#define ncclInvalidUsage __nccl(InvalidUsage)
#define ncclRemoteError __nccl(RemoteError)
#define ncclInProgress __nccl(InProgress)
#define ncclNumResults __nccl(NumResults) /* 8 */

/* const char*  ncclGetErrorString(ncclResult_t result); */
#define ncclGetErrorString(result) __nccl(GetErrorString(result))

#define ncclGetVersion(version) __nccl(GetVersion(version))
#define pncclGetVersion(version) __pnccl(GetVersion(version))

/**
 * typedef struct {
 *   char internal[128];
 * } ncclUniqueId;
 */
#define ncclUniqueId __nccl(UniqueId)
/**
 * ncclResult_t ncclGetUniqueId(ncclUniqueId* uniqueId);
 */
#define ncclGetUniqueId(id) __nccl(GetUniqueId(id))

/* Communicator */
#define ncclComm_t __nccl(Comm_t)

/**
 * ncclResult_t ncclCommInitRank(ncclComm_t* comm, int nranks, ncclUniqueId commId, int rank);
 */
#define ncclCommInitRank __nccl(CommInitRank)

/**
 * ncclResult_t ncclCommInitRankConfig(ncclComm_t* comm, int nranks,
 *                                     ncclUniqueId commId, int rank,
 *                                     ncclConfig_t* config);
 */
#define ncclCommInitRankConfig __nccl(CommInitRankConfig)

/**
 * ncclResult_t ncclCommInitAll(ncclComm_t* comms, int ndev, const int* devlist);
 */
#define ncclCommInitAll(comm, ndev, devlist) \
	__nccl(CommInitAll(comm, ndev, devlist))
#define ncclCommDestroy __nccl(CommDestroy)

#define ncclGroupStart __nccl(GroupStart)
#define ncclGroupEnd __nccl(GroupEnd)

#define ncclRedOp_t __nccl(RedOp_t)
#define ncclSum __nccl(Sum)
#define ncclProd __nccl(Prod)
#define ncclMax __nccl(Max)
#define ncclMin __nccl(Min)
#define ncclAvg __nccl(Avg)
#define ncclNumOps __nccl(NumOps)
#define ncclMaxRedOp __nccl(MaxRedOp)

#define ncclDataType_t __nccl(DataType_t)
#define ncclInt8 __nccl(Int8)
#define ncclChar __nccl(Char)
#define ncclUint8 __nccl(Uint8)
#define ncclInt32 __nccl(Int32)
#define ncclInt __nccl(Int)
#define ncclUint32 __nccl(Uint32)
#define ncclInt64 __nccl(Int64)
#define ncclUint64 __nccl(Uint64)
#define ncclFloat16 __nccl(Float16)
#define ncclHalf __nccl(Half)
#define ncclFloat32 __nccl(Float32)
#define ncclFloat __nccl(Float)
#define ncclFloat64 __nccl(Float64)
#define ncclDouble __nccl(Double)
#define ncclBfloat16 __nccl(Bfloat16)
#define ncclNumTypes __nccl(NumTypes)

/**
 * ncclResult_t  ncclAllReduce(const void* sendbuff, void* recvbuff, size_t count,
 *                             ncclDataType_t datatype, ncclRedOp_t op,
 *                             ncclComm_t comm, cudaStream_t stream);
 */
#define ncclAllReduce __nccl(AllReduce)

#endif
