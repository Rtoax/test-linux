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

struct callback_ctx {
  int loop_cnt;
};
static int callback(unsigned int index, void *data)
{
  struct callback_ctx *ctx = data;
  ctx->loop_cnt += 2;
  return 0;
}

int __bpf_count(unsigned int nr_loops)
{
  int BPF_FUNC_loop = 181;
  struct callback_ctx ctx = {
    .loop_cnt = 0,
  };

  register int ret asm("r0");

  /* bpf_loop(10, callback, 0, 0); */
  asm volatile (
      "r1 = %[nr_loops]\n"             // BPF_MOV64_IMM(BPF_REG_1, nr_loops)
      "r2 = %[callback] ll\n"          // BPF_MOV64_IMM(BPF_REG_2, callback)
      "r3 = %[callback_ctx]\n"         // BPF_MOV64_IMM(BPF_REG_3, callback_ctx)
      "r4 = 0\n"                       // BPF_MOV64_IMM(BPF_REG_4, 0)
      "call %[bpf_loop]\n"             // call bpf_loop()
      : "=r"(ret)
      : [nr_loops] "r" (nr_loops),
        [callback] "i" (callback),
        [callback_ctx] "r" (&ctx),
        [bpf_loop] "i" (BPF_FUNC_loop)
      : "r0", "r1", "r2", "r3", "r4"
  );
  ret = ctx.loop_cnt;
  return ret;
}
