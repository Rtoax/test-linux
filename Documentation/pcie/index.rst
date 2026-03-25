======================================================
PCI - Peripheral Component Interconnect (外围组件互联)
======================================================

The main ways for OS interact with PCI devices are PIO and MMIO:

* PIO: `/proc/ioports`
* MMIO: `/proc/iomem`


PCI Bus
-------

`0006:02:00.1` = `域号(Domain)`:`总线号(Bus Number)`:`设备号(Device Number)`. `功能号(Function Number)`

- 对于大多数系统，只有一个域，因此通常是`0000`。
- 在包含多个 PCIe 根总线的大型系统（例如多处理器服务器）中，域号用于区分不同的PCIe根总线。


Contents
--------

.. toctree::
   :maxdepth: 1

   abbrev
   mmio
   pio
   device-class
   configuration-space
   bar
   aer
   kernel-cmdline


Links
-----

- `Specifications <https://pcisig.com/specifications/pciexpress>`_
- `Become a Member <https://pcisig.com/membership/become-member>`_
- `Member Companies <https://pcisig.com/membership/member-companies>`_
- `PCI Device Vendors <https://admin.pci-ids.ucw.cz/read/PC>`_
- `All PCI Vendors <https://devicehunt.com/all-pci-vendors>`_
- `The PCI ID Repository <https://pci-ids.ucw.cz/>`_
- `PCI Device Vendors <https://admin.pci-ids.ucw.cz/read/PC>`_
- `PCI Device Classes <https://admin.pci-ids.ucw.cz/read/PD>`_


Git Links
~~~~~~~~~

- `GitHub pciutils <https://github.com/pciutils/pciutils>`_
- `GitHub hwdata <https://github.com/vcrhonek/hwdata>`_
- git://git.kernel.org/pub/scm/utils/pciutils/pciutils.git
