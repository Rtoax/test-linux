/**
 * - commit b290d3a5687e ("bpf/kfunc: add bpf_func_mapper.c to display all BPF_FUNC_xxx")
 */
#include <stdio.h>
#include <linux/bpf.h>

int main(void)
{
/**
 * linux v6.0-2740-g8a76145a2ec2 move __BPF_FUNC_MAPPER(FN) to ___BPF_FUNC_MAPPER(FN, ctx...)
 * commit 8a76145a2ec2 ("bpf: explicitly define BPF_FUNC_xxx integer values")
 */
#ifdef ___BPF_FUNC_MAPPER
# define __BPF_PRINT_FN(x, y)	printf("%-48s = %d\n", "BPF_FUNC_" #x, y);
	___BPF_FUNC_MAPPER(__BPF_PRINT_FN);
#elif defined(__BPF_FUNC_MAPPER)
# define __BPF_PRINT_FN(x)	printf("%-48s = %d\n", "BPF_FUNC_" #x, BPF_FUNC_ ## x)
	__BPF_FUNC_MAPPER(__BPF_PRINT_FN)printf("\n");
#else
# error "Not found BPF_FUNC_MAPPER macro, please check /usr/include/linux/bpf.h"
#endif
	return 0;
}
