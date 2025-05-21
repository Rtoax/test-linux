#include <libcgroup.h>
#include <stdio.h>

int main(int argc, char **argv)
{
/**
 * libcgroup commit a95532a8ea22 ("libcgroup.so: Add a function to get the library version")
 * add CGROUP_VER_MAJOR and cgroup_version().
 */
#ifdef CGROUP_VER_MAJOR
	const struct cgroup_library_version *version;
	version = cgroup_version();
	printf("%d.%d.%d\n", version->major, version->minor, version->release);
#else
# pragma message "libcgroup not support cgroup_version() yet"
#endif
	return 0;
}
