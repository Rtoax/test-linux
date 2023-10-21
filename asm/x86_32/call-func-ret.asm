global _start

_start:
	call func	; call function
	mov eax, 1	; exit
	int 0x80

func:
	mov ebx, 42
	ret
