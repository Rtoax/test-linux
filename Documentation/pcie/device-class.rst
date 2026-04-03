=================
PCIe Device Class
=================

- `PCI Device Classes <https://admin.pci-ids.ucw.cz/read/PD>`_

.. list-table::
   :widths: 10 25 15 15
   :header-rows: 1

   * - Code
     - Description
     - Examples
     - Command
   * - 0x00
     - Unclassified Device
     -
     -
   * - 0x01
     - Mass Storage Controller
     - SATA, NVMe, SCSI, IDE
     -
   * - 0x02
     - Network Controller
     -
     - lspci -d ::0200
   * - 0x03
     - Display Controller
     - VGA, 3D, XGA
     -
   * - 0x04
     - Multimedia Controller
     -
     -
   * - 0x05
     - Memory Controller
     - RAM(00), FLASH(01), CXL(02)
     - CXL: lspci -d ::0502
   * - 0x06
     - Bridge Device
     - PCI-PCI, ISA, CardBus, PCIe-PCI
     -
   * - 0x07
     - Simple Communication Controller
     -
     -
   * - 0x08
     - Generic System Peripheral
     -
     -
   * - 0x09
     - Input Device Controller
     -
     -
   * - 0x0a
     - Docking Station
     -
     -
   * - 0x0b
     - Processor
     -
     -
   * - 0x0c
     - Serial Bus Controller
     - USB, Firewire, SPI, I2C
     -
   * - 0x0d
     - Wireless Controller
     -
     -
   * - 0x0e
     - Intelligent I/O controller
     -
     -
   * - 0x0f
     - Satellite communications controller
     -
     -
   * - 0x10
     - Encryption/Decryption Controller
     -
     -
   * - 0x11
     - Data Acquisition and Signal Processing
     -
     -
   * - 0x12
     - Processing accelerators
     -
     -
   * - 0x13
     - Non-Essential Instrumentation
     -
     -
   * - 0x14
     -
     -
     -
   * - 0x15
     -
     -
     -
   * - 0x16
     -
     -
     -
   * - 0x40
     - Coprocessor
     -
     -
   * - 0x64
     -
     -
     -
   * - 0xff
     - Unassigned class
     -
     -
