        [BITS 64]
	global strstr
	section .text

strstr:
	push rbp
	mov rbp, rsp
	mov r14, rdi

	cmp byte[rsi], 0
	je end

	cmp byte[rdi], 0
	je end_null	

loop:
	cmp byte[r14], 0
	je end_null

	mov r15, rsi
	
        other_loop:
		mov bl, [r14]
	
		cmp byte[r15], 0
		je end
	
		cmp byte[r15], bl
		jne end_loop
	
		inc r14
		inc r15
		jmp other_loop

end_loop:
	inc rdi
	mov r14, rdi
	jmp loop

my_first_end:
	mov rax, rdi
	leave
	ret

end_null:
	mov rax, 0
	leave
	ret

end:
	mov rax, rdi
	leave
	ret
