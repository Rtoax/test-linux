#include <stdlib.h>
#include <stdio.h>
#include <arm_sve.h>

/* Scalar version. */
void add_arrays(double * restrict dst, double *src, double c, const int N)
{
	int i;
	for (i = 0; i < N; i++)
		dst[i] = src[i] + c;
}

/* Vector version */
void vla_add_arrays(double * restrict dst, double *src, double c, const int N)
{
	int64_t i = 0;

	svbool_t pg = svwhilelt_b64(i, (int64_t)N);
	while (svptest_any(svptrue_b64(), pg)) {
		svfloat64_t vsrc = svld1(pg, src + i);
		svfloat64_t vdst = svadd_x(pg, vsrc, c);
		svst1(pg, dst + i, vdst);

		i += svcntd();
		pg = svwhilelt_b64(i, (int64_t)N);
		printf("# %ld\n", i);
	}
}

/* Vector version */
void vla_add_arrays_2(double *dst, double *src, double c, const int N)
{
	int i;
	for (i = 0; i < N; i += svcntd()) {
		svbool_t Pg = svwhilelt_b64(i, N);
		svfloat64_t vsrc = svld1(Pg, &src[i]);
		svfloat64_t vdst = svadd_x(Pg, vsrc, c);
		svst1(Pg, &dst[i], vdst);
		printf("* %d\n", i);
	}
}

int main(void)
{
	int i;
	double src[100];
	double c;
	double dst_serial[100], dst_vla[100], dst_vla2[100];
	for (i = 0; i < 100; ++i) {
		src[i] = (double) i / ((double) i + 1);
	}

	c = src[rand() % 100];

	add_arrays(dst_serial, src, c, 100);
	vla_add_arrays(dst_vla, src, c, 100);
	vla_add_arrays_2(dst_vla2, src, c, 100);

	for (i = 0; i < 100; ++i) {
		printf("%f %f %f, %f, %f\n", dst_serial[i], dst_vla[i], dst_vla2[i], src[i], c);
	}
	return 0; 
}

