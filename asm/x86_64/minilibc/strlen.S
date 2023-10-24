	[BITS 64]  		; Obligatoire

	global strlen 		;  initialize the name of the function Obligatoire 
	section .text 		; set the .text Obligatoire 

strlen:
	push rbp 		; initialize the stack
	mov rbp, rsp 		; initialize the pointer of the stack
	mov rcx, 0 		; set our incrementeur to 0

loop:
	cmp byte[rdi], 0 	; compare the string at rdi value with the character 0 (\0)
	je end		 	; if the cmp worked, je is called
	
	inc rdi		 	; if cmp didn't work, the rest of the code is executed,
				; starting here with the incrementation of rdi
	inc rcx			; increment rcx
	jmp loop		; called the loop

end:
	mov rax, rcx 		; assign rcx to rax
	leave			; free the stack
	ret 			; return obligatoire
