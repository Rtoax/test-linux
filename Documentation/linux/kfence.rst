Kernel Electric-Fence (KFENCE)
==============================

* https://www.kernel.org/doc/html/latest/dev-tools/kfence.html

Kernel Electric-Fence (KFENCE) is a low-overhead sampling-based memory safety error detector.
KFENCE detects:

在以下情况，会检测报错：

* heap out-of-bounds access
* use-after-free
* invalid-free errors

* 释放时发现Canary数据不对。
* 当KFENCE内存池的内存区域发生Page Fault时，它或者是因为越界访问、或者是释放后使用。
* 无效释放：当一段KFENCE内存没有被标记分配，但对齐释放时，会有相应报错提示。


KFENCE is designed to be enabled in production kernels, and has near zero performance overhead. Compared to KASAN, KFENCE trades performance for precision. The main motivation behind KFENCE’s design, is that with enough total uptime KFENCE will detect bugs in code paths not typically exercised by non-production test workloads. One way to quickly achieve a large enough total uptime is when the tool is deployed across a large fleet of machines.

* `CONFIG_KFENCE=y`:


Links
-----

- https://github.com/google/kernel-sanitizers/blob/master/KFENCE.md
