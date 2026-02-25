Test-Linux Quick Start
======================

The purpose of this document is to compile the code of this directory and subdirectories directly in each level of directory.

## Git Config

```bash
$ make gitconfig
```

## Install depends

```bash
$ sudo make deps
```

## Config

```bash
$ make config
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

```bash
$ make build V=1
```

Stop immediately when an error occurs:

```bash
$ make build CHECK_ERROR=1
```

## Create Makefile

You'd better use `template/main.mk`.
