#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

int show_complex(float complex c)
{
	printf("(%f, %f)\n", creal(c), cimag(c));
	return 0;
}

int main(void)
{
	float complex ic, icsin;

	ic = 1 + 1 * I;

	show_complex(ic);
	show_complex(ccos(ic));
	show_complex(conj(ccos(ic)));
	show_complex(conjf(ccos(ic)));
	show_complex(carg(ic));
	show_complex(cargf(ic));

	return 0;
}
