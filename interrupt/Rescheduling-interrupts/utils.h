#pragma once
#include <errno.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/types.h>

#if defined(__x86_64__)
#ifndef RDTSC
#define RDTSC() ({\
    register uint32_t a,d; \
    __asm__ __volatile__( "rdtsc" : "=a"(a), "=d"(d)); \
    (((uint64_t)a)+(((uint64_t)d)<<32)); \
    })
#endif

/**
 *  cas，默认 smp 架构
 */
#ifndef CAS
#define CAS(ptr, val_old, val_new) ({ \
    char ret; \
    __asm__ __volatile__("lock; "\
        "cmpxchgl %2,%0; setz %1"\
        : "+m"(*ptr), "=q"(ret)\
        : "r"(val_new),"a"(val_old)\
        : "memory"); \
    ret;})
#endif
#endif


#define gettid() syscall(__NR_gettid)

#define log_enqueue(fmt...)  do{printf("\033[33m[%ld]", gettid());printf(fmt);printf("\033[m");}while(0)
#define log_dequeue(fmt...)  do{printf("\033[32m[%ld]", gettid());printf(fmt);printf("\033[m");}while(0)

#ifndef _unused
#define _unused             __attribute__((unused))
#endif
#ifndef always_inline
#define always_inline __attribute__ ((__always_inline__))
#endif

#if defined(__x86_64__)
#include "atomic-x86_64.h"
#endif

