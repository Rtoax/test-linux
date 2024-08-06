	global  main
	extern  puts
	section .text
main:
	; FIXME: Only print one ABCD?
	push    `ABCD`
	push    `ABCD`
	mov     rdi, rsp
	call    puts
	pop     rsi
	pop     rsi
	ret
