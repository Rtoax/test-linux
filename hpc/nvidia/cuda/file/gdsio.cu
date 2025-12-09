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
#include <pthread.h>
#include "cuda_compat.h"

const char *version = "v0.0.1";

enum xfer_type {
	XFER_STORAGE_TO_GPU,
	XFER_STORAGE_TO_CPU,
	XFER_STORAGE_TO_CPU_TO_GPU,
	XFER_STORAGE_TO_CPU_TO_GPU_ASYNC,
	XFER_STORAGE_TO_PAGECACHE_TO_CPU_TO_GPU,
	XFER_STORAGE_TO_GPU_ASYNC,
	XFER_STORAGE_TO_GPU_BATCH,
	XFER_STORAGE_TO_GPU_BATCH_STREAM,
	XFER_NUM,
};

struct {
	int gpu;
	const char *filename;
	int nr_threads;
	size_t size;
	enum xfer_type xtype;
} env = {
	.gpu = 0,
	.filename = "./testfile.out",
	.nr_threads = 1,	/* TODO */
	.size = 8192,
	.xtype = XFER_STORAGE_TO_GPU,
};

CUfileHandle_t cfHandle;
CUfileDescr_t cfDescr = {};

const char argp_prog_doc[] =
	"USAGE: [-d <GPU>] [...]\n";

static const struct argp_option opts[] = {
	{ "file", 'f', "FILE", 0, "file name" },
	{ "device", 'd', "DEVICE", 0, "gpu index" },
	{ "size", 's', "SIZE", 0, "file size (K|M|G)" },
	{ "xfer_type", 'x', "XFER_TYPE", 0, "transfer type [0(GPU_DIRECT), 1(CPU_ONLY), 2(CPU_GPU), 3(CPU_ASYNC_GPU), 4(CPU_CACHED_GPU), 5(GPU_DIRECT_ASYNC), 6(GPU_BATCH), 7(GPU_BATCH_STREAM)]" },
	{ "verify", 'V', NULL, 1, "verify IO" },
	{ "version", 'v', NULL, 1, "display version" },
	{},
};

static unsigned long str2size(const char *str)
{
	unsigned long size = 0;

	if (!str) {
		errno = EINVAL;
		return 0;
	}

	if (str[0] == '0' && str[1] == 'x')
		size = strtoull(str, NULL, 16);
	else
		size = strtoull(str, NULL, 10);

#define KB 1024UL
#define MB (KB * 1024UL)
#define GB (MB * 1024UL)
	if (strstr(str, "G") || strstr(str, "GB") || strstr(str, "GiB"))
		size *= GB;
	else if (strstr(str, "M") || strstr(str, "MB") || strstr(str, "MiB"))
		size *= MB;
	else if (strstr(str, "K") || strstr(str, "KB") || strstr(str, "KiB"))
		size *= KB;

	return size;
}

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'f':
		env.filename = arg;
		break;
	case 'd':
		env.gpu = strtoul(arg, NULL, 10);
		break;
	case 's':
		env.size = str2size(arg);
		break;
	case 'x':
		env.xtype = (enum xfer_type)atoi(arg);
		if (env.xtype < XFER_STORAGE_TO_GPU || env.xtype >= XFER_NUM) {
			fprintf(stderr, "ERROR: bad xfer type value\n");
			exit(EXIT_FAILURE);
		}
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

void xfer_storage_to_gpu(void)
{
	/* Alloc GPU memory and fill GPU memory with data */
	void *devPtr;
	cudaMalloc(&devPtr, env.size);
	cudaMemset(devPtr, 0xAB, env.size);

	/* Perform the write */
	ssize_t writtenBytes = cuFileWrite(cfHandle, devPtr, env.size, 0, 0);
	if (writtenBytes < 0) {
		perror("cuFileWrite failed");
	} else {
		printf("Wrote %ld bytes to the file.\n", writtenBytes);
	}
	cudaFree(devPtr);
}

int main(int argc, char *argv[])
{
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

	switch (env.xtype) {
	case XFER_STORAGE_TO_GPU:
		xfer_storage_to_gpu();
		break;
	case XFER_STORAGE_TO_CPU:
	case XFER_STORAGE_TO_CPU_TO_GPU:
	case XFER_STORAGE_TO_CPU_TO_GPU_ASYNC:
	case XFER_STORAGE_TO_PAGECACHE_TO_CPU_TO_GPU:
	case XFER_STORAGE_TO_GPU_ASYNC:
	case XFER_STORAGE_TO_GPU_BATCH:
	case XFER_STORAGE_TO_GPU_BATCH_STREAM:
	case XFER_NUM:
	default:
		fprintf(stderr, "WARNING: not support xfer type %d yet.\n", env.xtype);
		break;
	}

	/* Clean up */
	cuFileHandleDeregister(cfHandle);
	close(fd);
	return 0;
}
