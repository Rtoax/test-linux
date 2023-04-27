[BITS 32]
	mov ax, 'B'
	add ax, '0'
	mov dx, 0x3f8
	out dx, al
	hlt	
