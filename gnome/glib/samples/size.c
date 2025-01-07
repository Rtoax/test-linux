#include <glib.h>
#include <stdio.h>
#include <locale.h>

int main(int argc, char *argv[])
{
#define P(v) printf("%-64s : %d\n", #v, v)

	P(GLIB_SIZEOF_SIZE_T);
	return 0;
}

