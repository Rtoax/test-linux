/* see arch/sw_64/include/asm/barrier.h */

#define smp_mb()    __asm__ __volatile__("memb" : : : "memory")
#define smp_rmb()   __asm__ __volatile__("memb" : : : "memory")
/* sw6b core3 */
#define smp_wmb()   __asm__ __volatile__("memb" : : : "memory")
/* sw8a core4 */
#define smp_wmb_c4()   __asm__ __volatile__("wmemb" : : : "memory")

/* FIXME: what */
#define smp_rwmb()    __asm__ __volatile__("memb" : : : "memory")
