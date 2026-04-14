/**
 * Test memory operation across NUMA node.
 *
 * Copyright (C) 2023-2026 Rong Tao
 */
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <numa.h>
#include <getopt.h>
#include <libgen.h>

#define VERSION_MAJOR 1
#define VERSION_MINOR 1
#define VERSION_PATCH 0

#define KB (sizeof(uint8_t) * 1024UL)
#define MB (KB * 1024UL)
#define GB (MB * 1024UL)

const char *progname = "numa-memory";

int base_cpu = 1;
int nr_numa_node;
int numa_pgsz;
long *node_sizes;
size_t numa_latencies[100];
size_t cross_read_numa_latencies[100];
size_t cross_write_numa_latencies[100];
size_t register_write_latencies[100];
size_t register_read_latencies[100];
uint8_t **numa_mems_1;
uint8_t **numa_mems_2;

size_t blk_size = 2 * GB;
size_t nloop = 10;

static inline unsigned long usecs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000UL + tv.tv_usec;
}

void print_lantency_array(int cpu, int numa, size_t latencies[])
{
	int i;
	printf("%-8s %-10s %-8s %-8s %-8s %-8s\n",
		"NUMA", "SPENT(us)", "CPU", "CPU_NUMA", "DISTANCE", "RATE(B/us)");
	for (i = 0; i < nr_numa_node; i++) {
		int distance = numa_distance(numa, i);
		printf("%-8d %-10ld %-8d %-8d %-8d %-8ld\n",
			i, latencies[i], cpu, numa, distance,
			(blk_size * nloop) / latencies[i]);
	}
}

void test_register_write(void)
{
	int i, j, k;
	size_t start;
	volatile register unsigned long val0 = 0x12345678ffffffffUL;

	/* Test write register variable to remote numa memory
	 * +--------------+     +--------------+
	 * |    NUMA0     |     |    NUMA1     |
	 * | +--+    +--+ |     | +--+    +--+ |
	 * | |  |    |  | |     | |  |    |  |<-- Register
	 * | +--+    +--+ |     | +--+    +--+ |
	 * +--------------+     +--------------+
	 */
	for (i = 0; i < nr_numa_node; i++) {
		if (!numa_mems_1[i] || !numa_mems_2[i])
			continue;

		printf("Test memory write on numa %d\n", i);

		start = usecs();
		for (j = 0; j < nloop; j++)
			for (k = 0; k < blk_size; k += sizeof(val0))
				*(unsigned long *)(numa_mems_1[i] + k) = val0;
		register_write_latencies[i] = usecs() - start;
	}
}

void test_register_read(void)
{
	int i, j, k;
	size_t start;
	volatile register unsigned long val1;

	/* Test write register variable to remote numa memory
	 * +--------------+     +--------------+
	 * |    NUMA0     |     |    NUMA1     |
	 * | +--+    +--+ |     | +--+    +--+ |
	 * | |  |    |  | |     | |  |    |  |--> Register
	 * | +--+    +--+ |     | +--+    +--+ |
	 * +--------------+     +--------------+
	 */
	for (i = 0; i < nr_numa_node; i++) {
		if (!numa_mems_1[i] || !numa_mems_2[i])
			continue;

		printf("Test memory write on numa %d\n", i);

		start = usecs();
		for (j = 0; j < nloop; j++)
			for (k = 0; k < blk_size; k += sizeof(val1))
				/**
				 * val1 may be optimized out, just calculate
				 * some thing and print it.
				 */
				val1 &= *(unsigned long *)(numa_mems_1[i] + k);
		register_read_latencies[i] = usecs() - start;
	}
	printf("Register and(&) result %lx\n", val1);
}

void version(const char *progname)
{
	printf("%s-%d.%d.%d\n", progname, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
}

void usage(const char *progname)
{
	printf("Usage: %s [--nloop=NUM] --blk=[SIZE]\n", progname);
	printf(
	"\n"
	"  -n, --nloop       Number of back-and-forth tests, default: %ld\n"
	"\n"
	"  -b, --blk         block bytes size of each memory test\n"
	"                    you could specify KB, MB or GB like --blk 2GB\n"
	"                    default: %ldB, %ldMB, %ldGB\n"
	"\n"
	"  -c, --cpu         Bind to cpu, default: %d\n"
	"\n"
	"  -h, --help        show this information\n"
	"  -v, --version     show version\n"
	"\n", nloop, blk_size, blk_size / MB, blk_size / GB, base_cpu);
}

int main(int argc, char *argv[])
{
	int i, j, ret;
	pid_t pid;
	size_t start;
	struct bitmask *cpumask;
	int base_numa_node;

	if (numa_available() < 0) {
		printf("ERROR: Numa unavailable.\n");
		exit(1);
	}

	nr_numa_node = numa_max_node() + 1;
	numa_pgsz = numa_pagesize();

	struct option options[] = {
		{"blk",         required_argument, 0,  'b'},
		{"cpu",         required_argument, 0,  'c'},
		{"nloop",       required_argument, 0,  'n'},
		{"help",        no_argument,       0,  'h'},
		{"version",     no_argument,       0,  'v'},
		{0, 0, 0, 0},
	};

	while (1) {
		int option_idx = 0;
		int c = getopt_long(argc, argv, "b:c:n:hv", options, &option_idx);
		if (c == -1)
			break;
		switch (c) {
		case 'b':
			blk_size = strtoul(optarg, NULL, 10);
			if (strstr(optarg, "GB"))
				blk_size *= GB;
			else if (strstr(optarg, "MB"))
				blk_size *= MB;
			else if (strstr(optarg, "KB"))
				blk_size *= KB;

			if (blk_size <= 8) {
				printf("ERROR: Block is too small\n");
				exit(1);
			}
			break;
		case 'c':
			base_cpu = atoi(optarg);
			break;
		case 'n':
			nloop = strtoul(optarg, NULL, 10);
			if (nloop <= 0) {
				printf("ERROR: Invalid nloop %ld\n", nloop);
				exit(1);
			}
			break;
		case 'h':
			usage(progname);
			exit(1);
		case 'v':
			version(progname);
			exit(1);
		case '?':
		default:
			fprintf(stderr, "Unknown option or requires an argument.\n");
			exit(1);
		}
	}

	if (nr_numa_node == 1) {
		fprintf(stderr, "WARNING: Your machine has only one NUMA node, "
			"no need to run this benchmark.\n");
		exit(0);
	}

	base_numa_node = numa_node_of_cpu(base_cpu);
	if (base_numa_node == -1) {
		printf("ERROR: Invalid CPU %d\n", base_cpu);
		exit(1);
	}

	memset(numa_latencies, 0x00, sizeof(numa_latencies));
	memset(cross_read_numa_latencies, 0x00,
		sizeof(cross_read_numa_latencies));
	memset(cross_write_numa_latencies, 0x00,
		sizeof(cross_write_numa_latencies));
	memset(register_write_latencies, 0x00,
		sizeof(register_write_latencies));
	memset(register_read_latencies, 0x00, sizeof(register_read_latencies));

	printf("Total %d numa node.\n", nr_numa_node);
	printf("Pagesize %d bytes.\n", numa_pgsz);
	printf("Block %ldB %ldMB, %ldGB (%s --blk [SIZE] to set)\n",
		blk_size, blk_size / MB, blk_size / GB, progname);
	printf("Nloop %ld (%s --nloop to set nloop)\n", nloop, progname);
	printf("Running on CPU%d, NUMA%d\n", base_cpu, base_numa_node);

	node_sizes = malloc(sizeof(long) * nr_numa_node);
	numa_mems_1 = (uint8_t **)malloc(sizeof(uint8_t *) * nr_numa_node);
	numa_mems_2 = (uint8_t **)malloc(sizeof(uint8_t *) * nr_numa_node);

	for (i = 0; i < nr_numa_node; i++) {
		/* Get each NUMA node memory size */
		node_sizes[i] = numa_node_size(i, NULL);
		if (node_sizes[i] >= blk_size * 2) {
			printf("Allocate memory %ld bytes on numa %d.\n",
			       blk_size, i);
			numa_mems_1[i] = numa_alloc_onnode(blk_size, i);
			numa_mems_2[i] = numa_alloc_onnode(blk_size, i);
			if (!numa_mems_1[i] || !numa_mems_2[i]) {
				printf("ERROR: alloc memory on numa %d failed.\n", i);
				numa_error("?");
				exit(1);
			}

			memset(numa_mems_1[i], 0xff, blk_size);
			memset(numa_mems_2[i], 0xff, blk_size);
		} else {
			printf("WARNING: No enough memory on numa %d.\n", i);
			numa_mems_1[i] = NULL;
			numa_mems_2[i] = NULL;
		}
	}

	/* Bind process to cpu1(maybe is numa0) */
	pid = getpid();
	cpumask = numa_bitmask_alloc(nr_numa_node);
	numa_bitmask_clearall(cpumask);
	numa_bitmask_setbit(cpumask, 1);
	ret = numa_sched_setaffinity(pid, cpumask);
	if (ret) {
		perror("sched_setaffinity");
		return ret;
	}

	/* base NUMA must have memory */
	if (!numa_mems_1[base_numa_node]) {
		printf("ERROR: No memory on numa %d.\n", base_numa_node);
		goto free_mem;
	}

	/* Test memcpy
	 * +--------------+
	 * |    NUMA0     |
	 * | +--+    +--+ |
	 * | |  |--->|  | |
	 * | +--+    +--+ |
	 * +-------------++
	 */
	for (i = 0; i < nr_numa_node; i++) {
		if (!numa_mems_1[i] || !numa_mems_2[i])
			continue;

		printf("Memory copy %ld bytes from numa %d to numa %d\n",
		       blk_size * nloop, i, i);

		start = usecs();
		for (j = 0; j < nloop; j++)
			memcpy(numa_mems_1[i], numa_mems_2[i], blk_size);
		numa_latencies[i] = usecs() - start;
	}

	/* Test cross read numa memcpy
	 * +--------------+     +--------------+
	 * |    NUMA0     |     |    NUMA1     |
	 * | +--+    +--+ |     | +--+    +--+ |
	 * | |  |    |  |<--------|  |    |  | |
	 * | +--+    +--+ |     | +--+    +--+ |
	 * +--------------+     +--------------+
	 */
	for (i = 0; i < nr_numa_node; i++) {
		if (!numa_mems_1[base_numa_node] || !numa_mems_2[i])
			continue;

		printf("Memory copy %ld bytes from numa %d to numa %d\n",
		       blk_size * nloop, i, base_numa_node);

		start = usecs();
		for (j = 0; j < nloop; j++)
			memcpy(numa_mems_1[base_numa_node], numa_mems_2[i],
				blk_size);
		cross_read_numa_latencies[i] = usecs() - start;
	}

	/* Test cross write numa memcpy
	 * +--------------+     +--------------+
	 * |    NUMA0     |     |    NUMA1     |
	 * | +--+    +--+ |     | +--+    +--+ |
	 * | |  |    |  |-------->|  |    |  | |
	 * | +--+    +--+ |     | +--+    +--+ |
	 * +--------------+     +--------------+
	 */
	for (i = 0; i < nr_numa_node; i++) {
		if (!numa_mems_1[i] || !numa_mems_2[base_numa_node])
			continue;

		printf("Memory copy %ld bytes from numa %d to numa %d\n",
		       blk_size * nloop, base_numa_node, i);

		start = usecs();
		for (j = 0; j < nloop; j++)
			memcpy(numa_mems_1[i], numa_mems_2[base_numa_node],
				blk_size);
		cross_write_numa_latencies[i] = usecs() - start;
	}

	test_register_read();
	test_register_write();

	printf("=============================================================\n");
	printf("== Local memory copy\n");
	print_lantency_array(base_cpu, base_numa_node, numa_latencies);
	printf("=============================================================\n");
	printf("== Cross memory read\n");
	print_lantency_array(base_cpu, base_numa_node, cross_read_numa_latencies);
	printf("=============================================================\n");
	printf("== Cross memory write\n");
	print_lantency_array(base_cpu, base_numa_node, cross_write_numa_latencies);
	printf("=============================================================\n");
	printf("== Read register\n");
	print_lantency_array(base_cpu, base_numa_node, register_read_latencies);
	printf("=============================================================\n");
	printf("== Write register\n");
	print_lantency_array(base_cpu, base_numa_node, register_write_latencies);

free_mem:
	/* Free all */
	for (i = 0; i < nr_numa_node; i++) {
		if (numa_mems_1[i])
			numa_free(numa_mems_1[i], blk_size);
		if (numa_mems_2[i])
			numa_free(numa_mems_2[i], blk_size);
	}

	free(numa_mems_1);
	free(numa_mems_2);
	numa_bitmask_free(cpumask);

	return 0;
}
