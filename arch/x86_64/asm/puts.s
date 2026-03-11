        .intel_syntax noprefix
        .global _start

_start:
        sub     rsp, 8                  /* 16-byte alignment */

        /* puts(3) library-call */
        lea     rdi, [rip + msg]        /* 1st argument */
        call    puts

        /* return from main */
        add     rsp, 8                  /* 16-byte alignment */
        ret

        /* read-only data */
        .section .rodata
msg:
        .string "Hello world!"
