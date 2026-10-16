========
Binutils
========

The GNU Binutils are a collection of binary tools. The main ones are:

- ld: the GNU linker.
- as: the GNU assembler.
- gold: a new, faster, ELF only linker.

But they also include:

- addr2line: Converts addresses into filenames and line numbers.
- ar: A utility for creating, modifying and extracting from archives.
- c++filt: Filter to demangle encoded C++ symbols.
- dlltool: Creates files for building and using DLLs.
- elfedit: Allows alteration of ELF format files.
- gprof: Displays profiling information.
- gprofng: Collects and displays application performance data.
- nlmconv: Converts object code into an NLM.
- nm: Lists symbols from object files.
- objcopy: Copies and translates object files.
- objdump: Displays information from object files.
- ranlib: Generates an index to the contents of an archive.
- readelf: Displays information from any ELF format object file.
- size: Lists the section sizes of an object or archive file.
- strings: Lists printable strings from files.
- strip: Discards symbols.
- windmc: A Windows compatible message compiler.
- windres: A compiler for Windows resource files.

As well as some libraries:

- libbfd: A library for manipulating binary files in a variety of different
  formats.
- libctf: A library for manipulating the CTF debug format.
- libopcodes: A library for assembling and disassembling a variety of different
  assembler languages.
- libsframe: A library for manipulating the SFRAME debug format.


BFD (Binary File Descriptor Library)
------------------------------------

The Binary File Descriptor library (BFD) is the GNU Project's main mechanism
for the portable manipulation of object files in a variety of formats. As of
2003, it supports approximately 50 file formats for some 25 instruction set
architectures.


Opcode (Operation Code)
-----------------------

- :ref:`opcode_table`


.. _opcode_table:

.. code-block:: text
   :caption: Opcode table

      |  0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
    --+---------------------------------------------------------------
     0|  00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F
     1|  10  11  12  13  14  15  16  17  18  19  1A  1B  5C  1D  1E  1F
     2|  20  21  22  23  24  25  26  27  28  29  2A  2B  2C  2D  2E  2F
     3|  30  31  32  33  34  35  36  37  38  39  3A  3B  3C  3D  3E  3F
     4|  40  41  42  43  44  45  46  47  48  49  4A  4B  4C  4D  4E  4F
     5|  50  51  52  53  54  55  56  57  58  59  5A  5B  5C  5D  5E  5F
     6|  60  61  62  63  64  65  66  67  68  69  6A  6B  6C  6D  6E  6F
     7|  70  71  72  73  74  75  76  77  78  79  7A  7B  7C  7D  7E  7F
     8|  80  81  82  83  84  85  86  87  88  89  8A  8B  8C  8D  8E  8F
     9|  90  91  92  93  94  95  96  97  98  99  9A  9B  9C  9D  9E  9F
     A|  A0  A1  A2  A3  A4  A5  A6  A7  A8  A9  AA  AB  AC  AD  AE  AF
     B|  B0  B1  B2  B3  B4  B5  B6  B7  B8  B9  BA  BB  BC  BD  BE  BF
     C|  C0  C1  C2  C3  C4  C5  C6  C7  C8  C9  CA  CB  CC  CD  CE  CF
     D|  D0  D1  D2  D3  D4  D5  D6  D7  D8  D9  DA  DB  DC  DD  DE  DF
     E|  E0  E1  E2  E3  E4  E5  E6  E7  E8  E9  EA  EB  EC  ED  EE  EF
     F|  F0  F1  F2  F3  F4  F5  F6  F7  F8  F9  FA  FB  FC  FD  FE  FF


Links
-----

- https://sourceware.org/binutils
- https://sourceware.org/git/binutils-gdb.git
- `BFD <https://en.wikipedia.org/wiki/Binary_File_Descriptor_library>`_
- https://en.wikipedia.org/wiki/Opcode
- https://en.wikipedia.org/wiki/Opcode_table
