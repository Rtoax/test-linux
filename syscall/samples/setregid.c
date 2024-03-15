#include <stdio.h>
#include <errno.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

int main(void)
{
	int ret;
	/* the real UID, the effective UID, and the saved set-user-ID */
	gid_t rgid, egid, sgid;

	ret = getresgid(&rgid, &egid, &sgid);
	printf("getresgid : rsig:%d egid:%d sgid:%d\n", rgid, egid, sgid);

	ret = setregid(rgid, egid);
	if (ret != 0) {
		perror("setregid: ");
	}

	return 0;
}
