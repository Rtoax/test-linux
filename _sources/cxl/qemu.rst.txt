========
Qemu CXL
========

Qemu Version
------------

.. list-table::
   :header-rows: 1

   * - Architecture
     - Qemu
     - Machine
   * - x86_64
     - 7.2(初步支持), 8.0(能力完善), 9.0(全场景覆盖), 10.x(稳定迭代)
     - q35
   * - aarch64
     - >= `10.1 <https://wiki.qemu.org/ChangeLog/10.1>`_ CXL can now be used on the Arm 'virt' board
     - virt


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


Qemu CXL FMAPI
--------------

.. code-block:: text

  > Dear Jonathan:
  >
  > I've recently been researching using QEMU to emulate CXL Type 3 devices, but I found that FMAPI testing isn't possible within the guestOS. Fortunately, I found your repository: https://gitlab.com/jic23/cxl-fmapi-tests.
  >
  > During testing, I noticed that you're using a custom version of QEMU. Could you please tell me what methods the current QEMU upstream code supports CXL FMAPI/MCTP?
  >

  Sadly that support needs a little more work for upstream...iirc the main thing for the USB endpoint was respecting the maximum message sizes.  Turns out Linux doesn't currently care if you send longer ones, but given the spec we need to make the emulation correct anyway.

  I changed jobs recently and have been working through legal stuff to be able to do CXL emulation work.  All in theory resolved now but waiting for last doc to move

  Tree wise there is a slightly old tree at gitlab.com/jic23/qemu. Choose branch with latest date.  That has fmapi over mctp over USB support.  Requires none of the hacks that were needed for earlier i2c transport.

  J
  > Best regards.
  >
  > Rong Tao


Linux Kernel
------------

Must enable linux config `CONFIG_CXL_REGION_INVALIDATION_TEST=y` if Qemu (default: `n`), see:

- https://lore.kernel.org/all/CAGEDW0dVEk-QXuL=DPVvSP4t5cafz6N-r_SrCxgFnBfFOsixSA@mail.gmail.com/
- test-linux commit 6f08f902ef5c ("cxl: vm: Report error: cxl region0: Failed to synchronize CPU cache state (todo)")
- test-linux commit c3f026dc37c9 ("cxl: vm: kconfig: Fix error: cxl region0: Failed to synchronize CPU cache state")


Links
-----

- https://www.qemu.org/docs/master/system/devices/cxl.html
- https://github.com/pmem/run_qemu
- Jonathan Cameron:
        - Qemu: https://gitlab.com/jic23/qemu
        - FM API: https://gitlab.com/jic23/cxl-fmapi-tests
