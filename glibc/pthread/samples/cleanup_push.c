/**
 * 从pthread_cleanup_push()的调用点到pthread_cleanup_pop()之间的程序段中的终止
 * 动作（包括调用 pthread_exit()和取消点终止）都将执行pthread_cleanup_push()所
 * 指定的清理函数。
 */
#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <pthread.h>

/* Allocate a temporary buffer. */
void *allocate_buffer(size_t size)
{
	printf("allocate_buffer.\n");
	return malloc(size);
}

/* Deallocate a temporary buffer. */
void deallocate_buffer(void *buffer)
{
	printf("deallocate_buffer.\n");
	free(buffer);
}

void do_some_work(void)
{
	/* Allocate a temporary buffer. */
	void *temp_buffer = allocate_buffer(1024);

	/* Register a cleanup handler for this buffer, to deallocate it in
	 * case the thread exits or is cancelled. */
	pthread_cleanup_push(deallocate_buffer, temp_buffer);

	/* Exit */
	int status = 12121;
	pthread_exit(&status);

	pthread_cleanup_pop(1);

	/* Never called because thread already exit. */
	deallocate_buffer(temp_buffer);
}

int main(void)
{
	do_some_work();
	return 0;
}
