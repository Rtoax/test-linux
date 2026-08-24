Xconn CXL 2.0 交换机
====================

XC50256
-------

XConn的CXL 2.0交换芯片（XC50256）是全球首款兼容CXL 2.0和PCIe 5.0的解决方案，具备以下优势：

- **性能卓越** 提供高达2,048 GB/s的带宽和低延迟，适用于高性能计算场景。
- **节能设计** 每端口功耗极低，并优化了PCB面积，从而降低系统成本（TCO）。
- **多功能性** 支持内存扩展、池化和共享，同时兼容CXL和PCIe的混合模式，为数据中心和企业计算提供灵活性。
- 上市时间客户样品现已推出，计划于2024年9月正式量产。

这款产品定位为高效的CXL解决方案，适合未来数据中心和内存计算场景的需求。

DCMFM (Data Center Fabric Manager) 数据中心Fabric管理器是CXL交换机和设备的核心管理组件，通过REST API和FM Agent实现与编排器和底层设备的通信，支持高效的资源管理和故障转移能力。
技术特点 包括支持Redfish管理协议、时间敏感的操作，以及对Fabric架构的参考实现，助力实现高性能、可扩展的内存管理解决方案。


CXL 2.0 交换机 热插拔特性
-------------------------

- CXL 2.0 的新特性支持 **热添加（hot-add）** 和 **受控热移除（managed hot-remove）** ，允许在不关闭系统的情况下动态添加或移除内存设备。
- **受控移除** 的关键点需要软件配合，通过清空缓存和下线相关页面确保安全移除。
- 限制 **不支持意外移除（surprise removal）** ，否则可能导致系统异常。
- 兼容性基于PCIe规范定义的热插拔模型，确保了跨设备的标准化操作。
- 应用场景该功能提高了数据中心的灵活性和可扩展性，特别是在动态内存池化和共享的使用中。


Links
-----

- `Xconn：CXL 2.0 交换机实现内存共享 <https://cloud.tencent.com/developer/article/2495652>`_
- `XConn XC50256 CXL 2.0 Switch Chip Shown <https://www.servethehome.com/xconn-xc50256-cxl-2-0-switch-chip-shown/>`_
- `XConn XC50256 CXL 2.0 Switch Chip Linked and Running at FMS 2023 <https://www.servethehome.com/xconn-xc50256-cxl-2-0-switch-chip-linked-and-running-at-fms-2023/>`_
