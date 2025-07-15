test-linux README
=================

This code repository contains **GNU/Linux** related test case codes, scripts and knowledge points, as well as operating system related content.

I'd rather name the repository **test-gnu-linux**, but it's too late to regret it, because I should have referenced the name test-linux somewhere else, like **ostools**.

You must clone this repo under **Linux(UNIX like)** system. Because there are lots of symbol links, some file system not support in Windows OS.

You'd better don't rename any of folder and file's name, because of symlinks. If you rename/move/update/remove path/directory, you need to run **make check** under top-dir and fix the invalid-symlinks.

It may be that the repository will contain **desktop-related** test code, such as **GNOME**, but that is not the main purpose of the repository. Perhaps researching the **GUI** is also the purpose of this repository, such as **GTK**.

You could always use [man-pages](https://git.kernel.org/pub/scm/docs/man-pages/man-pages.git/) to check what you want to know.


# Linux Kernel Development

Linus Torvalds releases a new kernel and opens a **2-week merge window**.

## Commit Tags

- `Signed-off-by`: Using sign-off, developers certify the patch to be their original work or have the right to pass it on as an open source patch. In our example, the author signed off and then, as the usb maintainer, Greg KH signed-off on the patch. Please refer to Sign your work - the Developer's Certificate of Origin for detailed information on this tag, as it is a very important part of the kernel development process.
- `Acked-by`: This tag is often used by the maintainer of the affected code when that maintainer neither contributed to, nor forwarded the patch. As an example, I maintain the usbip driver and I use the Acked-by tag to ask the USB maintainer to pick patches sent by other developers.
- `Reviewed-by`: This tag indicates that the patch has been reviewed by the person named in the tag.
- `Reported-by`: This tag gives credit to people who find bugs and report them.
- `Tested-by`: This tag indicates that the patch has been tested by the person named in the tag.
- `Suggested-by`: This tag indicates that the patch has been tested by the person named in the tag.
- `Fixes`: This tag indicates that the patch fixes an issue in a previous commit referenced by its Commit ID. This tag allows us to track where the bug originated.


## Linux Debug Options

```
CONFIG_KASAN
CONFIG_KMSAN
CONFIG_UBSAN
CONFIG_LOCKDEP
CONFIG_PROVE_LOCKING
CONFIG_LOCKUP_DETECTOR
```

- [Bug hunting](https://www.kernel.org/doc/html/latest/admin-guide/bug-hunting.html)
- [Bisecting a regression(二分回归)](https://www.kernel.org/doc/html/latest/admin-guide/bug-bisect.html)
- [Dynamic debug](https://www.kernel.org/doc/html/latest/admin-guide/dynamic-debug-howto.html)


# test-linux

## Relative Architecture

- [x] `x86_64`
- [x] `aarch64`
- [x] `sw_64`
- [ ] `riscv64`
- [ ] `loongarch64`

## Sub-Directories

* Each `scripts` directory contain scriptions(bpftrace, bcc, shell).
* Each `modules` directory contain Linux Modules(KO) source code.
* Each `samples` directory contain source userspace code.
* Each `commands` directory contain relative command lines.
* Each `images` directory contains relative images.

## Files

* Each `README.md` is current directory's description.
* Each `abbreviation.md` is current directory's relative abbreviation.
	- format: **abbreviation: full name (中文全称) @relate1 @relate2**
	- scripts: `./abbreviation.sh` to check all abbreviations.
* Each `history.md` is store history of some technology.
* Each **drawio** contains relate directory diagrams.
* Never call `include` in `*.mk` file, only call `include` in Makefile.
* Each `kconfig` contains kernel CONFIG.
* Each `*_helpers*` is helpers program/script of current directory, better `LGPL-2.1 OR BSD-2-Clause` license.


## abbreviation.md Example

- Syntax: `NAME[,ALIAS1,ALIAS2]: English shotcut (Chinese shotcut) @RELATE1 @RELATE2`

```
- AB: A Ball (一个球[, RFC|IEEE])
- ABC[,ALIAS1,ALIAS2]: A Ball Circle (一个球圈[, RFC|IEEE]) @AB
```


# About

## Symbol Links

There are so many **symlinks** in this repo, so you better clone this repo in linux system, if windows, oops. You'd better use `make check`(or `./scripts/broken-symlinks.sh`) check invalid links and modify them.

## Ignore

This repo ignore file(check `.gitignore`). If you want to write a text `Note`, use `.md`(`markdown`).

## Reference

* linux-6.14.2 (fedora40,fedora41,fedora42)
* linux-5.15.0
* linux-5.14.0
* linux-5.10.13


# APIs

## POSIX (Portable Operating System Interface of UNIX)

see [posix/README.md](posix/README.md).

## System V

**System V**, also known as **System V Release**, is one of the versions of the Unix operating system. Below are the key standard versions of System V:

- `System V Release 1 (SVR1) (1983)`: Initial release by `AT&T`, derived from `UNIX System III`.
- `System V Release 2 (SVR2) (1984)`: Introduced demand paging, filesystem enhancements, and improvements in memory management.
- `System V Release 3 (SVR3) (1987)`: Introduced new IPC mechanisms, improved file system performance, and virtual memory improvements.
- `System V Release 4 (SVR4) (1989)`: Unified features from BSD, Xenix, and SunOS, support for TCP/IP, virtual file system (VFS), and improved inter-process communication.
- `System V Release 5 (SVR5) (1997)`(as UnixWare 7): Enhanced scalability, better file system support, improved networking capabilities, and enhanced security features.

System V has evolved through multiple standard versions, each adding significant improvements and features to the Unix operating system. The most notable versions include SVR1, SVR2, SVR3, SVR4, and SVR5, with **SVR4 being a major milestone due to its unification of features from various Unix variants**.


# Function Name

If glibc/posix/syscall already have name `a`, The function test-linux implemented is name `tl_a`(the `tl_` prefix).


# License

If the source code file has a copyright information at the beginning, the copyright of the source code is the description content, otherwise, it is the copyright of the test-linux repository.


# Links

## Linux

- [The Linux Kernel Archives](https://www.kernel.org/)
- [Linux Foundation: Referenced Specifications](https://refspecs.linuxfoundation.org/)
- [LSB: Linux Standard Base](https://refspecs.linuxfoundation.org/lsb.shtml)
- [vger.kernel.org](https://subspace.kernel.org/vger.kernel.org.html)
	- [lore.kernel.org/lkml](https://lore.kernel.org/lkml/)
- [elixir.bootlin.com](https://elixir.bootlin.com/linux/latest/source)
- [www.kernel.org/doc/html/latest](https://www.kernel.org/doc/html/latest/)
- [Contributors to the Linux Kernel](https://cregit.linuxsources.org/)
- [KernelCI](https://kernelci.org/)
- [linaro LKFT](https://qa-reports.linaro.org/lkft/)
- [kerneltests](https://kerneltests.org/)
- [kernel/map](https://makelinux.github.io/kernel/map/)
	- [github.com/makelinux](https://github.com/makelinux/linux_kernel_map)
- linux git
	- [github torvalds](https://github.com/torvalds/linux)
	- [git.kernel.org stable](git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git)
	- [git.kernel.org torvalds](git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git)
	- [mirrors.kernel.org](https://mirrors.kernel.org/)

## Relative Projects

- [linux-test-project](https://github.com/linux-test-project/ltp)
- [unpbook/unpv13e](https://github.com/unpbook/unpv13e)

## Relate Repos

* [GitHub test-linux(Me)](https://github.com/Rtoax/test-linux)
* [Gitee test-linux(Me)](https://gitee.com/rtoax/test-linux)

## Tools

- [asciiflow](https://asciiflow.com/#/)
- [monosketch](https://app.monosketch.io/)
	- [github](https://github.com/tuanchauict/MonoSketch)
- [drawio](https://github.com/jgraph/drawio-desktop)
	- [releases](https://github.com/jgraph/drawio-desktop/releases)
- [IDA](https://hex-rays.com/ida-free)
	- [Download Center](https://my.hex-rays.com/dashboard/download-center/)

## Standard

- [IEEE](https://www.ieee.org/)
