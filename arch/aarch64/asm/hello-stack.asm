
.text
.globl _start
_start:
	sub	sp, sp, #0x10
	str	x0, [sp, #8]
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

	mov	x0, #1			/* fd := STDOUT_FILENO */
	ldr	x1, [sp, #24]		/* buf := msg */
	mov	x2, #0x8		/* count := len */
	mov	w8, #64			/* write is syscall #64 */
	svc	#0			/* invoke syscall */

	/* exit(0) */
	mov	x0, #0
	mov	w8, #93
	svc	#0
	nop
	add	sp, sp, #0x10
	ret
