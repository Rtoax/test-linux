.section .rodata
Lhello:
	.asciz "Hello!"

.section .text
someFunction:
	# R_X86_64_REX_GOTPCRELX
	movq Lhello@GOTPCREL(%rip), %rdi       # Copy the address of Lhello in the GOT into RDI
	call puts@PLT                          # Print to stdout
	ret
