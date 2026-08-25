#define _XOPEN_SOURCE
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <regex.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

struct timerun {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_day;
	int tm_year;
};

typedef enum {
	__TIME_PATTERN_MS = 0,		//00:00
	__TIME_PATTERN_HMS = 1,		//00:00:00
	__TIME_PATTERN_DHMS = 2,	//00-00:00:00
	__TIME_PATTERN_NOTMATCH = 3,
}__TIME_PATTERN;

static int parse_time_string(__TIME_PATTERN time_pattern, const char *time_str, struct timerun *tr)
{
	if (time_pattern != __TIME_PATTERN_MS &&
		time_pattern != __TIME_PATTERN_HMS &&
		time_pattern != __TIME_PATTERN_DHMS
		)
	{
		return -1;
	}

	if (!time_str)
		return -1;

	static const char * const time_strptime_pattern[] = {
		"%M:%S",	//00:00
		"%H:%M:%S",	//00:00:00
		"%j-%H:%M:%S",	//00-00:00:00
	};

	struct tm t4;

	memset(&t4, 0, sizeof(struct tm));
	memset(tr, 0, sizeof(struct timerun));

	strptime(time_str, time_strptime_pattern[time_pattern], &t4);

	tr->tm_year = 0;
	tr->tm_day = t4.tm_yday?t4.tm_yday+1:0;
	tr->tm_hour = t4.tm_hour;
	tr->tm_min = t4.tm_min;
	tr->tm_sec = t4.tm_sec;

	return 0;
}

static __TIME_PATTERN match_pattern(const char *str)
{
	static const char * const time_regex_pattern[] = {
		"^(([0-9]|[0-9]\\w+)\\:([0-9]|[0-9]\\w+)){1,1}$",   //00:00
		"^(([0-9]|[0-9]\\w+)\\:){2,2}([0-9]|[0-9]\\w+)$",   //00:00:00
		"^([0-9]|([0-9]\\w+))\\-(([0-9]|[0-9]\\w+)\\:){2,2}[0-9]\\w+$",   //00-00:00:00
	};

	int status = 0;
	int flag = REG_EXTENDED, ipattern = __TIME_PATTERN_MS;
	regmatch_t pmatch[1];
	const size_t nmatch = 1;
	regex_t reg;

	do {
		regcomp(&reg, time_regex_pattern[ipattern], flag);
		status = regexec(&reg, str, nmatch, pmatch, 0);
		if (status == REG_NOMATCH) {
			ipattern++;
		} else if (status == 0) {
			regfree(&reg);
			break;
		}
		if (ipattern == __TIME_PATTERN_NOTMATCH) {
			regfree(&reg);
			break;
		}
	} while(1);

	return ipattern;
}

int get_process_runtime(int pid, const char *pname, struct timerun *tr)
{
	char cmd[256] = {0};
	char buffer[256] = {0};

	if (pname) {
		sprintf(cmd, "ps -eo pid,etime,cmd | grep %s | grep %d | awk '{print $2}'", pname, pid);
	} else {
		sprintf(cmd, "ps -eo pid,etime,cmd | grep %d | awk '{print $2}'", pid);
	}
	FILE *fpcmd = popen(cmd, "r");

	fgets(buffer, sizeof(buffer), fpcmd);

	buffer[strlen(buffer)-1] = '\0';
	int pattern = match_pattern(buffer);

	parse_time_string(pattern, buffer, tr);

	pclose(fpcmd);

	return 0;
}

int main(int argc, char *argv[])
{
	struct timerun tr;

	while (1) {
		sleep(1);
		get_process_runtime(getpid(), argv[0], &tr);
		get_process_runtime(1, "systemd", &tr);
		printf("running time %d-%d:%d:%d\n", tr.tm_day, tr.tm_hour, tr.tm_min, tr.tm_sec);
	}
}
