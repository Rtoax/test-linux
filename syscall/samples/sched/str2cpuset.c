#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sched.h>

#include "sched_helpers.h"

int main(int argc, char *argv[])
{
	int i;
	cpu_set_t cpuset;

	char *cpulist[] = {
		"1",
		"25",
		"1-9",
		"1,9",
		"1,9-12",
		"1,9-12,20-25,28,29",
	};

	for (i = 0; i < ARRAY_SIZE(cpulist); i++) {
		char *cpu = cpulist[i];
		str2cpuset(cpu, &cpuset);
		printf("- %32s : ", cpu);
		print_cpuset(&cpuset);
	}
	return 0;
}
