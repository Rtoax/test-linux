Qemu - Quick Emulator
=====================

.. toctree::
   :maxdepth: 1

   abbrev
   tcg


A generic and open source machine emulator and virtualizer.


Accelerators
------------

Initialization
~~~~~~~~~~~~~~

Command `qemu-kvm -accel=[kvm|tcg]`:

.. code-block:: c
   :caption: Qemu Initialization

    qemu_init() {
      configure_accelerators() {
        do_configure_accelerator() {
          accel_init_machine() {
            /**
             * kvm: kvm_init();
             * tcg: tcg_init_machine();
             */
            acc->init_machine();
          }
        }
      }
    }


Links
~~~~~

- https://www.qemu.org/
- https://gitlab.com/qemu-project/qemu
- https://github.com/qemu/QEMU
