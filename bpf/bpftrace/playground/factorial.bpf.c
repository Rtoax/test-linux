#define __KERNEL__

long __bpf_factorial(long a)
{
  long i, factorial = 1;
  for (i = 1; i <= a; i++)
    factorial *= i;
  return factorial;
}
