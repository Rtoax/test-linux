#define barrier() __asm__ __volatile__("": : :"memory")

#if defined(__i386__)
#define mb()	asm volatile("lock; addl $0,0(%%esp)" ::: "memory")
#define rmb()	asm volatile("lock; addl $0,0(%%esp)" ::: "memory")
#define wmb()	asm volatile("lock; addl $0,0(%%esp)" ::: "memory")
#elif defined(__x86_64__)
#define mb() 	asm volatile("mfence":::"memory")
#define rmb()	asm volatile("lfence":::"memory")
#define wmb()	asm volatile("sfence" ::: "memory")
#endif

