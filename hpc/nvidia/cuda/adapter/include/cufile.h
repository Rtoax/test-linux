// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
/******************************************************************************\
 * GPUDirect Storage, cuFile                                                  *
\******************************************************************************/
#ifndef __CUDA_ADAPTER_FILE_H
#define __CUDA_ADAPTER_FILE_H 1

#ifdef __CUFILE_H_
#error "CudaAdapter not allow include origin CUDA cufile.h"
#endif

#include "wrapper_defs.h"

#define CUfileHandle_t CUX(fileHandle_t)
#define CUfileFileHandleType CUX(fileFileHandleType)
/* Linux based fd */
#define CU_FILE_HANDLE_TYPE_OPAQUE_FD CUX(_FILE_HANDLE_TYPE_OPAQUE_FD)
/* Windows based handle (unsupported) */
#define CU_FILE_HANDLE_TYPE_OPAQUE_WIN32 CUX(_FILE_HANDLE_TYPE_OPAQUE_WIN32)
/* Userspace based FS */
#define CU_FILE_HANDLE_TYPE_USERSPACE_FS CUX(_FILE_HANDLE_TYPE_USERSPACE_FS)

#define CUfileDescr_t CUX(fileDescr_t)
#define CUfileError_t CUX(fileError_t)
#define CU_FILE_SUCCESS CUX(_FILE_SUCCESS)

#define CUfileOpError CUX(fileOpError)
/**
 * static inline const char *cufileop_status_error(CUfileOpError status)
 */
#define cufileop_status_error cuX(fileop_status_error)

/**
 * CUfileError_t cuFileDriverOpen(void);
 * LCfileError_t lcFileDriverOpen(void);
 */
#define cuFileDriverOpen cuX(FileDriverOpen)

/**
 * LUCA 3.2.1
 * LCfileError_t lcFileHandleRegister(LCfileHandle_t *fh, LCfileDescr_t *descr);
 */
#define cuFileHandleRegister cuX(FileHandleRegister)
#define cuFileHandleDeregister cuX(FileHandleDeregister)

/**
 * LCfileError_t lcFileBufRegister(const void *devPtr_base, size_t length, int flags);
 */
#define cuFileBufRegister cuX(FileBufRegister)
/**
 * LCfileError_t lcFileBufDeregister(const void *devPtr_base);
 */
#define cuFileBufDeregister cuX(FileBufDeregister)

/**
 * ssize_t cuFileWrite(CUfileHandle_t fh, const void *bufPtr_base, size_t size,
 *                     off_t file_offset, off_t bufPtr_offset);
 */
#define cuFileWrite cuX(FileWrite)
/**
 * ssize_t cuFileRead(CUfileHandle_t fh, void *bufPtr_base, size_t size,
 *                    off_t file_offset, off_t bufPtr_offset);
 */
#define cuFileRead cuX(FileRead)

/**
 * CUDA/HPCC/LUCA all have this macro
 * #define CUFILEOP_STATUS_ENTRIES \
 *     CUFILE_OP(0, LC_FILE_SUCCESS, lcfile success) \
 *     ....
 */
#define CUFILEOP_STATUS_ENTRIES CUX(FILEOP_STATUS_ENTRIES)

#ifdef __USE_HPCC__
# include <hcfile.h>
#elif defined(__USE_LUCA__)
# ifdef LUCA_PHASE_II_PROJECT
#  include <lcfile.h>
# else
#  include <hcfile.h>
# endif
#elif defined(__USE_HIP__)
#endif

#endif
