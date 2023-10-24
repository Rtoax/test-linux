	[BITS 64]
	global strncmp
	section .text

strncmp:
	push rbp
	mov rbp, rsp
	mov rax, 0
	mov rbx, 0

loop:
	mov al, [rdi]
	mov bl, [rsi]

	cmp al, bl
	jne end_null

	cmp bl, 0
	je end_null
	
	cmp al, 0
	je end_null

	cmp rdx, 1
	je end
	
	dec rdx

	inc rdi
	inc rsi
	jmp loop

end_null:
	sub rax, rbx
	leave
	ret
end:
	mov rax, 0
	leave
	ret
