#define __KERNEL__

int __bpf_memcpy(char *dest, const char *src, int n)
{
  int i;
  for (i = 0; i < n; i++)
    dest[i] = src[i];
  return i;
}
