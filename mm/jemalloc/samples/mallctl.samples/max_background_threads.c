#include <stdio.h>
#include <jemalloc/jemalloc.h>

//max_background_threads (size_t) rw
//--------------------------------------------------------------------------------------------------------------------
//	Maximum number of background worker threads that will be created. This value is capped at opt.max_background_threads
//	at startup.
//	最大的后台线程数

void set_jemalloc_max_bg_thread(size_t value) {
	char val = sizeof(size_t);
	je_mallctl("max_background_threads", NULL, 0, &value, val);
}
void get_jemalloc_max_bg_thread(size_t *value) {
	size_t size = sizeof(size_t);
	je_mallctl("max_background_threads", value, &size, NULL, 0);
}

void set_jemalloc_bg_thread(bool enable) {
	char val = !!enable;
	je_mallctl("background_thread", NULL, 0, &val, 1);
}
void get_jemalloc_bg_thread(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("background_thread", enable, &size, NULL, 0);
}


int main(int argc,char **argv)
{
	size_t value = 0;

	bool enable = true;

	get_jemalloc_bg_thread(&enable);
	printf("enable = %d\n", enable);

	enable = true;
	set_jemalloc_bg_thread(enable);


	get_jemalloc_max_bg_thread(&value);
	printf("value = %d\n", value);

	set_jemalloc_max_bg_thread(3);

	value = 0;
	get_jemalloc_max_bg_thread(&value);
	printf("value = %d\n", value);

	while(1)sleep(1);

}

