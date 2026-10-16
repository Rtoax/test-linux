.. _arm64_simd_index:

==========
ARM64 SIMD
==========

SIMD
----

Bits: NEON < SVE <= SVE2

NEON
~~~~

- Since Armv7-A.
- Arm **Cortex-A** and Arm **Cortex-R** series of processors.

Operations
""""""""""

Neon instructions allow up to:

- 16x8-bit, 8x16-bit, 4x32-bit, 2x64-bit integer operations
- 8x16-bit, 4x32-bit, 2x64-bit floating-point operations


Register
""""""""

.. code-block:: text

    128bit         0
    +---------------+
    |               |  NEON
    +---------------+
        Q0-Q15


          32bit    0
           +--------+
           |        |
           +--------+
            D0-D31


SVE/SVE2
~~~~~~~~

- SVE/SVE2  Scalable Vector Registers

.. code-block:: text

                  128 bits ~ 2048 bits
                                      Neon
            LEN x 128                128 bits
    +------------------------   --+------------+
    |          Z32          ....  |    V32     |
    +------------------------   --+------------+
                            ....      .....
    +------------------------   --+------------+
    |          Z2           ....  |    V2      |
    +------------------------   ---------------+
    |          Z1           ....  |    V1      |
    +------------------------   --+------------+


- SVE/SVE2 Scalable Predicate Registers

.. code-block:: text

       LEN x 16
    +-----------+   +-----------+
    |    P7     |   |    P15    |
    +-----------+   +-----------+
         ...             ...
    +-----------+   +-----------+
    |    P1     |   |    p9     |
    +-----------+   +-----------+   +----------+
    |    P0     |   |    P8     |   |   FFR    |
    +-----------+   +-----------+   +----------+

- SVE/SVE2 Scalable Vector Control Registers

.. code-block:: text

      LEN=1...16
    +----------+  +----------+  +----------+
    | ZCR_EL1  |  | ZCR_EL2  |  | ZCR_EL3  |
    +----------+  +----------+  +----------+


Links
-----

- Intel ISA-L: https://github.com/intel/isa-l
- https://en.wikipedia.org/wiki/CPUID
- https://en.wikipedia.org/wiki/Advanced_Vector_Extensions
