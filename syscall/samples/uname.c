#include <stdio.h>
#include <sys/utsname.h>


int main(void)
{
	struct utsname name;

	uname(&name);

	printf(
		"sysname = %s\n"
		"release = %s\n"
		"version = %s\n"
		"machine = %s\n"
		"nodename = %s\n"
		"domainname = %s\n",
		name.sysname,
		name.release,
		name.version,
		name.machine,
		name.nodename,
#if _UTSNAME_DOMAIN_LENGTH - 0
		/* Name of the domain of this node on the network.  */
# ifdef __USE_GNU
		name.domainname
# else
		name.__domainname
# endif
#else
		/*no domainname*/ "no domainname"
#endif
	);

	return 0;
}
