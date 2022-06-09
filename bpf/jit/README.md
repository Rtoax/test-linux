JIT - Just In Time Compiler
===========================

# 及时编译器

在一些特定硬件平台，进行提速

* `bpf_init_jit_compile()`: 将传入的 BPF 伪代码加以编译，编译结果取代原有的处理函数
* `sk_run_filter()`: 负责报文到来时进行过滤的操作，提升效率

