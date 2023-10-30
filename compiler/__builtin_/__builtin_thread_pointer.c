#include <pthread.h>
#include <stdio.h>

/* Return the thread descriptor for the current thread. */
pthread_t rtoax_pthread_self(void)
{
	  return (pthread_t)__builtin_thread_pointer();
}

int main(void)
{
	printf("%ld:%ld\n", rtoax_pthread_self(), pthread_self());
	return 0;
}