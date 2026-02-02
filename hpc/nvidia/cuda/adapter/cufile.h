// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
/******************************************************************************\
 * GPUDirect Storage, cuFile                                                  *
\******************************************************************************/
#ifndef __CUDA_ADAPTER_FILE_H
#define __CUDA_ADAPTER_FILE_H 1

#define CUfileHandle_t __CU(fileHandle_t)
#define CUfileFileHandleType __CU(fileFileHandleType)
/* Linux based fd */
#define CU_FILE_HANDLE_TYPE_OPAQUE_FD __CU(_FILE_HANDLE_TYPE_OPAQUE_FD)
/* Windows based handle (unsupported) */
#define CU_FILE_HANDLE_TYPE_OPAQUE_WIN32 __CU(_FILE_HANDLE_TYPE_OPAQUE_WIN32)
/* Userspace based FS */
#define CU_FILE_HANDLE_TYPE_USERSPACE_FS __CU(_FILE_HANDLE_TYPE_USERSPACE_FS)

#define CUfileDescr_t __CU(fileDescr_t)
#define CUfileError_t __CU(fileError_t)
#define CU_FILE_SUCCESS __CU(_FILE_SUCCESS)

#define CUfileOpError __CU(fileOpError)
/**
 * static inline const char *cufileop_status_error(CUfileOpError status)
 */
#define cufileop_status_error __cu(fileop_status_error)

/**
 * CUfileError_t cuFileDriverOpen(void);
 * LCfileError_t lcFileDriverOpen(void);
 */
#define cuFileDriverOpen __cu(FileDriverOpen)

/**
 * LUCA 3.2.1
 * LCfileError_t lcFileHandleRegister(LCfileHandle_t *fh, LCfileDescr_t *descr);
 */
#define cuFileHandleRegister __cu(FileHandleRegister)
#define cuFileHandleDeregister __cu(FileHandleDeregister)

/**
 * LCfileError_t lcFileBufRegister(const void *devPtr_base, size_t length, int flags);
 */
#define cuFileBufRegister __cu(FileBufRegister)
/**
 * LCfileError_t lcFileBufDeregister(const void *devPtr_base);
 */
#define cuFileBufDeregister __cu(FileBufDeregister)

/**
 * ssize_t cuFileWrite(CUfileHandle_t fh, const void *bufPtr_base, size_t size,
 *                     off_t file_offset, off_t bufPtr_offset);
 */
#define cuFileWrite __cu(FileWrite)
/**
 * ssize_t cuFileRead(CUfileHandle_t fh, void *bufPtr_base, size_t size,
 *                    off_t file_offset, off_t bufPtr_offset);
 */
#define cuFileRead __cu(FileRead)

/**
 * CUDA/HPCC/LUCA all have this macro
 * #define CUFILEOP_STATUS_ENTRIES \
 *     CUFILE_OP(0, LC_FILE_SUCCESS, lcfile success) \
 *     ....
 */
#define CUFILEOP_STATUS_ENTRIES __CU(FILEOP_STATUS_ENTRIES)

#endif
