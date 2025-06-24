/**
 * Module Specific Register - MSR
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>
#include <inttypes.h>
#include <linux/types.h>


uint64_t rdmsr_on_cpu(uint32_t reg, int cpu)
{
	uint64_t data;
	int fd;
	char msr_file_name[64];

	sprintf(msr_file_name, "/dev/cpu/%d/msr", cpu);
	fd = open(msr_file_name, O_RDONLY);
	if (fd < 0) {
		if (errno == ENXIO) {
			fprintf(stderr, "rdmsr: No CPU %d\n", cpu);
			exit(2);
		} else if (errno == EIO) {
			fprintf(stderr, "rdmsr: CPU %d doesn't support MSRs\n",
				cpu);
			exit(3);
		} else {
			perror("rdmsr: open");
			exit(127);
		}
	}

	if (pread(fd, &data, sizeof(data), reg) != sizeof(data)) {
		if (errno == EIO) {
			fprintf(stderr, "rdmsr: CPU %d cannot read "
				"MSR 0x%08"PRIx32"\n",
				cpu, reg);
			exit(4);
		} else {
			perror("rdmsr: pread");
			exit(127);
		}
	}

	close(fd);

	return data;
}

void rdmsr_on_all_cpus(uint32_t reg)
{
	uint64_t data;
	int ncpu, i;

	ncpu = sysconf(_SC_NPROCESSORS_ONLN);
	printf("ncpu = %d\n", ncpu);

	for (i = 0; i < ncpu; i++) {
		data = rdmsr_on_cpu(reg, i);
		printf("CPU %-4d : %lx (%ld)\n", i, data, data);
	}
}

static int32_t rdmsr(int msr, uint64_t *val)
{
	int fd, ret;

	fd = open("/dev/cpu/0/msr", O_RDONLY);
	if (fd < 0) {
		perror("open:");
		return fd;
	}
	ret = pread(fd, val, sizeof(uint64_t), msr);
	close(fd);
	return ret;
}

int main(void)
{
	uint64_t tsc_hz;
	int32_t ret;

	ret = rdmsr(0xCE, &tsc_hz);
	printf("MSR tsc_hz = %lx\n", tsc_hz);

	rdmsr_on_all_cpus(0xCE);

	return ret;
}
