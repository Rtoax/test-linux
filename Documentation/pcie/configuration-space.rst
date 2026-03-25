========================
PCIe Configuration Space
========================

At least 256 bytes, the first 64 bytes are standardized and the same for all
devices.


Type 0 Header (Normal)
----------------------

.. code-block:: text

        0x00     0x01       0x02     0x03       0x04     0x05       0x06      0x07  B
    +---------+---------+---------+---------+---------+---------+---------+---------+
    |     Vendor ID     |    Device ID      |  Command Reg      |    Status         |
    +---------+---------+---------+---------+---------+---------+---------+---------+
    | Revison |          Class Code         |  Cache  | Latency |  Header |   BIST  |
    |    ID   |         |         |         |   Line  |  Timer  |   Type  |         |
    +---------+---------+---------+---------+---------+---------+---------+---------+
    |             Base Address0             |             Base Address1             |
    +---------------------------------------+---------------------------------------+
    |             Base Address2             |             Base Address3             |
    +---------------------------------------+---------------------------------------+
    |             Base Address4             |             Base Address5             |
    +---------------------------------------+-------------------+-------------------+
    |           CardBus CIS Pointer         |Subsystem Vendor ID|Subsystem Device ID|
    +---------------------------------------+---------+---------+-------------------+
    |      Expansion ROM Base Address       | Cap Ptr |          Reserved           |
    +---------------------------------------+---------+---------+---------+---------+
    |                Reserved               | IRQ Line| IRQ Pin | Min_Gnt | Max_Lat |
    +---------------------------------------+---------+---------+---------+---------+


Type 1 Header (Bridge)
----------------------

.. code-block:: text

        0x00     0x01       0x02     0x03       0x04     0x05       0x06      0x07  B
    +---------+---------+---------+---------+---------+---------+---------+---------+
    |     Vendor ID     |    Device ID      |  Command Reg      |    Status         |
    +---------+---------+---------+---------+---------+---------+---------+---------+
    | Revison |          Class Code         |  Cache  | Latency |  Header |   BIST  |
    |    ID   |         |         |         |   Line  |  Timer  |   Type  |         |
    +---------+---------+---------+---------+---------+---------+---------+---------+
    |             Base Address0             |             Base Address1             |
    +---------+---------+---------+---------+---------+---------+-------------------+
    | Primary | Second  |   High  | Second  | IO Base |IO Limit | Secondary Status  |
    | Bus     | Bus     |   Bus   | LatTimer|         |         |                   |
    +---------+---------+---------+---------+---------+---------+-------------------+
    |    Memory Base    |   Memory Limit    | Pref Memory Base  | Pref Memory Limit |
    +-------------------+-------------------+-------------------+-------------------+
    |Upper half of prefetchable memory range| Limit                                 |
    +-------------------+-------------------+---------+-----------------------------+
    |    IO Base Upper  |   IO Limit Upper  | Cap Ptr |          Reserved           |
    +-------------------+-------------------+---------+---------+-------------------+
    |                ROM Address            | IRQ Line| IRQ Pin | Bridge Control    |
    +---------------------------------------+-------------------+-------------------+


Type 2 Header (CardBus)
-----------------------


BAR: Base Address Register
--------------------------

/sys/bus/pci/devices/0000:0d:00.0/resource
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Format: `start_address   end_address   flags`

.. code-block:: shell

    sudo dd if=/dev/mem bs=1 count=4 skip=<start_address> 2>/dev/null | hexdump -C


.. code-block:: c

    void __iomem *bar_addr;
    bar_addr = ioremap(BAR_PHYS_ADDR, BAR_SIZE);
    u32 value = readl(bar_addr + 0);


/sys/bus/pci/devices/0000:0d:00.0/resourceN
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c

    int fd = open("/sys/bus/pci/devices/0000:0d:00.0/resource2", O_RDWR | O_SYNC);
    void *map_base = mmap(0, map_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
