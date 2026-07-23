============
CXL Overview
============

* **Compute Express Link (CXL)** is an open standard interconnect for
  high-speed, high capacity central processing unit (CPU)-to-device and
  CPU-to-memory connections, designed for high performance data center
  computers.
* CXL is built on the serial PCI Express (PCIe) physical and electrical
  interface and includes PCIe-based block input/output protocol (**CXL.io**)
  and new cache-coherent protocols for accessing system memory (**CXL.cache**)
  and device memory (**CXL.mem**).
* The serial communication and pooling capabilities allows CXL memory to
  overcome performance and socket packaging limitations of common DIMM memory
  when implementing high storage capacities.

- 保持了完全的向后兼容性。
- PCIe 物理层上动态多路复用。
    - **事务层** 负责处理与每个协议相关的事务以及任何架构排序语义、流量控制和信用。 **具有较低的延迟**
    - **数据链路层（或链路层）** 负责可靠的数据传输服务，并在设备之间建立逻辑连接。 **具有较低的延迟**
    - **物理层** 负责物理信息交换、接口初始化和维护。
        - `物理层进行多路复用` 有助于为 CXL.cache 和 CXL.mem 流量提供低延迟路径。
        - 物理层可区分 CXL.io、CXL.cache-mem、ALMP（Arb/Mux 链路管理包） 和 NULL Flits（不发送任何内容）。
    - 每一层都有一组 `寄存器` ，软件可访问这些寄存器来配置、控制和获取链路状态。


CXL 三种协议实现
----------------

- CXL.io
- CXL.cache
- CXL.memory

CXL.io
~~~~~~

- CXL.io 对所有设备都是强制性的；
- CXL.io 协议基于 PCIe；
- 用于设备发现、状态报告、虚拟到物理地址转换、I/O 虚拟化和直接内存访问（DMA）。

CXL.cache
~~~~~~~~~

- CXL.cache 是可选的。
- CXL.cache 用于设备缓存系统内存。

CXL.memory（又名 CXL.mem）
~~~~~~~~~~~~~~~~~~~~~~~~~~

- CXL.mem 是可选的。
- CXL.mem 使 CPU 和其他 CXL 设备能将设备内存作为可缓存内存访问。
- CXL.mem 使连接到设备的内存成为可缓存内存（称为主机管理设备内存 (HDM)），类似于主机内存，从而实现主机在 HDM 和主机内存之间的统一视图


CXL Type 1/2/3
--------------

.. list-table::
   :header-rows: 1

   * - Item
     - CXL Type 1
     - CXL Type 2
     - CXL Type 3
   * - 支持协议
     - CXL.io + CXL.cache
     - CXL.io + CXL.cache + CXL.mem
     - CXL.io + CXL.mem
   * - 设备是否有本地内存
     - ❌
     - ✅
     - ✅
   * - 是否缓存主机内存
     - ✅
     - ✅
     - ❌
   * - 典型应用
     - SmartNIC, FPGA 加速卡
     - GPU、AI 加速卡、FPGA 异构计算
     - 内存扩展，内存池化，分层内存
   * - 商业产品
     - Intel Agilex FPGA, ...
     - Intel Agilex FPGA, ...
     - Samsung CXL Memory Module (CMM-D), ...
   * - 成熟度
     - 已有原型/少量产品
     - 极少产品，未来方向
     - 大量量产，生态最成熟


CXL 协议版本
------------

CXL 3.0 相比 CXL 2.0 新增特性支持
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. 多级 CXL Switch；
2. 引入了名为 "动态容量设备 "的扩展，灵活性更高；


CXL 2.0 相比 CXL 1.0 新增特性支持
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. 热插拔；
2. 安全增强；
3. pmem；
4. 内存错误上报；
5. 遥测；
6. 支持single-level交换，跨多个虚拟层次结构池设备的能力，包括对内存设备的多域支持；
7. 引入 CXL Switch；
8. **内存池** ，设备池；

CXL 1.1
~~~~~~~

- 为直接连接到主机的设备引入了一致性和内存语义;


Linux Kernel
------------

- /sys/bus/cxl/
- /dev/cxl/memX: ioctl(2)


EDSFF
-----

- Ex #1: EDSFF E1.S (Smaller), 12 ~ 25W
- Ex #2: EDSFF E3.S / E3.L (Larger), 25W ~ 40W (1T), 40W ~ 70W (2T)
- Ex #3: Add-in Card (AIC) (Larger than E3.S/L), Similar range compared to E3.S/L


Links
-----

Specification
~~~~~~~~~~~~~

- https://computeexpresslink.org/cxl-specification/

Kernel
~~~~~~

- https://lore.kernel.org/linux-cxl/
- https://git.kernel.org/pub/scm/linux/kernel/git/cxl/cxl.git

GitHub
~~~~~~

- https://github.com/computexpresslink/
- https://github.com/pmem/ndctl

Qemu
~~~~

- https://www.qemu.org/docs/master/system/devices/cxl.html

Others
~~~~~~

- https://en.wikipedia.org/wiki/Compute_Express_Link
- https://www.lazystones.com/project/559625
- For CI testing of CXL emulation work and other things I might want to do in the future. https://gitlab.com/jic23/qemu
- CXL，最强科普！ https://fpga.eetrend.com/content/2024/100583618.html
