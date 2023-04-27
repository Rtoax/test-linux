	global start

start:
	mov dx, 0x3f8
	mov eax, "abcd"
	call print_eax
	hlt

print_eax:
	push edx
	push ecx
	mov ecx, 0x4
	mov dx, 0x3f8
.loop:
	out dx, al
	shr eax, 0x8
	sub ecx, 0x1
	jnz .loop
.end:
	mov al, "x"
	out dx, al
	pop ecx
	pop edx
	ret
