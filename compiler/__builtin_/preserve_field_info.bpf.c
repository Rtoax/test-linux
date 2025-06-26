/**
 * BPF Compile Once-Run Everywhere (CO-RE) support. This builtin is used to
 * extract information to aid in struct/union relocations. expr is an access
 * to a field of a struct or union. Depending on kind, different information
 * is returned to the program. A CO-RE relocation for the access in expr with
 * kind kind is recorded if -mco-re is in effect.
 *
 * - unsigned long long __builtin_bpf_load_byte (unsigned long long offset)
 * - unsigned long long __builtin_bpf_load_half (unsigned long long offset)
 * - unsigned long long __builtin_bpf_load_word (unsigned long long offset)
 * - type __builtin_preserve_access_index (type expr)
 * - unsigned int __builtin_preserve_field_info (expr, unsigned int kind)
 * - unsigned int __builtin_preserve_enum_value (type, enum, unsigned int kind)
 * - unsigned int __builtin_btf_type_id (type, unsigned int kind)
 * - unsigned int __builtin_preserve_type_info (type, unsigned int kind)
 *
 * [1] https://gcc.gnu.org/onlinedocs/gcc/BPF-Built-in-Functions.html
 * [2] see libbpf bpf_core_field_exists()
 * [3] https://www.ebpf.top/post/ebpf_struct_ops/
 */

struct task_struct {
	int state;
};

struct task_struct___x {
	int __state;
}
#if 0
__attribute__((preserve_access_index))
#endif
;

enum {
	FIELD_BYTE_OFFSET = 0,
	FIELD_BYTE_SIZE = 1,
	FIELD_EXISTENCE = 2,
#define BPF_FIELD_EXISTS	FIELD_EXISTENCE
	FIELD_SIGNEDNESS = 3,
	FIELD_LSHIFT_U64 = 4,
	FIELD_RSHIFT_U64 = 5,
};

enum {
	ENUM_VALUE_EXISTS = 0,
	ENUM_VALUE = 1,
};

enum {
	BTF_TYPE_ID_LOCAL = 0,
	BTF_TYPE_ID_TARGET = 1,
};

enum {
	BTF_TYPE_EXISTS = 0,
	BTF_TYPE_MATCHES = 1,
	BTF_TYPE_SIZE = 2,
};

#define bpf_core_field_exists(field)					\
	__builtin_preserve_field_info(field, BPF_FIELD_EXISTS)

int kprobe__foo(void)
{
	char buffer[256] = {};
	struct task_struct___x *t = (struct task_struct___x *)buffer;

	(void)t;

	return 0;
}

int main(void)
{
	return 0;
}
