# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## Unreleased
#### Breaking Changes
#### Added
- libvirt: Add pci xml demos.
- qemu/libvirt: Test cxl persistent,volatile memory.
- kmod: Add libkmod test directory.
- systemd: Add udev.
- network: Add mctp directory.
- cxl: Add kconfig, abbreviation.md, history.md, libcxl, qemu/cxl/.
- mm: Add README.dimm.md.
- blazesym: Introduce and add capi/compile.
- libbpf: Add test `ring_buffer`,`perf_buffer` symlink.
- libbpf: Test `bpf_loop()` helper.
#### Changed
- main.mk: Rename `TARGETS_PRE` to `TARGETS_PREP`.
#### Deprecated
#### Removed
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.2.12] 2025-06-06

#### Breaking Changes
- template: introduce main.mk, and all Makefile should use main.mk.
- pmem: Introduce (and libpmem).
- pxe: Introduce from ostools.
- libvirt: Introduce from ostools.
- top-Makefile: Apply sub-dir to user targets.
- bpf/libbpf: compile with -std=gnu89.
#### Added
- signal: Test `sigabbrev_np()`.
- libbpf: Add `skel_defs.h`.
- libbpf: Add `BPF__OPEN_AND_LOAD()` macro.
- libbpf: add `bpf_experimental.h` from linux upstream.
- libbpf: Test `bpf_get_task_exe_file()/bpf_path_d_path()` in lsm.
- libbpf: Test spin lock and add wrapper `libbpf_bpf_map_update_elem()`.
- template: Add target-liba.mk,target-libso.mk,target-exe.mk,main.mk,target-output.mk.
- bpf: test `bpf_task_cwd_from_pid()`.
- fs/modules: add getcwd.c get task cwd from pid.
- scripts/git: add bigfile.sh, statistic.sh, statistic.py from ostools.
- shell: add align.sh, alias.sh.
- cpp: Test `std::weak_ptr expired()`.
- tkill(2): add tkill.c demo.
- tgkill(2): add tgkill.c demo.
- flock(2): add `flock_helpers.c`.
- qemu: qcow2: Parse qcow2 file.
- libvirt: add memory directory.
- initrd: Add minimal image from ostools.
- install-deps.sh: add --srvs argument.
- elf/plt: add overwrite-plt.c.
- linker-script: Test multi scripts(.text+.data).
- nvdimm: Introduce, kconfig, ndctl/dax.md.
- network/9p: Introduce.
- virtio/9p: Introduce.
- virtio/fs: Introduce.
- distributions: add sources.list.d,yum.repos.d from ostools.
- add admin.sh,password.sh from ostools.
- coredump: add dump.sh.
- kata-containers: Add config-kata.toml, deploy.sh and create.sh.
- opcode: Add samples.
#### Changed
- libbpf: wrapper use `libbpf_` prefix instead of `tl_` prefix.
- Move libs/proc.c to `fs/procfs/proc_helpers.c`.
- Move libs/qemu.sh to qemu/libqemu.sh.
#### Deprecated
#### Removed
- libbpf: remove macro `STRICT_SEC_NAME`.
#### Fixed
#### Security
#### Docs
#### Tools
- Install firecracker.
- Add patchset.sh examples scripts.


## [v2.2.11] 2025-05-21

#### Breaking Changes
#### Added
- kata-containers: First commit.
- procfs: add mounts.sh.
- cpp: try test fmtlib.
- cgroup: Support sub-dir.
- add posix sub-directory.
- scripts: add ascii.mk.
- vsock: samples,kconfig and add link to qemu/virtio/vhost.
- scripts: Add kconfig_compare.sh to compare kernel config file.
- ipc/socket/syscall: add socket.bt
- netlink: Add samples/NETLINK_KOBJECT_UEVENT.c
- syscall/samples: Add close(2) test.
- errno: Add test EAFNOSUPPORT.c
- rootfs,initrd: add qemu.sh
- c: add C standard comment, and test c17,c98,c++98,gnu++98.
- libbpf: parse auxv in bpf prog.
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
