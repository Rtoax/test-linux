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
    |    ID   | ProgIF  | SubClass|BaseClass|   Line  |  Timer  |   Type  |         |
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


Header Type: 7bit: **Multi-Function Device**, 0-6bits: Type;


Type 1 Header (Bridge)
----------------------

.. code-block:: text

        0x00     0x01       0x02     0x03       0x04     0x05       0x06      0x07  B
    +---------+---------+---------+---------+---------+---------+---------+---------+
    |     Vendor ID     |    Device ID      |  Command Reg      |    Status         |
    +---------+---------+---------+---------+---------+---------+---------+---------+
    | Revison |          Class Code         |  Cache  | Latency |  Header |   BIST  |
    |    ID   | ProgIF  | SubClass|BaseClass|   Line  |  Timer  |   Type  |         |
    +---------+---------+---------+---------+---------+---------+---------+---------+
    |             Base Address0             |             Base Address1             |
    +---------+---------+---------+---------+---------+---------+-------------------+
    | Primary | Second  |   Sub   | Second  | IO Base |IO Limit | Secondary Status  |
    | Bus     | Bus     |   Bus   | LatTimer|         |         |                   |
    +---------+---------+---------+---------+---------+---------+-------------------+
    |    Memory Base    |   Memory Limit    | Pref Memory Base  | Pref Memory Limit |
    +-------------------+-------------------+-------------------+-------------------+
    |      Prefetchable Base Upper          |       Prefetchable Limit Upper        |
    +-------------------+-------------------+---------+-----------------------------+
    |    IO Base Upper  |   IO Limit Upper  | Cap Ptr |          Reserved           |
    +-------------------+-------------------+---------+---------+-------------------+
    |      Expansion ROM Base Address       | IRQ Line| IRQ Pin | Bridge Control    |
    +---------------------------------------+-------------------+-------------------+


Type 2 Header (CardBus)
-----------------------

.. code-block:: text

        0x00     0x01       0x02     0x03       0x04     0x05       0x06      0x07  B
    +---------+---------+---------+---------+---------+---------+---------+---------+
    |     Vendor ID     |    Device ID      |  Command Reg      |    Status         |
    +---------+---------+---------+---------+---------+---------+---------+---------+
    | Revison |          Class Code         |  Cache  | Latency |  Header |   BIST  |
    |    ID   | ProgIF  | SubClass|BaseClass|   Line  |  Timer  |   Type  |         |
    +---------+---------+---------+---------+---------+---------+---------+---------+
    | TODO ...
