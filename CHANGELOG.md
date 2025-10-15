# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## Unreleased

#### Breaking Changes
- cuda/samples: Rename code to remove cuda,hip,hc prefix;
#### Added
- cuda/intrinsics: add double.cu;
- bpftrace/samples: add auxv.bt;
- cuda/intrinsics: add test bfloat16.cu;
- ubuntu: add sources.list.d/ubuntu25.04.sources;
- make: add MAKECMDGOALS.mk, filter-out.mk;
- rootfs: add multistrap.sh to build rootfs for ubuntu;
#### Changed
- cuda/samples: Rename cudaGetDeviceProperties.cu to properties.cu;
- Move rootfs/qemu.sh to qemu/qemu-vm.sh;
#### Deprecated
#### Removed
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.8] 2025-10-10

#### Breaking Changes
#### Added
- amd/rocm: introduce RCCL;
- nvidia: introduce NCCL;
- rccl: try test ncclGetVersion.hip;
- nccl: try test ncclGetVersion.cu;
- trace: add kconfig;
- cuda: add `cuda_compat.h`;
- hpc/nvidia/cuda/intrinsics/ support HPCC, HIP;
- Add hpc/nvidia/cuda/intrinsics/;
- Makefile: add config target to no interaction configuration;
- nvidia: add ptx/;
- amd: add amdgcn/;
- c: add `__bf16.c`;
- clang: plugins: add pid.cpp;
- fakeCUDA/frontend: add attribute-device.cpp, attribute-global.cpp;
- add scripts/dialog/config.sh;
- sw: add README.md;
- fakeCUDA: add fakeCUDA/frontend;
- compiler: add plugins;
- Add zluda;
- Add ieee/;
- Add init/kernel/cmdline.md;
#### Changed
- hpc: compile cuda/samples for ROCm HIP directly, not use symlink;
- oom: add adaptive-oom-score sub-dir;
- kernel.mk: Rename kernel version compare functions.
- cuda/samples: all apply `cuda_compat.h`;
- fakeCUDA: Move compat.hpp to cuda/`cuda_compat.h`;
- Move kernel.mk into template/;
- menuconfig: rename scripts/dialog/main.sh to scripts/config/dialog.sh;
- hpc: Rename `HAVE_HCCL` to `HAVE_HPCC`;
- targets: don't use `LD_LIBRARY_PATH` CC PFX;
- kconfig.mk: Move it into template/;
#### Deprecated
#### Removed
- Remove Dockerfile of test-linux and docker target of Makefile;
- hpc: remove HAVE_HCCL;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.7] 2025-09-22

#### Breaking Changes
#### Added
- fakeCUDA: add libhipblas.map, libhipblaslt.map;
- template: add sudo.mk;
- bpf: test map-in-map;
- fakeCUDA: hip: add libhipsparse.so.1 librocsparse.so.1;
- fakeCUDA: hip: add libhipfft.so.0 and librocfft.so.0;
- fakeCUDA: add libcublas.so.12 and cublasGetStatusString();
- libbpf: add string_helpers.bpf.h;
- fakeCUDA: support ROCm HIP;
- fakeCUDA: add libamdhip64.map;
- targets: add amd.mk;
- amd: add ROCm samples;
- fakeCUDA: add device-mars-x203.h;
- targets/nvidia.mk: add .nv_fatbin and .nvFatBinSegment targets;
- fakeCUDA: add fatbin.hpp, fatbin.cpp, fatbin-hip.hpp;
- fakeCUDA: add runtime.hpp;
- fakeCUDA: add utils.cpp;
#### Changed
- fakeCUDA: only extern "C" in header;
#### Deprecated
#### Removed
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.6] 2025-09-18

#### Breaking Changes
- Rename synchronization/ to sync/;
- Rename instructions/ to insn/;
- template: add targets directory and move all target mk into it;
- Makefile: Rename target installdeps to deps;
#### Added
- fakeCUDA: add hccl.cpp;
- fakeCUDA: add libhcblas.map,libhcblasLt.map,libhccl.map,libhcfft.map,libhcrand.map,libhcruntime.map,libhcsparse.map;
- fakeCUDA: add libhccompiler.map for hpcc;
- targets/libso.mk: support C++;
- hpc: add ROCm;
- metax: add hpcc.mk from template/targets/metax.mk;
- cuda: add cuda.mk;
- fakeCUDA: add libcudart.map, libcusparse.map, libcufft.map, libcublas.map, libcublasLt.map, libcuda.map, libcurand.map;
- linker: add libhello.map and test --version-script;
- cuda: add fakeCUDA;
- tmux: add tmux.md;
- tools: add trans/trans.sh;
- xmllint: Add from ostools;
- python: add crypt/password.py;
- storage: add disk_helpers.sh;
- cloud-native: add kubernetes;
- scripts/git: add config.sh from ostools;
- qcow2: add qcow2-extend.sh;
- kata-containers: add kylin from ostools;
- kata-containers: add kata-agent-kmod.sh from ostools;
- tools: add fstabd from ostools;
- tools: add samba directory;
- shell: add mpstat;
- initramfs: add README.md;
- shell: add genisoimage from ostools;
- tools: add heatmap/ from ostools;
- network: add http directory;
- network: add dhcp directory;
- network: add bond config example;
- network: Add snmp directory and speed from ostools;
- qcow2: add guestmount.sh from ostools;
- openssh: add scripts from ostools;
- shell/commands: add sar, nmcli directory;
- Add tcp-sysrq-trigger/ from ostools;
- dir.mk: add CURDIR;
- opencv: Introduce;
- linker: add LD_SHOW_AUXV.sh;
- hpc: add gpu/abbrev.md;
- kunlunxin: add info.sh;
- hpc/kunlunxin: Introduce;
#### Changed
- fakeCUDA: Swap to C++, use g++ compile it;
- fakeCUDA: adaptive to hpcc 3.0.0;
- ftrace: Move mcount-nop.c to ftrace/samples/;
- ftrace: Move ftrace/demos to ftrace/samples;
- targets/nvidia.mk: split some code to cuda.mk;
- cuda_adapter.h: Rename macros __pfx and __PFX to __cu,__CU;
- linker: Rename linker-script to script;
- Move SR-IOV into virt/;
- systemtap: Move to tools/;
- kconfig: split CONFIG to seperate files;
#### Deprecated
#### Removed
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.5] 2025-09-05

#### Breaking Changes
#### Added
- metax: add hcTracer.sh;
- cuda_helpers: add cufft_version(), cusparse_version() API;
- python: add scipy/fft.py;
- hpc: add fft.cu, sparse.cu demo;
- svr: add svr directory;
- Add debug/kconfig;
- Add virt directory;
- kgdb: add kconfig;
- bpftrace: add macro.bt test;
- target-metax.mk: support .devbin and .fatbin target;
- target-nvidia.mk: support .cubin and .fatbin target;
- hpc: add amd/README.md;
- cuda_helpers: add gpu_compute_cap_str();
- template: add os.mk;
- kinstall: Install init/kernel/install.sh to /usr/bin/kinstall;
- cuda: add cudaMallocManaged.cu, module.cu;
- oom: add `oom_minimal.c`;
#### Changed
- cuda: Rename cuda2hccl.h to cuda_adapter.h;
- Update top README.md;
#### Deprecated
#### Removed
- nvidia: Remove README.benchmark.md;
- bpftrace: remove runqlat.bt;
- pthread/samples: Remove `sys_affinity_bind.c`, `create_thread.h`;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.4] 2025-09-01

#### Breaking Changes
#### Added
- hpc: blas: add blas-md5.sh, matrix-md5.sh;
- python/numpy: add array test;
- keras: Train MNIST with keras;
- python: add numpy;
- pthread: move `pthread_helpers` to top pthread directory;
- ai: Introduce tensorflow, mnist, keras;
- glibc/string: test strspn.c and strcspn.c;
#### Changed
- main.mk: add PIE cflags/ldflags from pie.mk;
- template: Rename target-cuda.mk to target-nvidia.mk;
- template: Rename topdir.mk to dir.mk;
- pthread/samples: Remove `pthread_` prefix of source code;
#### Deprecated
#### Removed
- pie.mk: Remove cflags/ldflags;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.3] 2025-08-22

#### Breaking Changes
#### Added
- pytorch: Added;
- libbpf: add symlink `ksym_helpers` and apply to stack;
- aslr: add info.sh;
#### Changed
- Makefile: rename target config to gitconfig;
- template: mk: Define DEBUG=${DEBUG}
#### Deprecated
#### Removed
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.2] 2025-08-19

#### Breaking Changes
#### Added
- cuda: add cooperative.cu;
- ksym: add kallsyms/ksym_helpers.c;
- security: add openssh;
- bpf: add wordcloud from ostools;
- metax/samples: add __GNUC__ and __STDC__ test;
- HPC: add README.GPU.md;
- coredump: add info.sh;
- sched_ext: add kconfig;
- metax: add smi.sh;
- template: add arch.sh, cpu.sh, topdir.mk, git.mk, verbose.mk;
- debian: add upgrade.sh;
- fedora: add upgrade.sh;
- ubuntu: add upgrade.sh;
#### Changed
#### Deprecated
#### Removed
- remove tlbuild.mk;
- remove tlconfig;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.1] 2025-08-12

#### Breaking Changes
#### Added
- ipc: introduce iovec_helpers.c;
- ipc/socket/iovec: remove send_fd() and recv_fd() from socketpair.c;
- metax: add more htvs benchmark results;
- c: add float.c;
- instructions: add breakpoint.h;
- interrupt: add cli.c;
- mm: add scripts/`handle_mm_fault.bt`;
- template: add log.mk;
- Add INSTALL.md;
- kmod: add kcompile.mk;
- bpf: add kconfig;
- btf: add kconfig;
- btf: parse kernel structure;
- bpf: add pure userspace code tcpdump.c;
- kprobe: add README.md;
- scripts: add termplot.sh;
#### Changed
- Rename all abbreviation.md to abbrev.md;
- make,script: Remove sudo from scripts;
#### Deprecated
#### Removed
- bpftool: remove vmlinux.h.mk;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.0] 2025-08-06

#### Breaking Changes
#### Added
- hpc: add README.benchmark.md;
- oom.c: support memory cgroup limit, and add global env;
- libcgroup: add libcgroup.mk;
- procfs: add sysrq-trigger tool;
- `proc_helpers`: Rename `proc_for_each_mnt_point()` to `proc_for_each_mount()`;
- cgroup: add `cgroup_helpers`;
- gtk: add deepseek.c;
- module: add license direcory;
- cuda: nvcc: display __GNUC__ and __STDC__;
- hpc: blas: fp32+fp64 at the same time, and remove symlink blas-double;
- metax: Symlink `hpcc_helpers` to `cuda_helpers`;
- cuda: add cudaEvent.cu;
- metax: add symlink hcEvent.hpcc;
- hpc: `gpu_name()` add `dev_id` param;
#### Changed
- hpc: Rename matrix-mul to matrix;
#### Deprecated
#### Removed
- oom: remove symlink popen.c;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.2.19] 2025-07-29

#### Breaking Changes
- mk: All targets use small case words, this is a big change;
#### Added
- ascend: add abbreviation.md;
- metax: add hcGetDeviceProperties.hpcc, cuda2hccl.h, hcDeviceGetAttribute.hpcc, hcDeviceGetP2PAttribute.hpcc, blas.hpcc, symlink dim3.hpcc, matrix-mul-int8.hpcc, matrix-mul-fp16.hpcc, rand.hpcc;
- cuda: add dim3.cu, symlink cudaDeviceGetP2PAttribute.cu, matrix-mul.sh, matrix-mul-double.cu, matrix-mul-int8.cu, blas.cu;
- nvidia: add README.Nsight.md from ostools, add rand.cu;
#### Changed
#### Deprecated
#### Removed
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.2.18] 2025-07-20

#### Breaking Changes
#### Added
- c: add approaching.c;
- make: add filter.mk;
- wayland: add info.sh;
- X11/Xorg: Introduce;
- metax: add ht-envs.sh to set ENVs of hpcc, add abbreviation.md, parallel.hpcc, hcclGetVersion.hpcc, `hpcc_helpers.hpcc`, hcMalloc.hpcc, matrix-mul.hpcc;
- hpc: add metax/ directory;
- cuda: add driver-version.c from ostools, add parallel.cu, cudaMalloc.cu, `cuda_helpers.cu`, metax symlink matrix-mul.cu;
- compiler: Introduce OpenACC directory;
- ai: Introduce AI directory;
- git: add push-remote-all.sh, rm-permanent.sh from ostools;
- dnf: add cuda rhel9 yum repo;
#### Changed
- bpf: Move `libbpf/btf_helpers.c` to `btf/`;
#### Deprecated
#### Removed
#### Fixed
- OUTPUT must end with '/';
#### Security
#### Docs
#### Tools


## [v2.2.17] 2025-07-12

#### Breaking Changes
#### Added
- compiler: add jit/libgccjit/;
- syscall/samples: add `bpf/bpf_helpers.c`, bpf.bt;
- bpf: add history.md, c/foo.bpf.c, kfunc/modules/`bpf_task_cwd_from_pid.c`, README.ISA.md, tcpdump.bpf.c;
- qemu: add replay directory, symlink record.
#### Changed
- `socket_helpers`: Rename `open_raw_sock` to `socket_raw`;
#### Deprecated
#### Removed
- Remove `ipc/socket/raw/raw_helpers.c`, use `socket_helpers.c` instead;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.2.16] 2025-07-04

#### Breaking Changes
- Introduce scripts/dialog/main.sh;
#### Added
- glibc: test fread.c,sprintf.c;
- oom: introduce adaptive-oom-score tools, and test it;
- gdb/samples: add mmap-file.gdb to test mmap syscall, add signal.gdb, fcntl.gdb, mman.gdb;
#### Changed
- gdb/samples: use -x instead of `<` to pass gdb script;
#### Deprecated
#### Removed
- Remove libs/libs.mk;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.2.15] 2025-07-01

#### Breaking Changes
- Remove **user** and **kernel** target in main Makefile, use build,test,clean instead;
#### Added
- licenses: add BSD/BSD-2-Clause.txt;
- python: add import/log.py to test import from python source code;
#### Changed
- helpers: change license to (LGPL-2.1 OR BSD-2-Clause).
#### Deprecated
#### Removed
- Remove selftests directory.
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.2.14] 2025-06-30

#### Breaking Changes
- main.mk: all Makefile use main.mk;
- main.mk: cflags: default `-Werror -Wall -D_GNU_SOURCE -Wstrict-prototypes`.
#### Added
- distributions: add asterinas;
- make: test gnu/make/addsuffix.mk;
- foption: test -fsanitize=address for g++, test -fsanitize={leak,thread}, add libtsan.bt;
- go: Add C/malloc.go,mmap.go.
- pcie: add configuration-space and pciutils directory.
- make.list: add driver, python directory.
- cgroup/v1: add some controller.
- template: Add target-shell.mk, target-golang.mk, target-java.mk, target-libso.sh, target-python.mk, target-rust.mk, target-llvm.mk, target-cuda.mk, target-make.mk, target-bpf.mk;
#### Changed
- macro: support cross-compile.
- syscall: Use main.mk.
#### Deprecated
#### Removed
- Remove `bpf/tools/bpf_dbg.c`;
- Remove `bpf/socket/packet-filtering-raw-sockets/*`;
- Remove `bpf/samples/bpf_fs/`;
- Remove `arch/x86_64/asm/minilibc`;
- Remove `tracepoint/trace_events/samples/trace-events-sample.c`.
- Remove numa/numa.mk.
- Remove fs/procfs/procfs-lib-target.mk.
- Remove tlconfig.
- Remove scripts/makefile-modify.sh.
- Remove rust/rust.mk.
- Remove `fprobe/samples/fprobe_example.c`.
- Remove go/go.mk.
- Remove compiler/force-cflags.mk, move FORCE to main.mk.
- Remove shell/shell-run.mk.
#### Fixed
#### Security
#### Docs
#### Tools

## [v2.2.13] 2025-06-19

#### Breaking Changes
- cxl: Support create vmem/pmem Qemu VM.
#### Added
- ntp: First commit.
- oom: add cgroup-oom.sh.
- rootfs/qemu.sh: support sata,nvme,virtio-blk,virtio-scsi.
- wayland: Add helloworld.c demo.
- python: add split.py,hexdump().
- libvirt: Add pci xml demos.
- qemu/libvirt: Test cxl persistent,volatile memory.
- kmod: Add libkmod test directory.
- systemd: Add udev.
- network: Add mctp directory.
- cxl: Add kconfig, abbreviation.md, history.md, libcxl, qemu/cxl/, CEDT/CHBS/CFMWS, cxl.sh.
- mm: Add README.dimm.md.
- blazesym: Introduce and add capi/compile.
- libbpf: Add test `ring_buffer`,`perf_buffer` symlink.
- libbpf: Test `bpf_loop()` helper.
#### Changed
- main.mk: Rename `TARGETS_PRE` to `TARGETS_PREP`.
#### Deprecated
#### Removed
- cxl: Temp remove driver directory.
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
