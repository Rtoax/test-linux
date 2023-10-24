	[BITS 64]
	global strcasecmp
	section .text

strcasecmp:
	push rbp
	mov rbp, rsp
	mov r8, 0
	mov rax, 0

check_argument:
	mov al, [rdi]
	mov r8b, [rsi]
		
loop:
	cmp al, 0
	je end
	
	cmp r8b, 0
	je end

	cmp al, 65
	jge cmp_a

middle_loop:	
	cmp r8b, 65
	jge cmp_b

end_loop:
	cmp al, r8b
	jne end

	inc rdi
	inc rsi
	jmp check_argument

cmp_a:	
	cmp al, 90
	jg middle_loop
	
to_lower_a:
	add al, 32
	jmp loop

cmp_b:	
	cmp r8b, 90
	jg end_loop
	
to_lower_b:
	add r8b, 32
	jmp loop

end:
	sub rax, r8
	leave
	ret
