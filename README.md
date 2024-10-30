test-linux
==========

This code repository contains **GNU/Linux** related test case codes, scripts and knowledge points, as well as operating system related content.

I'd rather name the repository test-gnu-linux, but it's too late to regret it, because I should have referenced the name test-linux somewhere else, like **ostools**.

You must clone this repo under **Linux(UNIX like)** system. Because there are lots of symbol links, some file system not support in Windows OS.

> 1969: UNIX born at Bell Labs (AT&T).
> You'd better don't rename any of folder and file's name, because of symlinks. If you rename/move/update/remove path/directory, you need to run **make check** under top-dir and fix the invalid-symlinks.

It may be that the repository will contain **desktop-related** test code, such as **GNOME**, but that is not the main purpose of the repository. Perhaps researching the **GUI** is also the purpose of this repository, such as **GTK**.


# Linux Kernel Git

* [https://github.com/torvalds/linux](https://github.com/torvalds/linux)
* [git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git](git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git)
* [git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git](git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git)


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


## Linux Version

`linux >= 5.0`, some time 5.14 will successful.
You can use the following macro

```c
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 15, 0)
	[...]
#else
	[...]
#endif
```


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


## Linux Licenses

See [Linux kernel licensing rules](https://www.kernel.org/doc/html/latest/process/license-rules.html).


# test-linux

## Relative Architecture

- [x] `x86_64`
- [x] `aarch64`
- [x] `sw_64`
- [ ] `riscv64`
- [ ] `loongarch64`


## Relate Repos

* [GitHub test-linux(Me)](https://github.com/Rtoax/test-linux)
* [Gitee test-linux(Me)](https://gitee.com/rtoax/test-linux)


## sub-Directories

* Each `scripts` directory contain scriptions(bpftrace, bcc, shell).
* Each `modules` directory contain Linux Modules(KO) source code.
* Each `selftests` directory from linux source code.
	- Normally there is no need to sync from Linux upstream.
* Each `samples` directory contain source userspace code.
* Each `commands` directory contain relative command lines.


## Files

* Each `README.md` is current directory's description.
* Each `abbreviation.md` is current directory's relative abbreviation.
	- format: **abbreviation: full name (中文全称) @relate1 @relate2**
	- scripts: `./abbreviation.sh` to check all abbreviations.
* Each **drawio** contains relate directory diagrams.


## abbreviation.md example

```
- AB: A Ball (一个球)
- ABC: A Ball Circle (一个球圈) @AB
```


## Defaults

- `SHELL`: `bash`


# About

## Symbol Links

There are so many **symlinks** in this repo, so you better clone this repo in linux system, if windows, oops. You'd better use `make check`(or `./scripts/invalid-link.sh`) check invalid links and modify them.


## Ignore

This repo ignore file(check `.gitignore`). If you want to write a text `Note`, use `.md`(`markdown`).


## Reference

* linux-5.10.13
* linux-5.14.0
* linux-5.15.0 ~ ?


# APIs

## POSIX

## System V


# Function Name

If glibc/posix/syscall already have name `a`, The function test-linux implemented is name `tl_a`(the `tl_` prefix).


# Compile

## Install depends

Install depends with `make installdeps`.

## Compile User

```
make user
```

Compile with `-m32`:

```
make user M32=1
```


# Links

## Licenses

- [https://spdx.org/licenses/](https://spdx.org/licenses/)


## Linux

- [The Linux Kernel Archives](https://www.kernel.org/)
- [vger.kernel.org](https://subspace.kernel.org/vger.kernel.org.html)
	- [https://lore.kernel.org/lkml/](https://lore.kernel.org/lkml/)
- [https://elixir.bootlin.com/linux/latest/source](https://elixir.bootlin.com/linux/latest/source)
- [https://lore.kernel.org/lkml/](https://lore.kernel.org/lkml/)
- [https://www.kernel.org/doc/html/latest/](https://www.kernel.org/doc/html/latest/)
- [Contributors to the Linux Kernel](https://cregit.linuxsources.org/)
- [KernelCI](https://kernelci.org/)
- [linaro LKFT](https://qa-reports.linaro.org/lkft/)
- [kerneltests](https://kerneltests.org/)


## Relative Projects

- [https://github.com/linux-test-project/ltp](https://github.com/linux-test-project/ltp)
- [https://github.com/unpbook/unpv13e](https://github.com/unpbook/unpv13e)


## Tools

- [drawio](https://github.com/jgraph/drawio-desktop)
