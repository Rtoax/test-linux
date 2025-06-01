Test-Linux Compile
==================

The purpose of compilation is to compile the code of this directory and subdirectories directly in each level of directory.

## Config First

```
$ make config
```

## Install depends

```
$ make installdeps
```

## Compile User

> You'd better compiled under git-repo, because some Makefile use 'git rev-parse --show-toplevel' get top-dir.

```bash
$ make user
```

Compile with `-m32`:

```bash
$ make user M32=1
```

Compile with verbose:

```
$ make user V=1
```

## Create Makefile

You should better use `template/main.mk`.
