Message Queue - (msgq, mq, msgqueue, mqueue)
============================================

1. `#include <mqueue.h>` is POSIX API;
2. `#include <sys/msgq.h>` is System V API;


Kernel Sysctl
-------------

Check with `sudo sysctl -a | grep kernel.msg`

- `kernel.msgmni`: max queues system wide(系统最大队列数)
- `kernel.msgmax`: max size of message (bytes)
- `kernel.msgmnb`: default max size of queue (bytes)
