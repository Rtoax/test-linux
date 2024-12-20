#include <syscall.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "bpf.h"

int sys_bpf(int cmd, union bpf_attr *attr, unsigned int size)
{
	return syscall(__NR_bpf, cmd, attr, size);
}

