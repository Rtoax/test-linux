NO_HZ: Reducing Scheduling-Clock Ticks
======================================


1. 永远不要省略调度时钟滴答, `CONFIG_HZ_PERIODIC=y` 或 `CONFIG_NO_HZ=n`
2. 省略空闲 CPU 上的调度时钟滴答, `CONFIG_NO_HZ_IDLE=y`或 `CONFIG_NO_HZ=y`
3. 忽略空闲或只有一个可运行任务的 CPU 上的调度时钟滴答, `CONFIG_NO_HZ_FULL=y`


Links
-----

* https://www.kernel.org/doc/html/latest/timers/no_hz.html
