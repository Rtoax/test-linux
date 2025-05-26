Storage
=========

# Flash

Flash Memory 是一种非易失性的存储器。在嵌入式系统中通常用于存放系统、应用和数据
等。在 PC 系统中，则主要用在固态硬盘以及主板 BIOS 中。另外，绝大部分的 U 盘、
SDCard 等移动存储设备也都是使用 Flash Memory 作为存储介质。

根据硬件存储原理的不同，Flash Memory 主要可以分为：

- NOR Flash
- NAND Flash


## 常见的 Flash

- eMMC
- SD Card
- UFS
- NAND Flash
- NOR Flash
- NVMe


# 主流的软件分区技术

- `MBR`: Master Boot Record
	- 支持最大`2TB`硬盘
	- 正在被`GPT`取代
- `GPT`: GUID Partition Table
	- 支持最大`128PB`(1PB=1024TB)


# Links

- https://www.thomas-krenn.com/en/wiki/Linux_I/O_Stack_Diagram
