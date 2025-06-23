PCI - Peripheral Component Interconnect (外围组件互联)
======================================================

The main ways for OS interact with PCI devices are PIO and MMIO:

* PIO: `/proc/ioports`
* MMIO: `/proc/iomem`


# PCI Bus

`0006:02:00.1` = `域号(Domain)`:`总线号(Bus Number)`:`设备号(Device Number)`.`功能号(Function Number)`

- 对于大多数系统，只有一个域，因此通常是`0000`。
- 在包含多个 PCIe 根总线的大型系统（例如多处理器服务器）中，域号用于区分不同的PCIe根总线。


# PCI Configration Space

At least 256 bytes, the first 64 bytes are standardized and the same for all devices.

* BAR - Base Address Register

## Type 0 Header

```
   0x0   0x1    0x2   0x3   0x4  0x5   0x6   0x7    0x8     0x9   0xa   0xb   0xc     0xd     0xe     0xf
 +-----------+------------+----------+------------+-------+-----------------+------+-------+-------+------+
 |   Vendor  |    Device  |  Command |    Status  |Revison|    Class Code   |Cache |Latency| Header|  BIST|
 |     ID    |      ID    |   Reg    |     Reg    |  ID   |                 | Line | Timer |  Type |      |
 +-----------+------------+----------+------------+-------+-----------------+------+-------+-------+------+

 +------------------------+-----------------------+-------------------------+-----------------------------+
 |     Base Address0      |    Base Address1      |        Base Address2    |       Base Address3         |
 +------------------------+-----------------------+-------------------------+-----------------------------+

 +------------------------+-----------------------+-------------------------+--------------+--------------+
 |     Base Address4      |    Base Address5      |     CardBus CIS Pointer |   Subsystem  |   Subsystemd |
 |                        |                       |                         |   Vendor ID  |   Device ID  |
 +------------------------+-----------------------+-------------------------+--------------+--------------+

 +------------------------+----+--------------------------------------------+------+-------+-------+------+
 |      Expansion ROM     |Cap |               Reserved                     |IRQ   |  IRQ  | Min_  | Max_ |
 |       Base Addres      |Ptr |                                            |Line  |  Pin  | Gnt   | Lat  |
 +------------------------+----+--------------------------------------------+------+-------+-------+------+
```

## Type 1 Header

```
   0x0   0x1    0x2   0x3   0x4  0x5   0x6   0x7    0x8     0x9   0xa   0xb   0xc     0xd     0xe     0xf
 +-----------+------------+----------+------------+-------+-----------------+------+-------+-------+------+
 |   Vendor  |    Device  |  Command |    Status  |Revison|    Class Code   |Cache |Latency| Header|  BIST|
 |     ID    |      ID    |   Reg    |     Reg    |  ID   |                 | Line | Timer |  Type |      |
 +-----------+------------+----------+------------+-------+-----------------+------+-------+-------+------+

 ...
```

# Vendors

- https://pcisig.com/membership/member-companies


# Device classes

```
00	Unclassified device
01	Mass storage controller
02	Network controller
03	Display controller
04	Multimedia controller
05	Memory controller
06	Bridge
07	Communication controller
08	Generic system peripheral
09	Input device controller
0a	Docking station
0b	Processor
0c	Serial bus controller
0d	Wireless controller
0e	Intelligent controller
0f	Satellite communications controller
10	Encryption controller
11	Signal processing controller
12	Processing accelerators
13	Non-Essential Instrumentation
14
15
16
40	Coprocessor
64
ff	Unassigned class
```

## 根据 Class 过滤

```bash
$ lspci -d ::0200
00:1f.6 Ethernet controller: Intel Corporation Ethernet Connection (10) I219-V

$ lspci -d ::0280
00:14.3 Network controller: Intel Corporation Comet Lake PCH-LP CNVi WiFi
```


# Linux kernel cmdline

- `pcie_aspm=off`: 禁用 PCIe 设备进入节能状态


# Links

- https://admin.pci-ids.ucw.cz/read/PC
- https://admin.pci-ids.ucw.cz/read/PD
- https://pcisig.com/membership/member-companies
