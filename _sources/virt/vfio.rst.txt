===========================
VFIO - Virtual Function I/O
===========================

**VFIO (Virtual Function I/O)** is a Linux kernel subsystem that provides a framework for exposing direct device access to userspace applications and virtual machines, enabling them to interact with hardware devices at a low level. VFIO is particularly useful in virtualized environments, allowing virtual machines to use physical devices, such as **graphics cards** and **network interfaces**, with near-native performance.

The main purpose of VFIO is to provide userspace processes and virtual machines with safe and efficient access to hardware devices while maintaining isolation between them. This is achieved through features such as **IOMMU (Input/Output Memory Management Unit)** and device allocation, which provide fine-grained control over the resources allocated to each virtual machine or process.

VFIO is often used in conjunction with QEMU and KVM to implement hardware-accelerated virtualization on Linux systems. By using VFIO, virtual machines can take advantage of hardware capabilities and achieve performance levels similar to native applications running directly on the host system.

Virtual Function I/O (VFIO) 是一种现代化的设备直通方案，它充分利用了VT-d/AMD-Vi技术提供的DMA Remapping和Interrupt Remapping特性， 在保证直通设备的DMA安全性同时可以达到接近物理设备的I/O的性能。 用户态进程可以直接使用VFIO驱动直接访问硬件，并且由于整个过程是在IOMMU的保护下进行因此十分安全， 而且非特权用户也是可以直接使用。 换句话说，VFIO是一套完整的用户态驱动(userspace driver)方案，因为它可以安全地把设备I/O、中断、DMA等能力呈现给用户空间。

为了达到最高的IO性能，虚拟机就需要VFIO这种设备直通方式，因为它具有低延时、高带宽的特点，并且guest也能够直接使用设备的原生驱动。 这些优异的特点得益于VFIO对VT-d/AMD-Vi所提供的DMA Remapping和Interrupt Remapping机制的应用。 VFIO使用DMA Remapping为每个Domain建立独立的IOMMU Page Table将直通设备的DMA访问限制在Domain的地址空间之内保证了用户态DMA的安全性， 使用Interrupt Remapping来完成中断重映射和Interrupt Posting来达到中断隔离和中断直接投递的目的。

整个VFIO框架设计十分简洁清晰，可以用下面的一幅图描述：

.. code-block:: text

    +-------------------------------------------+
    |                                           |
    |             VFIO Interface                |
    |                                           |
    +---------------------+---------------------+
    |                     |                     |
    |     vfio_iommu      |      vfio_pci       |
    |                     |                     |
    +---------------------+---------------------+
    |                     |                     |
    |    iommu driver     |    pci_bus driver   |
    |                     |                     |
    +---------------------+---------------------+


ioctl
-----

- `VFIO_SET_IOMMU`
- `VFIO_DEVICE_SET_IRQS`
- `VFIO_DEVICE_GET_REGION_INFO`


Links
-----

- https://docs.kernel.org/driver-api/vfio.html
- https://kernelgo.org/vfio-introduction.html
