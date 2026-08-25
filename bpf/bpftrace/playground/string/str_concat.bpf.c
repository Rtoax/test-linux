#define __KERNEL__
#include <asm/errno.h>
#include <asm/posix_types.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <stddef.h>

#include <bpf/bpf_helpers.h>

extern int bpf_strnlen(const char *s__ign, size_t count) __ksym __weak;

#define has_bpf_loop 1 /* TODO: pass from bpftrace feature cflags */

/* copy from test-linux/bpf/bpftrace/playground/loop.bpf.c */
struct strnlen_ctx {
  const char *str;
  __u32 sz;
  __u32 len;
};

static int strnlen_cb(__u32 index, void *data)
{
  struct strnlen_ctx *ctx = data;
  if (index > ctx->sz) {
    return 1;
  }
  /* avoid verifier error: unbounded memory access */
  __u64 unsafe_addr = (__u64)ctx->str;
  unsafe_addr += index;
  char ch;
  bpf_probe_read_kernel(&ch, sizeof(char), (void *)unsafe_addr);
  if (ch == '\0') {
    return 1;
  }
  ctx->len++;
  return 0;
}

long __bpf_strnlen(const char *ptr, size_t max_size)
{
  if (bpf_strnlen) {
    return bpf_strnlen(ptr, max_size);
  }
#ifdef has_bpf_loop
  struct strnlen_ctx ctx = {
    .str = ptr,
    .sz = max_size,
    .len = 0,
  };
  bpf_loop(max_size, strnlen_cb, &ctx, 0);
  return ctx.len;
#else
  long sz = 0;
  for (size_t i = 0; i < max_size; ++i) {
    if (ptr[i] == 0) {
      break;
    }
    ++sz;
  }
  return sz;
#endif
}

// see https://github.com/bpftrace/bpftrace/pull/5231
size_t __bpf_str_concat(char *dst, size_t dst_sz, const char *src,
                        size_t src_sz)
{
  long dst_len = __bpf_strnlen(dst, dst_sz);
  if (dst_len < 0 || dst_len >= dst_sz)
    return 0;
#if 1
  return bpf_probe_read_kernel_str(dst + dst_len, dst_sz - dst_len, src);
#else
  __u32 i, j;
  // Provide sufficient conditions for the BPF Verifier
  for (i = dst_len, j = 0; i < dst_sz - 1 && j < src_sz - 1 && src[j] != '\0';
       j++, i++)
    dst[i] = src[j];

  dst[i % dst_sz] = '\0';

  return j;
#endif
}
