#pragma once
#include <pthread.h>

pthread_t start_thread(void *(*routine)(void *), int cpu, void *arg);
