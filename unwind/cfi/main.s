; This file is compile srouce CODE `main.c`:
; -----------------------------
; int f()
; {
;	return 2;
; }
;
; int main()
; {
;	return f();
; }
; --------------------------------
; gcc main.c -S -o main.s
;
; 文章 libunwind 详解 - https://blog.csdn.net/Rong_Toa/article/details/110846509
;
	.file	"main.c"
	.text
	.globl	f
	.type	f, @function
f:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$2, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	f, .-f
	.globl	main
	.type	main, @function
main:
.LFB1:
	; cfi_startproc 用在每个函数的入口处
	.cfi_startproc
	pushq	%rbp
	; .cfi_def_cfa_offset offset
	; 用来修改 CFA计算规则，不变寄存器不变，offset变化
	; CFA = register + offset(new)
	.cfi_def_cfa_offset 16
	; .cfi_offset regiser, offset
	; 寄存器register 上一次值保存在 CFA偏移 offset的堆栈中
	; *(CFA + offset) = register(pre_value)
	; rbp 为 6
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	; .cfi_def_cfa_register register
	; use to modify CFA 规则，基址寄存器 从 rsp 转移到新的register
	; register = new register
	; rbp 为 6
	.cfi_def_cfa_register 6
	movl	$0, %eax
	call	f
	popq	%rbp
	; .cfi_def_cfa register, offset
	; 用来定义 CFA 的计算规则
	; CFA = register + offset
	; 基址寄存器 register = rsp
	; x86_64 的 register 编号从0-15对应如下
	; %rax，%rbx，%rcx，%rdx，%esi，%edi，%rbp，%rsp，%r8，%r9，%r10，%r11，%r12，%r13，%r14，%r15
	; rsp 为 7
	; r8 为 8
	.cfi_def_cfa 7, 8
	ret
	; cfi_endproc 用在函数结尾处
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.4.1 20200928 (Red Hat 8.4.1-1)"
	.section	.note.GNU-stack,"",@progbits
