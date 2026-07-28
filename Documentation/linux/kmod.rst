Linux Kernel Module
===================

ELF
---

.. code-block:: shell

   $ strip --strip-debug input.ko -o output-no-debug.ko


grub cmdline
------------

* rd.driver.blacklist=MOD
  - `rd.driver.blacklist=nouveau`
* modprobe.blacklist=MOD1,MOD2
  - `modprobe.blacklist=nouveau`


/etc/modprobe.d/
----------------

* MOD.blacklist=1
  - nouveau.blacklist = 1


Links
-----

- https://git.kernel.org/pub/scm/utils/kernel/kmod/kmod.git
    - github: https://github.com/kmod-project/kmod
- Patch `arm64: module: improve module VA range selection <https://lore.kernel.org/all/20230530110328.2213762-1-mark.rutland@arm.com/>`_
