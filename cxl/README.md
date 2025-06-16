CXL - Compute Express Link (计算快速链接)
==========================================

* Compute Express Link (CXL) is an open standard interconnect for high-speed, high capacity central processing unit (CPU)-to-device and CPU-to-memory connections, designed for high performance data center computers.
* CXL is built on the serial PCI Express (PCIe) physical and electrical interface and includes PCIe-based block input/output protocol (**CXL.io**) and new cache-coherent protocols for accessing system memory (**CXL.cache**) and device memory (**CXL.mem**).
* The serial communication and pooling capabilities allows CXL memory to overcome performance and socket packaging limitations of common DIMM memory when implementing high storage capacities.

- CXL.io
- CXL.cache
- CXL.memory


# Linux Kernel

- /sys/bus/cxl/
- /dev/cxl/memX: ioctl(2)


# ACPI

> /sys/firmware/acpi/

- ACPI0017
- ACPI0016: CXL Host Bridge Object, CXL root complex


# EDSFF

- Ex #1: EDSFF E1.S (Smaller), 12 ~ 25W
- Ex #2: EDSFF E3.S / E3.L (Larger), 25W ~ 40W (1T), 40W ~ 70W (2T)
- Ex #3: Add-in Card (AIC) (Larger than E3.S/L), Similar range compared to E3.S/L


# Links

- https://computeexpresslink.org/cxl-specification/
- https://en.wikipedia.org/wiki/Compute_Express_Link
- https://www.lazystones.com/project/559625
- https://www.qemu.org/docs/master/system/devices/cxl.html
- https://github.com/computexpresslink/
- https://git.kernel.org/pub/scm/linux/kernel/git/cxl/cxl.git/
