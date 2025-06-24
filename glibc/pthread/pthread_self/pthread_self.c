#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>

#include "tls.h"
#include "res_state.h"

int sys_gettid(void)
{
	int ret = syscall(__NR_gettid);
	return ret >= 0 ? ret : -errno;
}

int gettid(void)
{
	return sys_gettid();
}

/* Some compilers, like SunOS4 cc, don't have offsetof in <stddef.h>.  */
#ifndef offsetof
# define offsetof(type,ident) ((size_t)&(((type*)0)->ident))
#endif

#ifdef __x86_64__
# define __PTHREAD_MUTEX_HAVE_PREV      1
#elif !defined(__aarch64__)
# define __PTHREAD_MUTEX_HAVE_PREV      0
#endif

/* Alignment requirement for TCB.  */
#define TCB_ALIGNMENT		16
/* This is the value this implementation supports.  */
#define PTHREAD_KEYS_MAX	1024
/* We indeed have inlined functions.  */
#define HP_TIMING_INLINE	(1)


/* We keep thread specific data in a special data structure, a two-level
	 array.  The top-level array contains pointers to dynamically allocated
	 arrays of a certain number of data pointers.  So we can implement a
	 sparse array.  Each dynamic second-level array has
		    PTHREAD_KEY_2NDLEVEL_SIZE
	 entries.  This value shouldn't be too large.  */
#define PTHREAD_KEY_2NDLEVEL_SIZE       32
/* We need to address PTHREAD_KEYS_MAX key with PTHREAD_KEY_2NDLEVEL_SIZE
	 keys in each subarray.  */
#define PTHREAD_KEY_1STLEVEL_SIZE \
	((PTHREAD_KEYS_MAX + PTHREAD_KEY_2NDLEVEL_SIZE - 1) \
	 / PTHREAD_KEY_2NDLEVEL_SIZE)


/* We use 64bit values for the times.  */
typedef unsigned long long int hp_timing_t;

/* Internal: doubly linked lists.  */

/* Basic type for the double-link list.  */
typedef struct list_head {
	struct list_head *next;
	struct list_head *prev;
} list_t;


/* Data structure used by the kernel to find robust futexes.  */
struct robust_list_head {
	void *list;
	long int futex_offset;
	void *list_op_pending;
};

/* Internal version of the buffer to store cancellation handler
 * information.  */
struct pthread_unwind_buf {
	struct {
		__jmp_buf jmp_buf;
		int mask_was_saved;
	} cancel_jmp_buf[1];

	union {
		/* This is the placeholder of the public version.  */
		void *pad[4];

		struct {
			/* Pointer to the previous cleanup buffer.  */
			struct pthread_unwind_buf *prev;

			/* Backward compatibility: state of the old-style cleanup
			 * handler at the time of the previous new-style cleanup handler
			 * installment.  */
			struct _pthread_cleanup_buffer *cleanup;

			/* Cancellation type before the push call.  */
			int canceltype;
		} data;
	} priv;
};

#define TD_EVENTSIZE	2
#define BT_UISHIFT	5 /* log base 2 of BT_NBIPUI, to extract word index */
#define BT_NBIPUI	(1 << BT_UISHIFT)       /* n bits per unsigned int */
#define BT_UIMASK	(BT_NBIPUI - 1)         /* to extract bit index */

/* Bitmask of enabled events. */
typedef struct td_thr_events {
	uint32_t event_bits[TD_EVENTSIZE];
} td_thr_events_t;

/* Events reportable by the thread implementation.  */
typedef enum {
	TD_ALL_EVENTS,		 /* Pseudo-event number.  */
	TD_EVENT_NONE = TD_ALL_EVENTS, /* Depends on context.  */
	TD_READY,			 /* Is executable now. */
	TD_SLEEP,			 /* Blocked in a synchronization obj.  */
	TD_SWITCHTO,			 /* Now assigned to a process.  */
	TD_SWITCHFROM,		 /* Not anymore assigned to a process.  */
	TD_LOCK_TRY,			 /* Trying to get an unavailable lock.  */
	TD_CATCHSIG,			 /* Signal posted to the thread.  */
	TD_IDLE,			 /* Process getting idle.  */
	TD_CREATE,			 /* New thread created.  */
	TD_DEATH,			 /* Thread terminated.  */
	TD_PREEMPT,			 /* Preempted.  */
	TD_PRI_INHERIT,		 /* Inherited elevated priority.  */
	TD_REAP,			 /* Reaped.  */
	TD_CONCURRENCY,		 /* Number of processes changing.  */
	TD_TIMEOUT,			 /* Conditional variable wait timed out.  */
	TD_MIN_EVENT_NUM = TD_READY,
	TD_MAX_EVENT_NUM = TD_TIMEOUT,
	TD_EVENTS_ENABLE = 31		/* Event reporting enabled.  */
} td_event_e;

/* Structure containing event data available in each thread structure.  */
typedef struct
{
	td_thr_events_t eventmask;    /* Mask of enabled events.  */
	td_event_e eventnum;      /* Number of last event.  */
	void *eventdata;      /* Data associated with event.  */
} td_eventbuf_t;


/* @@@ The IA-64 ABI uses a 64-bit word to identify the producer and
 * consumer of an exception.  We'll go along with this for now even on
 * 32-bit machines.  We'll need to provide some other option for
 * 16-bit machines and for machines with > 8 bits per byte.  */
typedef unsigned _Unwind_Exception_Class __attribute__((__mode__(__DI__)));

/* The unwind interface uses reason codes in several contexts to
 * identify the reasons for failures or other actions.  */
typedef enum {
	_URC_NO_REASON = 0,
	_URC_FOREIGN_EXCEPTION_CAUGHT = 1,
	_URC_FATAL_PHASE2_ERROR = 2,
	_URC_FATAL_PHASE1_ERROR = 3,
	_URC_NORMAL_STOP = 4,
	_URC_END_OF_STACK = 5,
	_URC_HANDLER_FOUND = 6,
	_URC_INSTALL_CONTEXT = 7,
	_URC_CONTINUE_UNWIND = 8
} _Unwind_Reason_Code;

typedef unsigned _Unwind_Word __attribute__((__mode__(__unwind_word__)));

/* The unwind interface uses a pointer to an exception header object
 * as its representation of an exception being thrown. In general, the
 * full representation of an exception object is language- and
 * implementation-specific, but it will be prefixed by a header
 * understood by the unwind interface.  */

struct _Unwind_Exception;

typedef void (*_Unwind_Exception_Cleanup_Fn) (_Unwind_Reason_Code,
					      struct _Unwind_Exception *);

struct _Unwind_Exception
{
	_Unwind_Exception_Class exception_class;
	_Unwind_Exception_Cleanup_Fn exception_cleanup;
	_Unwind_Word private_1;
	_Unwind_Word private_2;

	/* @@@ The IA-64 ABI says that this structure must be double-word aligned.
	 * Taking that literally does not make much sense generically.  Instead we
	 * provide the maximum alignment required by any type for the machine.  */
} __attribute__((__aligned__));


/* Data strcture used to handle thread priority protection.  */
struct priority_protection_data {
	int priomax;
	unsigned int priomap[];
};

struct tls_internal_t {
	char *strsignal_buf;
	char *strerror_l_buf;
};


/* Thread descriptor data structure.  */
struct pthread {
	union {
#if !TLS_DTV_AT_TP
		/* This overlaps the TCB as used for TLS without threads (see tls.h).  */
		tcbhead_t header;
#else
		struct {
		/* multiple_threads is enabled either when the process has spawned at
		 * least one thread or when a single-threaded process cancels itself.
		 * This enables additional code to introduce locking before doing some
		 * compare_and_exchange operations and also enable cancellation points.
		 * The concepts of multiple threads and cancellation points ideally
		 * should be separate, since it is not necessary for multiple threads to
		 * have been created for cancellation points to be enabled, as is the
		 * case is when single-threaded process cancels itself.

		 * Since enabling multiple_threads enables additional code in
		 * cancellation points and compare_and_exchange operations, there is a
		 * potential for an unneeded performance hit when it is enabled in a
		 * single-threaded, self-canceling process.  This is OK though, since a
		 * single-threaded process will enable async cancellation only when it
		 * looks to cancel itself and is hence going to end anyway.  */
			int multiple_threads;
			int gscope_flag;
		} header;
#endif
		/* This extra padding has no special purpose, and this structure layout
		 * is private and subject to change without affecting the official ABI.
		 * We just have it here in case it might be convenient for some
		 * implementation-specific instrumentation hack or suchlike.  */
		void *__padding[24];
	};

	/* This descriptor's link on the `stack_used' or `__stack_user' list.  */
	list_t list;

	/* Thread ID - which is also a 'is this thread descriptor (and
	 * therefore stack) used' flag.  */
	pid_t tid;

	/* Ununsed.  */
	pid_t pid_ununsed;


	/* List of robust mutexes the thread is holding.  */
#if __PTHREAD_MUTEX_HAVE_PREV
	void *robust_prev;
	struct robust_list_head robust_head;
#else
	union {
		__pthread_slist_t robust_list;
		struct robust_list_head robust_head;
	};
#endif

	/* List of cleanup buffers.  */
	struct _pthread_cleanup_buffer *cleanup;

	/* Unwind information.  */
	struct pthread_unwind_buf *cleanup_jmp_buf;
#define HAVE_CLEANUP_JMP_BUF

	/* Flags determining processing of cancellation.  */
	int cancelhandling;


	/* Flags.  Including those copied from the thread attribute.  */
	int flags;

	/* We allocate one block of references here.  This should be enough
		 to avoid allocating any memory dynamically for most applications.  */
	struct pthread_key_data {
		/* Sequence number.  We use uintptr_t to not require padding on
		 * 32- and 64-bit machines.  On 64-bit machines it helps to avoid
		 * wrapping, too.
		 */
		uintptr_t seq;

		/* Data pointer.  */
		void *data;
	} specific_1stblock[PTHREAD_KEY_2NDLEVEL_SIZE];

	/* Two-level array for the thread-specific data.  */
	struct pthread_key_data *specific[PTHREAD_KEY_1STLEVEL_SIZE];

	/* Flag which is set when specific data is set.  */
	bool specific_used;

	/* True if events must be reported.  */
	bool report_events;

	/* True if the user provided the stack.  */
	bool user_stack;

	/* True if thread must stop at startup time.  */
	bool stopped_start;

	/* Formerly used for dealing with cancellation.  */
	int parent_cancelhandling_unsed;

	/* Lock to synchronize access to the descriptor.  */
	int lock;

	/* Lock for synchronizing setxid calls.  */
	unsigned int setxid_futex;

#if HP_TIMING_INLINE
	hp_timing_t cpuclock_offset_ununsed;
#endif

	/* If the thread waits to join another one the ID of the latter is
	 * stored here.
	 *
	 * In case a thread is detached this field contains a pointer of the
	 * TCB if the thread itself.  This is something which cannot happen
	 * in normal operation.
	 */
	struct pthread *joinid;
	/* Check whether a thread is detached.  */
	#define IS_DETACHED(pd) ((pd)->joinid == (pd))

	/* The result of the thread function.  */
	void *result;

	/* Scheduling parameters for the new thread.  */
	struct sched_param schedparam;
	int schedpolicy;

	/* Start position of the code to be executed and the argument passed
		 to the function.  */
	void *(*start_routine) (void *);
	void *arg;

	/* Debug state.  */
	td_eventbuf_t eventbuf;
	/* Next descriptor with a pending event.  */
	struct pthread *nextevent;

#if 1
	/* Machine-specific unwind info.  */
	struct _Unwind_Exception exc;

	/* If nonzero, pointer to the area allocated for the stack and guard. */
	void *stackblock;
	/* Size of the stackblock area including the guard.  */
	size_t stackblock_size;
	/* Size of the included guard area.  */
	size_t guardsize;
	/* This is what the user specified and what we will report.  */
	size_t reported_guardsize;

	/* Thread Priority Protection data.  */
	struct priority_protection_data *tpp;

	/* Resolver state.  */
	struct __res_state res;

	/* Signal mask for the new thread.  Used during thread startup to
	 * restore the signal mask.  (Threads are launched with all signals
	 * masked.)  */
	sigset_t sigmask;

	/* Indicates whether is a C11 thread created by thrd_creat.  */
	bool c11;

	/* Used on strsignal.  */
	struct tls_internal_t tls_state;

	/* This member must be last.  */
	char end_padding[];

	#define PTHREAD_STRUCT_END_PADDING \
	(sizeof (struct pthread) - offsetof (struct pthread, end_padding))
#else
	char more_data[0];
#endif
} __attribute ((aligned (TCB_ALIGNMENT)));

/**
 * Return the thread descriptor for the current thread.
 *
 * The contained asm must *not* be marked volatile since otherwise
 * assignments like
 *	pthread_descr self = thread_self();
 * do not get optimized away.
 */
# define THREAD_SELF \
	({ struct pthread *__self;					\
		 asm ("mov %%fs:%c1,%0" : "=r" (__self)			\
		: "i" (offsetof (struct pthread, header.self)));	\
		 __self;})

pthread_t rtoax_pthread_self(void)
{
	return (pthread_t)THREAD_SELF;
}

void *task(void *arg)
{
	printf("%ld:%ld.\n", pthread_self(), rtoax_pthread_self());

	struct pthread *pt = (struct pthread *)rtoax_pthread_self();

	printf("header.multiple_threads = %d\n", pt->header.multiple_threads);
	printf("header.gscope_flag = %d\n", pt->header.gscope_flag);
	printf("tid = %d(%d)\n", pt->tid, gettid());
	printf("pid_ununsed = %d(%d)\n", pt->pid_ununsed, getpid());
	printf("cancelhandling = %d\n", pt->cancelhandling);
	printf("flags = %d\n", pt->flags);
	printf("user_stack = %d\n", pt->user_stack);

	printf("schedparam.sched_priority = %d\n", pt->schedparam.sched_priority);
	printf("schedpolicy = %d\n", pt->schedpolicy);
	printf("start_routine = %p(%p)\n", pt->start_routine, task);
	printf("arg = %p(%p)\n", pt->arg, arg);
	printf("stackblock_size = %zd\n", pt->stackblock_size);
	printf("guardsize = %zd\n", pt->guardsize);
	printf("reported_guardsize = %zd\n", pt->reported_guardsize);

	printf("c11 = %d\n", pt->c11);

	pthread_exit(NULL);
}

int main(void)
{
	static int arg;

	pthread_t thread1;
	pthread_create(&thread1, NULL, task, &arg);
	pthread_join(thread1, NULL);
	return 0;
}
