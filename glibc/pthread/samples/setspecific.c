/**
 * TSD - thread specific data
 */
#include <malloc.h>
#include <pthread.h>
#include <stdio.h>

static unsigned int nr_threads = 10;

/* The key used to associate a log file pointer with each thread. */
static pthread_key_t thread_log_key;

/* Write MESSAGE to the log file for the current thread. */
void write_to_thread_log(const char *message)
{
	FILE *thread_log = (FILE *) pthread_getspecific(thread_log_key);
	fprintf(thread_log, "%s\n", message);
}

/* Close the log file pointer THREAD_LOG. */
void close_thread_log(void *thread_log)
{
	fclose((FILE *) thread_log);
}

void *thread_function(void *args)
{
	char thread_log_filename[20];
	FILE *thread_log;

	sprintf(thread_log_filename, "thread%d.log", (int)pthread_self());
	thread_log = fopen(thread_log_filename, "w");
	pthread_setspecific(thread_log_key, thread_log);
	write_to_thread_log("Thread starting.");

	/* Do work here... */

	return NULL;
}

int main(void)
{
	int i;
	pthread_t threads[nr_threads];

	/* Create a key to associate thread log file pointers in
	 * thread-specific data. Use close_thread_log to clean up the file
	 * pointers. */
	pthread_key_create(&thread_log_key, close_thread_log);

	printf("thread_log_key = %d\n", thread_log_key);

	/* Create threads to do the work. */
	for (i = 0; i < nr_threads; ++i)
		pthread_create(&(threads[i]), NULL, thread_function, NULL);

	/* Wait for all threads to finish. */
	for (i = 0; i < nr_threads; ++i)
		pthread_join(threads[i], NULL);

	return 0;
}
