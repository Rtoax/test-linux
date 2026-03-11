.section .rodata
Lhello:
	.asciz "Hello!"

.section .text
	.globl someRelocations
	.type someRelocations, STT_FUNC
someRelocations:
	# Lhello is R_X86_64_GOT32
	movq $Lhello@GOT, %rax                  # Store the offset from GOT to its entry for Lhello in RAX
	# _GLOBAL_OFFSET_TABLE_ R_X86_64_GOTPC32
	leaq _GLOBAL_OFFSET_TABLE_(%rip), %rcx  # Store the address of _GLOBAL_OFFSET_TABLE_ in RCX
	addq %rcx, %rax                         # Calculate abs address of GOT entry for Lhello
	movq (%rax), %rdi                       # Resolve absolute address of Lhello (dereference the pointer)
	# R_X86_64_PLT32
	call puts@PLT
	ret
