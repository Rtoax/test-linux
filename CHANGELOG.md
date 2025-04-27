# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## Unreleased

#### Breaking Changes
#### Added
- instructions/examples: Add compiler.h
- module: Add info.sh and kmod/ directory.
- instructions: Add asm 'ret' test.
- gdb: Add info-address.gdb
- c: Add return.c
- syscall/module: Add `init_module(2)` and `finit_module(2)` tests
- syscall/module: Add `mod_helpers.c` and test `create_module(2)` for linux v2.6
- module: Test linux/vermagic.h `VERMAGIC_STRING`
- Add openssl.mk
- Add distributions UOS
- OpenSSL add md5 samples
- Support Fedora Linux 42
- Add depends screenshot software shutter
- Add more aarch64 elf/rela tests
- Add compiler/force-cflags.mk
#### Changed
#### Deprecated
#### Removed
#### Fixed
- Fix lots of `__attribute__` warnings
- argp.h: Remove VERBOSE from `struct argp_option`
#### Security
#### Docs
- Add COMPILE.md and modify README.md
#### Tools

## [v2.2.10-rc2] 2025-04-23
## [v2.2.10-rc1] 2025-04-17
