test-linux
==========

This code repository contains **GNU/Linux** related test case codes, scripts and knowledge points, as well as operating system related content.

I'd rather name the repository test-gnu-linux, but it's too late to regret it, because I should have referenced the name test-linux somewhere else, like **ostools**.

You must clone this repo under **Linux(UNIX like)** system. Because there are lots of symbol links, some file system not support in Windows OS.

> You'd better don't rename any of folder and file's name, because of symlinks.


# Linux Kernel Git

* [https://github.com/torvalds/linux](https://github.com/torvalds/linux)
* [git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git](git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git)
* [git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git](git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git)


# Relative Architecture

- [x] `x86_64`
- [x] `aarch64`
- [x] `sw_64`
- [ ] `riscv64`
- [ ] `loongarch64`


# Relate Repos

* [GitHub test-linux(Me)](https://github.com/Rtoax/test-linux)
* [Gitee test-linux(Me)](https://gitee.com/rtoax/test-linux)


# Linux Version

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


# Directories

* Each `scripts` directory contain scriptions(bpftrace, bcc, shell).
* Each `modules` directory contain Linux Modules(KO) source code.
* Each `selftests` directory from linux source code.
* Each `samples` directory contain source userspace code.
* Each `commands` directory contain relative command lines.


# Files

* Each `README.md` is current directory's description.
* Each `abbreviation.md` is current directory's relative abbreviation.
	- format: **abbreviation: full name (中文全称) @relate1 @relate2**
	- scripts: `./abbreviation.sh` to check all abbreviations.

## abbreviation.md example

```
- AB: A Ball (一个球)
- ABC: A Ball Circle (一个球圈) @AB
```


# Defaults

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

Compile all userspace code with `make user`.


# Links

## Licenses

- [https://spdx.org/licenses/](https://spdx.org/licenses/)

## Projects

- [https://github.com/linux-test-project/ltp](https://github.com/linux-test-project/ltp)
- [https://github.com/unpbook/unpv13e](https://github.com/unpbook/unpv13e)

## Linux

- [https://www.kernel.org/](https://www.kernel.org/)
- [https://elixir.bootlin.com/linux/latest/source](https://elixir.bootlin.com/linux/latest/source)
- [https://lore.kernel.org/lkml/](https://lore.kernel.org/lkml/)
- [https://www.kernel.org/doc/html/latest/](https://www.kernel.org/doc/html/latest/)
