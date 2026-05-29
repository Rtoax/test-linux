#include <stdio.h>
#include <float.h>

int main(void)
{
#define Pe(v) printf("%-16s = %e\n", #v, v)
#define PLe(v) printf("%-16s = %Le\n", #v, v)
	Pe(FLT_MIN);
	Pe(-FLT_MIN);
	Pe(FLT_MAX);
	Pe(-FLT_MAX);
	Pe(DBL_MIN);
	Pe(-DBL_MIN);
	Pe(DBL_MAX);
	Pe(-DBL_MAX);
	PLe(LDBL_MIN);
	PLe(-LDBL_MIN);
	PLe(LDBL_MAX);
	PLe(-LDBL_MAX);
#undef Pe
#undef PLe
	return 0;
}
