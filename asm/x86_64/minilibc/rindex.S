	[BITS 64]
	global rindex
	section .text
	
rindex:
	push rbp
	mov rbp, rsp
	mov rdx, 0

loop:
	cmp byte[rdi + rdx], 0
	je other_loop

	inc rdx
	jmp loop
	
other_loop:
	cmp byte[rdi + rdx], sil
	je end

	cmp rdx, 0
	je end_null

	dec rdx
	jmp other_loop

end:
	add rdi, rdx
	mov rax, rdi
	leave
	ret

end_null:
	mov rax, 0
	leave
	ret
	
