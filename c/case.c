#include <stdio.h>

int main(void)
{
	int a = 11;

	switch (a) {
	case 'a'...'z':
		printf("a-z\n");
		break;
#if 0
	/* error: duplicate (or overlapping) case value */
	case 3:
		break;
#endif
	case 0 ... 10:
		break;
	/**
	 * This is a label
	 */
	defualt:
		break;
	default:
		break;
	}
	return 0;
}
