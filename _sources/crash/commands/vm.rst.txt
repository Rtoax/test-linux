vm
==

.. code-block:: text

    crash> vm 1
    PID: 1      TASK: ffff7000019c0000  CPU: 21  COMMAND: "systemd"
           MM               PGD          RSS    TOTAL_VM
    ffff00ff960c6d40  ffff00ff960d7200  81280k  240448k
          VMA           START       END     FLAGS FILE
    ffff00ff963516a8 aaaab8900000 aaaab8a80000     75 /usr/lib/systemd/systemd
    ffff00ff9635e5b0 aaaab8a80000 aaaab8ad0000 100071 /usr/lib/systemd/systemd
    ffff00ff963581b0 aaaab8ad0000 aaaab8ae0000 100073 /usr/lib/systemd/systemd
    ...
