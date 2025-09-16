/* 2025-02-08	Rong Tao	Create this */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <elf.h>
#include <sys/mman.h>
#include <linux/prctl.h>
#include <sys/prctl.h>
#include <setjmp.h>

#include "helpers.h"

#define NVDSO_SHOULD_SKIP	0xdead1234

#define LOG_DEBUG(fmt...) do {	\
		if (!nvdso_debug)	\
			break;	\
		fprintf(stderr, "nvDSO: DEBUG: [%s:%d] ", __func__, __LINE__);	\
		fprintf(stderr, fmt);	\
	} while (0)

#define LOG_ERROR(fmt...) do {	\
		fprintf(stderr, "nvDSO: ERROR: [%s:%d] ", __func__, __LINE__);	\
		fprintf(stderr, fmt);	\
	} while (0)

#define nvdso_should_skip()	longjmp(nvdso_jmp, NVDSO_SHOULD_SKIP)

static const char *const nvdso_version = "v1.0.0";
static jmp_buf nvdso_jmp;
static unsigned long vdso_start, vdso_end;
static int nvdso_debug = 0;
static bool nvdso_anon = false;

static unsigned long get_vdso_range(size_t *size)
{
	char *line = NULL;
	size_t len = 0;
	unsigned long start, end;
	FILE *fp;

	fp = fopen("/proc/self/maps", "r");
	if (!fp) {
		perror("fopen");
		return 0;
	}

	start = end = 0;

	while (getline(&line, &len, fp) != -1) {
		if (strstr(line, "[vdso]")) {
			if (sscanf(line, "%lx-%lx", &start, &end) == 2) {
				LOG_DEBUG("vDSO VMA size: %lu bytes\n", end - start);
				break;
			}
		}
	}
	free(line);

	/**
	 * If kernel cmdline specify vdso=0, the vDSO will be turned off.
	 */
	if (!start || !end) {
		LOG_ERROR("Couldn't get [vdso] vma.\n");
		nvdso_should_skip();
	}

	if (size)
		*size = end - start;

	return start;
}

static int open_proc_pid_mem(pid_t pid)
{
	char proc_mem[64];
	int mem_fd;

	sprintf(proc_mem, "/proc/%d/mem", pid);
	mem_fd = open(proc_mem, O_RDWR);
	if (mem_fd <= 0) {
		LOG_ERROR("Open %s failed.\n", proc_mem);
		return -1;
	}
	return mem_fd;
}

static int proc_pid_mem_read(int mem_fd, off_t paddr, void *buf, size_t len)
{
	int ret;
	ret = pread(mem_fd, buf, len, paddr);
	if (ret <= 0)
		LOG_ERROR("pread: %m.\n");
	return ret;
}

static int proc_pid_mem_write(int mem_fd, off_t paddr, void *src, size_t len)
{
	int ret;
	ret = pwrite(mem_fd, src, len, paddr);
	if (ret <= 0)
		LOG_ERROR("pwrite: %m.\n");
	return ret;
}

static int proc_vdso_dump(const char *filename)
{
	int err = 0, mem_fd;
	FILE *fp;
	void *mem;
	size_t size;
	unsigned long addr;

	addr = vdso_start;
	size = vdso_end - vdso_start;

	mem_fd = open_proc_pid_mem(getpid());
	mem = malloc(size);

	if (proc_pid_mem_read(mem_fd, addr, mem, size) < size) {
		close(mem_fd);
		nvdso_should_skip();
	}

	/* Dump [vdso] to vdso.elf */
	fp = fopen(filename, "w");
	if (fwrite(mem, size, 1, fp) != 1) {
		LOG_ERROR("Write %s failed.\n", filename);
		err = -1;
	}

	free(mem);
	close(mem_fd);
	fclose(fp);

	if (err)
		nvdso_should_skip();

	return 0;
}

static int map_new_vdso(const char *vdsoelf, void *addr, size_t size, bool anon)
{
	int fd, mmap_fd, ret = 0;
	void *mem, *buf;
	Elf64_Ehdr *ehdr;
	int flags = MAP_PRIVATE;
	int prot = PROT_READ | PROT_EXEC;
	char *nvdso_name = "vdso.new";

	fd = open(vdsoelf, O_RDONLY);
	if (fd == -1) {
		perror("open\n");
		return -errno;
	}

	LOG_DEBUG("open(%s) = %d\n", vdsoelf, fd);

	mmap_fd = fd;

	if (anon) {
		flags |= MAP_ANONYMOUS;
		/**
		 * If anonymous new vdso, need write permission, see memcpy(3)
		 * below.
		 */
		prot |= PROT_WRITE;

		buf = malloc(size);
		ssize_t n = read(fd, buf, size);
		if (n <= 0) {
			perror("read");
		}
		mmap_fd = -1;
	}

	/**
	 * There can be multiple mapping rules here, for example:
	 *
	 * 1. Each process has an independent address mapping (The current
	 * code sample is for this rule);
	 *
	 * 2. By recording the relationship between the dumped vDSO file and
	 *    the loaded physical address (NUMA node information) of each new
	 *    mapping, the NUMA-level vDSO copy is guaranteed; this solution
	 *    requires the use of inter-process shared memory
	 *
	 *    for example:
	 *
	 *        vDSO file   paddr  NUMA
	 *        ---------   -----  ----
	 *        vdso1.elf   0x111  0
	 *        vdso2.elf   0x222  1
	 *        vdso3.elf   0x333  2
	 *        vdso4.elf   0x444  4
	 *
	 *    By querying the above table, if the NUMA node where the current
	 *    process is running already has the physical address of vdso, you
	 *    can directly map the corresponding file without dumping a new
	 *    vdso file.
	 */

	mem = mmap((void *)addr, size, prot, flags, mmap_fd, 0);
	if (mem == MAP_FAILED) {
		perror("mmap");
		close(fd);
		return -errno;
	}

	if (anon) {
		memcpy(mem, buf, size);
		/* Remove write permission */
		mprotect(mem, size, PROT_READ | PROT_EXEC);
		LOG_DEBUG("memcpy(%p, %p, %ld)\n", mem, buf, size);
		free(buf);

#ifdef CONFIG_ANON_VMA_NAME
		/**
		 * see manual R_SET_VMA(2const)
		 *
		 * The name can contain only printable ascii characters
		 * (isprint(3)), except '[', ']', '\', '$', and '`'.
		 */
		char *vma_name = getenv("NVDSO_NAME");
		if (vma_name)
			nvdso_name = vma_name;
		LOG_DEBUG("set vdso name to %s", nvdso_name);
		if (prctl(PR_SET_VMA, PR_SET_VMA_ANON_NAME, addr, size, nvdso_name) != 0) {
			perror("prctl: PR_SET_VMA_ANON_NAME");
			ret = -EINVAL;
		}
#else
# pragma message("Kernel is not support CONFIG_ANON_VMA_NAME!!!")
#endif
	}
done_to_set_name:

	ehdr = (void *)mem;

	if (ehdr->e_ident[EI_MAG1] != 'E' || ehdr->e_ident[EI_MAG2] != 'L' ||
	    ehdr->e_ident[EI_MAG3] != 'F') {
		LOG_ERROR("%s is not ELF.\n", vdsoelf);
		ret = -EINVAL;
	}

	close(fd);
	return ret;
}

/**
 * This function will be executed before the main() function.
 */
void __attribute__((constructor)) __attribute__((visibility("default")))
_nvdso_start(void)
{
	int ret;
	unsigned long size;
	char *vdsoelf = "vdso.elf";

	if (atoi(getenv("NVDSO_DEBUG") ?: "0")) {
		nvdso_debug = 1;
		LOG_DEBUG("Start debug mode.\n");
	}

	LOG_DEBUG("nvDSO version %s\n", nvdso_version);
	LOG_DEBUG("Start replace vDSO vma\n");

	/* Anonymons nvdso anyway */
	nvdso_anon = getenv("NVDSO_ANON");
	if (nvdso_anon)
		LOG_DEBUG("Use anonymous nvdso.\n");

	ret = setjmp(nvdso_jmp);
	if (ret == NVDSO_SHOULD_SKIP) {
		LOG_DEBUG("Skipping nvDSO.\n");
		return;
	}

	vdso_start = get_vdso_range(&size);
	if (vdso_start == 0) {
		LOG_ERROR("Could not get [vdso] address.\n");
		return;
	}

	vdso_end = vdso_start + size;

	LOG_DEBUG("[vdso] %lx ~ %lx\n", vdso_start, vdso_end);

	if (nvdso_debug)
		proc_display_maps(stderr, "Before:");

	/* Dump [vdso] to file */
	proc_vdso_dump(vdsoelf);

	/**
	 * At this point, it is no longer recoverable. We need to ensure that
	 * the subsequent processes are executed correctly, otherwise, when
	 * the process calls the vdso function, a segmentation error will
	 * occur directly.
	 */

	ret = munmap((void *)vdso_start, vdso_end - vdso_start);
	if (ret != 0) {
		LOG_ERROR("munmap() old vDSO failed, %m\n");
		return;
	}

#ifdef CONFIG_ANON_VMA_NAME
	map_new_vdso(vdsoelf, (void *)vdso_start, vdso_end - vdso_start, true);
#else
	map_new_vdso(vdsoelf, (void *)vdso_start, vdso_end - vdso_start, !!nvdso_anon);
#endif

	if (nvdso_debug)
		proc_display_maps(stderr, "After: ");

	LOG_DEBUG("Done!!\n");

	return;
}

void __attribute__((destructor)) __attribute__((visibility("default")))
_nvdso_end(void)
{
	LOG_DEBUG("Release.\n");
	/**
	 * TODO: Remove useless vdso dump files, release resources, etc.
	 */
}
