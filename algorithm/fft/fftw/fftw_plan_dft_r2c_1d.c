#include <stdio.h>
#include <fftw3.h>

#define FFT_WINSZ_IN 	1024
#define FFT_WINSZ_OUT	(FFT_WINSZ_IN / 2) + 1


int main(void)
{
	int i;

	fftw_plan plan;
	double *fft_in;
	fftw_complex *fft_out;

	fft_in = (double *)fftw_malloc(sizeof(double) * FFT_WINSZ_IN);
	fft_out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * FFT_WINSZ_IN);

	for (i = 0; i < FFT_WINSZ_IN; i++) {
		fft_in[i] = 10.0;
	}

	plan = fftw_plan_dft_r2c_1d(FFT_WINSZ_IN, fft_in, fft_out, FFTW_MEASURE);

	fftw_execute(plan);

	for (i = 0; i < FFT_WINSZ_IN; i++) {
		printf("%lf \t %lf\n", fft_out[i][0], fft_out[i][1]);
	}

	fftw_destroy_plan(plan);
	fftw_free(fft_in);
	fftw_free(fft_out);

	return 0;
}
