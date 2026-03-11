.section .rodata
Lhello:
	.asciz "Hello!"

.section .got
LhelloOff:
	.quad sayHello@GOTPLT                    # It's happy in .got, but not .got.plt

.section .text
	.globl someRelocations
	.type someRelocations, STT_FUNC
someRelocations:

	movq LhelloOff(%rip), %rax              # Store the offset from GOT to its entry for sayHello in RAX
	# R_X86_64_GOTPC32
	leaq _GLOBAL_OFFSET_TABLE_(%rip), %rcx  # Store the address of _GLOBAL_OFFSET_TABLE_ in RCX
	addq %rcx, %rax                         # Calculate abs address of sayHello
	call *(%rax)

	ret

	.globl sayHello
	.type sayHello, STT_FUNC
sayHello:
	movq Lhello@GOTPCREL(%rip), %rdi
	call puts@PLT
	ret
