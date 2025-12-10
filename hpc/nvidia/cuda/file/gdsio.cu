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
#include <assert.h>
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
	bool bufregister;
} env = {
	.gpu = 0,
	.filename = "gdsio.out",
	.dir = ".",
	.nr_threads = 1,	/* TODO */
	.size = 8192,
	.xtype = XFER_BETWEEN_STORAGE__GPU,
	.otype = OP_WRITE,
	.verify = false,
	.bufregister = true,
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
	{ "nthreads", 'w', "NTHREADS", 0, "number of threads for a job" },
	{ "xfer_type", 'x', "XFER_TYPE", 0, "transfer type [0(GPU_DIRECT), 1(CPU_ONLY), 2(CPU_GPU), 3(CPU_ASYNC_GPU), 4(CPU_CACHED_GPU), 5(GPU_DIRECT_ASYNC), 6(GPU_BATCH), 7(GPU_BATCH_STREAM)]" },
	{ "op_type", 'I', "OP_TYPE", 0, "[0(read), 1(write), 2(randread), 3(randwrite)]" },
	{ "verify", 'V', NULL, 1, "verify IO" },
	{ "bufregister", 'b', NULL, 1, "skip bufregister" },
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
		if (env.size % getpagesize()) {
			fprintf(stderr, "ERROR: size must page aliged.\n");
			exit(EXIT_FAILURE);
		}
		break;
	case 'w':
		env.nr_threads = atoi(arg);
		if (env.nr_threads <= 0) {
			fprintf(stderr, "ERROR: bad number of threads\n");
			exit(EXIT_FAILURE);
		}
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
	case 'b':
		env.bufregister = false;
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

struct thread_arg {
	int idx;
	void *mem;
	size_t size;
	enum op_type otype;
	off_t file_offset;
	off_t mem_offset;
};

static pthread_t *threads;
static struct thread_arg *thread_args;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/**
 * Distribute memory @mem evenly among each thread.
 */
void multithread_create(void *mem, enum op_type otype,
			void *(*thread_fn)(void *targ))
{
	threads = (pthread_t *)malloc(sizeof(pthread_t) * env.nr_threads);
	assert(threads && "Malloc fatal");
	thread_args = (struct thread_arg *)malloc(sizeof(struct thread_arg) * env.nr_threads);
	assert(thread_args && "Malloc fatal");

	for (int i = 0; i < env.nr_threads; i++) {
		size_t tsize = env.size / env.nr_threads;
		thread_args[i].idx = i;
		thread_args[i].mem = mem;
		thread_args[i].size = tsize;
		thread_args[i].otype = otype;
		thread_args[i].file_offset = tsize * i;
		thread_args[i].mem_offset = tsize * i;

		pthread_create(&threads[i], NULL, thread_fn, &thread_args[i]);
#ifdef DEBUG
		fprintf(stderr, "Create thread %d\n", i);
#endif
	}

	/* Make sure all child threads are running */
	sleep(1);
}

void multithread_execute(void)
{
	unsigned long start = nsecs();

	/* Wakeup all threads */
	pthread_cond_broadcast(&cond);
#ifdef DEBUG
	fprintf(stderr, "Wakeup all threads\n");
#endif

	for (int i = 0; i < env.nr_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	total_consuming_ns += nsecs() - start;
}

void multithread_destroy(void)
{
	free(threads);
	free(thread_args);
}

void *thread_cufile(void *targ)
{
	struct thread_arg *arg = (struct thread_arg *)targ;
	ssize_t bytes = 0;
	void *devPtr = arg->mem;
	enum op_type otype = arg->otype;
	size_t size = arg->size;
	off_t foff = arg->file_offset;
	off_t doff = arg->mem_offset;

	pthread_mutex_lock(&mutex);
#ifdef DEBUG
	fprintf(stderr, "Thread %d waiting.\n", arg->idx);
#endif
	pthread_cond_wait(&cond, &mutex);

	switch (otype) {
	case OP_READ:
		bytes = cuFileRead(cfHandle, devPtr, size, foff, doff);
		break;
	case OP_WRITE:
		bytes = cuFileWrite(cfHandle, devPtr, size, foff, doff);
		break;
	case OP_RANDREAD:
	case OP_RANDWRITE:
	default:
		fprintf(stderr, "WARNING: not support %s yet.\n", op_name[otype]);
		break;
	}

	if (bytes < 0) {
		fprintf(stderr, "ERROR: GPU %s(fd=%d,buf=%p,count=%ld) failed, %m\n",
			op_name[otype], fd, devPtr, env.size);
	}

	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}

void* xfer_between_storage__gpu(void *devPtr, bool alloc, enum op_type otype,
				uint8_t init)
{
	bool allocated = false;

	if (!devPtr) {
		CUDA_CHECK_EXIT(cudaMalloc(&devPtr, env.size));
		CUDA_CHECK_EXIT(cudaMemset(devPtr, init, env.size));
		allocated = true;
	}

	if (env.bufregister)
		CUFILE_CHECK_EXIT(cuFileBufRegister(devPtr, env.size, 0));

	multithread_create(devPtr, otype, thread_cufile);
	multithread_execute();
	multithread_destroy();

	if (env.verify)
		verify_io_devmem(devPtr, env.size, init);

	if (env.bufregister)
		CUFILE_CHECK_EXIT(cuFileBufDeregister(devPtr));

	if (allocated && !alloc) {
		CUDA_CHECK_EXIT(cudaFree(devPtr));
		devPtr = NULL;
	}

	return devPtr;
}

/**
 * read(2) from a specified postion
 */
ssize_t pos_read(int fd, off_t pos, void *buf, size_t count)
{
	off_t cur_pos = lseek(fd, 0, SEEK_CUR);
	lseek(fd, pos, SEEK_SET);
	ssize_t bytes = read(fd, buf, count);
	lseek(fd, cur_pos, SEEK_SET);
	return bytes;
}

/**
 * write(2) to a specified postion
 */
ssize_t pos_write(int fd, off_t pos, void *buf, size_t count)
{
	off_t cur_pos = lseek(fd, 0, SEEK_CUR);
	lseek(fd, pos, SEEK_SET);
	ssize_t bytes = write(fd, buf, count);
	lseek(fd, cur_pos, SEEK_SET);
	return bytes;
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
		bytes = pos_read(fd, 0, ptr, env.size);
		break;
	case OP_WRITE:
		bytes = pos_write(fd, 0, ptr, env.size);
		break;
	case OP_RANDREAD:
	case OP_RANDWRITE:
	default:
		fprintf(stderr, "WARNING: not support %s yet.\n", op_name[otype]);
		break;
	}

	total_consuming_ns += nsecs() - start;

	if (bytes < 0) {
		fprintf(stderr, "ERROR: %s(fd=%d,buf=%p,count=%ld) failed, %m\n",
			op_name[otype], fd, ptr, env.size);
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
	CUFILE_CHECK_EXIT(cuFileDriverOpen());

	/* Set up GDS descriptor */
	cfDescr.handle.fd = fd;
	cfDescr.type = CU_FILE_HANDLE_TYPE_OPAQUE_FD;

	CUFILE_CHECK_EXIT(cuFileHandleRegister(&cfHandle, &cfDescr));
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

	if (env.size % env.nr_threads) {
		fprintf(stderr, "ERROR: The total size needs to be evenly distributed among all threads.\n");
		exit(EXIT_FAILURE);
	}

	if ((env.size / env.nr_threads) % getpagesize()) {
		fprintf(stderr, "ERROR: Each thread should page-align the memory block it processes.\n");
		exit(EXIT_FAILURE);
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
