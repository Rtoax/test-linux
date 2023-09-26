EEVDF - Earliest Eligible Virtual Deadline First
================================================

EEVDF: 最早符合条件的虚拟截止日期优先.

EEVDF的核心，顾名思义，就是会优先运行虚拟deadline最早的进程.

确保某些进程可以快速访问 CPU 而不必让这些进程能够获得超过其公平份额的 CPU 时间
的方法。与 CFS 一样，EEVDF 尝试在争用它的进程之间公平地分配可用 CPU 时间。例如，
如果有五个进程试图在一个 CPU 上运行，那么每个进程都应该获得 20% 的可用时间。给
定进程的 nice 值可用于调整其公平时间的计算；具有较低 nice 值（因此具有较高优先级）
的进程有权获得更多 CPU 时间，但代价是具有较高 nice 值的进程。

对于每个进程，EEVDF 计算进程本应获得的时间与实际获得的时间之间的差值；这种差异
称为“滞后”。因此，滞后的计算是 EEVDF 调度程序的关键部分.


# Links

- https://lwn.net/Articles/925371/
- https://zhuanlan.zhihu.com/p/617184812 (译上)
- https://lwn.net/ml/linux-kernel/20230306132521.968182689@infradead.org/

