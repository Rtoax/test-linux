; -----------------------------------------------------------------------------
; 一个用于计算 x^y 的 64 位命令行程序。
;
; 格式: power x y
; x 和 y 均为 32 位的正整数
;
; $ nasm -felf64 power.asm && gcc -o power.out power.o
; $ ./power 2 19
; 524288
; $ ./power 3 -8
; The exponent may not be negative
; $ ./power 1 500
; 1
; $ ./power 1
; Requires exactly two arguments
; -----------------------------------------------------------------------------

        global  main
        extern  printf
        extern  puts
        extern  atoi

        section .text
main:
        push    r12                     ; 调用者保存寄存器
        push    r13
        push    r14
        ; 通过压入三个寄存器的值, 栈已经对齐

        cmp     rdi, 3                  ; 必须有且仅有 2 个参数
        jne     error1

        mov     r12, rsi                ; argv

; 我们将使用 ecx 作为指数的计数器, 直至 ecx 减到 0。
; 使用 esi 来保存基数, 使用 eax 保存乘积。

        mov     rdi, [r12+16]           ; argv[2]
        call    atoi                    ; y 存放在 eax 中
        cmp     eax, 0                  ; 不允许负指数
        jl      error2
        mov     r13d, eax               ; y 存放在 r13d 中

        mov     rdi, [r12+8]            ; argv
        call    atoi                    ; x 存放在 eax 中
        mov     r14d, eax               ; x 存放在 r14d 中

        mov     eax, 1                  ; 初始结果 answer = 1
check:
        test    r13d, r13d              ; 递减 y 直至 0
        jz      gotit                   ; 完成
        imul    eax, r14d               ; 再乘上一个 x
        dec     r13d
        jmp     check
gotit:                                  ; 输出成功信息
        mov     rdi, answer
        movsxd  rsi, eax
        xor     rax, rax
        call    printf
        jmp     done
error1:                                 ; 输出错误信息
        mov     edi, badArgumentCount
        call    puts
        jmp     done
error2:                                 ; 输出错误信息
        mov     edi, negativeExponent
        call    puts
done:                                   ; 恢复所保存的寄存器
        pop     r14
        pop     r13
        pop     r12
        ret

answer:
        db      "%d", 10, 0
badArgumentCount:
        db      "Requires exactly two arguments", 10, 0
negativeExponent:
        db      "The exponent may not be negative", 10, 0