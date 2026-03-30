	global start

start:
	mov eax, 'C'
	add eax, '0'
	mov dx, 0x3f8
	out dx, al
	hlt
