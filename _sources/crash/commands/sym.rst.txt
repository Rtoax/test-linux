sym
===

.. code-block:: text

    crash> sym kernel_clone
    ffff8000080b4874 (T) kernel_clone /path/to/kernel/fork.c: 2545

    crash> sym ffff8000080b4874
    ffff8000080b4874 (T) kernel_clone /path/to/kernel/fork.c: 2545

    crash> sym 0xffff8000080b4874
    ffff8000080b4874 (T) kernel_clone /path/to/kernel/fork.c: 2545
