foreach
=======

- show tasks

.. code-block:: text

    crash> ps -S
      RU: 264
      IN: 20808
      ID: 1386
      NE: 3

    crash> foreach NE ps
       PID    PPID  CPU       TASK        ST  %MEM     VSZ    RSS  COMM
      1302345  1302341  38  ffff710162497a00  NE   0.0    4416    768  bash
      1302349  1302346  53  ffff01012f96ac00  NE   0.0    4416    832  bash
      1302350  1302348  96  ffff6101ff632a00  NE   0.0    4416    768  bash

    crash> foreach NE ps | tail -n2
      1302349  1302346  53  ffff01012f96ac00  NE   0.0    4416    832  bash
      1302350  1302348  96  ffff6101ff632a00  NE   0.0    4416    768  bash
