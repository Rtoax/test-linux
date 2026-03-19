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

You could always use `man-pages <https://git.kernel.org/pub/scm/docs/man-pages/man-pages.git/>`_
to check what you want to know.


Architecture-specific documentation
===================================

.. toctree::
   :maxdepth: 2

   CPU architecture <arch/index>


eBPF: extended Berkeley Packet Filter
=====================================

.. toctree::
   :maxdepth: 2

   eBPF <bpf/index>


GNU (GNU is not UNIX)
=====================

.. toctree::
   :maxdepth: 2

   gnu/index


Hardware
=========

.. toctree::
   :maxdepth: 1

   gpu/index
