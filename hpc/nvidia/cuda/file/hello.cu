/**
 * Original code:
 * https://docs.nvidia.com/gpudirect-storage/getting-started/index.html
 *
 * Example 1:
 * The simplest GDSIO command performs a GPU-to-storage write operation. The
 * following command writes 8 KB (-s 8K) of data from GPU 0 (-d 0) to the file.
 * The data is written in two 4 KB blocks (-i 4K), and the -I 1 flag specifies
 * a single iteration.
 *
 *   $ /usr/local/cuda/gds/tools/gdsio -x 0 -d 0 -s 8K -i 4K -f $PWD/testfile.out -I 1
 *
 * Example 2:
 * To compare GPU-Direct transfers (GPUD) with traditional GPU ↔ CPU ↔ Storage
 * transfers, simply switch to the -x 2 mode:
 *
 *   $ /usr/local/cuda/gds/tools/gdsio -x 2 -d 0 -s 8K -i 4K -f $PWD/testfile.out -I 1
 */
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "cuda_compat.h"

int main(void)
{
	CUfileHandle_t cfHandle;
	CUfileDescr_t cfDescr = {};
	const char *filename = "./testfile.out";
	int fd = open(filename, O_CREAT | O_RDWR, 0664);
	if (fd < 0) {
		perror("File open failed");
		return 1;
	}

	// Set up GDS descriptor
	cfDescr.handle.fd = fd;
	cfDescr.type = CU_FILE_HANDLE_TYPE_OPAQUE_FD;
	CUfileError_t status = cuFileHandleRegister(&cfHandle, &cfDescr);
	if (status.err != CU_FILE_SUCCESS) {
		fprintf(stderr, "cuFileHandleRegister failed: %s\n",
			cufileop_status_error(status.err));
		close(fd);
		return 1;
	}

	// Alloc GPU memory and fill GPU memory with data
	void *devPtr;
	size_t bufferSize = 8192;
	cudaMalloc(&devPtr, bufferSize);
	cudaMemset(devPtr, 0xAB, bufferSize);

	// Perform the write
	ssize_t writtenBytes = cuFileWrite(cfHandle, devPtr, bufferSize, 0, 0);
	if (writtenBytes < 0) {
		perror("cuFileWrite failed");
	} else {
		std::cout << "Wrote " << writtenBytes << " bytes to the file." << std::endl;
	}
	// Clean up
	cuFileHandleDeregister(cfHandle);
	close(fd);
	cudaFree(devPtr);
	return 0;
}
