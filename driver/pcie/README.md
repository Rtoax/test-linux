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

| Code  | Description                            | Examples               |
| ----- | ---------------------------------------| ---------------------- |
| 0x00  | Unclassified Device                    |                        |
| 0x01  | Mass Storage Controller                | SATA, NVMe, SCSI, IDE  |
| 0x02  | Network Controller                     |                        |
| 0x03  | Display Controller                     | VGA, 3D, XGA           |
| 0x04  | Multimedia Controller                  |                        |
| 0x05  | Memory Controller                      | CXL                    |
| 0x06  | Bridge Device                          | PCI-PCI, ISA, CardBus, PCIe-PCI |
| 0x07  | Simple Communication Controller        |                        |
| 0x08  | Generic System Peripheral              |                        |
| 0x09  | Input Device Controller                |                        |
| 0x0a  | Docking Station                        |                        |
| 0x0b  | Processor                              |                        |
| 0x0c  | Serial Bus Controller                  | USB, Firewire, SPI, I2C |
| 0x0d  | Wireless Controller                    |                        |
| 0x0e  | Intelligent I/O controller             |                        |
| 0x0f  | Satellite communications controller    |                        |
| 0x10  | Encryption/Decryption Controller       |                        |
| 0x11  | Data Acquisition and Signal Processing |                        |
| 0x12  | Processing accelerators                |                        |
| 0x13  | Non-Essential Instrumentation          |                        |
| 0x14  |                                        |                        |
| 0x15  |                                        |                        |
| 0x16  |                                        |                        |
| 0x40  | Coprocessor                            |                        |
| 0x64  |                                        |                        |
| 0xff  | Unassigned class                       |                        |


## 根据 Class 过滤

```bash
$ lspci -d ::0200
00:1f.6 Ethernet controller: Intel Corporation Ethernet Connection (10) I219-V

$ lspci -d ::0280
00:14.3 Network controller: Intel Corporation Comet Lake PCH-LP CNVi WiFi
```


# BAR: Base Address Register

## /sys/bus/pci/devices/0000:0d:00.0/resource

- Format: `start_address   end_address   flags`

```bash
sudo dd if=/dev/mem bs=1 count=4 skip=<start_address> 2>/dev/null | hexdump -C
```

```c
void __iomem *bar_addr;
bar_addr = ioremap(BAR_PHYS_ADDR, BAR_SIZE);
u32 value = readl(bar_addr + 0);
```

## /sys/bus/pci/devices/0000:0d:00.0/resourceN

```c
int fd = open("/sys/bus/pci/devices/0000:0d:00.0/resource2", O_RDWR | O_SYNC);
void *map_base = mmap(0, map_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
```


# Linux kernel cmdline

- `pcie_aspm=off`: 禁用 PCIe 设备进入节能状态


# Links

- https://pcisig.com/specifications/pciexpress
- https://admin.pci-ids.ucw.cz/read/PC
- https://admin.pci-ids.ucw.cz/read/PD
- https://pcisig.com/membership/member-companies

## Git Links

- https://github.com/pciutils/pciutils
- git://git.kernel.org/pub/scm/utils/pciutils/pciutils.git
