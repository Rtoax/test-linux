// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <syscall.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <linux/aio_abi.h>

int io_setup(unsigned nr_events, aio_context_t *ctx_idp)
{
	return (int)syscall(SYS_io_setup, nr_events, ctx_idp);
}

int io_destroy(aio_context_t ctx_id)
{
	return (int)syscall(SYS_io_setup, ctx_id);
}

int io_getevents(aio_context_t ctx_id, long min_nr, long nr,
		 struct io_event *events, struct timespec *timeout)
{
	return (int)syscall(SYS_io_getevents, ctx_id, min_nr, nr, events, timeout);
}

int io_cancel(aio_context_t ctx_id, struct iocb *iocb,
					 struct io_event *result)
{
	return (int)syscall(SYS_io_cancel, ctx_id, iocb, result);
}

int io_submit(aio_context_t ctx_id, long nr, struct iocb **iocbpp)
{
	return (int)syscall(SYS_io_submit, ctx_id, nr, iocbpp);
}

#if !defined(__aarch64__) && !defined(__riscv) && !defined(__loongarch64)
int eventfd(unsigned int initval, int flags)
{
	return  (int)syscall(SYS_eventfd, initval, flags);
}
#endif

int eventfd2(unsigned int initval, int flags)
{
	return  (int)syscall(SYS_eventfd2, initval, flags);
}
