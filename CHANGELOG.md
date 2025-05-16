# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## Unreleased
#### Breaking Changes
#### Added
#### Changed
#### Deprecated
#### Removed
#### Fixed
#### Security
#### Docs
#### Tools

## [v2.2.10] 2025-05-16

#### Breaking Changes
#### Added
- cpp: Add std::format test.
- macros: Test **-std=c++20** for `__cplusplus`.
- distributions: add abbreviation.md.
- Top Makefile add kconfig target to display all kconfig.
- network: add symlink qdisc to qdiscs.
- compiler: add libasan directory.
- storage: add info.sh
- algorithm/list/modules: Add os.h
- algorithm: Symlink hlist,llist to list, add symlink md5/openssl.
- compiler/attribute: Add `patchable_function_entry` and `hotpatch`.
- interrupt: Add `tracing_irq.sh` and msi directory.
- Add LTTng.
- time: add modules/{msleep.c,mdelay.c} test.
- rcu: Add info.sh, `{urcu,liburcu}`, modules/stall.c(symlink to sched/softlockup/modules), kconfig and scripts/`check_cpu_stall.bt`.
- synchronization: Add abbreviation.md
- shell: Add commands/dmesg directory.
- kernel.mk: add kuapi functions and macros `KUAPIVERSION`,`KUAPIPATCHLEVEL`,`KUAPISUBLEVEL`,`KUAPIVERSION_CODE`.
- libbpf: Test `bpf_rbtree_{add_impl,first,remove}` kfuncs helpers.
- lvm: Add create2.sh to test lv name length of df -hT.
- pahole: First commit (add Makefile, pahole.mk).
- libbpf: Test `BTF_KIND_DECL_TAG` (17).
- glibc/ucontext: Add setcontext.c
- pthread: samples: Rename `helpers.c` to `pthread_helpers.c`
- syscall: fork: Rename `helpers.c` to `fork_helpers.c`
- syscall: sched: Rename `helpers.c` to `sched_helpers.c`
- instructions/examples: Add compiler.h
- module: Add info.sh, kconfig and kmod/ directory.
- instructions: Add asm 'ret' test.
- gdb: Add info-address.gdb
- c: Add return.c, string.c, argv.c
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
- Move smt/ into sched/.
- libbpf: Move `libbpf_print_fn()` to `trace_helpers.c`.
- lvm: create.sh: Test with loop device and add to sub-dir.
- Change AUTHORS text format.
- Add the prefix of the corresponding project to the `helpers.c` file name.
- Move helpers from `pthread_helpers.c` to `sched_helpers.c`
- Move helpers from `instructions` to `pthread_helpers.c`
#### Deprecated
#### Removed
- modules/Makefile: Remove include tlbuild.mk.
- Makefile: Remove white lines in front of Makefile.
#### Fixed
- elf/reloc: Fix typos
- Fix lots of `__attribute__` warnings
- argp.h: Remove VERBOSE from `struct argp_option`
#### Security
#### Docs
- Add COMPILE.md and modify README.md
#### Tools

## [v2.2.10-rc4] 2025-04-30
## [v2.2.10-rc3] 2025-04-28
## [v2.2.10-rc2] 2025-04-23
## [v2.2.10-rc1] 2025-04-17
