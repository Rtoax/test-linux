#include <stdio.h>
#include <pwd.h>

int main(void)
{
	FILE *fp;

	setpwent();

	fp = fopen("./new_passwd", "w");

	struct passwd *passwd;

	while ((passwd = getpwent()) != NULL) {
		printf("%s:%s:%d:%d:%s%s%s\n",
			passwd->pw_name, passwd->pw_passwd, passwd->pw_uid,
			passwd-> pw_gid, passwd->pw_gecos, passwd->pw_dir, passwd->pw_shell);
		putpwent(passwd, fp);
		passwd = NULL;
	}

	endpwent();
	fclose(fp);
	return 0;
}
