MSI/MSI-X - (Extended) Message Signaled Interrypts
===================================================

- `MSI(Message Signaled Interrupts)`是一种通过在内存中写入信息来产生中断的方式，其中内存地址由设备驱动程序和硬件设备协商确定。MSI与传统的中断线不同，它不需要单独的中断线，而是通过PCI总线进行通信。
- `MSI-X(Extended Message Signaled Interrupts)`是在MSI的基础上扩展的一种中断方式，它允许设备使用多个独立的中断信号，从而提高了中断处理的效率。这对于那些需要高速响应的应用程序尤其有用，例如虚拟化或者高性能计算。

