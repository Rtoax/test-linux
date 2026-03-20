.. SPDX-License-Identifier: GPL-2.0

=================
Development rules
=================

Linus Torvalds releases a new kernel and opens a **2-week merge window**,
however, test-linux has no development cycle restrictions, submissions,
development, and releases can be done at any time.


Commit Tags
===========

- **Signed-off-by**: Using sign-off, developers certify the patch to be their
  original work or have the right to pass it on as an open source patch. In
  our example, the author signed off and then, as the usb maintainer, Greg KH
  signed-off on the patch. Please refer to Sign your work - the Developer's
  Certificate of Origin for detailed information on this tag, as it is a very
  important part of the kernel development process.
- **Acked-by**: This tag is often used by the maintainer of the affected code
  when that maintainer neither contributed to, nor forwarded the patch. As an
  example, I maintain the usbip driver and I use the Acked-by tag to ask the
  USB maintainer to pick patches sent by other developers.
- **Reviewed-by**: This tag indicates that the patch has been reviewed by the
  person named in the tag.
- **Reported-by**: This tag gives credit to people who find bugs and report
  them.
- **Tested-by**: This tag indicates that the patch has been tested by the
  person named in the tag.
- **Suggested-by**: This tag indicates that the patch has been tested by the
  person named in the tag.
- **Fixes**: This tag indicates that the patch fixes an issue in a previous
  commit referenced by its Commit ID. This tag allows us to track where the
  bug originated.
- **Envs**: This tag indicates the env of your system.
- **Vers**: This tag indicates the software/hardware version of your system.


Sub-Directories
===============

- Each **scripts** directory contain scriptions(bpftrace, bcc, shell).
- Each **modules** directory contain Linux Modules(KO) source code.
- Each **samples** directory contain source userspace code.
- Each **commands** directory contain relative command lines.
- Each **images** directory contains relative images.


Files
=====

- Each **README.md** is current directory's description.
- Each **FAQ.md** is current directory's FAQs.
- Each **abbrev.md** is current directory's relative abbreviation.
  - scripts: **./abbrev.sh** to check all abbreviations.
- Each **history.md** is store history of some technology.
- Each **drawio** contains relate directory diagrams.
- Never call **include** in ***.mk** file, only call **include** in Makefile.
- Each **kconfig** contains kernel CONFIG, each CONFIG is placed in the kconfig
  of the corresponding directory, and the public CONFIG is placed in the
  kconfig of the top-level directory.
  - scripts: **./kconfig.sh** to check all kernel config;
- Each ***_helpers*** is helpers program/script of current directory, better
  **LGPL-2.1 OR BSD-2-Clause** license.
- Each **requirements.txt** is Python pip --requirement for each directory.
- Ignore file (check **.gitignore**).
- If you want to write a text **Note**, use **.md**(**markdown**).
- There are so many **symlinks** in this repo, so you better clone this repo in
  linux system, if windows, oops. You'd better use **make check**
  (or **./scripts/broken-symlinks.sh**) check invalid links and modify them.


Licenses
========

If the source code file has a copyright information at the beginning, the
copyright of the source code is the description content, otherwise, it is the
copyright of the test-linux repository.

If the code does not specify, then it follows **GPLv3**.

BPF programs always follow **GPLv2**.

The copyright line format must be **Copyright (C) Year-Year Author**.
