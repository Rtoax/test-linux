#include <bpf/bpf_tracing.h>


/**
 * TODO: why failed???????
 */
void __bpf_str_append(char *dst__ign, size_t dst_sz, const char *src__ign, size_t src_sz)
{
	dst__ign[0] = 'A';
	int i, j;

	for (i = 0; i < dst_sz && dst__ign[i] != '\0'; i++);

	dst__ign[0] = 'B';

	for (j = 0; i < dst_sz && j < src_sz && src__ign[j] != '\0'; j++, i++);
		//dst__ign[i++] = src__ign[j];

	dst__ign[0] = 'C';
#if 0
	if (i < dst_sz) {
		dst__ign[i] = '\0';
	} else {
		dst__ign[dst_sz - 1] = '\0';
	}
#endif
}
