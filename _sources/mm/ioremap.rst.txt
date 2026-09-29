ioremap
=======

`ioremap()` 和 `vmalloc()` 类似，需要建立新的页表，但是不进行 `vmalloc()` 中所执行的内存分二批行为。
