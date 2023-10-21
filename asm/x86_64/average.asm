; -----------------------------------------------------------------------------
; 一个把参数当做整数处理, 并且以浮点数形式输出他们平均值的 64 位程序。
; 这个程序将使用一个数据段来保存中间结果。
; 这不是必须的, 但是在此我们想展示数据段是如何使用的。
;
; $ nasm -felf64 average.asm && gcc average.o && ./a.out 19 8 21 -33
; 3.75
; $ nasm -felf64 average.asm && gcc average.o && ./a.out
; There are no command line arguments to average
; -----------------------------------------------------------------------------

        global   main
        extern   atoi
        extern   printf
        default  rel

        section  .text
main:
        dec      rdi                    ; argc-1, 因为我们不需要读入程序名称
        jz       nothingToAverage
        mov      [count], rdi           ; 保存浮点数参数的个数
accumulate:
        push     rdi                    ; 保存调用 atoi 需要使用的寄存器
        push     rsi
        mov      rdi, [rsi+rdi*8]       ; argv[rdi]
        call     atoi                   ; 现在 rax 里保存着 arg 的整数值
        pop      rsi                    ; 调用完 atoi 函数后恢复寄存器
        pop      rdi
        add      [sum], rax             ; 继续累加
        dec      rdi                    ; 递减
        jnz      accumulate             ; 还有参数吗?
average:
        cvtsi2sd xmm0, [sum]
        cvtsi2sd xmm1, [count]
        divsd    xmm0, xmm1             ; xmm0 现在值为 sum/count
        mov      rdi, format            ; printf 的第一个参数 [注: 输出格式]
        mov      rax, 1                 ; printf 是多参数的, 含有一个不是整数的参数

        sub      rsp, 8                 ; 对齐栈指针
        call     printf                 ; printf(format, sum/count)
        add      rsp, 8                 ; 恢复栈指针

        ret

nothingToAverage:
        mov      rdi, error
        xor      rax, rax
        call     printf
        ret

        section  .data
count:  dq       0
sum:    dq       0
format: db       "%g", 10, 0
error:  db       "There are no command line arguments to average", 10, 0