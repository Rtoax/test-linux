IOMMU (Input/Output Memory Management Unit)
===========================================

- iommu: AMD
- vt-d: Intel

在计算机领域，IOMMU（Input/Output Memory Management Unit）是一个内存管理单元
（Memory Management Unit），它的作用是连接DMA-capable I/O总线（Direct Memory
Access-capable I/O Bus）和主存（main memory）。传统的内存管理单元会把CPU访问
的虚拟地址转化成实际的物理地址。而IOMMU则是把设备（device）访问的虚拟地址转化
成物理地址。为了防止设备错误地访问内存，有些IOMMU还提供了访问内存保护机制。
参考下图：

```
     +----------------------------------+
     |                                  |
     |         Main Memory              |
     |                                  |
     +-----^---------------------^------+
           |  Physical Address   |
           |                     |
           |                     |
     +-----+------+       +------+------+
+----+   IOMMU    +---+---+     MMU     +----+
     +------^-----+   |   +------^------+
            |         |          |
            |         |          |
     +------+-----+   |   +------+------+
     |   Device   |   |   |     CPU     |
     +------------+   |   +-------------+
     Device Address   |    Virtual Address
                      |
                      +
```


# Kernel cmdline

- `iommu.passthrough=1`
- `iommu=pt`


# 虚拟化

- GPA to HPA

IOMMU的一个重要用途是在虚拟化技术（virtualization）：虚拟机上运行的操作系统
（guest OS）通常不知道它所访问的host-physical内存地址。如果要进行DMA操作，就
有可能破坏内存，因为实际的硬件（hardware）不知道guest-physical和host-physical
内存地址之间的映射关系。IOMMU根据guest-physical和host-physical内存地址之间的
转换表（translation table），re-mapping硬件访问的地址，就可以解决这个问题。


# Links

- https://en.wikipedia.org/wiki/Input%E2%80%93output_memory_management_unit

