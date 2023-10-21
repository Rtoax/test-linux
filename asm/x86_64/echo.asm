; -----------------------------------------------------------------------------
; 一个显示命令行参数的 64 位程序。一行一个地输出。
;
; 在函数入口处,rdi 保存 argc 的值,rsi 保存 argv 的值。
;
; nasm -felf64 echo.asm && gcc echo.o && ./a.out dog 22 -zzz "hi there"
; -----------------------------------------------------------------------------

        global  main
        extern  puts
        section .text
main:
        push    rdi                     ; argc, 保存 puts 函数需要用到的寄存器
        push    rsi                     ; argv
        sub     rsp, 8                  ; 调用函数前让栈顶对齐

        mov     rdi, [rsi]              ; 需要输出的字符串参数
        call    puts                    ; 调用 puts 输出 /span>

        add     rsp, 8                  ; 恢复 %rsp 到未对齐前的值
        pop     rsi                     ; 恢复 puts 用到的寄存器
        pop     rdi

        add     rsi, 8                  ; 指向下一个参数
        dec     rdi                     ; 递减
        jnz     main                    ; 如果未读完参数则继续

        mov     rax, 0                  ; 返回 0
        ret
