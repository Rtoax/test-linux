
```
                                     User Data
                                        |
                                        |
                                stdio library calls
                                printf(),fputs(),etc.--------+
            To force buffer             |                    |
             flush fflush()             |                    | Make flush automatic
                    |                   |                    +  on each IO call
                    |               stdio buffer            /    setbuf(stream, NULL)
                    +--------------+    |           +------+
user space                          \   |          /
----------------------------------IO system calls------------------
kernel space                         write(), etc.\
                                        |          +---------+
                                        |                    |
                                    Kernel buffer            |
                                        cache                |open(path, flags|O_SYNC, mode);
            fsync(),                    |                    |
            fdatasync(),                |                    |
            sync(),.                    |                    |
                |                       |                    |
                *----------------->kernel-initiated----------+
                                        write
                                        |
                                        |
                                        DISK
```

