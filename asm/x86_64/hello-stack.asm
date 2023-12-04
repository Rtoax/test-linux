; ----------------------------------------------------------------------------------------
; 仅使用系统调用来输出 "Hello, World" 到控制台。 这个程序仅在 64 位的 Linux 下运行。
; 如何编译执行:
;
;     nasm -felf64 hello.asm && ld hello.o && ./a.out
; ----------------------------------------------------------------------------------------

        global  _start

        section .text
_start:
        ; write(1, message, 13)
        mov     al  , 0x01
        mov     dil , al

        push    0x0a20206f  ; text: "o  \n"
        push    0x6c6c6548  ; text: "Hell"

        mov     rsi , rsp
        mov     dl  , 0x0c
        syscall

        ; exit(0)
        mov     eax, 60                 ; 60 号系统调用是退出
        xor     rdi, rdi                ; 0 号系统调用作为退出
        syscall                         ; 调用系统执行退出

