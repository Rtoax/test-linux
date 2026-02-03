RDMA - Remote Direct Memory Access
=================================

意思是远程直接数据存取，就是为了解决网络传输中服务器端数据处理的延迟而产生的。RDMA 通过网络把资料直接传入计算机的存储区，将数据从一个系统快速移动到远程系统存储器中，而不对操作系统造成任何影响，这样就不需要用到多少计算机的处理功能。它消除了外部存储器复制和上下文切换的开销，因而能解放内存带宽和CPU周期用于改进应用系统性能。


# RDMA 三种不同的硬件实现

1. `InfiniBand(IB)`: 从一开始就支持RDMA的新一代网络协议。依赖支持该技术的网卡和交换机。
2. RDMA过融合以太网(`RoCE`): 即`RDMA over Ethernet`, 允许通过以太网执行RDMA的网络协议。这允许在标准以太网基础架构(交换机)上使用RDMA，只不过网卡必须是支持RoCE的特殊的NIC。
3. 互联网广域RDMA协议(`iWARP`): 即`RDMA over TCP`, 允许通过TCP执行RDMA的网络协议。这允许在标准以太网基础架构(交换机)上使用RDMA，只不过网卡要求是支持iWARP(如果使用CPU offload的话)的NIC。否则，所有iWARP栈都可以在软件中实现，但是失去了大部分的RDMA性能优势。


# Links

- [https://github.com/linux-rdma](https://github.com/linux-rdma)
