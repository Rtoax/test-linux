Kernel Concurrency Sanitizer (KCSAN) 内核并发消杀
=================================================

The Kernel Concurrency Sanitizer (KCSAN) is a dynamic race detector, which relies on compile-time instrumentation, and uses a watchpoint-based sampling approach to detect races. KCSAN’s primary purpose is to detect data races.

内核并发消毒器(Kernel Concurrency sanitzer，KCSAN)是一个动态竞争检测器，它依赖于编译时插装，并使用基于观察点的采样方法来检测竞争。的主要目的是检测数据竞争。

- 参见内核补丁`commit b1fc58333575("stop_machine: Avoid potential race behaviour")`

*Kernel Concurrency Sanitizer (KCSAN)* is a watchpoint-based dynamic race-detector for the Linux kernel.

For details, see the LWN articles:

* [Concurrency bugs should fear the big bad data-race detector (part 1)](https://lwn.net/Articles/816850/)
* [Concurrency bugs should fear the big bad data-race detector (part 2)](https://lwn.net/Articles/816854/)

And a talk:

* [Data-race detection in the Linux kernel at Linux Plumbers Conference 2020](/kcsan/LPC2020-KCSAN.pdf)

For an alternative approach based on a happens-before algorithm, see [Kernel Thread Sanitizer (KTSAN)](/KTSAN.md).


Continuous testing & fuzzing
----------------------------

We have a [public syzbot instance](https://syzkaller.appspot.com/upstream?manager=ci2-upstream-kcsan-gce). Reports will appear on the dashboard after internal review, to keep the volume of bugs manageable (which gives us a chance to carefully react to KCSAN reports while best practices are still evolving).


Links
-----

- https://docs.kernel.org/dev-tools/kcsan.html
- https://www.kernel.org/doc/html/latest/dev-tools/kcsan.html
- https://github.com/google/kernel-sanitizers
