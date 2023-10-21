global _start

_start:
	sub esp, 4
	mov [esp], byte 'H'
	mov [esp+1], byte 'e'
	mov [esp+2], byte 'y'
	mov [esp+3], byte '.'

	mov eax, 4	; sys_write
	mov ebx, 1	; stdout
	mov ecx, esp; bytes to write
	mov edx, 4	; number bytes to write
	int 0x80	; int
	mov eax, 1	; exit
	mov ebx, 0	; exit status
	int 0x80
