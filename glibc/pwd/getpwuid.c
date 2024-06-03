#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

int main(void)
{
	struct passwd *_passwd = getpwuid(getuid());

	printf("pw_name = %s\n", _passwd->pw_name);
	printf("pw_passwd = %s\n", _passwd->pw_passwd);
	printf("pw_uid = %d\n", _passwd->pw_uid);
	printf(" pw_gid = %d\n", _passwd->pw_gid);
	printf("pw_gecos = %s\n", _passwd->pw_gecos);
	printf("pw_dir = %s\n", _passwd->pw_dir);
	printf("pw_shell = %s\n", _passwd->pw_shell);

	return 0;
}
