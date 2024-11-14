/**
 * bool __atomic_always_lock_free (size_t size, void *ptr)
 *
 * - returns true if objects of size bytes always generate lock-free atomic
 *   instructions for the target architecture.
 *   如果大小为字节的对象始终为目标体系结构生成无锁原子指令，则返回 true。
 *
 * - size must resolve to a compile-time constant and the result also resolves
 *   to a compile-time constant.
 *   大小必须解析为编译时常量，并且结果也解析为编译时常量。
 *
 * - ptr is an optional pointer to the object that may be used to determine
 *   alignment. A value of 0 indicates typical alignment should be used. The
 *   compiler may also ignore this parameter.
 *   ptr 是指向可用于确定对齐的对象的一个​​可选指针。
 *   值为 0 表示应使用典型对齐。编译器也可能忽略此参数。
 *
 * bool __atomic_is_lock_free (size_t size, void *ptr)
 *
 * - size could be runtime variable.
 */
#include <stdio.h>
#include <stdint.h>

int main(void)
{
	int size = 8;

#define PR_ALWAYS_LOCK_FREE(size, ptr) \
	printf("__atomic_always_lock_free(%s, ...) = %d\n", \
		#size, __atomic_always_lock_free(size, ptr));

#define PR_IS_LOCK_FREE(size, ptr) \
	printf("__atomic_is_lock_free(%s, ...) = %d\n", \
		#size, __atomic_is_lock_free(size, ptr));

	PR_ALWAYS_LOCK_FREE(1, 0);
	PR_ALWAYS_LOCK_FREE(2, 0);
	PR_ALWAYS_LOCK_FREE(3, 0);	// return false
	PR_ALWAYS_LOCK_FREE(4, 0);
	PR_ALWAYS_LOCK_FREE(5, 0);
	PR_ALWAYS_LOCK_FREE(6, 0);
	PR_ALWAYS_LOCK_FREE(7, 0);
	PR_ALWAYS_LOCK_FREE(8, 0);
	PR_ALWAYS_LOCK_FREE(sizeof(long long), 0);
	PR_ALWAYS_LOCK_FREE(16, 0);
	PR_ALWAYS_LOCK_FREE(32, 0);
#if defined(COMPILE_ERROR)
	PR_ALWAYS_LOCK_FREE(size, 0);
#endif

	printf("\n");

	PR_IS_LOCK_FREE(1, 0);
	PR_IS_LOCK_FREE(2, 0);
	PR_IS_LOCK_FREE(3, 0);	// return true
	PR_IS_LOCK_FREE(4, 0);
	PR_IS_LOCK_FREE(5, 0);
	PR_IS_LOCK_FREE(6, 0);
	PR_IS_LOCK_FREE(7, 0);
	PR_IS_LOCK_FREE(8, 0);
	PR_IS_LOCK_FREE(sizeof(long long), 0);
	PR_IS_LOCK_FREE(16, 0);
	PR_IS_LOCK_FREE(32, 0);
	PR_IS_LOCK_FREE(size, 0);

#undef PR_ALWAYS_LOCK_FREE
#undef PR_IS_LOCK_FREE

	return 0;
}
