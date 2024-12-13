/**
 * BPF_PROG_TYPE_LWT_IN
 *
 * LWT (Light Weight Tunnel) Input programs attach to the ingress path of a
 * light weight tunnel.
 *
 * see linux/tools/testing/selftests/bpf/progs/verifier_lwt.c
 */
#include <vmlinux.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

#define XSTR(s) STR(s)
#define STR(s) #s

#define __naked __attribute__((naked))
#define __clobber_all "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "memory"
#define __imm_const(name, expr) [name]"i"(expr)

#define __description(desc)     __attribute__((btf_decl_tag("comment:test_description=" desc)))
#define __msg(msg)              __attribute__((btf_decl_tag("comment:test_expect_msg=" XSTR(__COUNTER__) "=" msg)))
#define __failure               __attribute__((btf_decl_tag("comment:test_expect_failure")))
#define __success               __attribute__((btf_decl_tag("comment:test_expect_success")))


SEC("lwt_in")
__description("invalid direct packet write for LWT_IN")
__failure __msg("cannot write into packet")
__naked void packet_write_for_lwt_in(void)
{
	asm volatile ("					\
	r2 = *(u32*)(r1 + %[__sk_buff_data]);		\
	r3 = *(u32*)(r1 + %[__sk_buff_data_end]);	\
	r0 = r2;					\
	r0 += 8;					\
	if r0 > r3 goto l0_%=;				\
	*(u8*)(r2 + 0) = r2;				\
l0_%=:	r0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(struct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(struct __sk_buff, data_end))
	: __clobber_all);
}

char _license[] SEC("license") = "GPL";
