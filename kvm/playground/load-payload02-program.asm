	global start

start:
	mov dx, 0x3f8
	add eax, ebx
	add eax, 0x1
	add eax, '0'
	out dx, al
	hlt
