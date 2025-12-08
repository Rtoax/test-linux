/**
 * gdsio - GPUDirect Storage IO
 *
 * See also /usr/local/cuda/gds/tools/gdsio
 *          commit 998aaea56a78 ("cufile: add gpsio.cu")
 *
 * Refs:
 * - https://docs.nvidia.com/gpudirect-storage/getting-started/index.html
 */
#include <argp.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "cuda_compat.h"

const char *version = "v0.0.1";

struct {
	int gpu;
	const char *filename;
} env = {
	.gpu = 0,
	.filename = "./testfile.out",
};

const char argp_prog_doc[] =
	"USAGE: [-d <GPU>] [...]\n";

static const struct argp_option opts[] = {
	{ "file", 'f', "FILE", 0, "file name" },
	{ "device", 'd', "DEVICE", 0, "gpu index" },
	{ "verify", 'V', NULL, 1, "verify IO" },
	{ "version", 'v', NULL, 1, "display version" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'f':
		env.filename = arg;
		break;
	case 'd':
		env.gpu = strtoul(arg, NULL, 10);
		break;
	case 'v':
		printf("gpsio %s\n", version);
		exit(EXIT_SUCCESS);
		break;
	case ARGP_KEY_ARG:
		break;
	case ARGP_KEY_END:
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static const struct argp argp = {
	.options = opts,
	.parser = parse_arg,
	.doc = argp_prog_doc,
};

int main(int argc, char *argv[])
{
	CUfileHandle_t cfHandle;
	CUfileDescr_t cfDescr = {};
	int err, fd;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	fd = open(env.filename, O_CREAT | O_RDWR | O_DIRECT, 0664);
	if (fd < 0) {
		fprintf(stderr, "Open %s failed\n", env.filename);
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
