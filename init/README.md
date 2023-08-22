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
|     MBR       |<--------+-------------------+
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
