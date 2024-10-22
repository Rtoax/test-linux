#include <syslog.h>
#include <unistd.h>
#include <stdarg.h>


void mysyslog(int priority, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vsyslog(priority, fmt, ap);
	va_end(ap);
}

int main(void)
{
	openlog("log1", LOG_PERROR, LOG_MAIL);
	syslog(LOG_INFO, "info: %s, %m", __FILE__);
	syslog(LOG_ERR, "err: %s", __FILE__);
	syslog(LOG_WARNING, "warning: %s", __FILE__);
	closelog();

	openlog("log2", LOG_PERROR, LOG_MAIL);
	syslog(LOG_INFO, "info: %s", __FILE__);
	syslog(LOG_ERR, "info: %s", __FILE__);
	syslog(LOG_WARNING, "info: %s", __FILE__);
	closelog();

	setlogmask(LOG_UPTO(LOG_NOTICE));
	openlog("log3", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	mysyslog(LOG_NOTICE, "notice: uid = %d", getuid());
	syslog(LOG_NOTICE, "notice: %s", __FILE__);
	mysyslog(LOG_INFO, "info");
	closelog();

	return 0;
}
