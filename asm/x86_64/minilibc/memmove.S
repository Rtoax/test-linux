        [BITS 64]               ; Obligatoire

	global memmove	;  initialize the name of the function Obligatoire
	section .text	; // set the .text Obligatoire

memmove:
	push rbp        ; Initialize stack
	mov rbp, rsp    ; Initialize stack

	cmp rdx, 0
	je end

	cmp rsi, 0
	je end

	mov r14, rdi
	
	mov bl, [rsi]
	
	cmp rdi, rsi
	jl loop

	dec rdx
	add rdi, rdx
	add rsi, rdx
	jmp other_loop

loop:
	cmp rdx, 0
	je end

	mov bl, [rsi]
	mov [rdi], bl

	dec rdx
	inc rdi
	inc rsi

	jmp loop

other_loop:
	cmp rdx, -1
	je end

	mov bl, [rsi]
	mov [rdi], bl
	
	dec rdx
	dec rdi
	dec rsi

	jmp other_loop
	
end:
	mov rax, r14	; assign cl to rax
	leave		; free the stack
	ret             ; return obligatoire 
