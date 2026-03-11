        .intel_syntax noprefix
        .global _start

_start:
        sub     rsp, 8                  /* 16-byte alignment */

        mov     rcx, 100                /* test data */

        /* printf(3) library-call */
        lea     rdi, [rip + msg]        /* 1st argument */
        mov     rsi, rcx                /* 2nd argument */
        mov     eax, 0                  /* the number of vector regsters */
        call    printf

        /* return from main */
        add     rsp, 8                  /* 16-byte alignment */
        ret

        /* read-only data */
        .section .rodata
msg:
        .string "rcx = %d\n"
