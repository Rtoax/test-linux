HyperCall
=========

# KVM_EXIT_HYPERCALL

在Linux中，大家应该对syscall非常的了解和熟悉，其是用户态进入内核态的一种途径或者说是一种方式，完成了两个模式之间的切换；

而在虚拟环境中，有没有一种类似于syscall这种方式，能够从no root模式切换到root模式呢？
答案是肯定的，KVM提供了Hypercall机制，x86体系架构也有相关的指令支持。

