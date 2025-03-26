UEFI (Unified Extensible Firmware Interface)
============================================


# 介绍

UEFI (可扩展固件接口) ，也称为 UEFI BIOS，是两种不同类型的主板固件中最常见的一种(另一种为 BIOS)。


# Services

- Boot Services
- Runtime Services


# UEFI Precedures

- SEC: Security
	- 重启事件
	- 临时内存
	- 安全的根
	- 信息交换
- PEI: Pre-EFI Initialization
	- 永久内存
	- HOB 内存
	- HOB 固件
	- 信息交换
- DXE: Driver Execution Envrionment
	- DXE 基础
	- DXE 分发
	- DXE 驱动
- BDS: Boot Device Selection
	- 启动设备
- TSL: Transient System Load
	- OS 预加载
	- (OS Loader)
- RT: Runtime
	- 运行时
- AL: After Life
	- 关机
	- 休眠
	- 睡眠
	- 重启


# efivars `/sys/firmware/efi/vars/`

通过sysfs接口来实现对 EFI variables的管理。


# efivarfs `/sys/firmware/efi/efivars/`

从 linux 3.8 开始，内核中添加的一个新的文件系统。efivarfs 文件系统是为了解决在
sysfs 中使用entries来维护EFI variables的缺点。旧的 sysfs EFI variables 只技持
1024 bytes, 这是EFI 0.99标准之前的限制。在新的标准中已经被删除。


# Links

- https://uefi.org/specifications
- https://en.wikipedia.org/wiki/UEFI

