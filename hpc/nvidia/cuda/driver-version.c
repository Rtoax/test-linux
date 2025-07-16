#include <errno.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <pthread.h>
#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define LOGGER(lv, fmt...) printf(fmt);

#define DRIVER_VERSION_PROC_PATH "/proc/driver/nvidia/version"
#define DRIVER_VERSION_MATCH_PATTERN "([0-9]+)(\\.[0-9]+)+"

static void matchRegex(const char *pattern, const char *matchString, char *version)
{
	regex_t	 regex;
	int		 reti;
	regmatch_t	  matches[1];
	char		msgbuf[512];

	reti = regcomp(&regex, pattern, REG_EXTENDED);
	if (reti) {
		LOGGER(4, "Could not compile regex: %s", DRIVER_VERSION_MATCH_PATTERN);
		return;
	}

	reti = regexec(&regex, matchString, 1, matches, 0);
	switch (reti) {
	case 0:
		strncpy(version, matchString + matches[0].rm_so,
			matches[0].rm_eo - matches[0].rm_so);
		version[matches[0].rm_eo - matches[0].rm_so] = '\0';
		break;
	case REG_NOMATCH:
		LOGGER(4, "Regex does not match for string: %s", matchString);
		break;
	default:
		regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		LOGGER(4, "Regex match failed: %s", msgbuf);
	}

	regfree(&regex);
	return;
}

static void read_version_from_proc(char *version)
{
	char *line = NULL;
	size_t len = 0;

	FILE *fp = fopen(DRIVER_VERSION_PROC_PATH, "r");
	if (fp == NULL) {
		LOGGER(4, "can't open %s, error %s", DRIVER_VERSION_PROC_PATH, strerror(errno));
		return;
	}

	while ((getline(&line, &len, fp) != -1)) {
		if (strncmp(line, "NVRM", 4) == 0) {
			matchRegex(DRIVER_VERSION_MATCH_PATTERN, line, version);
			break;
		}
	}
	fclose(fp);
}

int main(void)
{
	char version[512];
	read_version_from_proc(version);
	printf("%s\n", version);
	return 0;
}
