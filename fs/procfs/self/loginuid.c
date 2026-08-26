#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


uid_t get_process_owner(pid_t pid)
{
	char procpath[128];
	struct stat info;

	snprintf(procpath, sizeof(procpath), "/proc/%d/loginuid", pid);

	if (stat(procpath, &info))
		return 0;
	return info.st_uid;
}

int main(void)
{
	pid_t pid = getpid();
	uid_t uid = get_process_owner(pid);
	printf("Pid %d belongs to uid %d\n", pid, uid);
	return 0;
}
