test-linux
==========

> Rong Tao <rtoax@foxmail.com>
> more about auther see AUTHOR file.
> You must clone this repo under Linux(UNIX like) system. Because
> there are lots of symbol links, some file system not support in
> Windows OS.
>
> In directory `modules` store some API demos.
> You'd better don't rename any of folder and file's name.


# Linux Kernel Git

* [https://github.com/torvalds/linux](https://github.com/torvalds/linux)
* [git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git](git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git)
* [git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git](git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git)


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


# About

## Links

There are so many LINKs in this repo, so you better clone this repo
in linux system, if windows, oops.


## Ignore

This repo ignore `.txt` file(check `.gitignore`). If you want to write
a text `Note`, use `.md`(`markdown`) instead.


## Reference

* linux-5.10.13
* linux-5.14.0
* linux-5.15.0 ~ ?


# Licenses

* https://spdx.org/licenses/


# Links

## Projects

- [https://github.com/linux-test-project/ltp](https://github.com/linux-test-project/ltp)

