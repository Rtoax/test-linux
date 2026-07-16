/**
 * Examples:
 * - commit bbcd5250f2b0 ("bpftrace/playground: loop.bpf.c: fix: unreachable insn N")
 */
#define __KERNEL__

static int loop_cnt = 0;
static int callback(unsigned int index, void *data)
{
  loop_cnt++;
  return 0;
}

int __bpf_count(void)
{
  int BPF_FUNC_loop = 181;

  /* bpf_loop(10, callback, 0, 0); */
  asm volatile (
      "r1 = 10\n"                      // BPF_MOV64_IMM(BPF_REG_1, 10)
      "r2 = %[callback] ll\n"          // BPF_MOV64_IMM(BPF_REG_2, callback)
      "r3 = 0\n"                       // BPF_MOV64_IMM(BPF_REG_3, 0)
      "r4 = 0\n"                       // BPF_MOV64_IMM(BPF_REG_4, 0)
      "call %[bpf_loop]\n"             // call bpf_loop()
      "r0 = %[cnt]\n"                  // BPF_MOV64_IMM(BPF_REG_0, cnt)
      :
      : [callback] "i" (callback),
        [bpf_loop] "i" (BPF_FUNC_loop),
	[cnt] "i" (10) /* TODO: replace to loop_cnt */
      : "r0", "r1", "r2", "r3", "r4"
  );
  /**
   * No need "exit\n" in asm(), because exit is here in the end of function.
   */
}
