#include <stdio.h>

int main(void)
{
	int a = 11;

	switch (a) {
#if 0
	/* error: duplicate (or overlapping) case value */
	case 3:
		break;
#endif
	case 0 ... 10:
		break;
	}
	return 0;
}
