BITS 64
mov rax, QWORD 'A'
add rax, QWORD '0'
mov rdx, QWORD 0x3f8
out dx, al
mov rax, QWORD 0xc000
jmp rax
