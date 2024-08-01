        .global main

main:
        /* write(2) system-call */
        mov     x8, 64                  /* system-call number: write() */
        mov     x0, 1                   /* fd: stdout */
        adr     x1, msg                 /* buf: */
        mov     x2, 13                  /* count: */
        svc     0                       /* system call */


        /* return from main */
        ret

        /* read-only data */
        .section .rodata
msg:
        .string "Hello world!\n"
