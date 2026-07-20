CXL Software
============

ACPI
----

通过 :doc:`ACPI <acpi>` 发现并描述 CXL 设备，把硬件信息传递给操作系统。


Linux Kernel
------------

核心模块
~~~~~~~~

1. cxl_core: 提供 CXL 设备模型、总线和通用的枚举、注册功能。定义了 cxl_dev_state、cxl_port、cxl_decoder 等基础对象。
2. cxl_acpi: 解析 ACPI CEDT 表，发现 Host Bridge (CXL.mem 控制器) 和根端口，创建 cxl_port 拓扑。
3. cxl_pci: CXL 设备的 PCIe 驱动。负责：
    - 通过 PCIe DVSEC 探测 CXL 能力。
    - 映射 CXL 设备内存 BAR，建立 cxl_memdev。
    - 处理 CXL.io（本质就是 PCIe 传输）和错误上报。
4. cxl_mem: 面向 CXL.mem 协议的设备驱动。它把 CXL Type 3 内存设备抽象为 内存设备（memdev），并通过 CXL Mailbox 与设备固件通信（获取健康信息、配置标签、请求内存分区等）。
5. cxl_pmem: 当 CXL 内存被配置为持久内存（pmem）时，此驱动将 memdev 注册为 nd_pmem 命名空间，使其符合 libnvdimm 框架。这样就可以像管理 Optane PMem 那样管理 CXL 持久内存。
6. cxl_region（区域管理）: 最核心的用户态配置接口。通过 /sys/bus/cxl/ 下的 decoder 和 region 子目录：
    - 创建 CXL 区域（Region），可组合多个 memdev 实现交织。
    - 决定将区域映射为 pmem 或 volatile ram 模式。
    - 支持在线/离线、热插拔。
7. dax_kmem 与内存热添加
    - 如果 CXL 内存是易失性的，通常先将其配置为设备 DAX（/dev/daxX.Y），再由 dax_kmem 驱动将这段 DAX 内存在线为系统内存（System RAM）。内核通过内存热添加机制，创建新的 NUMA 节点或挂到现有节点上。
    - 这样，CXL 内存就变成了 Movable 或普通内存，可被 buddy allocator 分配。


缓存一致性协议（CXL.cache）支持
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. 主要面向 Type 1/2 加速器。这类设备驱动需要请求 CPU 缓存的回写/无效化等操作。
2. 内核通过 CXL 加速器框架（早期使用 cxl_accel 或结合新式 UAPI）为设备提供页对齐、主机物理地址转换、缓存一致性访问控制。
3. 通常加速器厂商（如 GPU、FPGA）会提供自己的内核驱动，他们直接调用 CXL 核心 API 来映射一致性内存窗口。


内存分层（Memory Tiering）
~~~~~~~~~~~~~~~~~~~~~~~~~~

CXL 内存带来的核心价值之一是内存分层：DRAM + CXL 内存构成不同性能层。

1. 内核将 CXL 内存节点视为 **低级（lower tier）** ，DRAM 视为 **高级（higher tier）** 。
2. 通过 NUMA Balancing 和 回收/降级（demotion） 机制，内核可以将冷页从 DRAM 迁移到 CXL 内存，热页从 CXL 内存提升回 DRAM。
3. 相关配置：/sys/devices/system/node/nodeX/access0/initiators，numa_balancing 等。
4. 用户空间工具（如 numactl、page-types）可进一步精细控制。


RAS 与错误处理
~~~~~~~~~~~~~~

1. CXL 2.0+ 支持链路级 CRC、毒化（poison）传播、先进错误报告。
2. cxl_mem 通过 Mailbox 获取设备健康状态、温度、介质错误日志。
3. 内核利用 MCE（Machine Check Exception） 和 CXL 错误中断，配合 ACPI 的 CPER 记录进行隔离和恢复。


User space
----------
