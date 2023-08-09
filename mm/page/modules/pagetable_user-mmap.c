#include <stdio.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>

#define SIZE 1024

int main() {

    pid_t pid = getpid();
    printf("pid %d\n", pid);

    uint64_t *addr = mmap(NULL, SIZE*sizeof(uint64_t), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );

    if(addr == MAP_FAILED){
        printf("could not allocate data\n");
        return 1;
    }

    for(int i=0; i<SIZE; i++)
        addr[i] = (uint64_t)i * 31337;

    sleep(99999999);

    int err = munmap(addr, SIZE*sizeof(uint64_t));
    if(err != 0){
        printf("unmap failed\n");
        return 1;
    }

    return 0;
}
