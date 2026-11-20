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
    - :doc:`../../mm/pim`
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


PXL: Parallel Xceleration Library
---------------------------------

**Parallel Xceleration Library (PXL)** is a key component of XCENA SDK designed to facilitate optimized communication between host system and XCENA computational memory devices.

By leveraging PXL, developers can unlock the full potential of in-memory computing technology through a robust and efficient API.


XCENA Software Development Kit
------------------------------

The **XCENA Software Development Kit (SDK)** provides libraries and tools for running computation on XCENA devices. **Compute Express Link (CXL)** connects the host to the device’s memory. A device kernel is a function that runs on the device’s **memory execution units (MUs)**. The host application allocates device memory and launches kernels through the **Parallel Xceleration Library (PXL)**.

`Example <https://xcena-dev.github.io/sdk_release/tools/pxcc.html#programming-model>`_:

.. code-block:: c

    int hostUtil(int x);                    // no annotation → host only; not callable from a kernel
    __mu_device__ int devUtil(int x);       // device only
    __mu_shared__ int shared(int x);        // host and device

    __pxl_kernel__ void k(int* a, int n)
    {
        a[0] = devUtil(a[0]) + shared(a[0]); // OK
        // a[0] = hostUtil(a[0]);            // ERROR: host-only symbol on the device
    }


XCENA MX1
---------

XCENA is presenting its MX1 CXL computational memory device at Hot Chips 2026 in a joint session with Samsung that pairs the device with a rack-scale CXL memory plan. The XCENA MX1 is a Type 3 CXL part that fuses three ideas in one package: CXL memory expansion, SSD-backed storage presented as byte-addressable CXL memory, and **near-memory processing** across thousands of RISC-V cores. We covered the first generation of MX1 when it appeared as a CXL 3.0 computational memory part, and this session extends that story into rack-scale systems.

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
- XCENA MX1 CXL Computational Memory Device at Hot Chips 2026 with Samsung https://www.servethehome.com/xcena-mx1-cxl-computational-memory-device-at-hot-chips-2026/
    - CSDN: https://blog.csdn.net/Rong_Toa/article/details/165346869
- PXL: https://xcena-dev.github.io/pxl/
- SDK: https://xcena-dev.github.io/sdk_release/
    - PXCC: https://xcena-dev.github.io/sdk_release/tools/pxcc.html
