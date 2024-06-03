#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>

int main(void)
{
	struct passwd *passwd;
	FILE *fp = fopen("./new_passwd", "r");

	if (!fp) {
		fprintf(stderr, "fopen new_passwd %m\b");
		exit(1);
	}

	while ((passwd = fgetpwent(fp)) != NULL) {
		printf("pw_name = %s\n", passwd->pw_name);
		printf("pw_passwd = %s\n", passwd->pw_passwd);
		printf("pw_uid = %d\n", passwd->pw_uid);
		printf(" pw_gid = %d\n", passwd-> pw_gid);
		printf("pw_gecos = %s\n", passwd->pw_gecos);
		printf("pw_dir = %s\n", passwd->pw_dir);
		printf("pw_shell = %s\n", passwd->pw_shell);
		passwd = NULL;
	}
	return 0;
}
