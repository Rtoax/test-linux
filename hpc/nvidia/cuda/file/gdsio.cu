// SPDX-License-Identifier: GPL-3.0
/**
 * gdsio - GPUDirect Storage IO
 *
 * This program will be developed to resemble Nvidia's GDSIO tool as closely
 * as possible.
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
#include "../cuda_helpers.h"

const char *version = "v0.0.1";

enum xfer_type {
	XFER_BETWEEN_STORAGE__GPU,
	XFER_BETWEEN_STORAGE__CPU,
	XFER_BETWEEN_STORAGE__CPU__GPU,
	XFER_BETWEEN_STORAGE__CPU__GPU_ASYNC,
	XFER_BETWEEN_STORAGE__PAGECACHE__CPU__GPU,
	XFER_BETWEEN_STORAGE__GPU_ASYNC,
	XFER_BETWEEN_STORAGE__GPU_BATCH,
	XFER_BETWEEN_STORAGE__GPU_BATCH_STREAM,
	XFER_NUM,
};

const char *xfer_name[XFER_NUM] = {
	[XFER_BETWEEN_STORAGE__GPU] = "Storage<->GPU",
	[XFER_BETWEEN_STORAGE__CPU] = "Storage<->CPU",
	[XFER_BETWEEN_STORAGE__CPU__GPU] = "Storage<->CPU<->GPU",
	[XFER_BETWEEN_STORAGE__CPU__GPU_ASYNC] = "Storage<->CPU<->GPU_ASYNC",
	[XFER_BETWEEN_STORAGE__PAGECACHE__CPU__GPU] = "Storage<->PageCache<->CPU<->GPU",
	[XFER_BETWEEN_STORAGE__GPU_ASYNC] = "Storage<->GPU_ASYNC",
	[XFER_BETWEEN_STORAGE__GPU_BATCH] = "Storage<->GPU_BATCH",
	[XFER_BETWEEN_STORAGE__GPU_BATCH_STREAM] = "Storage<->GPU_BATCH_STREAM",
};

enum op_type {
	OP_READ,
	OP_WRITE,
	OP_RANDREAD,
	OP_RANDWRITE,
	OP_NUM,
};

const char *op_name[OP_NUM] = {
	[OP_READ] = "READ",
	[OP_WRITE] = "WRITE",
	[OP_RANDREAD] = "RANDREAD",
	[OP_RANDWRITE] = "RANDWRITE",
};

struct {
	int gpu;
	const char *filename;
	const char *dir;
	int nr_threads;
	size_t size;
	enum xfer_type xtype;
	enum op_type otype;
	bool verify;
} env = {
	.gpu = 0,
	.filename = "gdsio.out",
	.dir = ".",
	.nr_threads = 1,	/* TODO */
	.size = 8192,
	.xtype = XFER_BETWEEN_STORAGE__GPU,
	.otype = OP_WRITE,
	.verify = false,
};

static int fd = -1;
CUfileHandle_t cfHandle = NULL;
CUfileDescr_t cfDescr = {};
unsigned long total_consuming_ns = 0;

const char argp_prog_doc[] =
	"USAGE: [-d <GPU>] [...]\n";

static const struct argp_option opts[] = {
	{ "file", 'f', "FILE", 0, "file name" },
	{ "DIR", 'D', "DIR", 0, "directory name" },
	{ "device", 'd', "DEVICE", 0, "gpu index" },
	{ "size", 's', "SIZE", 0, "file size (K|M|G)" },
	{ "xfer_type", 'x', "XFER_TYPE", 0, "transfer type [0(GPU_DIRECT), 1(CPU_ONLY), 2(CPU_GPU), 3(CPU_ASYNC_GPU), 4(CPU_CACHED_GPU), 5(GPU_DIRECT_ASYNC), 6(GPU_BATCH), 7(GPU_BATCH_STREAM)]" },
	{ "op_type", 'I', "OP_TYPE", 0, "[0(read), 1(write), 2(randread), 3(randwrite)]" },
	{ "verify", 'V', NULL, 1, "verify IO" },
	{ "version", 'v', NULL, 1, "display version" },
	{},
};

void verify_io_devmem(void *devptr, size_t size, uint8_t expect);
void verify_io_cpumem(void *ptr, size_t size, uint8_t expect);

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

unsigned long nsecs(void)
{
	struct timespec start;
	clock_gettime(CLOCK_MONOTONIC, &start);
	return (start.tv_sec * 1E9 + start.tv_nsec);
}

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'f':
		env.filename = arg;
		break;
	case 'D':
		env.dir = arg;
		if (access(env.dir, F_OK)) {
			fprintf(stderr, "ERROR: %s is not exist.\n", env.dir);
			exit(EXIT_FAILURE);
		}
		break;
	case 'd':
		env.gpu = strtoul(arg, NULL, 10);
		break;
	case 's':
		env.size = str2size(arg);
		break;
	case 'x':
		env.xtype = (enum xfer_type)atoi(arg);
		if (env.xtype < XFER_BETWEEN_STORAGE__GPU || env.xtype >= XFER_NUM) {
			fprintf(stderr, "ERROR: bad xfer type value\n");
			exit(EXIT_FAILURE);
		}
		break;
	case 'I':
		env.otype = (enum op_type)atoi(arg);
		if (env.otype < OP_READ || env.otype >= OP_NUM) {
			fprintf(stderr, "ERROR: bad op type value\n");
			exit(EXIT_FAILURE);
		}
		break;
	case 'v':
		printf("gpsio %s\n", version);
		exit(EXIT_SUCCESS);
		break;
	case 'V':
		env.verify = true;
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

void* xfer_between_storage__gpu(void *devPtr, bool alloc, enum op_type otype,
				uint8_t init)
{
	ssize_t bytes = 0;
	bool allocated = false;
	unsigned long start;

	if (!devPtr) {
		CUDA_CHECK_EXIT(cudaMalloc(&devPtr, env.size));
		CUDA_CHECK_EXIT(cudaMemset(devPtr, init, env.size));
		allocated = true;
	}

	start = nsecs();

	switch (otype) {
	case OP_READ:
		bytes = cuFileRead(cfHandle, devPtr, env.size, 0, 0);
		break;
	case OP_WRITE:
		bytes = cuFileWrite(cfHandle, devPtr, env.size, 0, 0);
		break;
	case OP_RANDREAD:
	case OP_RANDWRITE:
	default:
		fprintf(stderr, "WARNING: not support %s yet.\n", op_name[otype]);
		break;
	}

	total_consuming_ns += nsecs() - start;

	if (bytes < 0) {
		fprintf(stderr, "cuFile %s failed\n", op_name[otype]);
	} else {
		printf("%s %ld bytes to the file.\n", op_name[otype], bytes);
	}

	if (env.verify)
		verify_io_devmem(devPtr, env.size, init);

	if (allocated && !alloc) {
		CUDA_CHECK_EXIT(cudaFree(devPtr));
		devPtr = NULL;
	}

	return devPtr;
}

/**
 * @alloc: allocate new memory, need free.
 */
void* xfer_between_storage__cpu(void *ptr, bool alloc, enum op_type otype,
				uint8_t init)
{
	ssize_t bytes = 0;
	bool allocated = false;
	unsigned long start;

	if (!ptr) {
		posix_memalign(&ptr, getpagesize(), env.size);
		memset(ptr, init, env.size);
		allocated = true;
	}

	start = nsecs();

	switch (otype) {
	case OP_READ:
		bytes = read(fd, ptr, env.size);
		break;
	case OP_WRITE:
		bytes = write(fd, ptr, env.size);
		break;
	case OP_RANDREAD:
	case OP_RANDWRITE:
	default:
		fprintf(stderr, "WARNING: not support %s yet.\n", op_name[otype]);
		break;
	}

	total_consuming_ns += nsecs() - start;

	if (bytes < 0) {
		fprintf(stderr, "%s(fd=%d,buf=%p,count=%ld) failed, %m\n",
			op_name[otype], fd, ptr, env.size);
	} else {
		printf("%s %ld bytes to the file.\n", op_name[otype], bytes);
	}

	if (env.verify)
		verify_io_cpumem(ptr, env.size, init);

	if (allocated && !alloc) {
		free(ptr);
		ptr = NULL;
	}
	return ptr;
}

void cufile_init(void)
{
	CUfileError_t status;

	status = cuFileDriverOpen();
	if (status.err != CU_FILE_SUCCESS) {
		fprintf(stderr, "cuFileDriverOpen failed: %s\n",
			cufileop_status_error(status.err));
		exit(EXIT_FAILURE);
	}

	/* Set up GDS descriptor */
	cfDescr.handle.fd = fd;
	cfDescr.type = CU_FILE_HANDLE_TYPE_OPAQUE_FD;

	status = cuFileHandleRegister(&cfHandle, &cfDescr);
	if (status.err != CU_FILE_SUCCESS) {
		fprintf(stderr, "cuFileHandleRegister failed: %s\n",
			cufileop_status_error(status.err));
		exit(EXIT_FAILURE);
	}
}

void cufile_destroy(void)
{
	cuFileHandleDeregister(cfHandle);
}

__global__ void __verify_io_kernel(void *devptr, size_t size, uint8_t expect)
{
	for (size_t i = 0; i < size; i++) {
		uint8_t real = *(uint8_t *)((char *)devptr + i);
		if (real != expect) {
			printf("GPU: Verify IO failed with value 0x%x, expect 0x%x\n",
				real, expect);
		}
	}
}

void verify_io_devmem(void *devptr, size_t size, uint8_t expect)
{
	__verify_io_kernel<<<1, 1>>>(devptr, size, expect);
	cudaDeviceSynchronize();
}

void verify_io_cpumem(void *ptr, size_t size, uint8_t expect)
{
	for (size_t i = 0; i < size; i++) {
		uint8_t real = *(uint8_t *)((char *)ptr + i);
		if (real != expect) {
			printf("CPU: Verify IO failed with value 0x%x, expect 0x%x\n",
				real, expect);
		}
	}
}

int main(int argc, char *argv[])
{
	int err;
	unsigned long start;
	void *host_ptr, *dev_ptr;
	char filepath[256];

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	snprintf(filepath, sizeof(filepath), "%s/%s", env.dir, env.filename);
	fd = open(filepath, O_CREAT | O_RDWR | O_DIRECT, 0664);
	if (fd < 0) {
		fprintf(stderr, "Open %s failed\n", filepath);
		return 1;
	}

	switch (env.xtype) {
	case XFER_BETWEEN_STORAGE__GPU:
		cufile_init();
		xfer_between_storage__gpu(NULL, false, env.otype, 0xAB);
		cufile_destroy();
		break;
	case XFER_BETWEEN_STORAGE__CPU:
		xfer_between_storage__cpu(NULL, false, env.otype, 0xAC);
		break;
	case XFER_BETWEEN_STORAGE__CPU__GPU:
		switch (env.otype) {
		/**
		 * Storage->CPU->GPU
		 */
		case OP_READ:
			host_ptr = xfer_between_storage__cpu(NULL, true, OP_READ, 0xAD);
			CUDA_CHECK_EXIT(cudaMalloc(&dev_ptr, env.size));
			start = nsecs();
			CUDA_CHECK_EXIT(cudaMemcpy(dev_ptr, host_ptr, env.size, cudaMemcpyHostToDevice));
			total_consuming_ns += nsecs() - start;
			free(host_ptr);
			CUDA_CHECK_EXIT(cudaFree(dev_ptr));
			break;
		/**
		 * GPU->CPU->Storage
		 */
		case OP_WRITE:
			CUDA_CHECK_EXIT(cudaMalloc(&dev_ptr, env.size));
			CUDA_CHECK_EXIT(cudaMemset(dev_ptr, 0xAD, env.size));
			posix_memalign(&host_ptr, getpagesize(), env.size);
			start = nsecs();
			CUDA_CHECK_EXIT(cudaMemcpy(host_ptr, dev_ptr, env.size, cudaMemcpyDeviceToHost));
			total_consuming_ns += nsecs() - start;
			xfer_between_storage__cpu(host_ptr, false, OP_WRITE, 0);
			free(host_ptr);
			CUDA_CHECK_EXIT(cudaFree(dev_ptr));
			break;
		case OP_RANDREAD:
		case OP_RANDWRITE:
		default:
			fprintf(stderr, "WARNING: not support %s yet.\n", op_name[env.otype]);
			break;
		}
		break;
	case XFER_BETWEEN_STORAGE__CPU__GPU_ASYNC:
	case XFER_BETWEEN_STORAGE__PAGECACHE__CPU__GPU:
	case XFER_BETWEEN_STORAGE__GPU_ASYNC:
	case XFER_BETWEEN_STORAGE__GPU_BATCH:
	case XFER_BETWEEN_STORAGE__GPU_BATCH_STREAM:
	case XFER_NUM:
	default:
		fprintf(stderr, "WARNING: not support %s yet.\n", xfer_name[env.xtype]);
		break;
	}

	printf("IoType: %s, XferType: %s,", op_name[env.otype], xfer_name[env.xtype]);
	printf(" Threads: %d,", env.nr_threads);
	printf(" DataSetSize: %ld B,", env.size);
	//printf(" OSize: ?,", );
	printf(" Throughput: %f GiB/sec,", env.size * 1.f / total_consuming_ns);
	//printf(" Avg_Latency: ? usecs,");
	printf(" total_time %f secs\n", total_consuming_ns * 1.f / 1E9);

	close(fd);
	return 0;
}
