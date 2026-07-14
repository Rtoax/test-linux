#define __KERNEL__
#include <asm/errno.h>
#include <asm/posix_types.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <stddef.h>

#include <bpf/bpf_helpers.h>

long __bpf_strnlen(const char *ptr, size_t max_size);

// see https://github.com/bpftrace/bpftrace/pull/5231
size_t __bpf_str_concat(char *dst, size_t dst_sz, const char *src,
                        size_t src_sz)
{
  __u8 i, j;
  size_t dst_len = __bpf_strnlen(dst, dst_sz);
  size_t src_len = __bpf_strnlen(src, src_sz);

  // Provide sufficient conditions for the BPF Verifier
  for (i = dst_len, j = 0; i < dst_sz - 1 && j < src_sz - 1 && src[j] != '\0';
       j++, i++)
    dst[i] = src[j];

  dst[i] = '\0';

  return j;
}
