        .intel_syntax noprefix
        .global _start

_start:
        sub     rsp, 8                  /* 16-byte alignment */

        /* putchar(3) library-call */
        mov     edi, 0x41               /* 'A' */
        call    putchar

        mov     edi, 0x42               /* 'B' */
        call    putchar

        mov     edi, 'C'
        call    putchar

        mov     edi, '\n'
        call    putchar

        /* return from main */
        add     rsp, 8                  /* 16-byte alignment */
        ret
