; -----------------------------------------------------------------------------
; 一个输出 Fibonacci 数列前 90 项的 64 位 Linux 程序。
; 如何编译执行:
;
;     nasm -felf64 fib.asm && gcc fib.o && ./a.out
; -----------------------------------------------------------------------------

        global  main
        extern  printf

        section .text
main:
        push    rbx                     ; 因为需要用 rbx 寄存器所以需要保存

        mov     ecx, 90                 ; ecx 作为计数器直至减到 0
        xor     rax, rax                ; rax 将记录当前的数字
        xor     rbx, rbx                ; rbx 将记录下一个的数字
        inc     rbx                     ; rbx 初始值 1
print:
        ; 我们需要调用 printf 函数, 但是我们也同时在使用 rax,rbx 和 rcx 这三个寄存器。
        ; 调用 printf 函数会破坏 rax 和 rcx 这两个寄存器的值, 所以我们要在调用前保存
        ; 并且在调用后恢复这两个寄存器中的数据。

        push    rax                     ; 调用者保存寄存器
        push    rcx                     ; 调用者保存寄存器

        mov     rdi, format             ; 设置第一个参数 (format)
        mov     rsi, rax                ; 设置第二个参数 (current_number)
        xor     rax, rax                ; 因为 printf 是多参数的

        ; 栈内已经对齐, 因为我们压入了三个 8 字节的数据。
        call    printf                  ; printf(format, current_number)

        pop     rcx                     ; 恢复调用者所保存的寄存器
        pop     rax                     ; 恢复调用者所保存的寄存器

        mov     rdx, rax                ; 保存当前的数字
        mov     rax, rbx                ; 下一个数字保存在当前数字的位置
        add     rbx, rdx                ; 计算得到下一个数字
        dec     ecx                     ; ecx 减 1
        jnz     print                   ; 如果不是 0, 继续循环

        pop     rbx                     ; 返回前恢复 rbx 的值
        ret
format:
        db  "%20ld", 10, 0
