XCENA CXL
=========

The World’s First CXL 3.2 Computational Memory.

- **CXL Memory Expansion**
    - CXL Type 3 HDM-DB with PCIe 6.0 dual x8 interface
    - CXL 3.2-compliant coherency
    - Hot-page monitoring for memory tiering
    - CXL 3.2, Type3 HDM-DB with BI
    - Up to 2 TB (256 GB DIMM, 2DPC)
- **Near Data Processing**
    - 1,000s of custom `RISC-V` cores
    - FP32 / FP16 vector engines
    - `LLVM-based` custom toolchain
- **Memory Compression**
    - SW compression/decompression
    - HW-assisted decompression
- **Enhanced RAS**
    - Chipkill + Multi-bit error detection
    - E2E data protection
- **InfiniteMemory™**
    - Integrated `PCIe 6.0 RC`
    - SSD RAID support
    - Petabyte-scale memory expansion
    - SSD connection through separate PCIe 6.0 connection
    - Virtually unlimited memory access with low-latency


.. code-block:: text
  :caption: Hot Chips 2026 XCENA MX1 CXL Slide 7 Host and MU share one virtual address space

           ┌──────────┐
           │  Virtual │
           │Address #1│                              ┌─────┐ ┌─────┐ ┌─────┐
           │          │                              │ MU  │ │ MU  │ │ MU  │
           │          │                              └─────┘ └──┬──┘ └─────┘
           │          │      ┌─────────────┐                 VA │
  ┌────┐   ├──────────┤      │Host Physical│         ┌─────┐ ┌──┴──┐ ┌─────┐
  │Proc├───┤Mapped CXL│MMU/OS│   Address   │         │ MMU │ │ MMU │ │ MMU │
  │ #1 │   │   Space  ├───┐  │             │         └─────┘ └──┬──┘ └─────┘
  └────┘   │          │   │  │             │                    │
           ├──────────┤   │  ├─────────────┤         ┌──────────┼──────────┐
           │          │   │  │             │─────────┼───┐ ┌────┘          │
           │          │   └──┤   CXL HPA   │         │   │ │   SNOOP       │
           └──────────┘      │             │<────────┤   │ │               │
                             ├─────────────┤ BI-Snoop└───┼─┼───────────────┘
           ┌──────────┐      │             │             │ │
           │  Virtual │      │             │             │ │
           │Address #2│      ├─────────────┤             │ │
           │          │      │             │             ▼ ▼                     Device Private Memory
           │          │   ┌──┤   CXL HPA   │         ┌─┬────────┬──────────┐      ┌─────────────────────┐
           │          │   │  │             │         │ │ Device │          │    ┌─┴───────────────────┐N│
           ├──────────┤   │  ├─────────────┤         │ │Physical│ CXL DRAM │  ┌─┴───────────────────┐2├─┘
  ┌────┐   │Mapped CXL│   │  │             │         │ │Address │          │  │Virtual─Page─Table─#1├─┘
  │Proc├───┤   Space  ├───┘  │             │         └─┴────────┴┬────▲────┘  └─────────────────────┘
  │ #2 │   │          │      │             │                     │    │ Page Caching
  └────┘   ├──────────┤      │             │                     │    │
           │          │      │             │         ┌───────────▼────┴────────────┐
           │          │      │             │         │ SSD-backed Memory Expansion │
           └──────────┘      └─────────────┘         └─────────────────────────────┘


Links
-----

- https://xcena.com/computational_memory
- https://www.servethehome.com/xcena-mx1-cxl-computational-memory-device-at-hot-chips-2026/
