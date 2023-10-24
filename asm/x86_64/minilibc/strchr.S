        [BITS 64]               ; Obligatoire

	global strchr  ;  initialize the name of the function Obligatoire
	section .text   ; // set the .text Obligatoire

strchr:
	push rbp	; Initialize stack
	mov rbp, rsp 	; Initialize stack

loop:
	mov al, [rdi]   ; assign cl (register) with the first parameter of the function

	cmp al, sil     ; compare the two value of the character stocked in the cl and dl register
	je end		; if the value are different, go to the end, because its an error
	
	cmp al, 0       ; compare cl (first) == \0
	je exit_null	; stop if the compare wor

	
	inc rdi         ; increment rdi (1st operand)
	jmp loop        ; call loop (recursive)

exit_null:
	mov rax, 0 	; set rax to 0
	leave		; free the stack
	ret		; ret rax
	
end:
	mov rax, rdi   	; assign cl to rax
	leave		; free the stack
	ret             ; return obligatoire
