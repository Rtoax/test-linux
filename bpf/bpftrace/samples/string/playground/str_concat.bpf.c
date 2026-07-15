#define __KERNEL__
#include <asm/errno.h>
#include <asm/posix_types.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <stddef.h>

#include <bpf/bpf_helpers.h>

extern int bpf_strnlen(const char *s__ign, size_t count) __ksym __weak;

long __bpf_strnlen(const char *ptr, size_t max_size)
{
  if (bpf_strnlen) {
    return bpf_strnlen(ptr, max_size);
  }
  long sz = 0;
  for (size_t i = 0; i < max_size; ++i) {
    if (ptr[i] == 0) {
      break;
    }
    ++sz;
  }
  return sz;
}

// see https://github.com/bpftrace/bpftrace/pull/5231
size_t __bpf_str_concat(char *dst, size_t dst_sz, const char *src,
                        size_t src_sz)
{
  __u32 i, j;
  size_t dst_len = __bpf_strnlen(dst, dst_sz);
  size_t src_len = __bpf_strnlen(src, src_sz);

  // Provide sufficient conditions for the BPF Verifier
  for (i = dst_len, j = 0; i < dst_sz - 1 && j < src_sz - 1 && src[j] != '\0';
       j++, i++)
    dst[i] = src[j];

  dst[i % dst_sz] = '\0';

  return j;
}
