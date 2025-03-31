#include <libcgroup.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
	char string[100];
	char *mntpoint;

	strcpy(string, "memory");
	cgroup_get_subsys_mount_point(string, &mntpoint);

	printf("The mount point is: %s\n", string);

	return 0;
}
