BITS 32
mov eax, 'A'
add eax, '0'
mov edx, 0x3f8
out dx, al
mov eax, 0xc000
jmp eax
