#define __KERNEL__

static int loop_cnt = 0;
static int loop_callback(unsigned int index, void *data)
{
  loop_cnt++;
  return 0;
}

int __bpf_count(void)
{
  int BPF_FUNC_loop = 181;

  /* bpf_loop(10, loop_callback, 0, 0); */
  asm volatile (
      "r1 = 10\n"                      // BPF_MOV64_IMM(BPF_REG_1, 10)
      "r2 = %[callback] ll\n"          // r2
      "r3 = 0\n"                       // BPF_MOV64_IMM(BPF_REG_3, 0)
      "r4 = 0\n"                       // BPF_MOV64_IMM(BPF_REG_4, 0)
      "call %[bpf_loop]\n"             // call bpf_loop()
      "r0 = 0\n"                       // BPF_MOV64_IMM(BPF_REG_0, 0)
      "exit\n"                         // BPF_EXIT_INSN()
      :
      : [callback] "i" (loop_callback),
        [bpf_loop] "i" (BPF_FUNC_loop)
      : "r0", "r1", "r2", "r3", "r4"
  );
  return loop_cnt;
}
