	[BITS 64]               	; Obligatoire

	global memset  ;  initialize the name of the function Obligatoire
	section .text   ; // set the .text Obligatoire

memset:
	push rbp        ; Initialize stack
	mov rbp, rsp    ; Initialize stack
	mov r14, rdi

loop:
	cmp rdx, 0	; compare the two value of the character stocked in the cl and dl register
	je end		; if the value are different, go to the end, because its an error

	cmp rdi, 0
	je end 
	
	mov [rdi], sil
	sub rdx, 1
	inc rdi         ; increment rdi (1st operand)
	jmp loop        ; call loop (recursive)

end:
	mov rax, r14    ; assign cl to rax
	leave		; free the stack
	ret             ; return obligatoire 
