/**
 * see bpf_core_field_exists()
 */
#include <stdio.h>

struct task_struct {
	int state;
};

struct task_struct___x {
	int __state;
} __attribute__((preserve_access_index));

enum {
	BPF_FIELD_EXISTS = 2,
};

#define bpf_core_field_exists(field)					\
	__builtin_preserve_field_info(field, BPF_FIELD_EXISTS)

int main(void)
{
	char buffer[256] = {};
	struct task_struct___x *t = (struct task_struct___x *)buffer;

	printf("%d\n", bpf_core_field_exists(t->__state));

	return 0;
}
