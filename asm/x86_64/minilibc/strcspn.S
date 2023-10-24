	[BITS 64]
	global strcspn
	section .text
	
strcspn:
	xor rdx, rdx
	mov rcx, 0

loop:
	cmp byte[rdi + rdx], 0
	je end

	jmp second_loop

second_loop:
	mov al, [rsi + rcx]

	cmp al, 0
	je end_loop

	cmp al, [rdi + rdx]
	je end
	
	inc rcx
	jmp second_loop

end_loop:
	inc rdx
	mov rcx, 0
	jmp loop

end:
	mov rax, rdx
	ret
