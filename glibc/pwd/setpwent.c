#include <stdio.h>
#include <pwd.h>

int main(void)
{
	struct passwd *_passwd;

	setpwent();

	while ((_passwd = getpwent()) != NULL) {
	    printf("%s:%s:%d:%d:%s:%s:%s\n",
	            _passwd->pw_name, _passwd->pw_passwd, _passwd->pw_uid,
	            _passwd->pw_gid, _passwd->pw_gecos, _passwd->pw_dir, _passwd->pw_shell);

	    _passwd = NULL;
	}

	endpwent();

	return 0;
}

