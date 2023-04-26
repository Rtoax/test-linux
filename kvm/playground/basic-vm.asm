	global start

start:	mov dx, 0x3f8
	add al, bl
	mov al, `0`
	out dx, al
	mov al, `\n`
	out dx, al
	hlt
