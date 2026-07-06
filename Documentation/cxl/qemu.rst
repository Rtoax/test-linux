========
Qemu CXL
========

Must enable linux config `CONFIG_CXL_REGION_INVALIDATION_TEST` if Qemu, see:

- https://lore.kernel.org/all/CAGEDW0dVEk-QXuL=DPVvSP4t5cafz6N-r_SrCxgFnBfFOsixSA@mail.gmail.com/
- test-linux commit 6f08f902ef5c ("cxl: vm: Report error: cxl region0: Failed to synchronize CPU cache state (todo)")
- test-linux commit c3f026dc37c9 ("cxl: vm: kconfig: Fix error: cxl region0: Failed to synchronize CPU cache state")


- QEMU CCIX patches
- Q35


Qemu Version
------------

.. list-table::
   :widths: 15 30
   :header-rows: 1

   * - Architecture
     - Qemu
   * - x86_64
     - 7.2(初步支持), 8.0(能力完善), 9.0(全场景覆盖), 10.x(稳定迭代)
   * - aarch64
     - >= 9.0/10.x


Qemu PCIe
---------

.. code-block:: text

    ┌─────────────────────────────────────────┐
    │             Q35 Host bridge             │
    │                 (0:0.0)                 │
    │                                         │
    │     ┌───────────┐     ┌───────────┐     │
    │     │ Root Port │     │ Root Port │     │
    │     │  (0:7.0)  │     │ (0:1c.0)  │     │
    └─────┴──────┬────┴─────┴─────┬─────┴─────┘
         ┌───────┘                │
         ▼                        ▼
    ┌────────┐          ┌─────┬────────┬────┐
    │Endpoint│          │     │upstream│    │
    │(10:0.0)│          │     └────────┘    │
    └────────┘          │┌────┐      ┌────┐ │
                        ││down│      │down│ │
                        └┴──┬─┴──────┴──┬─┴─┘
                         ┌──┘           └─┐
                         ▼                ▼
                     ┌────────┐       ┌────────┐
                     │Endpoint│       │Endpoint│
                     │(20:0.0)│       │(30:0.0)│
                     └────────┘       └────────┘


Links
-----

- https://www.qemu.org/docs/master/system/devices/cxl.html
- https://github.com/pmem/run_qemu
