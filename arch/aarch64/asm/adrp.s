.text
.globl _start
_start:
	// Obtain the base address of the 4KB page where the msg is located
	adrp    x1, msg
	// Adding the page offset gives the complete address of msg.
	add     x1, x1, #:lo12:msg

	// write(x0, x1, x2)
	mov     x2, #13
	mov     x0, #1
	mov     x8, #64
	svc     #0

	// exit(0)
	mov     x0, #0
	mov     x8, #93
	svc     #0

.section .rodata
msg:
	.ascii  "Hello, ADRP!\n"
