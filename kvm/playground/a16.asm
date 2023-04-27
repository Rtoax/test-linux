BITS 16
mov ax, 'A'
add ax, '0'
mov dx, 0x3f8
out dx, al
mov eax, 0xc000
jmp eax
