.text
.globl _start
_start:
	/* exit(0xff) */
	mov	x0, #0xff
	mov	w8, #93
	svc	#0
	ret
