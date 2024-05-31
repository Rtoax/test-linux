/**
 * pthread_cond_signal惊群现象
 *
 * 程序运行结果
 * decrement:waiting
 * decrement:waiting
 * decrement:count = 1
 * decrement:waiting
 * decrement:count = 0
 * exit count:0
 *
 * * 最后退出了，为什么？ *
 *
 * 如果把tid1,tid2,tid3表示为每个线程获得互斥锁，那么这种情况的发生说明tid1和
 * tid3顺序获得锁执行了(顺序也可能为tid3和tid1).
 *
 * 单从pthread_cond_signal函数的定义上看，如果严格的只发一个"信号"给指定一个线
 * 程，这种情况是绝对不可能发生的。
 *
 * 因为函数中pthread_cond_wait的返回代表了此线程接受到“信号”
 * （pthread_cond_wait执行包括1.解锁2.wait3.获得锁4.返回）
 *
 * 只有一个原因能解释：
 * pthread_cond_signal一次唤醒了2个wait线程，第1个获得锁的线程把count置为0，
 * 第2个线程发现count=0直接exit，pthread_cond_signal发生了惊群现象。
 *
 * 怎么预防：
 *	while (count == 0)
 *		pthread_cond_wait(&count_ready, &count_lock);
 *
 * 在wait返回后加一个while来判断“条件”是否满足要求。
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t count_lock;
pthread_cond_t count_ready;
int count;

void *decrement_count(void *arg)
{
	while (1) {
		pthread_mutex_lock(&count_lock);
		printf("%ld: decrement:waiting\n", pthread_self());
		/* 等待满足条件，期间互斥量仍然可用 */
		pthread_cond_wait(&count_ready, &count_lock);
		printf("%ld: decrement:count = %d\n", pthread_self(),  count);
		if (count == 0) {
			printf("%ld: exit count:%d\n", pthread_self(), count);
			exit(1);
		}
		count = 0;
		pthread_mutex_unlock(&count_lock);
	}
	pthread_exit(NULL);
}

void *increment_count(void *arg)
{
	while (1) {
		pthread_mutex_lock(&count_lock);
		count = 1;
		/* 通知线程条件已满足 */
		pthread_cond_signal(&count_ready);
		pthread_mutex_unlock(&count_lock);
	}
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t tid1,tid2,tid3;
	count=0;
	pthread_mutex_init(&count_lock, NULL);
	pthread_cond_init(&count_ready, NULL);

	pthread_create(&tid1, NULL, decrement_count, NULL);
	sleep(3);
	pthread_create(&tid3, NULL, decrement_count, NULL);
	sleep(3);
	pthread_create(&tid2, NULL, increment_count, NULL);

	/* 等待decrement退出 */
	pthread_join(tid2, NULL);
	printf("decrement quit\n");
	pthread_join(tid3, NULL);
	pthread_join(tid1, NULL);
	return 0;
}

