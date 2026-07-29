The Kernel Address Sanitizer (KASAN)
=====================================

KernelAddressSANitizer (KASAN)
------------------------------

*Kernel Address Sanitizer (KASAN)* is a fast memory safety error detector for the Linux kernel. It detects out-of-bounds and use-after-free bugs in `slab, page_alloc, vmalloc, stack, and global memory`.

KASAN has a `Hardware Tag-Based mode <https://www.kernel.org/doc/html/latest/dev-tools/kasan.html#hardware-tag-based-kasan>`_ intended to be used in production as a security mitigation. This mode is based on the Arm Memory Tagging Extension and is expected to have a low performance overhead.

* slab out of bounds
* use after free
* stack out of bounds
* global out of bounds

* `CONFIG_KASAN=y`: To enable KASAN;
* `CONFIG_KASAN_GENERIC`: to enable generic KASAN;
* `CONFIG_KASAN_SW_TAGS`: to enable software tag-based KASAN;
* `CONFIG_KASAN_HW_TAGS`: to enable hardware tag-based KASAN


KASAN 原理
----------

`KASAN` 的原理是利用额外的内存标记可用内存的状态。这部分额外的内存被称作 `shadow memory` （影子区）。 `KASAN` 将 `1/8` 的内存用作shadow memory。使用特殊的 `magic num` 填充shadow memory，在每一次 `load/store` （ `load/store` 检查指令由编译器插入）内存的时候检测对应的 `shadow memory` 确定操作是否 `valid` 。连续 `8 bytes` 内存（8 bytes align）使用 `1 byte shadow memory` 标记。如果 `8 bytes` 内存都可以访问，则shadow memory的值为0；如果连续N(`1 =< N <= 7`) bytes可以访问，则 `shadow memory` 的值为N；如果8 bytes内存访问都是invalid，则shadow memory的值为负数。


Links
-----

* https://www.kernel.org/doc/html/latest/dev-tools/kasan.html
