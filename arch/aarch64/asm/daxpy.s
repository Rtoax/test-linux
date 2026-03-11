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
