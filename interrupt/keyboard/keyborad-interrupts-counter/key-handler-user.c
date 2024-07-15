#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "module-interface.h"

void print_help(void)
{
	printf("Available commands:\n\n");
	printf("key-handler-api --help                      \t - show this help\n");
	printf("key-handler-api, key-handler-api --get-count\t - show interrupts counter\n");
	printf("key-handler-api --get-reset-date            \t - show last counter reset\n");
	printf("key-handler-api --reset                     \t - reset interrupts counter\n");
}

void get_interrupts_count(int file)
{
	char output[MAX_IO_BUFFER];
	if (ioctl(file, QUERY_GET_RESET_COUNT, output) != -1)
		printf("Interrupts: %s\n", output);
}

void get_reset_date(int file)
{
	unsigned long long timestamp;
	if (ioctl(file, QUERY_GET_RESET_DATE, &timestamp) != -1)
		printf("Last reset (UTC): %llu\n", timestamp);
}

void reset_counter(int file)
{
	ioctl(file, QUERY_RESET_COUNTER);
}

int main(int argc, char ** argv)
{
	int device_file = open("/dev/"DEVICE_NAME, O_RDWR);

	if (argc > 2) {
		printf("Unsupported operation\n");
		print_help();
	} else if (argc == 1) {
		get_interrupts_count(device_file);
	} else if (argc == 2) {
		if (strcmp(argv[1], "--help") == 0)
			print_help();
		else if (strcmp(argv[1], "--get-count") == 0)
			get_interrupts_count(device_file);
		else if (strcmp(argv[1], "--get-reset-date") == 0)
			get_reset_date(device_file);
		else if (strcmp(argv[1], "--reset") == 0)
			reset_counter(device_file);
		else {
			printf("Unsupported operation\n");
			print_help();
		}
	}

	return 0;
}
