/**
 * https://users.ece.utexas.edu/~gerstl/ee382m_f18/lectures/SVE_Seminar_UT_Rico.pdf
 */

/**
 * void daxpy(double *x, double *y, double a, int n) {
 *     for (int i = 0; i < n; i ++) {
 *         y[i] = a * x[i] + y[i];
 *     }
 * }
 */
.text
.globl daxpy_sve
daxpy_sve:
	ldrsw	x3, [x3]
	mov	x4, #0
	whilelt	p0.d, x4, x3
	ld1rd	z0.d, p0/z, [x2]
.loop:
	ld1d	z1.d, p0/z, [x0, x4, lsl #3]
	ld1d	z2.d, p0/z, [x1, x4, lsl #3]
	fmla	z2.d, p0/m, z1.d, z0.d
	st1d	z2.d, p0, [x1, x4, lsl #3]
	incd	x4
.latch:
	whilelt	p0.d, x4, x3
	b.first	.loop
	ret


.text
.globl daxpy
daxpy:
	ldrsw	x3, [x3]
	mov	x4, #0
	ldr	d0, [x2]
	b	.latch2
.loop2:
	ldr	d1, [x0, x4, lsl #3]
	ldr	d2, [x1, x4, lsl #3]
	fmadd	d2, d1, d0, d2
	str	d2, [x1, x4, lsl #3]
	add	x4, x4, #1
.latch2:
	cmp	x4, x3
	b.lt	.loop2
	ret
