	[BITS 64]
	global strpbrk
	section .text

strpbrk:
	push rbp
	mov rbp, rsp
	cmp rdi, 0
	je end_null

loop:
	mov bl, BYTE [rdi]
	cmp bl, 0
	je end_null
	
	mov r15, rsi

other_loop:
	cmp BYTE[r15], 0
	je end_loop

	cmp bl, [r15]
	je end
	
	inc r15
	jmp other_loop

end_loop:
	inc rdi
	inc rcx
	jmp loop

end_null:
	mov rax, 0
	leave
	ret

end:
	mov rax, rdi
	leave
	ret
	
	
	
	
