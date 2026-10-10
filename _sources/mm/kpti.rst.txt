KPTI - Kernel Page Table Isolation
==================================

cmdline
-------

- `kpti=1`
- `nopti`

.. code-block:: shell

  $ sudo grubby --update-kernel=ALL --args='kpti=1'
  $ sudo grubby --update-kernel=ALL --remove-args='kpti=1'


Links
-----

- https://ctf-wiki.org/pwn/linux/kernel-mode/defense/isolation/user-kernel/kpti/
