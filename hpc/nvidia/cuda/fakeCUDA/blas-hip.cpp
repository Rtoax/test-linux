#define __USE_HIP__

#define libraryPropertyType	hipLibraryPropertyType
#define MAJOR_VERSION   HIP_LIBRARY_MAJOR_VERSION
#define MINOR_VERSION   HIP_LIBRARY_MINOR_VERSION
#define PATCH_LEVEL     HIP_LIBRARY_PATCH_LEVEL

#define cudaDataType_t	hipblasDatatype_t

/**
 * See /usr/include/hipblas/hipblas.h, hipblasHalf is uint16_t or __half,
 * we select __half to compat with CUDA.
 */
#define HIPBLAS_USE_HIP_HALF

#include "blas.cpp"
