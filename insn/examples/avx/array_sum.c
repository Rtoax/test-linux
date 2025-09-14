/**
 * Example: AVX
 */
#ifdef AVX
/**
 * 用AVX优化
 * https://www.jianshu.com/p/92a4f3d4434e
 */
void _array_sum_avx(double *a, double *b, double *re)
{
	int k, i;
	size_t t = clock();
	__m256d m1, m2;
	for (k = 0; k < 4; k++) {
		for (i = 0; i < 100000000; i += 4) {
			m1 = _mm256_set_pd(a[i], a[i + 1], a[i + 2], a[i + 3]);
			m2 = _mm256_set_pd(b[i], b[i + 1], b[i + 2], b[i + 3]);

			__m256d l1 = _mm256_add_pd(m1, m2);

			re[i + 3] = l1.m256d_f64[0];
			re[i + 2] = l1.m256d_f64[1];
			re[i + 1] = l1.m256d_f64[2];
			re[i]	 = l1.m256d_f64[3];
		}
	}
	size_t en = clock();
	cout << en - t << endl;
}
#else
void _array_sum(double *a, double *b, double *re)
{
	int k, i;
	size_t t = clock();
	for (k = 0; k < 4; k++) {
		for (i = 0; i < 100000000; i++) {
			re[i] = a[i] + b[i];
		}
	}
	size_t en = clock();
	cout << en - t << endl;
}
#endif
