        global  main
        extern  puts
        section .text
main:
        push    `ABCD`
        mov     rdi, rsp
        call    puts
        pop     rsi
        ret
