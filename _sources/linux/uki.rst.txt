UKI (Unified Kernel Image)
==========================

A UKI is a UEFI binary containing the Linux kernel image, initramfs, kernel
command line, and Red Hat signature. By shipping all these components together,
we extend the SecureBoot process to also cover initramfs and the kernel command
line.

.. code-block:: text

                         Unified Kernel Image
    ┌──────────────────────────────────────────────────────────┐
    │┌──────────────┐  ┌───────────┐  ┌─────────┐ ┌───────────┐│
    ││ Linux Kernel │  │ initramfs │  │ cmdline │ │ signature ││
    │└──────────────┘  └───────────┘  └─────────┘ └───────────┘│
    └──────────────────────────────────────────────────────────┘


Links
-----

- https://uapi-group.org/specifications/specs/unified_kernel_image/
- https://www.redhat.com/en/blog/extending-red-hat-unified-kernel-images-using-addons
