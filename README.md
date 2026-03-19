Test-Linux README
=================

# Relative Architecture

- [x] `x86_64`
- [x] `aarch64`
- [x] `sw_64`
- [ ] `riscv64`
- [ ] `loongarch64`


# Test Linux Development

## Sub-Directories

* Each `scripts` directory contain scriptions(bpftrace, bcc, shell).
* Each `modules` directory contain Linux Modules(KO) source code.
* Each `samples` directory contain source userspace code.
* Each `commands` directory contain relative command lines.
* Each `images` directory contains relative images.


## Files

* Each `README.md` is current directory's description.
* Each `FAQ.md` is current directory's FAQs.
* Each `abbrev.md` is current directory's relative abbreviation.
  - scripts: `./abbrev.sh` to check all abbreviations.
* Each `history.md` is store history of some technology.
* Each **drawio** contains relate directory diagrams.
* Never call `include` in `*.mk` file, only call `include` in Makefile.
* Each `kconfig` contains kernel CONFIG, each CONFIG is placed in the kconfig of the corresponding directory, and the public CONFIG is placed in the kconfig of the top-level directory.
  - scripts: `./kconfig.sh` to check all kernel config;
* Each `*_helpers*` is helpers program/script of current directory, better `LGPL-2.1 OR BSD-2-Clause` license.
* Each `requirements.txt` is Python pip --requirement for each directory.
* Ignore file (check `.gitignore`).
* If you want to write a text `Note`, use `.md`(`markdown`).
* There are so many **symlinks** in this repo, so you better clone this repo in linux system, if windows, oops. You'd better use `make check`(or `./scripts/broken-symlinks.sh`) check invalid links and modify them.


## Standard

- [IEEE](./ieee/README.md)
- [ISO](./iso/README.md)
- [POSIX](./posix/README.md)
- [System V](./svr/README.md).


# Miscs

It seems that I have also added some **GPU** and **AI** related content, which is less related to Linux, but most of it is still part of the Linux ecosystem.


# License

If the source code file has a copyright information at the beginning, the copyright of the source code is the description content, otherwise, it is the copyright of the test-linux repository.

If the code does not specify, then it follows **GPLv3**.

BPF programs always follow **GPLv2**.

The copyright line format must be `Copyright (C) Year-Year Author`.


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

- [linux-test-project/ltp](https://github.com/linux-test-project/ltp)
- [unpbook/unpv13e](https://github.com/unpbook/unpv13e)
- [GitHub mirror of test-linux](https://github.com/Rtoax/test-linux)
- [Gitee mirror of test-linux](https://gitee.com/rtoax/test-linux)

## Tools

- [asciiflow](https://asciiflow.com/#/)
- [monosketch](https://app.monosketch.io/)
  - [github](https://github.com/tuanchauict/MonoSketch)
- [drawio](https://github.com/jgraph/drawio-desktop)
  - [releases](https://github.com/jgraph/drawio-desktop/releases)
- [IDA](https://hex-rays.com/ida-free)
  - [Download Center](https://my.hex-rays.com/dashboard/download-center/)
