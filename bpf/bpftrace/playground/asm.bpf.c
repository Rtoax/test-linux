#define __KERNEL__
#include <linux/types.h>
#include <stddef.h>

int __bpf_asm_ret(void)
{
  register int ret asm("r6");
  asm volatile ("r6 = 123\n" : "=r"(ret));
  return ret;
}

int __bpf_asm_ret_v2(void)
{
  register int ret asm("r6");
  asm volatile ("r6 = %[val]\n"
    : "=r"(ret)
    : [val] "i" (123)
    :);
  return ret;
}

int __bpf_asm_ret_val(int val)
{
  register int ret asm("r6");
  asm volatile ("r6 = %[val]\n"
    : "=r"(ret)
    : [val] "r" (val)
    :);
  return ret;
}

/**
 * TODO: move it to bpf.h, included by bpf.c
 */
static int __bpf_helper_call(__u64 _nr_helper, __u64 arg0, __u64 arg1,
                             __u64 arg2, __u64 arg3, __u64 arg4)
{
  register int ret asm("r0");

  asm volatile (
      "r1 = %[arg0] ll\n"
      "r2 = %[arg1] ll\n"
      "r3 = %[arg2] ll\n"
      "r4 = %[arg3] ll\n"
      "r5 = %[arg4] ll\n"
      "call %[nr]\n"
      : "=r"(ret)
      : [arg0] "r" (arg0),
        [arg1] "r" (arg1),
        [arg2] "r" (arg2),
        [arg3] "r" (arg3),
        [arg4] "r" (arg4),
        [nr] "i" (_nr_helper)
      : "r0", "r1", "r2", "r3", "r4", "r5"
  );
  return ret;
}
