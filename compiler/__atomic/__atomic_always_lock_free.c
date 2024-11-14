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
 */
#include <stdio.h>
#include <stdint.h>

int main(void)
{
#define PRINT_ALWAY_LOCK_FREE(size, ptr) \
	printf("__atomic_always_lock_free(%s, ...) = %d\n", \
		#size, __atomic_always_lock_free(size, ptr));

	PRINT_ALWAY_LOCK_FREE(1, 0);
	PRINT_ALWAY_LOCK_FREE(2, 0);
	PRINT_ALWAY_LOCK_FREE(3, 0);
	PRINT_ALWAY_LOCK_FREE(4, 0);
	PRINT_ALWAY_LOCK_FREE(8, 0);
	PRINT_ALWAY_LOCK_FREE(sizeof(long long), 0);
	PRINT_ALWAY_LOCK_FREE(16, 0);
	PRINT_ALWAY_LOCK_FREE(32, 0);

#undef PRINT_ALWAY_LOCK_FREE
	return 0;
}
