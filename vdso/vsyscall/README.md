vsyscall
==============

芯片厂商的争斗导致的结果就是libc和内核开发者需要对不同的快速系统调用指令进行适配，而且开发人员肯定希望用一种通用方案能够同时解决两家芯片厂商不同的快速系统调用实现方式。

在那段时间里，开发人员针对当时的x86系统开发了vsyscall机制，即glibc通过调用__kernel_vsyscall来确定到底应该执行syscall/sysret指令还是sysenter/sysexit指令。__kernel_vsyscall是一个特殊的页，其位于内核地址空间，但也是唯一允许用户访问的区域，该区域的地址固定为0xffffffffff600000（64位系统），大小固定为4K。由于所有的进程都共享内核映射，因此所有的进程也自然而言能够访问到vsyscall page。

此外，vsyscall还提供了另一个重要的作用：加速某些系统调用函数的执行效率。以gettimeofday()系统调用为例。该系统调用返回的结果起始并不涉及任何数据安全问题，因为特权用户root和非特权用户都会获得相同的结果。这就意味着其实完全可以通过新的实现机制来避免执行系统调用的开销，因为本质上gettimeofday()就是从内核中读取与时间相关的数据（虽然会有一些复杂的计算过程）。与其费尽心力一定要通过陷入内核的方式来读取这些数据，不如在内核与用户态之间建立一段共享内存区域，由内核定期“推送”最新值到该共享内存区域，然后用户态程序在调用这些系统调用的glibc库函数的时候，库函数并不真正执行系统调用，而是通过vsyscall page来读取该数据的最新值，相当于将系统调用改造成了函数调用，直接提升了执行性能。vsyscall机制支持的系统调用有3个：

```
gettimeofday()
time()
getcpu()
```

从`glibc`提供的头文件`/usr/include/asm/vsyscall.h`中就可以看出vsyscall page的用法.

```c
#ifndef _ASM_X86_VSYSCALL_H
#define _ASM_X86_VSYSCALL_H

enum vsyscall_num {
        __NR_vgettimeofday,
        __NR_vtime,
        __NR_vgetcpu,
};

#define VSYSCALL_START (-10UL << 20)
#define VSYSCALL_SIZE 1024
#define VSYSCALL_END (-2UL << 20)
#define VSYSCALL_MAPPED_PAGES 1
#define VSYSCALL_ADDR(vsyscall_nr) (VSYSCALL_START+VSYSCALL_SIZE*(vsyscall_nr))

#endif /* _ASM_X86_VSYSCALL_H */
```

但由于一些原因，开发人员又抛弃了vsyscall机制：

`vsyscall`的映射地址是固定不变的（从`vsyscall.h`的定义就可以看出），因此很容易成为`ret2libc`攻击的跳板。
`vsyscall`能支持的系统调用数有限，无法很方便地进行扩展。
虽然开发人员在x86-64上实现了emulated vsyscall机制，同时借助vvar mapping在一定程度上缓解了第一个问题，但执行性能上不如vsyscall native模式。于是开发人员设计了vDSO机制来取代vsyscall，同时必须克服vsyscall的所有缺点。

# vDSO与vsyscall最大的不同体现在以下方面：

vDSO本质上是一个ELF共享目标文件；而vsyscall只是一段内存代码和数据。

vsyscall位于内核地址空间，采用静态地址映射方式；而vDSO借助共享目标文件天生具有的PIC特性，可以以进程为粒度动态映射到进程地址空间中。

不过vDSO的引入也带来了新的混乱：在Intel正式支持`syscall/sysret`指令后，内核开发人员决定不再在x86-64系统中对`sysenter/sysexit`提供支持，转而全部使用`syscall/sysret`，相当于vsyscall中对多种快速系统调用提供支持的`__kernel_vsyscall`功能被移除了。由于后来很多人都不再提这个特性，因此vsyscall这个词又有了第二层含义：一种旧有的实现`gettimeofday()`, `time()`和`getcpu()`快速系统调用的方式。

混乱之上再增加新的混乱其实也就没啥了。为了让仍旧依赖vsyscall机制的老旧程序（包括32位和64位）继续能够在x86-64系统上运行，vsyscall机制仍旧被保留了下来（包括native模式和emulation模式）。这也是为什么你在`/proc/<pid>/maps`中会同时看到`vvar`, `vdso`, `vsyscall`三种特殊的mapping。

# 内核命令行参数

`vsyscall=native|emulate`
