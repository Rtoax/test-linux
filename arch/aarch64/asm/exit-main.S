        .global main

main:
        /* exit(2) system-call */
        mov     x8, 93                  /* system-call number: exit() */
        mov     x0, 0                   /* status: success */
        svc     0                       /* system call */
