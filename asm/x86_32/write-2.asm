global _start

section .data
	msg db "hello, rtoax", 0x0a
	len equ $ - msg

section .text
_start:
	mov eax, 4	; sys_write
	mov ebx, 1	; stdout fd
	mov ecx, msg	; bytes to write
	mov edx, len	; number
	int 0x80	; sys call
	mov eax, 1	; sys_exit
	mov ebx, 0	; exit status is 0
	int 0x80
