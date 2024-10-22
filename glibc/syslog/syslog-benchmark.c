#include <syslog.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>


int main(void)
{
	size_t cnt = 100000;

	setlogmask(LOG_UPTO(LOG_NOTICE));

	openlog("syslog-benchmark", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

	do {
		syslog(LOG_NOTICE, "notice: %ld\n", cnt);
	} while (cnt--);

	closelog();

	return 0;
}
