#include <stdio.h>
#include <errno.h>
#include <grp.h>
#include <unistd.h>


int main(void)
{
	struct group *g = getgrgid(getgid());

	struct group *_group = getgrnam(g->gr_name);
	if (_group == NULL) {
		printf("getgrnam(\"%s\") failed\n", g->gr_name);

		switch(errno) {
		case EINTR:
			printf("A signal was caught.\n");
			break;
		case EIO:
			printf("I/O error.\n");
			break;

		case EMFILE:
			printf("The maximum number (OPEN_MAX) of files was open already in the calling process.\n");
			break;

		case ENFILE:
			printf("The maximum number of files was open already in the system.\n");
			break;

		case ENOMEM:
			printf("Insufficient memory to allocate group structure.\n");
			break;

		case ERANGE:
			printf("Insufficient buffer space supplied.\n");
			break;
		}

		return -1;
	}

	printf("%s:%d:%s\n", _group->gr_name, _group->gr_gid, _group->gr_mem[0]);
	return 0;
}
