#define __KERNEL__

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
