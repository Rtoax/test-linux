/**
 * pthread_detach函数吧指定的线程转变为脱离状态
 *
 * 一个线程可以使joinable（可汇合的，默认值），也可以是detached（脱离的），
 * 当一个可汇合的线程终止时，他的线程ID和退出状态将留存到另一个线程对它调用
 * pthread_join。脱离的线程却像守护进程，当他们终止时，所有相关资源都被释放.
 * 我们不能等待他们终止。如果一个线程需要知道另一个线程什么时候终止，那最好
 * 保持第二个线程的可汇合状态
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include <libs/log.h>

void *test_task_fn(void *unused)
{
	log_child("test_task_fn.\n");

	static int status = 12121;
	int a = 10;

	while (a--) {
		log_child("sleep %d\n", a);
		sleep(1);
	}

	pthread_exit(&status);
	return NULL;
}

int main(void)
{
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, test_task_fn, NULL);

	sleep(1);

	/* I don't want to know child thread exit, detach is different from join. */
	pthread_detach(thread_id);

	return 0;
}
