BITS 64
mov rax, 0x100000000
mov rbx, 0x200000000
add rax, rbx
mov rbx, 0x200000000
cmp rax, rbx
jz .equal

mov rax, 'N'
mov edx, 0x3f8
out dx, al
mov rax, 0xc000
jmp rax

.equal:
mov rax, 'Y'
mov edx, 0x3f8
out dx, al

mov rax, 0xc000
jmp rax
