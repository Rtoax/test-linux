
section .data
	; 5.5seconds ; dq..quaduple word
	delay dq 5, 500000000

section .text
	global _start

_start:
	; int nanosleep(const struct timespec *req, struct timespec *rem);
	; __NR_nanosleep 35
	mov rax, 35
	mov rdi, delay
	mov rsi, 0
	syscall

	; exit
	mov rax, 60
	mov rdi, 0
	syscall
