1. make
2. sudo insmod request-irq.ko name=rtoax
3. dmesg # see "Hello Witkacy!" in kernel message log
4. sudo rmmod request-irq.ko
5. dmesg # see "Cleaning up hello module." in kernel message log
6. modinfo request-irq.ko # read module metadata
