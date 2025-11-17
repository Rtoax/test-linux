#include <stdio.h>
#include <linux/bpf.h>

int main(void)
{
#ifdef ___BPF_FUNC_MAPPER
# define __BPF_PRINT_FN(x, y)	printf("%-48s = %d\n", "BPF_FUNC_" #x, y);
	___BPF_FUNC_MAPPER(__BPF_PRINT_FN);
#endif
	return 0;
}
