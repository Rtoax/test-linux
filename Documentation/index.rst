.. Test Linux Documentation documentation master file

.. _test_linux_doc:

============================
The Test Linux Documentation
============================

This is the top level of the test-linux's documentation tree.

The **Test Linux** repository contains **GNU/Linux** related test case codes,
scripts and knowledge points, as well as operating system related content.

You must clone test-linux under **Linux(UNIX like)** system. Because there are
lots of symbol links, some file system not support in Windows OS.

You'd better don't rename any of folder and file's name, because of symlinks.
If you rename/move/update/remove path/directory, you need to run **make check**
under top-dir and fix the invalid-symlinks.

It may be that the repository will contain **desktop-related** test code, such
as **GNOME**, but that is not the main purpose of the repository. Perhaps
researching the **GUI** is also the purpose of this repository, such as
**GTK**, **Wayland**.

It seems that I have also added some **GPU** and **AI** related content, which
is less related to Linux, but most of it is still part of the Linux ecosystem.

You could always use `man-pages <https://git.kernel.org/pub/scm/docs/man-pages/man-pages.git/>`_
to check what you want to know.


Standard and Development
========================

.. toctree::
   :maxdepth: 2

   Standard <standard/index>
   UEFI <uefi/index>

.. toctree::
   :maxdepth: 1

   Linux <linux/index>
   Linux Distributions <distro/index>
   Test Linux Development <devel/index>


Development Tools
=================

.. toctree::
   :maxdepth: 1

   Shell <shell/index>
   The GNU Project <gnu/index>


Hardware Architecture
=====================

.. toctree::
   :maxdepth: 1

   PCIe <pcie/index>
   CPU Architecture <arch/index>
   GPU Architecture <gpu/index>
   superPod <superpod/index>
   CXL <cxl/index>
   Interrupt <interrupt/index>


Linux Kernel
============

.. toctree::
   :maxdepth: 1

   Scheduler <sched/index>


Debug and Observability
=======================

.. toctree::
   :maxdepth: 1

   eBPF <bpf/index>


Network and Servers
===================

.. toctree::
   :maxdepth: 1

   Network <network/index>


Virtualization
==============

.. toctree::
   :maxdepth: 1

   virt/index


Benchmark System
================

.. toctree::
   :maxdepth: 1

   Benchmark <benchmark/index>


Tools
=====

.. toctree::
   :maxdepth: 1

   Grub <grub/index>
   Systemd <systemd/index>
   Tools <tools/index>


Frontier and Future Technology
==============================

.. toctree::
   :maxdepth: 1

   AI <ai/index>
   Big Data <bigdata/index>
   Cloud Native <cloud-native/index>


Relative Projects
=================

- `linux-test-project/ltp <https://github.com/linux-test-project/ltp>`_
- `unpbook/unpv13e <https://github.com/unpbook/unpv13e>`_
