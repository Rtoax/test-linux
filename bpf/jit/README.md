BPF JIT - Just In Time Compiler
===============================

# Linux JIT kstack

```c
bpf_prog_load(bpf_attr) {
  bpf_int_jit_compile(bpf_prog) {
    /* x86_64 */
    do_jit(prog, ...) {
      for (i = 1; i <= insn_cnt; i++) {
        /* BPF_ADD -> x86 add */
      }
    }
    /* aarch64 */
    build_body(jit_ctx) {
      build_insn(insn) {
        /* BPF_ADD -> x86 add */
      }
    }
  }
}
```


# Links

- https://gcc.gnu.org/wiki/JIT
- https://llvm.org/docs/DebuggingJITedCode.html
- https://llvm.org/docs/JITLink.html
- https://llvm.org/docs/ORCv2.html
- https://llvm.org/docs/MCJITDesignAndImplementation.html

