#define __KERNEL__

int __bpf_memcpy(char *dest, const char *src, int n)
{
  int i;
  for (i = 0; i < n; i++)
    dest[i] = src[i];
  return i;
}

int __bpf_strncpy(char *dest, const char *src, int n)
{
  int i;
  for (i = 0; i < n && src[i] != '\0'; i++)
    dest[i] = src[i];
  dest[i] = '\0';
  return i;
}
