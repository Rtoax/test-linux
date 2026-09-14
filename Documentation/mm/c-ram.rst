Computational RAM (C-RAM)
=========================

Computational RAM (C-RAM) is random-access memory with processing elements integrated on the same chip. This enables C-RAM to be used as a SIMD computer. It also can be used to more efficiently use memory bandwidth within a memory chip. The general technique of doing computations in memory is called processing-in-memory (PIM).


Compute In Memory (CIM)
-----------------------

In-memory processing, also called compute-in-memory (CIM) or processing-in-memory (PIM), is a computer architecture in which data operations are available directly on the data memory, rather than having to be transferred to CPU registers first. This may improve the power usage and performance of moving data between the processor and the main memory.

PIM could be implemented by:

- Processing-using-memory (PuM)
    - Adding limited processing capability (e.g., floating-point multiplication units, 4K row operations such as copy or zero, bitwise operations on two rows) to **conventional memory modules** (e.g., DIMM modules)
    - Adding processing capability to **memory controllers** so that the data that is accessed does not need to be forwarded to the CPU or affect the CPU' cache, but is dealt with immediately.
        - :doc:`../cxl/index`?
- Processing-near-memory (PnM)
    - 3D arrangements of silicon with memory layers and processing layers.


Intelligent RAM (IRAM)
----------------------


Links
-----

- https://en.wikipedia.org/wiki/Computational_RAM
- https://en.wikipedia.org/wiki/Computing_with_memory
- https://en.wikipedia.org/wiki/Berkeley_IRAM_project
- https://en.wikipedia.org/wiki/In-memory_processing
