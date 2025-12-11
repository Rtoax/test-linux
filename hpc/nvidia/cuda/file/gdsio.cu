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
#include <sys/types.h>
#include <sys/stat.h>
#include "cuda_compat.h"
#include "../cuda_helpers.h"

#define VERSION	"v1.0.0"

#define KiB 1024UL
#define MiB (KiB * 1024UL)
#define GiB (MiB * 1024UL)

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

static struct {
	int gpu;
	const char *filename;
	const char *dir;
	int nr_threads;
	size_t fsize;
	size_t iosize;
	int numa;
	enum xfer_type xtype;
	enum op_type otype;
	bool verify;
	bool bufregister;
	bool bufrand;
} env = {
	.gpu = 0,
	.filename = "gdsio.out",
	.dir = NULL, /* default to "." */
	.nr_threads = 1,
	.fsize = 1024 * KiB,
	.iosize = 1024 * KiB,
	.numa = 0,
	.xtype = XFER_BETWEEN_STORAGE__GPU,
	.otype = OP_WRITE,
	.verify = false,
	.bufregister = true,
	.bufrand = false,
};

static int fd = -1;
static CUfileHandle_t cfHandle = NULL;
static CUfileDescr_t cfDescr = {};
static unsigned long total_consumed_ns = 0;
static unsigned long total_ops = 0;

static inline unsigned long consuming_ns(unsigned long ns)
{
	return __atomic_fetch_add(&total_consumed_ns, ns, __ATOMIC_SEQ_CST);
}

static inline unsigned long consumed_ns(void)
{
	return consuming_ns(0);
}

static inline unsigned long increment_ops(void)
{
	return __atomic_fetch_add(&total_ops, 1, __ATOMIC_SEQ_CST);
}

const char argp_prog_doc[] = "gdsio version " VERSION "\n";

static const struct argp_option opts[] = {
	{ "file", 'f', "FILE", 0, "file name" },
	{ "DIR", 'D', "DIR", 0, "directory name" },
	{ "device", 'd', "DEVICE", 0, "gpu index" },
	{ "fsize", 's', "SIZE", 0, "file size (K|M|G)" },
	{ "iosize", 'i', "IOSIZE", 0, "io_size(K|M|G) <min_size:max_size:step_size>" },
	{ "numa", 'n', "NUMA", 0, "numa node" },
	{ "nthreads", 'w', "NTHREADS", 0, "number of threads for a job" },
	{ "xfer_type", 'x', "XFER_TYPE", 0, "transfer type [0(GPU_DIRECT), 1(CPU_ONLY), 2(CPU_GPU), 3(CPU_ASYNC_GPU), 4(CPU_CACHED_GPU), 5(GPU_DIRECT_ASYNC), 6(GPU_BATCH), 7(GPU_BATCH_STREAM)]" },
	{ "op_type", 'I', "OP_TYPE", 0, "[0(read), 1(write), 2(randread), 3(randwrite)]" },
	{ "verify", 'V', NULL, 1, "verify IO" },
	{ "bufregister", 'b', NULL, 1, "skip bufregister" },
	{ "bufrand", 'R', NULL, 1, "fill io buffer with random data" },
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

	if (strstr(str, "G") || strstr(str, "GB") || strstr(str, "GiB"))
		size *= GiB;
	else if (strstr(str, "M") || strstr(str, "MB") || strstr(str, "MiB"))
		size *= MiB;
	else if (strstr(str, "K") || strstr(str, "KB") || strstr(str, "KiB"))
		size *= KiB;

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
		env.fsize = str2size(arg);
		if (env.fsize % getpagesize()) {
			fprintf(stderr, "ERROR: size must page aliged.\n");
			exit(EXIT_FAILURE);
		}
		break;
	case 'i':
		env.iosize = str2size(arg);
		if (env.iosize % KiB) {
			fprintf(stderr, "ERROR: iosize must unaligned 0x%lx.\n", KiB);
			exit(EXIT_FAILURE);
		}
		break;
	case 'u':
		env.numa = atoi(arg);
		if (env.numa < 0) {
			fprintf(stderr, "ERROR: bad numa %d\n", env.numa);
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
		printf("gpsio %s\n", VERSION);
		exit(EXIT_SUCCESS);
		break;
	case 'b':
		env.bufregister = false;
		break;
	case 'R':
		env.bufrand = false;
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

	enum op_type otype;

	/**
	 * Maybe mem1 is host memory, mem2 is device memory, or in the other
	 * way.
	 */
	void *mem1;
	void *mem2;
	off_t mem1_offset;
	off_t mem2_offset;

	/* size of memory/file that current thread need to operate */
	size_t size;

	off_t file_offset;

	int (*workload)(struct thread_arg *arg);
};

static pthread_t *threads;
static struct thread_arg *thread_args;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread_func(void *targ)
{
	int err;
	struct thread_arg *arg = (struct thread_arg *)targ;

	pthread_mutex_lock(&mutex);
#ifdef DEBUG
	fprintf(stderr, "Thread %d waiting.\n", arg->idx);
#endif
	pthread_cond_wait(&cond, &mutex);

	err = arg->workload(arg);

	pthread_mutex_unlock(&mutex);
	pthread_exit((void *)(uintptr_t)err);
}
/**
 * Distribute memory @mem1 evenly among each thread.
 */
void multithread_create(void *mem1, void *mem2, enum op_type otype,
			const char *namepfx,
			int (*workload)(struct thread_arg *arg))
{
	threads = (pthread_t *)malloc(sizeof(pthread_t) * env.nr_threads);
	assert(threads && "Malloc fatal");
	thread_args = (struct thread_arg *)malloc(sizeof(struct thread_arg) * env.nr_threads);
	assert(thread_args && "Malloc fatal");

	for (int i = 0; i < env.nr_threads; i++) {
		size_t tsize = env.fsize / env.nr_threads;
		char name[128];

		thread_args[i].idx = i;
		thread_args[i].mem1 = mem1;
		thread_args[i].mem2 = mem2;
		thread_args[i].size = tsize;
		thread_args[i].otype = otype;
		thread_args[i].file_offset = tsize * i;
		thread_args[i].mem1_offset = tsize * i;
		thread_args[i].mem2_offset = tsize * i;
		thread_args[i].workload = workload;

		pthread_create(&threads[i], NULL, thread_func, &thread_args[i]);
		snprintf(name, sizeof(name) - 1, "%s/%d", namepfx, i);
		pthread_setname_np(threads[i], name);
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

	/**
	 * With multi-threaded execution, we only need to record the total
	 * execution time.
	 */
	consuming_ns(nsecs() - start);
}

void multithread_destroy(void)
{
	free(threads);
	free(thread_args);
}

int workload_cufile(struct thread_arg *arg)
{
	ssize_t i, bytes = 0;
	void *devPtr = arg->mem1;
	enum op_type otype = arg->otype;
	size_t size = arg->size;
	off_t foff = arg->file_offset;
	off_t doff = arg->mem1_offset;

	switch (otype) {
	case OP_READ:
		for (i = 0; i < size; i += env.iosize) {
			bytes += cuFileRead(cfHandle, devPtr, env.iosize,
					    foff + i, doff + i);
			increment_ops();
		}
		break;
	case OP_WRITE:
		for (i = 0; i < size; i += env.iosize) {
			bytes += cuFileWrite(cfHandle, devPtr, env.iosize,
					     foff + i, doff + i);
			increment_ops();
		}
		break;
	case OP_RANDREAD:
	case OP_RANDWRITE:
	default:
		fprintf(stderr, "WARNING: not support %s yet.\n", op_name[otype]);
		break;
	}

	if (bytes < 0) {
		fprintf(stderr, "ERROR: GPU %s(fd=%d,buf=%p,count=%ld) failed, %m\n",
			op_name[otype], fd, devPtr, env.fsize);
	}
	return 0;
}

void* xfer_between_storage__gpu(void *devPtr, bool alloc, enum op_type otype,
				uint8_t init)
{
	bool allocated = false;

	if (!devPtr) {
		CUDA_CHECK_EXIT(cudaMalloc(&devPtr, env.fsize));
		CUDA_CHECK_EXIT(cudaMemset(devPtr, init, env.fsize));
		allocated = true;
	}

	if (env.bufregister)
		CUFILE_CHECK_EXIT(cuFileBufRegister(devPtr, env.fsize, 0));

	multithread_create(devPtr, NULL, otype, op_name[otype],
			   workload_cufile);
	multithread_execute();
	multithread_destroy();

	if (env.verify)
		verify_io_devmem(devPtr, env.fsize, init);

	if (env.bufregister)
		CUFILE_CHECK_EXIT(cuFileBufDeregister(devPtr));

	if (allocated && !alloc) {
		CUDA_CHECK_EXIT(cudaFree(devPtr));
		devPtr = NULL;
	}

	return devPtr;
}

/**
 * read(2) from a specified postion with iosize
 */
ssize_t pos_read(int fd, off_t pos, void *buf, size_t count)
{
	ssize_t i, bytes = 0;
	off_t old_pos = lseek(fd, 0, SEEK_CUR);

	lseek(fd, pos, SEEK_SET);

	for (i = 0; i < count; i += env.iosize) {
#ifdef DEBUG
		printf("read(%d, %p, %ld)\n", fd, (char *)buf + i, env.iosize);
#endif
		bytes += read(fd, (char *)buf + i, env.iosize);
		increment_ops();
	}

	lseek(fd, old_pos, SEEK_SET);
	return bytes;
}

/**
 * write(2) to a specified postion with iosize
 */
ssize_t pos_write(int fd, off_t pos, void *buf, size_t count)
{
	ssize_t i, bytes = 0;
	off_t old_pos = lseek(fd, 0, SEEK_CUR);

	lseek(fd, pos, SEEK_SET);

	for (i = 0; i < count; i += env.iosize) {
#ifdef DEBUG
		printf("write(%d, %p, %ld)\n", fd, (char *)buf + i, env.iosize);
#endif
		bytes += write(fd, (char *)buf + i, env.iosize);
		increment_ops();
	}

	lseek(fd, old_pos, SEEK_SET);
	return bytes;
}

int workload_cpu_rw(struct thread_arg *arg)
{
	ssize_t bytes = 0;
	void *ptr = arg->mem1;
	enum op_type otype = arg->otype;
	size_t size = arg->size;
	off_t foff = arg->file_offset;
	off_t doff = arg->mem1_offset;

	switch (otype) {
	case OP_READ:
		bytes = pos_read(fd, foff, (char *)ptr + doff, size);
		break;
	case OP_WRITE:
		bytes = pos_write(fd, foff, (char *)ptr + doff, size);
		break;
	case OP_RANDREAD:
	case OP_RANDWRITE:
	default:
		fprintf(stderr, "WARNING: not support %s yet.\n", op_name[otype]);
		break;
	}

	if (bytes < 0) {
		fprintf(stderr, "ERROR: %s(fd=%d,buf=%p,count=%ld) failed, %m\n",
			op_name[otype], fd, ptr, env.fsize);
	}
	return 0;
}

/**
 * @alloc: allocate new memory, need free.
 */
void* xfer_between_storage__cpu(void *ptr, bool alloc, enum op_type otype,
				uint8_t init)
{
	bool allocated = false;

	if (!ptr) {
		posix_memalign(&ptr, getpagesize(), env.fsize);
		memset(ptr, init, env.fsize);
		allocated = true;
	}

	multithread_create(ptr, NULL, otype, op_name[otype],
			   workload_cpu_rw);
	multithread_execute();
	multithread_destroy();

	if (env.verify)
		verify_io_cpumem(ptr, env.fsize, init);

	if (allocated && !alloc) {
		free(ptr);
		ptr = NULL;
	}
	return ptr;
}

int workload_gpu_cpu(struct thread_arg *arg)
{
	void *dev_ptr = arg->mem1;
	void *host_ptr = arg->mem2;
	enum op_type otype = arg->otype;
	size_t size = arg->size;

	switch (otype) {
	case OP_READ:
		CUDA_CHECK_EXIT(cudaMemcpy(host_ptr, dev_ptr, size, cudaMemcpyDeviceToHost));
		break;
	case OP_WRITE:
		CUDA_CHECK_EXIT(cudaMemcpy(dev_ptr, host_ptr, size, cudaMemcpyHostToDevice));
		break;
	case OP_RANDREAD:
	case OP_RANDWRITE:
	default:
		fprintf(stderr, "WARNING: not support %s yet.\n", op_name[otype]);
		break;
	}

	return 0;
}

/**
 * @otype: READ is memory copy from GPU to CPU, WRITE is from CPU to GPU.
 */
int xfer_between_gpu__cpu(void **hostptr, void **devptr, bool alloc,
			  enum op_type otype, uint8_t init)
{
	bool allocated_host = false;
	bool allocated_device = false;
	void *host_ptr = hostptr ? *hostptr : NULL;
	void *dev_ptr = devptr ? *devptr : NULL;

	if (!host_ptr) {
		posix_memalign(&host_ptr, getpagesize(), env.fsize);
		memset(host_ptr, init, env.fsize);
		allocated_host = true;
	}

	if (!dev_ptr) {
		CUDA_CHECK_EXIT(cudaMalloc(&dev_ptr, env.fsize));
		CUDA_CHECK_EXIT(cudaMemset(dev_ptr, init, env.fsize));
		allocated_device = true;
	}

	multithread_create(dev_ptr, host_ptr, otype, op_name[otype],
			   workload_gpu_cpu);
	multithread_execute();
	multithread_destroy();

	if (allocated_host && (!alloc || !hostptr)) {
		free(host_ptr);
	} else if (alloc && allocated_host && hostptr) {
		*hostptr = host_ptr;
	}

	if (allocated_device && (!alloc || !devptr)) {
		CUDA_CHECK_EXIT(cudaFree(dev_ptr));
	} else if (alloc && allocated_device && devptr) {
		*devptr = dev_ptr;
	}

	return 0;
}

void cufile_init(void)
{
	CUDA_CHECK_EXIT(cudaSetDevice(env.gpu));
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
	void *host_ptr, *dev_ptr;
	char filepath[256];

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (env.fsize % env.nr_threads) {
		fprintf(stderr, "ERROR: The total size needs to be evenly distributed among all threads.\n");
		exit(EXIT_FAILURE);
	}

	if ((env.fsize / env.nr_threads) % getpagesize()) {
		fprintf(stderr, "ERROR: Each thread should page-align the memory block it processes.\n");
		exit(EXIT_FAILURE);
	}

	if ((env.fsize / env.nr_threads) % env.iosize) {
		fprintf(stderr, "ERROR: Each thread's memory block should iosize-align.\n");
		exit(EXIT_FAILURE);
	}

	if (env.fsize < env.nr_threads * env.iosize) {
		fprintf(stderr, "ERROR: File size cannot be evenly distributed among all threads.\n");
		exit(EXIT_FAILURE);
	}

	if (env.filename[0] == '/' && env.dir) {
		fprintf(stderr, "ERROR: Absolute file name don't need extra directory.\n");
		exit(EXIT_FAILURE);
	}

	if (!env.dir) {
		snprintf(filepath, sizeof(filepath), "%s", env.filename);
	} else if (env.dir) {
		snprintf(filepath, sizeof(filepath), "%s/%s", env.dir, env.filename);
	}

	if (env.otype == OP_READ && access(filepath, F_OK)) {
		fprintf(stderr, "ERROR: %s is not exist in %s mode.\n",
			filepath, op_name[OP_READ]);
		exit(EXIT_FAILURE);
	}

	if (env.otype == OP_READ) {
		struct stat st;
		if (stat(filepath, &st) != 0) {
			fprintf(stderr, "ERROR: could not stat(%s), %m\n", filepath);
			exit(EXIT_FAILURE);
		}
		if (env.fsize > st.st_size) {
			fprintf(stderr, "ERROR: size of %s is smaller than %ld\n",
				filepath, env.fsize);
			exit(EXIT_FAILURE);
		}
	}

	fd = open(filepath, O_CREAT | O_RDWR | O_DIRECT, 0664);
	if (fd < 0) {
		fprintf(stderr, "Open %s failed\n", filepath);
		return 1;
	}

	switch (env.xtype) {
	case XFER_BETWEEN_STORAGE__GPU:
		cufile_init();
		xfer_between_storage__gpu(NULL, false, env.otype, 'A');
		cufile_destroy();
		break;
	case XFER_BETWEEN_STORAGE__CPU:
		xfer_between_storage__cpu(NULL, false, env.otype, 'B');
		break;
	case XFER_BETWEEN_STORAGE__CPU__GPU:
		cufile_init();
		switch (env.otype) {
		/**
		 * Storage->CPU->GPU
		 */
		case OP_READ:
			host_ptr = xfer_between_storage__cpu(NULL, true, OP_READ, 0);
			xfer_between_gpu__cpu(&host_ptr, NULL, false, OP_WRITE, 'C');
			free(host_ptr);
			break;
		/**
		 * GPU->CPU->Storage
		 */
		case OP_WRITE:
			host_ptr = dev_ptr = NULL;
			xfer_between_gpu__cpu(&host_ptr, &dev_ptr, true, OP_READ, 'D');
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
		cufile_destroy();
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

	printf("IoType: %s,", op_name[env.otype]);
	printf(" XferType: %s,", xfer_name[env.xtype]);
	printf(" Threads: %d,", env.nr_threads);
	printf(" DataSetSize: %ld B (%ld KiB, %ld MiB, %ld GiB),", env.fsize,
		env.fsize / KiB, env.fsize / MiB, env.fsize / GiB);
	printf(" IOSize: %ld B (%ld KiB, %ld MiB),", env.iosize,
		env.iosize / KiB, env.iosize / MiB);
	printf(" Throughput: %f GiB/sec,", env.fsize * 1.f / consumed_ns());
	printf(" Avg_Latency: %f usecs,", consumed_ns() * 1.f / 1e3 / total_ops);
	printf(" ops: %ld,", total_ops);
	printf(" total_time %f secs,", consumed_ns() * 1.f / 1E9);
	printf(" numa: %d,", env.numa);
	printf(" File: %s\n", filepath);

	close(fd);
	return 0;
}
