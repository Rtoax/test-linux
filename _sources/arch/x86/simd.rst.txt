========
x86 SIMD
========

.. code-block:: text

   Bits: SSE < SSE2 < SSE3 < SSE4 < (SSE5) < AVX < AVX512

SSE5: AMD发布，Intel生气不玩了


Registers
~~~~~~~~~

.. code-block:: text

                                                   64bit  0
                                                   +-------+
                                                   |       |   MMX
                                                   +-------+
                                                   MM0 - MM7
                                            128bit         0
                                            +---------------+
                                            |               |  SSE
                                            +---------------+
                                                XMM0 - XMM7
                               256bit                      0
                              +-----------------------------+
                              |                             |  AVX
                              +-----------------------------+
                                      YMM0 - YMM15
   512bit                                                  0
   +--------------------------------------------------------+
   |                                                        |  AVX-512
   +--------------------------------------------------------+
                       ZMM0 - ZMM31

MMX
~~~

Introduced on January 8, 1997 with its Pentium P5.

SSE
~~~

SSE Instruction Set

- SSE: Added with Pentium III (70 new instructions)
- SSE2: Added with Pentium 4 in 2000 (144 new instructions over SSE)
- SSE3: Added with later Pentium 4 in 2004 (13 new instructions over SSE2)
- SSSE3: Added with Xeon 5100 and early Core 2 in 2006 (contains 16 new discrete instructions)
- SSE4: 2006 (consists of 54 instructions)
   - SSE4.1: Added with later Core 2 (Intel: consists of 47 instructions)
   - SSE4a: Added with Phenom (AMD: 4 SSE4 instructions and 4 new SSE instructions)
   - SSE4.2: Added with Nehalem (Intel: consists of the 7 remaining instructions)


AVX, AVX2, AVX-512
~~~~~~~~~~~~~~~~~~

- AVX:
- AVX2:
- AVX512:


Links
-----

- Intel ISA-L https://github.com/intel/isa-l
- https://en.wikipedia.org/wiki/CPUID
- https://en.wikipedia.org/wiki/Advanced_Vector_Extensions
- https://www.felixcloutier.com/x86/
- SSE: https://en.wikibooks.org/wiki/X86_Assembly/SSE
- AVX: oracle https://docs.oracle.com/cd/E36784_01/html/E36859/gntbd.html
- AVX2: oracle https://docs.oracle.com/cd/E36784_01/html/E36859/gntae.html
- AVX512: oracle https://docs.oracle.com/cd/E37838_01/html/E61064/gsesq.html
