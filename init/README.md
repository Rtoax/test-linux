BOOT
====

- BIOS/UEFI
	- Hardware Check
	- Hardware Informations
	- Hardware Configure
	- Security Configure
	- Boot Device Order Table
	- Hard Driver (disk)
- MBR (Master Boot Record) - 512 Bytes
	- 结束标识 2 Bytes
	- Partition Table 64 Bytes
	- Bootloader (GRUB) 446 Bytes
	- MBR的工作原理限制了BIOS最大只能支持2TB硬盘
- GPT (GUID Partition Table)
	- 支持最大128PB(1PB=1024TB)


# Boot Procedure

```
+---------------+
|    Kernel     |
+---------------+
        ^
        |
        +-----------------+-----------------+
        |                 |                 |
+---------------+ +---------------+ +---------------+
|     GRUB      | |    syslinux   | |      LILO     |
+---------------+ +---------------+ +---------------+
        ^                 ^                 ^
        |                 |                 |
        +-----------------+-----------------+
        |
+---------------+
|  Boot Loader  |
+---------------+
        ^
        |
+---------------+
|    MBR/GPT    |<--------+-------------------+
+---------------+         |                   |
        ^                 |                   |
        |                 |                   |
+---------------+    +----+----------+   +----+----------+
|      BIOS     |--->|      CMOS     |-->|      UEFI     |
+---------------+    +---------------+   +---------------+
        ^
        |
+---------------+
| ON/OFF Button |
+---------------+
```


# init

- `rdinit=`: for example: rdinit=/bin/bash
- `init=`: for example: init=/bin/bash

