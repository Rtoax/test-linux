Share Memory
============

POSIX
-----

Header `#include <sys/mman.h>`

syscalls & glibc
----------------

- `shm_open(3)`
- `mmap(2)`
- `shm_overview(3)`
- `shm_unlink(3)`


System V Share Memory
---------------------

Header `#include <sys/shm.h>`

syscalls
~~~~~~~~

- `shmctl(2)`
- `shmget(2)`
- `shmat(2)`
- `shmdt(2)`


Kernel Sysctl
-------------

Check with `sudo sysctl -a | grep kernel.shm`

- `kernel.shmmni`: max number of segments
- `kernel.shmmax`: max seg size (kbytes) = 32768
- `kernel.shmall`: max total shared memory (kbytes)
