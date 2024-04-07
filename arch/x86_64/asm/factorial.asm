; ----------------------------------------------------------------------------
; 一种递归函数的实现:
;
;   uint64_t factorial(uint64_t n) {
;       return (n <= 1) ? 1 : n * factorial(n-1);
;   }
; ----------------------------------------------------------------------------

        global  factorial

        section .text
factorial:
        cmp     rdi, 1                  ; n <= 1?
        jnbe    L1                      ; 如果不是, 进行递归调用
        mov     rax, 1                  ; 否则, 返回 1
        ret
L1:
        push    rdi                     ; 在栈上保存 n(同时对齐 %rsp 寄存器!)
        dec     rdi                     ; n-1
        call    factorial               ; factorial(n-1), 返回值保存在 %rax 中
        pop     rdi                     ; 保存 n
        imul    rax, rdi                ; n * factorial(n-1), 保存在 %rax 中
        ret
