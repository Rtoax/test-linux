#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>

/*
 * Measures the current (and peak) resident and virtual memories
 * usage of your linux C process, in kB
 */
void getMemory(long int *currRealMem, long int *peakRealMem,
	       long int *currVirtMem, long int *peakVirtMem)
{
	char buffer[1024];

	FILE* file = fopen("/proc/self/status", "r");

	while (fscanf(file, " %1023s", buffer) == 1) {
		if (strcmp(buffer, "VmRSS:") == 0) {
			fscanf(file, " %ld", currRealMem);
		}
		if (strcmp(buffer, "VmHWM:") == 0) {
			fscanf(file, " %ld", peakRealMem);
		}
		if (strcmp(buffer, "VmSize:") == 0) {
			fscanf(file, " %ld", currVirtMem);
		}
		if (strcmp(buffer, "VmPeak:") == 0) {
			fscanf(file, " %ld", peakVirtMem);
		}
	}
	fclose(file);
}

int main(void)
{
	long int currRealMem, peakRealMem, currVirtMem, peakVirtMem;

	char *str = malloc(1024 * 1024 * 1024);
	str[1024 * 1024 - 1] = 'A';

	getMemory(&currRealMem, &peakRealMem, &currVirtMem, &peakVirtMem);

	printf("%ld, %ld, %ld, %ld\n", currRealMem, peakRealMem, currVirtMem, peakVirtMem);

	free(str);

	return 0;
}
