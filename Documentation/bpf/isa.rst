======================================
BPF ISA (Instruction Set Architecture)
======================================

Compiler
--------

The GCC compiler comes with an eBPF backend starting from **GCC 10**. Up to
that point, LLVM has been the only compiler which supports generating eBPF
ELF files.


cBPF
----

cBPF only support two 32-bits registers, `A` add register and `X` index
register.


eBPF
----

Resigters
~~~~~~~~~

support 10 64-bits registers.

- `R0`: return value from function calls, and exit value for eBPF programs;
- `R1` - `R5`: arguments for function calls;
- `R6` - `R9`: callee saved registers that function calls will preserve;
- `R10`: read-only frame pointer to access stack;


Basic instruction encoding
~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: text
   :caption: Basic instruction encoding

    0                                                              4B
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |    opcode     |     regs      |            offset             |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                              imm                              |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


Wide instruction encoding
~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: text
   :caption: Wide instruction encoding

    0                                                              4B
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |    opcode     |     regs      |            offset             |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                              imm                              |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                           reserved                            |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                           next_imm                            |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


Links
-----

- `RFC 9669 in 2024 <ttps://www.rfc-editor.org/rfc/rfc9669.html>`_
- `eBPF Instruction Set Specification, v1.0 <https://www.kernel.org/doc/html/v6.1/bpf/instruction-set.html>`_
