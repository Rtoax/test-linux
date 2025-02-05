vDSO - Virtual Dynamic Shared Object
======================================

# vDSO 介绍

VDSO就是`Virtual Dynamic Shared Object`，就是内核提供的虚拟的.so,这个.so文件不在磁盘上，而是在内核里头。内核把包含某.so的内存页在程序启动的时候映射入其内存空间，对应的程序就可以当普通的.so来使用里头的函数。比如syscall()这个函数就是在`linux-vdso.so.1`里头的，但是磁盘上并没有对应的文件.可以通过ldd/bin/bash看看。

Linux下传统的系统调用是通过软中断(0x80)实现的,采用传统的int 0x80的系统调用浪费了很多时间,而sysenter/sysexit可以弥补这个缺点，所以才最终决定在linux内核中用后替换前者（最终在2.6版本的内核中才加入了此功能，即采用sysenter/sysexit）。

如何用替换sysenter/sysexit替换以前的int 0x80呢？

linux kenerl 需要考虑到这点：有的机器并不支持sysenter/sysexit，于是它跟glibc说好了，“你以后调用系统调用的时候就从我给你的这个地址调用，这个地址指向的内容要么是int 0x80调用方式，要么是sysenter/sysexit调用方式，我会根据机器来选择其中一个”（kernel与glibc的配合是如此的默契），这个地址便是vsyscall的首地址。

可以将`vdso`看成一个shared objdect file（这个文件实际上不存在）,内核将其映射到某个地址空间，被所有程序所共享。（我觉得这里用到了一个技术：多个虚拟页面映射到同一个物理页面。即内核把vdso映射到某个物理页面上，然后所有程序都会有一个页表项指向它，以此来共享，这样每个程序的vdso地址就可以不相同了）

可以看到，vDSO mapping的名称叫linux-vdso.so.1，其映射的基地址每次都是不同的：

```
$ ldd `which bash` | grep vdso
    linux-vdso.so.1 (0x00007ffe63bf8000)

$ ldd `which bash` | grep vdso
    linux-vdso.so.1 (0x00007ffd11978000)

$ ldd `which bash` | grep vdso
    linux-vdso.so.1 (0x00007fff6b3f1000)
```

这利用了内核的ASLR特性，以解决vsyscall page固定映射地址的安全问题。为了方便地利用ASLR特性，vDSO mapping的本体是一个ELF共享目标文件（x86-64下的文件名称叫做vdso64.so，位于内核源码arch/x86/entry/vdso/下）。


##  vDSO names

参见 `man vdso`:

       user ABI   vDSO name
       ─────────────────────────────
       aarch64    linux-vdso.so.1
       arm        linux-vdso.so.1
       ia64       linux-gate.so.1
       mips       linux-vdso.so.1
       ppc/32     linux-vdso32.so.1
       ppc/64     linux-vdso64.so.1
       riscv      linux-vdso.so.1
       s390       linux-vdso32.so.1
       s390x      linux-vdso64.so.1
       sh         linux-gate.so.1
       i386       linux-gate.so.1
       x86-64     linux-vdso.so.1
       x86/x32    linux-vdso.so.1


# vDSO image的构建过程

DSO image的构建过程比较复杂，下面是一个简要的过程描述：

编译出组成vDSO image的三个目标文件：`vdso-note.o vclock_gettime.o vgetcpu.o` 这几个目标文件主要就是实现了以下几个快速系统调用的函数实现：

```
clock_gettime()
gettimeofday()
time()
getcpu()
```

由于vDSO取代了vsyscall，内核开发人员也就不再在vsyscall上添加新的快速系统调用函数了，不过vDSO其实也就比vsyscall多实现了一个`clock_gettime()`。

* 使用专门定义的外部链接脚本vdso.lds生成raw vDSO image文件vdso64.so.dbg
* 调用objdump将vdso64.so.dbg strip为vdso64.so。
* 使用vdso2c工具将vdso64.so转换为vdso-image-64.c。vdso-image-64.c定义的是有关vdso64.so的各种blob信息，其中最重要一部分就是将vdso64.so的全部内容以C字节数组的形式放到了vdso-image-64.c中。
* 将vdso-image-64.c编译为vdso-image-64.o，并与内核中vDSO初始化相关的代码一起编译进内核。


# 应用程序如何使用vDSO mapping

在内核加载ELF binary时，内核中的ELF loader会通过辅助向量来向用户态传递一些信息；而getauxval()就是用来通过辅助向量来获取这些信息的函数：

```c
#include <sys/auxv.h>

void *vdso = (uintptr_t) getauxval(AT_SYSINFO_EHDR);
```

辅助向量中的每个entry是一个键值对儿：key称作类型，value就是值。与vDSO相关的辅助向量类型是`AT_SYSINFO_EHDR`，该向量值保存了vDSO mapping的基地址。

当然，识别vDSO mapping只是第一步，伴随而来的是繁复的解析工作；这些工作通常由glibc来承担，应用程序只要还是按照传统方式直接调用C库即可。这就意味着如果真遇到应用程序开发人员非要深入到vDSO如此细节的程度，要么是遇到了非常严重的问题，要么就是彻底搞错了方向。


# vDSO mapping支持重映射

其实这个也没什么神秘的。既然内核能够在加载ELF可执行文件的时候偷偷建立vDSO mapping，那应用程序在运行时也可以自己unmap掉它；还可以再重新映射到其他地址上。


# vvar mapping

与vDSO mapping相伴的是vvar mapping，大小8-12K，包含vDSO mapping中的代码要访问的内核与用户进程之间要共享的数据。


# Links

* [LWN: On vsyscalls and the vDSO](https://lwn.net/Articles/446528/)
* [LWN: Implementing virtual system calls](https://lwn.net/Articles/615809/)
* [LWN: vDSO, 32-bit time, and seccomp](https://lwn.net/Articles/795128/)
* selftests in linux:tools/testing/selftests/vDSO
