/**
 * gdsio - GPUDirect Storage IO
 *
 * See also /usr/local/cuda/gds/tools/gdsio
 *
 * Refs:
 * - https://docs.nvidia.com/gpudirect-storage/getting-started/index.html
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "cuda_compat.h"

int main(int argc, char *argv[])
{
	CUfileHandle_t cfHandle;
	CUfileDescr_t cfDescr = {};
	int fd;
	const char *filename = "./testfile.out";

	if (argc > 1) {
		filename = argv[1];
	}

	fprintf(stderr, "Usage: %s [filepath]\n", argv[0]);

	fd = open(filename, O_CREAT | O_RDWR | O_DIRECT, 0664);
	if (fd < 0) {
		fprintf(stderr, "Open %s failed\n", filename);
		return 1;
	}

	/* Set up GDS descriptor */
	cfDescr.handle.fd = fd;
	cfDescr.type = CU_FILE_HANDLE_TYPE_OPAQUE_FD;

	CUfileError_t status = cuFileHandleRegister(&cfHandle, &cfDescr);
	if (status.err != CU_FILE_SUCCESS) {
		fprintf(stderr, "cuFileHandleRegister failed: %s\n",
			cufileop_status_error(status.err));
		close(fd);
		return 1;
	}

	/* Alloc GPU memory and fill GPU memory with data */
	void *devPtr;
	size_t bufferSize = 8192;
	cudaMalloc(&devPtr, bufferSize);
	cudaMemset(devPtr, 0xAB, bufferSize);

	/* Perform the write */
	ssize_t writtenBytes = cuFileWrite(cfHandle, devPtr, bufferSize, 0, 0);
	if (writtenBytes < 0) {
		perror("cuFileWrite failed");
	} else {
		printf("Wrote %ld bytes to the file.\n", writtenBytes);
	}

	/* Clean up */
	cuFileHandleDeregister(cfHandle);
	close(fd);
	cudaFree(devPtr);
	return 0;
}
