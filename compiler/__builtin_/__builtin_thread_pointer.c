#include <pthread.h>
#include <stdio.h>

/* FIXME: check the gcc version and modify */
#if defined(__GNUC__) && ((__GNUC__ > 8) && (__GNUC_MINOR__ >= 5))
/* Return the thread descriptor for the current thread. */
pthread_t rtoax_pthread_self(void)
{
	  return (pthread_t)__builtin_thread_pointer();
}
#else
# define rtoax_pthread_self() pthread_self()
#endif

int main(void)
{
	printf("%ld:%ld\n", rtoax_pthread_self(), pthread_self());
	return 0;
}
