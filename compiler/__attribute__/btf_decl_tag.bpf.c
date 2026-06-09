#define __bpf_kfunc __attribute__((btf_decl_tag("bpf_kfunc")))

__bpf_kfunc void my_kfunc(void)
{
}
