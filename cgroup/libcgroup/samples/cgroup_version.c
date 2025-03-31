#include <libcgroup.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	const struct cgroup_library_version *version;
	version = cgroup_version();
	printf("%d.%d.%d\n", version->major, version->minor, version->release);
	return 0;
}
