log
===

show kernel logs, like `dmesg`
------------------------------

.. code-block:: text

    crash> log
    [    0.000000] Booting Linux on physical CPU 0x0000000000 [0x700f8620]
    [    0.000000] Linux version 5.15.131-3.cl9.aarch64 (root@e63e7c705f1d) (gcc (GCC) 11.3.1 20220421 (redhat 11.3.1-2), GNU ld version 2.35.2-24.el9) #1 SMP Thu Nov 30 15:28:49 CST 2023
    [    0.000000] efi: EFI v2.70 by Great Wall
    ...


filter with grep
----------------

.. code-block:: text

    crash> log | grep blocked
    crash> log | grep Booting
    [    0.000000] Booting Linux on physical CPU 0x0000000000 [0x700f8620]
