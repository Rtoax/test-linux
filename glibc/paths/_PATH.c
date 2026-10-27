#include <stdio.h>
#include <paths.h>

int main(void)
{
#define P(p) printf("%s = %s\n", #p, p)
	P(_PATH_DEFPATH);
	P(_PATH_STDPATH);
	P(_PATH_BSHELL);
	P(_PATH_CONSOLE);
	P(_PATH_CSHELL);
	P(_PATH_DEVDB);
	P(_PATH_DEVNULL);
	P(_PATH_DRUM);
	P(_PATH_GSHADOW);
	P(_PATH_KLOG);
	P(_PATH_KMEM);
	P(_PATH_LASTLOG);
	P(_PATH_MAILDIR);
	P(_PATH_MAN);
	P(_PATH_MEM);
	P(_PATH_MNTTAB);
	P(_PATH_MOUNTED);
	P(_PATH_NOLOGIN);
	P(_PATH_PRESERVE);
	P(_PATH_RWHODIR);
	P(_PATH_SENDMAIL);
	P(_PATH_SHADOW);
	P(_PATH_SHELLS);
	P(_PATH_TTY);
	P(_PATH_UNIX);
	P(_PATH_UTMP);
	P(_PATH_VI);
	P(_PATH_WTMP);
	P(_PATH_DEV);
	P(_PATH_TMP);
	P(_PATH_VARDB);
	P(_PATH_VARRUN);
	P(_PATH_VARTMP);
#undef P

	return 0;
}
