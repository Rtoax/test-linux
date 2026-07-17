/**
 * long bpf_loop(__u32 nr_loops, void *callback_fn, void *callback_ctx,
 *               __u64 flags);
 * BPF_FUNC_loop = 181;
 * typedef int (*callback_fn)(__u32 index, void *callback_ctx);
 *
 * linux >= v5.17
 *
 * Refs:
 * - https://docs.ebpf.io/linux/helper-function/bpf_loop/
 *
 * Examples:
 * - commit bbcd5250f2b0 ("bpftrace/playground: loop.bpf.c: fix: unreachable insn N")
 */
#define __KERNEL__
#include <linux/types.h>
#include <stddef.h>

static long (*const bpf_probe_read_kernel)(void *dst, __u32 size, const void *unsafe_ptr) = (void *)113;

typedef int (*callback_fn)(__u32 index, void *ctx);

/* Must be inline, becuase the register */
static inline int asm_bpf_loop(__u32 nr_loops, callback_fn fn, void *ctx,
                               __u64 flags)
{
  int BPF_FUNC_loop = 181;

  register int ret asm("r0");

  asm volatile (
      "r1 = %[nr_loops]\n"             // BPF_MOV64_IMM(BPF_REG_1, nr_loops)
      "r2 = %[callback] ll\n"          // BPF_MOV64_IMM(BPF_REG_2, callback)
      "r3 = %[callback_ctx]\n"         // BPF_MOV64_IMM(BPF_REG_3, callback_ctx)
      "r4 = %[flags]\n"                // BPF_MOV64_IMM(BPF_REG_4, 0)
      "call %[bpf_loop]\n"             // call bpf_loop()
      : "=r"(ret)
      : [nr_loops] "r" (nr_loops),
        [callback] "i" (fn),
        [callback_ctx] "r" (ctx),
        [flags] "r" (flags),
        [bpf_loop] "i" (BPF_FUNC_loop)
      : "r0", "r1", "r2", "r3", "r4"
  );
  return ret;
}

/******************************************************************************\
 * arithmetic sum
\******************************************************************************/
struct arithmetic_sum_cb_ctx {
  int sum;
};

static int arithmetic_sum_cb(__u32 index, void *data)
{
  struct arithmetic_sum_cb_ctx *ctx = data;
  ctx->sum += index + 1;
  return 0;
}

int __bpf_arithmetic_sum(__u32 nr_loops)
{
  struct arithmetic_sum_cb_ctx ctx = {
    .sum = 0,
  };
  asm_bpf_loop(nr_loops, arithmetic_sum_cb, &ctx, 0);
  return ctx.sum;
}

/******************************************************************************\
 * strnlen()
\******************************************************************************/
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

long __bpf_strnlen(const char *str, __u32 sz)
{
  struct strnlen_ctx ctx = {
    .str = str,
    .sz = sz,
    .len = 0,
  };
  asm_bpf_loop(sz, strnlen_cb, &ctx, 0);
  return ctx.len;
}

/******************************************************************************\
 * strcat()
\******************************************************************************/
struct strcat_ctx {
  const char *src;
  char *dst;
  __u32 ssz, dsz, dlen;
  __u32 copied;
};

static int strcat_cb(__u32 index, void *data)
{
  struct strcat_ctx *ctx = data;
  __u32 didx = index + ctx->dlen;
  if (didx >= ctx->dsz || index >= ctx->ssz || ctx->src[index] == '\0') {
    return 1;
  }
  // TODO: How to fix unbounded access, do not use '%'.
  ctx->dst[didx % 256] = ctx->src[index];
  ctx->copied++;
  return 0;
}

int __bpf_strcat(char *dst, __u32 dst_sz, const char *src, __u32 src_sz)
{
  __u32 i, j;
  size_t dst_len = __bpf_strnlen(dst, dst_sz);

  struct strcat_ctx ctx = {
    .src = src,
    .dst = dst,
    .ssz = src_sz,
    .dsz = dst_sz,
    .dlen = dst_len,
    .copied = 0,
  };
  asm_bpf_loop(src_sz, strcat_cb, &ctx, 0);

  return ctx.copied + dst_len;
}
