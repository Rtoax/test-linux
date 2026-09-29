Secure Boot
===========


Q&A
---

- Q: insmod 失败

.. code-block:: shell

  $ sudo insmod completion.ko
  insmod: ERROR: could not insert module completion.ko: Key was rejected by service
  $ dmesg
  ...
  [   43.493148] Loading of unsigned module is rejected

- A: 关闭 Secure Boot.


Links
-----
