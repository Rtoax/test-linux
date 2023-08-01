JIT - Just In Time Compiler
===========================

# 及时编译器

在一些特定硬件平台，进行提速

* `bpf_init_jit_compile()`: 将传入的 BPF 伪代码加以编译，编译结果取代原有的处理函数
* `sk_run_filter()`: 负责报文到来时进行过滤的操作，提升效率


# libgccjit

看个评论: libgccjit简直就只是一个玩具，根本没有办法拿来做即时编译器， 所以我决定不学libgccjit.


# Links

- https://gcc.gnu.org/wiki/JIT
- https://llvm.org/docs/DebuggingJITedCode.html
- https://llvm.org/docs/JITLink.html
- https://llvm.org/docs/ORCv2.html
- https://llvm.org/docs/MCJITDesignAndImplementation.html

