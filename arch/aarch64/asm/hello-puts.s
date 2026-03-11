.text
.globl puts

.globl _start
_start:
	stp	x29, x30, [sp, #-32]!
	mov	x29, sp

	mov	w0, #0x48		// #72
	strb	w0, [sp, #24]

	mov	w0, #0x65		// #101
	strb	w0, [sp, #25]

	mov	w0, #0x6c		// #108
	strb	w0, [sp, #26]

	mov	w0, #0x6c		// #108
	strb	w0, [sp, #27]

	mov	w0, #0x6f		// #111
	strb	w0, [sp, #28]

	add	x0, sp, #0x18
	// This will cause segv fault
	//ldr	x0, [sp, #0x18]		/* buf := msg */
	bl	puts

	mov	w0, #0x0
#if !defined(INFINITE_LOOP)
	# If no this line, this program will running in infinite loop.
	ldp	x29, x30, [sp], #32
#endif
	ret
