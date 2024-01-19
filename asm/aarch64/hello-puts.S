
.text
.globl puts
.globl main
main:
	stp	x29, x30, [sp, #-32]!
	mov	x29, sp
	str	xzr, [sp, #16]
	mov	w0, #0x48		// #72
	strb	w0, [sp, #16]
	mov	w0, #0x65		// #101
	strb	w0, [sp, #17]
	mov	w0, #0x6c		// #108
	strb	w0, [sp, #18]
	mov	w0, #0x6c		// #108
	strb	w0, [sp, #19]
	mov	w0, #0x6f		// #111
	strb	w0, [sp, #20]
	mov	w0, #0xa		// #10 '\n'
	strb	w0, [sp, #21]
	add	x0, sp, #0x10
	str	x0, [sp, #24]

	ldr	x0, [sp, #24]		/* buf := msg */
	bl	puts
	nop
	mov	w0, #0
	ret
