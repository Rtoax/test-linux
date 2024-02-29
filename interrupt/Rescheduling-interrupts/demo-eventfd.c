#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/eventfd.h>

#include "utils.h"
#include "common.h"

int efd=0;

void *write_task(void *arg)
{
    int ret;
    eventfd_t count = 1;

    while (1) {
        ret = eventfd_write(efd, count);
        if(ret < 0) {
            continue;
        }
    }
    pthread_exit(NULL);
}

void *read_task(void *arg)
{
    int ret;
    long long int total_count = 0;

    eventfd_t count;

    while (1) {
        ret = eventfd_read(efd, &count);
        if (ret < 0) {
            break;
        }
        total_count+=count;

        if ((total_count / 1000000) % 2 == 0) {
            log_dequeue("read ret = %d, total_count = %lld\n", ret, total_count);
        }
    }
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t write_taskid[10], read_taskid;

    int nwrite = 3, i;

    //EFD_CLOEXEC|EFD_NONBLOCK | EFD_SEMAPHORE
    efd = eventfd_create();

    for (i = 0; i < nwrite; i++) {
        pthread_create(&write_taskid[i], NULL, write_task, NULL);
    }

    pthread_create(&read_taskid, NULL, read_task, NULL);

    for (i = 0; i < nwrite; i++) {
        pthread_join(write_taskid[i], NULL);
    }
    pthread_join(read_taskid, NULL);

    printf("Exit.\n");

    close(efd);
    return EXIT_SUCCESS;
}
