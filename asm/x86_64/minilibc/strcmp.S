	[BITS 64]  		; Obligatoire

	global strcmp 	;  initialize the name of the function Obligatoire
	section .text 	; set the .text Obligatoire

strcmp:
	push rbp 	; initialize the stack
	mov rbp, rsp 	; initialize the pointer of the stack
	xor rax, rax
	xor rbx, rbx

loop:
	mov al, [rdi] 	; assign cl (register) with the first parameter of the function
	mov bl, [rsi] 	; assign cl (register) with the second parameter of the function

	cmp al, 0	; compare cl (first) == \0
	je end		; stop if the compare worked
	
	cmp bl, 0	; compare cl (first) == \0
	je end		; stop if the compare worked

	cmp al, bl	; compare the two value of the character stocked in the cl and dl register
	jne end		; if the value are different, go to the end, because its an error
	
	inc rdi		; increment rdi (1st operand)
	inc rsi		; increment rsi (2nd operand)
	jmp loop	; call loop (recursive)

end:
	sub rax, rbx	; substract the value of the 2nd operand to the value of the 1st operand
	leave		; free the stack
	ret		; return obligatoire
