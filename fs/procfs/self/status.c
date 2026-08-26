#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

/*
 * Measures the current (and peak) resident and virtual memories
 * usage of your linux C process, in kB
 */
void getMemory(long int *currRealMem, long int *peakRealMem,
	       long int *currVirtMem, long int *peakVirtMem)
{
	char buffer[128];
	FILE *file = fopen("/proc/self/status", "r");

	while (fscanf(file, " %127s", buffer) == 1) {
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
	size_t i, size = 1024 * 10240;
	char *str;

	str = malloc(size);

	for (i = 0; i < size; i += getpagesize())
		str[i] = 'A';

	getMemory(&currRealMem, &peakRealMem, &currVirtMem, &peakVirtMem);

	printf("RSS: %ld, HWM: %ld, Size: %ld, Peak: %ld\n",
		currRealMem, peakRealMem, currVirtMem, peakVirtMem);

	free(str);

	return 0;
}
