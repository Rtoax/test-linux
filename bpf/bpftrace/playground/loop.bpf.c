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

typedef int (*callback_fn)(unsigned int index, void *ctx);

/* Must be inline, becuase the register */
static inline int __bpf_loop(unsigned int nr_loops, callback_fn fn, void *ctx)
{
  int BPF_FUNC_loop = 181;

  register int ret asm("r0");

  asm volatile (
      "r1 = %[nr_loops]\n"             // BPF_MOV64_IMM(BPF_REG_1, nr_loops)
      "r2 = %[callback] ll\n"          // BPF_MOV64_IMM(BPF_REG_2, callback)
      "r3 = %[callback_ctx]\n"         // BPF_MOV64_IMM(BPF_REG_3, callback_ctx)
      "r4 = 0\n"                       // BPF_MOV64_IMM(BPF_REG_4, 0)
      "call %[bpf_loop]\n"             // call bpf_loop()
      : "=r"(ret)
      : [nr_loops] "r" (nr_loops),
        [callback] "i" (fn),
        [callback_ctx] "r" (ctx),
        [bpf_loop] "i" (BPF_FUNC_loop)
      : "r0", "r1", "r2", "r3", "r4"
  );
  return ret;
}

struct arithmetic_sum_cb_ctx {
  int sum;
};

static int arithmetic_sum_cb(unsigned int index, void *data)
{
  struct arithmetic_sum_cb_ctx *ctx = data;
  ctx->sum += index + 1;
  return 0;
}

int __bpf_arithmetic_sum(unsigned int nr_loops)
{
  struct arithmetic_sum_cb_ctx ctx = {
    .sum = 0,
  };
  __bpf_loop(nr_loops, arithmetic_sum_cb, &ctx);
  return ctx.sum;
}

struct strlen_ctx {
  const char *str;
  int str__sz;
  int len;
};

static int strlen_cb(unsigned int index, void *data)
{
  struct strlen_ctx *ctx = data;
  if (index > ctx->str__sz) {
    return 1;
  }
  // TODO: How to fix unbounded access, do not use '%'.
  if (ctx->str[index % 256] == '\0') {
    return 1;
  }
  ctx->len++;
  return 0;
}

int __bpf_strlen(const char *str, int str__sz)
{
  struct strlen_ctx ctx = {
    .str = str,
    .str__sz = str__sz,
    .len = 0,
  };
  __bpf_loop(str__sz, strlen_cb, &ctx);
  return ctx.len;
}
