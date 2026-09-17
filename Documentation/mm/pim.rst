Compute In Memory (CIM) or Processing In Memory (PIM)
=====================================================

In-memory processing, also called compute-in-memory (CIM) or processing-in-memory (PIM), is a computer architecture in which data operations are available directly on the data memory, rather than having to be transferred to CPU registers first. This may improve the power usage and performance of moving data between the processor and the main memory.

PIM could be implemented by:

- Processing-using-memory (PuM)
    - Adding limited processing capability (e.g., floating-point multiplication units, 4K row operations such as copy or zero, bitwise operations on two rows) to **conventional memory modules** (e.g., DIMM modules)
    - Adding processing capability to **memory controllers** so that the data that is accessed does not need to be forwarded to the CPU or affect the CPU' cache, but is dealt with immediately.
        - :doc:`../cxl/index`?
- Processing-near-memory (PnM)
    - 3D arrangements of silicon with memory layers and processing layers.


.. _fig-PIM-category:

.. mermaid::
   :caption: PIM 分类

    flowchart LR
        PIM(PIM) ==> CRAM([计算型CRAM])
        PIM ==> IRAM([智能IRAM])


PIM systems implement computing primitives such as logic operations and multiply-accumulate acceleration through compute-in-memory, near-memory processing, or hybrid designs.

.. _fig-PIM-normal-form:

.. mermaid::
   :caption: PIM 范式

    flowchart LR
        PIM(PIM) ==> CIM([CIM 存内计算])
        PIM ==> NMP([NMP 近存计算])


Computational RAM (CRAM)
------------------------

Computational RAM (C-RAM) is random-access memory with processing elements integrated on the same chip. This enables C-RAM to be used as a SIMD computer. It also can be used to more efficiently use memory bandwidth within a memory chip. The general technique of doing computations in memory is called processing-in-memory (PIM).


Intelligent RAM (IRAM)
----------------------


Links
-----

- `A Survey on the Expanding Scope and Interdisciplinary Opportunities for Processing-in-Memory Techniques 内存处理技术的扩展范围和跨学科机会综述 <https://ieeexplore.ieee.org/abstract/document/11369959#1>`_
- https://en.wikipedia.org/wiki/Berkeley_IRAM_project
- https://en.wikipedia.org/wiki/Computational_RAM
- https://en.wikipedia.org/wiki/Computing_with_memory
- https://en.wikipedia.org/wiki/In-memory_processing
