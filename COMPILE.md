Test-Linux Compile
==================

The purpose of compilation is to compile the code of this directory and subdirectories directly in each level of directory.

## Config First

```
$ make config
```

## Install depends

```
$ sudo make installdeps
```

## Compile in Top Directory

> You'd better compiled under git-repo, because some Makefile use 'git rev-parse --show-toplevel' get top-dir.

```bash
$ make build
```

Compile without kernel modules:

```bash
$ make build KMOD=0
```

Compile with `-m32`:

```bash
$ make build M32=1
```

Compile with verbose:

```
$ make build V=1
```

## Create Makefile

You should better use `template/main.mk`.
