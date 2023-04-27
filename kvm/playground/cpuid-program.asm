	global start

start:  mov dx, 0x3f8	
        mov eax, 0x0
        cpuid
	mov eax, ebx 
	call print_eax
	mov eax, edx 
	call print_eax
	mov eax, ecx 
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
	pop ecx
	pop edx
	ret	
