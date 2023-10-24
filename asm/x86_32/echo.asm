; ----------------------------------------------------------------------------
; echo.asm
;
; NASM implementation of a program that displays its commandline arguments,
; one per line.
; ----------------------------------------------------------------------------

	global	main
	extern	printf

	section .text
main:
	mov	ecx, [esp+4]	        ; argc
	mov	edx, [esp+8]		; argv
top:
	push	ecx			; save registers that printf wastes
	push	edx

	push	dword [edx]		; the argument string to display
	push	format			; the format string
	call	printf
	add	esp, 8			; remove the two parameters

	pop	edx			; restore registers printf used
	pop	ecx

	add	edx, 4			; point to next argument
	dec	ecx			; count down
	jnz	top			; if not done counting keep going
	mov	eax, 0

	ret
format:
	db	'%s', 10, 0
