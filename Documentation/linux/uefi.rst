UEFI (Unified Extensible Firmware Interface)
============================================

UEFI (可扩展固件接口) ，也称为 UEFI BIOS，是两种不同类型的主板固件中最常见的一种(另一种为 BIOS)。

Services
--------

- Boot Services
- Runtime Services


UEFI Precedures
---------------

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


UEFI Image Types
----------------

.. list-table::
   :widths: 15 15 15
   :header-rows: 1

   * - Architecture
     - File Name Convention
     - PE Executable Machine Type
   * - 32-bit
     - BOOTIA32.EFI
     - 0x14c
   * - x64
     - BOOTx64.EFI
     - 0x8664
   * - AArch32
     - BOOTARM.EFI
     - 0x01c2
   * - AArch64
     - BOOTAA64.EFI
     - 0xAA64
   * - RISC-V 32-bit
     - BOOTRISCV32.EFI
     - 0x5032
   * - RISC-V 64-bit
     - BOOTRISCV64.EFI
     - 0x5064
   * - RISC-V 128-bit
     - BOOTRISCV128.EFI
     - 0x5128
   * - LoongArch32
     - BOOTLOONGARCH32.EFI
     - 0x6232
   * - LoongArch64
     - BOOTLOONGARCH64.EFI
     - 0x6264


efivars `/sys/firmware/efi/vars/`
----------------------------------

通过sysfs接口来实现对 EFI variables的管理。


efivarfs `/sys/firmware/efi/efivars/`
-------------------------------------

从 linux 3.8 开始，内核中添加的一个新的文件系统。efivarfs 文件系统是为了解决在 sysfs 中使用entries来维护EFI variables的缺点。旧的 sysfs EFI variables 只技持 1024 bytes, 这是EFI 0.99标准之前的限制。在新的标准中已经被删除。


shim (垫片)
-----------

Boot Flow
~~~~~~~~~

- Normal BootFlow:
- Fallback BootFlow:
- MOK Manager:

.. code-block:: text

      +---------------------------------------------+
      |                                             |   fallback
      |          +---------------------+       +----+--------------+
      |  +------>|EFI/BOOT/BOOTX64.EFI |------>|EFI/BOOT/fbx64.efi |
      |  |       |EFI/BOOT/BOOTAA64.EFI| +-----|EFI/BOOT/fbaa64.efi|
      |  |       +---------------------+ |     +-------------------+
      |  |                shim           |      scan all EFI/*/BOOT*.CSV
      |  |                               |      create and store Boot0001~n BootEntry
      |  |                               |      create adn store first found BootEntry
      |  |                               |
      |  |                               |
      v  |                shim           v               grub2
    +----+-+     +-------------------------+    +-------------------------+   +-------+
    | UEFI |---->|EFI/<vendor>/shimx64.efi |--->|EFI/<vendor>/grubx64.efi |-->|vmlinuz|
    +------+     |EFI/<vendor>/shimaa64.efi|    |EFI/<vendor>/grubaa64.efi|   |       |
                 +-------+-----------------+    +-------------------------+   +-------+
                         |       ^
                         |       |
                         v       |
                  +--------------+--------+
                  |EFI/<vendor>/mmx64.efi |
                  |EFI/<vendor>/mmaa64.efi|
                  +-----------------------+
                          MOK Manager

`fedora x64` example

.. code-block:: text

    EFI
    ├── BOOT
    │   ├── BOOTX64.EFI
    │   └── fbx64.efi
    └── fedora
        ├── BOOTX64.CSV
        ├── grub.cfg
        ├── grubx64.efi
        ├── mmx64.efi
        └── shimx64.efi

.. code-block:: text

     ISO: UEFI → /EFI/BOOT/BOOT*.efi → /EFI/BOOT/grub*.efi
        Example:
        EFI/BOOT/
        ├── BOOTAA64.EFI
        ├── grubaa64.efi
        ├── grub.cfg
        └── TRANS.TBL


Links
-----

- https://uefi.org/specifications
- https://en.wikipedia.org/wiki/UEFI
- 'Unified Extensible Firmware Interface (UEFI) Specification Release 2.10'
- https://github.com/rhboot/shim.git
