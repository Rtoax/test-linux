#include <stdio.h>
#include <jemalloc/jemalloc.h>

//epoch (uint64_t) rw 时代，世
//If a value is passed in, refresh the data from which the mallctl*() functions report values, and increment the epoch.
//Return the current epoch. This is useful for detecting whether another thread caused a refresh.
//如果参数提供了，刷新从mallctl函数上报的值的数据，并且epoch递减。返回当前的epoch值，用于检测是否另一个线程刷新过。


void set_jemalloc_epoch(uint64_t epoch)
{
	size_t size = sizeof(uint64_t);
	je_mallctl("epoch", NULL, 0, &epoch, size);
}
void get_jemalloc_epoch(uint64_t *epoch)
{
	size_t size = sizeof(uint64_t);
	je_mallctl("epoch", epoch, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	uint64_t epoch = 0;

	get_jemalloc_epoch(&epoch);
	printf("epoch = %ld\n", epoch);
	get_jemalloc_epoch(&epoch);
	printf("epoch = %ld\n", epoch);


	set_jemalloc_epoch(epoch);

	get_jemalloc_epoch(&epoch);
	printf("epoch = %ld\n", epoch);

	set_jemalloc_epoch(epoch);
	set_jemalloc_epoch(epoch);
	set_jemalloc_epoch(epoch);

	get_jemalloc_epoch(&epoch);
	printf("epoch = %ld\n", epoch);

}
