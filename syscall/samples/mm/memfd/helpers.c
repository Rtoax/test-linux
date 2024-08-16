#include <unistd.h>
#include <errno.h>
#include <linux/memfd.h>
#include <sys/syscall.h>
#include <sys/mman.h>


int sys_memfd_create(const char *name, unsigned int flags)
{
#if __GLIBC__ == 2 && __GLIBC_MINOR__ >= 26
	return memfd_create(name, flags);
#else
	return syscall(__NR_memfd_create, name, flags);
#endif
}

int sys_memfd_secret(unsigned int flags)
{
	return syscall(SYS_memfd_secret, flags);
}
