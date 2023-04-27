BITS 64
mov esp, 0xe000
mov rax, 'N'
mov edx, 0x3f8
out dx, al

int 0 
hlt
