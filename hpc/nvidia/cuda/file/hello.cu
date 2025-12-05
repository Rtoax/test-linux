/**
 * https://docs.nvidia.com/gpudirect-storage/getting-started/index.html
 */
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cuda_runtime.h>
#include <cufile.h>

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
		std::cerr << "cuFileHandleRegister failed: " << status.err << std::endl;
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
