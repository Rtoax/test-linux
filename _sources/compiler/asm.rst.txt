ASM
===

Inline Assembly in Linux C
--------------------------

AT&T Synx
~~~~~~~~~

`OP-code src dst`, for example: `"movl $78, %1 \n"`.


asm()
~~~~~

.. code-block:: c

  asm (
  	assembler template
  	: output operands (optional)
  	: input operands (optional)
  	: list of clobbered registers (optional)
  );


Cross Compile
-------------

.. code-block:: shell

  $ aarch64-linux-gnu-gcc -print-sysroot
  /usr/aarch64-linux-gnu/sys-root
