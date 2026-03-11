
.text
.globl _start
_start:
	/* int nanosleep(const struct timespec *req, struct timespec *rem); */
	mov x0, 2
	str x0, [sp, 56]
	str xzr, [sp, 48]
	ldr x0, [sp, 56]
	str x0, [sp, 24]
	ldr x0, [sp, 48]
	str x0, [sp, 32]
	add x0, sp, 24
	mov x1, 0	/* rem = NULL */
	mov x8, 0x65
	svc #0		/* syscall */
	ret
