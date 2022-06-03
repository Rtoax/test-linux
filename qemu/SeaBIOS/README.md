SeaBIOS
=======

# BIOS - Basic IO System

1. 上电自检(Power On Self Test, POST) 指的是 BIOS 针对计算机硬件(如CPU、主板、存储器等)进行检测；
2. POST 之后初始化与启动相关硬件(磁盘、键盘控制器等)；
3. 为操作系统创建以一些参数，比如 ACPI 表；
4. 选择引导设备，从设备中加载 bootloader，进而启动操作系统；

# SeaBIOS

SeaBIOS 是开源的 16 位 x86 BIOS 的实现。SeaBIOS 能够运行在模拟器中或者在使用coreboot的情况下，
运行在 x86 硬件上，是 QEMU/KVM 虚拟化默认 BIOS。
