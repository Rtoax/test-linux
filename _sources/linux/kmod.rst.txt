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


module SIGN
-----------

- `CONFIG_MODULE_SIG`
- `CONFIG_MODULE_SIG_FORCE`
   - command line `module.sig_enforce=1`
   - `/proc/sys/module/sig_enforce`
- `CONFIG_MODULE_SIG_ALL`
- `CONFIG_MODULE_SIG_KEY`
- `CONFIG_MODULE_SIG_SHA1`
- `CONFIG_MODULE_SIG_SHA224`
- `CONFIG_MODULE_SIG_SHA256`
- `CONFIG_MODULE_SIG_SHA384`
- `CONFIG_MODULE_SIG_SHA512`


keyctl(2)
~~~~~~~~~

.. code-block:: shell

  $ sudo cat /proc/keys


Links
-----

- https://git.kernel.org/pub/scm/utils/kernel/kmod/kmod.git
    - github: https://github.com/kmod-project/kmod
- https://www.kernel.org/doc/html/latest/admin-guide/module-signing.html
- https://www.kernel.org/doc/html/v4.15/admin-guide/module-signing.html
- Patch `arm64: module: improve module VA range selection <https://lore.kernel.org/all/20230530110328.2213762-1-mark.rutland@arm.com/>`_
