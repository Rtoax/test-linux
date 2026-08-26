/**
 * /proc/self/stat format:
 * pid (comm) state ppid pgrp session tty_nr tpgid flags minflt cminflt majflt cmajflt utime stime cutime cstime priority nice num_threads itrealvalue starttime
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

time_t get_process_start_time(pid_t pid)
{
	char path[256];
	char buffer[2048];
	char *token;
	char *saveptr;
	int field = 0;
	unsigned long starttime_ticks = 0;
	FILE *fp;

	snprintf(path, sizeof(path), "/proc/%d/stat", pid);

	fp = fopen(path, "r");
	if (!fp) {
		perror("Failed to open stat file");
		return -1;
	}

	if (fgets(buffer, sizeof(buffer), fp) == NULL) {
		perror("Failed to read stat file");
		fclose(fp);
		return -1;
	}
	fclose(fp);

	/* locate (comm) */
	char *start_paren = strchr(buffer, '(');
	char *end_paren = strrchr(buffer, ')');
	if (!start_paren || !end_paren) {
		fprintf(stderr, "Failed to parse command field\n");
		return -1;
	}

	/* Handle left string */
	char *remaining = end_paren + 1;
	/* skip space */
	while (*remaining == ' ') remaining++;

	token = strtok_r(remaining, " ", &saveptr);
	while (token != NULL) {
		/* get starttime */
		if (field == 19) {
			starttime_ticks = strtoul(token, NULL, 10);
			break;
		}
		token = strtok_r(NULL, " ", &saveptr);
		field++;
	}

	if (field < 19) {
		fprintf(stderr, "Insufficient fields in stat file\n");
		return -1;
	}

	FILE *uptime_fp = fopen("/proc/uptime", "r");
	if (!uptime_fp) {
		perror("Failed to open uptime file");
		return -1;
	}

	double uptime_seconds;
	if (fscanf(uptime_fp, "%lf", &uptime_seconds) != 1) {
		perror("Failed to read uptime");
		fclose(uptime_fp);
		return -1;
	}
	fclose(uptime_fp);

	time_t now = time(NULL);
	time_t boot_time = now - (time_t)uptime_seconds;

	long clk_tck = sysconf(_SC_CLK_TCK);
	if (clk_tck <= 0) {
		fprintf(stderr, "Failed to get system clock ticks per second\n");
		return -1;
	}

	time_t start_time = boot_time + (starttime_ticks / clk_tck);
	return start_time;
}

int main(int argc, char *argv[])
{
	pid_t target_pid;
	char time_str[64];
	time_t start_time;
	struct tm *time_info;

	if (argc > 1) {
		target_pid = (pid_t)atoi(argv[1]);
	} else {
		target_pid = getpid();
	}

	start_time = get_process_start_time(target_pid);
	if (start_time == -1) {
		fprintf(stderr, "Error retrieving start time\n");
		return EXIT_FAILURE;
	}

	time_info = localtime(&start_time);
	strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);

	printf("Process %d started at: %s\n", target_pid, time_str);
	return EXIT_SUCCESS;
}
