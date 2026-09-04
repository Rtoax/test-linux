===
GDB
===

/proc/sys/kernel/core_pattern
-----------------------------

systemd-coredump
~~~~~~~~~~~~~~~~

Examples:

.. code-block:: text
   :caption: systemd-coredump pattern

   |/usr/lib/systemd/systemd-coredump %P %u %g %s %t %c %h %d %F
   |/usr/lib/systemd/systemd-coredump %P %u %g %s %t %c %h


x86 debug registers (DR0-DR7)
-----------------------------

- :ref:`x86_debug_register`


.. _x86_debug_register:

.. code-block:: text
   :caption: x86 Debug Registers

    DR0-DR3: Store breakpoint register
    DR4,DR5: Reserved
    DR6:     Status register
    DR7:     Control register, flags:
    ------------------------------------------------------
                                     | Type | Length |
                                     |              /
                                     |             /
                                     |            /
                                     |           /
                                     |          /
                                     |         /
                                     |        /
                                     |       /
                                     |      /
                                     |     |
                                      16 18 20 22 24 26 28 30
     0 1 2 3 4 5 6 7       8-15       17 19 21 23 25 27 29 31
    |L|G|L|G|L|G|L|G|                |T |L |T |L |T |L |T |L |
    +--------------------------------------------------------+
    |D|D|D|D|D|D|D|D|                |D |D |D |D |D |D |D |D |
    |R|R|R|R|R|R|R|R|                |R |R |R |R |R |R |R |R |
    |0|0|1|1|2|2|3|3|                |0 |0 |1 |1 |2 |2 |3 |3 |
         Enable                      Type: Breakpoint type (00 execute, 01 write, 11 read-write)
                                   Length: Breakpoint length (00 1-byte, 01 2-bytes, 11 4-bytes)
