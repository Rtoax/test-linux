backtrace
=========

show backtrace
--------------

.. code-block:: text

    crash> bt 1302352
    PID: 1302352  TASK: ffff500010a3ba00  CPU: 30  COMMAND: "sh"
     #0 [ffff80016406fa40] machine_kexec at ffff800008052ee0
     #1 [ffff80016406fa80] __crash_kexec at ffff80000819ffc4
     ...
    #14 [ffff80016406fea0] el0t_64_sync_handler at ffff800008c48670
    #15 [ffff80016406ffe0] el0t_64_sync at ffff80000803160c
         PC: 0000ffff90f1b580   LR: 0000ffff90eba1fc   SP: 0000ffffce14dd70
        X29: 0000ffffce14dd70  X28: 0000000000000000  X27: 0000aaaaab590000
        X26: 0000aaaaab5f3010  X25: 0000aaaaab6389bc  X24: 0000000000000002
        X23: 0000aaaacc1e4110  X22: 0000ffff910c3aa0  X21: 0000ffff90fe15c0
        X20: 0000aaaacc1e4110  X19: 0000000000000001  X18: 0000000000000000
        X17: 0000ffff90eb6ec0  X16: 0000ffff90ebb5e0  X15: 0000000000000000
        X14: 0000000000000002  X13: 0000000000000410  X12: 0000000000000000
        X11: 0000000000000020  X10: 00000000ffffffff   X9: 0000aaaacc1e3ca0
         X8: 0000000000000040   X7: 0000000000000010   X6: 000000000000021a
         X5: 00000000fbad2a84   X4: 00000000ffffffff   X3: 0000ffff910c32e0
         X2: 0000000000000002   X1: 0000aaaacc1e4110   X0: 0000000000000001
        ORIG_X0: 0000000000000001  SYSCALLNO: 40  PSTATE: 20001000


display the stack trace of the panic task only
----------------------------------------------

.. code-block:: text

    crash> bt -p
    PID: 1302352  TASK: ffff500010a3ba00  CPU: 30  COMMAND: "sh"
     #0 [ffff80016406fa40] machine_kexec at ffff800008052ee0
     #1 [ffff80016406fa80] __crash_kexec at ffff80000819ffc4
     ...
    #14 [ffff80016406fea0] el0t_64_sync_handler at ffff800008c48670
    #15 [ffff80016406ffe0] el0t_64_sync at ffff80000803160c
         PC: 0000ffff90f1b580   LR: 0000ffff90eba1fc   SP: 0000ffffce14dd70
        X29: 0000ffffce14dd70  X28: 0000000000000000  X27: 0000aaaaab590000
        X26: 0000aaaaab5f3010  X25: 0000aaaaab6389bc  X24: 0000000000000002
        X23: 0000aaaacc1e4110  X22: 0000ffff910c3aa0  X21: 0000ffff90fe15c0
        X20: 0000aaaacc1e4110  X19: 0000000000000001  X18: 0000000000000000
        X17: 0000ffff90eb6ec0  X16: 0000ffff90ebb5e0  X15: 0000000000000000
        X14: 0000000000000002  X13: 0000000000000410  X12: 0000000000000000
        X11: 0000000000000020  X10: 00000000ffffffff   X9: 0000aaaacc1e3ca0
         X8: 0000000000000040   X7: 0000000000000010   X6: 000000000000021a
         X5: 00000000fbad2a84   X4: 00000000ffffffff   X3: 0000ffff910c32e0
         X2: 0000000000000002   X1: 0000aaaacc1e4110   X0: 0000000000000001
        ORIG_X0: 0000000000000001  SYSCALLNO: 40  PSTATE: 20001000
