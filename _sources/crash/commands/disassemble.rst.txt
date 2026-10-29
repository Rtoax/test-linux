disassemble
===========

disassemble function
--------------------

.. code-block:: text

    crash> disassemble kernel_clone
    Dump of assembler code for function kernel_clone:
       0xffff8000080b4874 <+0>:     mov     x9, x30
       0xffff8000080b4878 <+4>:     nop
       0xffff8000080b487c <+0>:     paciasp
    ...


display filename and line number
--------------------------------

.. code-block:: text

    crash> dis -s kernel_clone
    FILE: kernel/fork.c
    LINE: 2545

      2540                  .stack_size     = (unsigned long)arg,
      2541                  .io_thread      = 1,
      2542          };
      2543
      2544          return copy_process(NULL, 0, node, &args);
    * 2545  }
      2546
      2547  /*
      2548   *  Ok, this is the main fork-routine.
      2549   *

    crash> dis -s 0xffff8000080b4874
    FILE: kernel/fork.c
    LINE: 2545

      2540                  .stack_size     = (unsigned long)arg,
      2541                  .io_thread      = 1,
      2542          };
      2543
      2544          return copy_process(NULL, 0, node, &args);
    * 2545  }
      2546
      2547  /*
      2548   *  Ok, this is the main fork-routine.
      2549   *
