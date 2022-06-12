MMIO - Memory mapping I/O
=========================

# 介绍

`内存映射I/O`，它是`PCI规范`的一部分，`I/O`设备被放置在内存空间而不是`I/O`空间。
从处理器的角度看，内存映射`I/O`后系统设备访问起来和内存一样。
这样访问`AGP/PCI-E`显卡上的帧缓存，BIOS，PCI设备就可以使用读写内存一样的汇编指令完成，简化了程序设计的难度和接口的复杂性。

# `/proc/iomem`

```
sudo more /proc/iomem

00000000-00000fff : Reserved
00001000-00099fff : System RAM
0009a000-0009ffff : Reserved
000a0000-000bffff : PCI Bus 0000:00
000c0000-000dffff : PCI Bus 0000:00
  000c0000-000c7fff : Video ROM
  000c8000-000cfbff : Adapter ROM
[...]
```
