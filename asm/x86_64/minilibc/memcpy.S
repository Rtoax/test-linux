	[BITS 64]		; Obligatoire
	global memcpy  	;  initialize the name of the function Obligatoire
	section .text   	; // set the .text Obligatoire

memcpy:
	push rbp        ; Initialize stack
	mov rbp, rsp	; Initialize stack
	mov r14, rdi

loop:	
	cmp rdx, 0
	je end

	mov bl, [rsi]
	mov [rdi], bl
	
	dec rdx
	inc rdi
	inc rsi
	jmp loop

end:
	mov rax, r14
	leave
	ret
