#define __KERNEL__

long __1234UL(void)
{
  return 1234UL;
}

long __bpf_dummy(void)
{
  return __1234UL();
}
