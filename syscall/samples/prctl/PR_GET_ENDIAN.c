#include <stdio.h>
#include <sys/prctl.h>

void pr_get_endian(void)
{
	int endian;
	prctl(PR_GET_ENDIAN, &endian, 0, 0, 0);

	switch (endian) {
	case PR_ENDIAN_BIG:
		printf("PR_ENDIAN_BIG\n");
		break;
	case PR_ENDIAN_LITTLE:
		printf("PR_ENDIAN_LITTLE\n");
		break;
	case PR_ENDIAN_PPC_LITTLE:
		printf("PR_ENDIAN_PPC_LITTLE\n");
		break;
	default:
		printf("unknown endian.%d\n", endian);
		break;
	}
}

int main(void)
{
	pr_get_endian();
	return 0;
}
