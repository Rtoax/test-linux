# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## Unreleased

#### Breaking Changes
- log.mk: `log_obj()` remove 2nd argument;
#### Added
- nvidia: add nvidia-smi subdir;
- lsof: first commit;
- psmisc: add fuser subdir;
- psmisc: first commit;
- gdb: add version.sh;
- gdb/samples: test detach-on-fork and follow-fork-mode;
- cpu: add cpuname.sh;
- sched/reparent: add parent-crash.c;
- sched: add reparent subdir;
- strace: add version.sh;
- prctl(2): test `PR_SET_PDEATHSIG`;
- procps-ng: add version.sh;
- procfs: add procps-ng subdir;
- cuda/{adapter,intrinsics}: support and test fp4;
- cuda/adapter: add empty `Openacc/cupti_openacc.h` and `Openmp/cupti_openmp.h`;
- cuda/{adapter,intrinsics}: support and test all cuComplex.h;
- macro: add splice.c;
- kickstart: add minimal.ks, efi.ks, bios.ks;
- anaconda: add kickstart subdir;
- anaconda: add product.img/ from ostools;
- distro: add anaconda subdir;
- scap: add openscap,oscap subdir;
- python: add blivet subdir;
- rust: add version.sh;
- template: add rust.mk;
- device-tree: add abbrev.md;
#### Changed
- rename COMPILE.md to QUICKSTART.md;
- move coredump into gnu/gdb/;
- move binfmt, criu, livepatch, `static_key` into tools;
#### Deprecated
#### Removed
- log.mk: remove `log_start()` and `log_end()`;
- log.mk: remove `log_exe()` and use `log_tgt()`;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.16] 2026-02-20

#### Breaking Changes
#### Added
- scripts: add history.sh from ostools;
- dnf: add repodiff.py,`gen_rootfs_img.sh` from ostools;
- rpm: add rpmcpy.sh from ostools;
- desktop: first commit;
- template: add gnome.mk;
- cuda/adapter: add nvml.h;
- cuda/adapter: add from `cuda_compat.h` and `cuda_adapter.h`;
- ostree: first commit;
- shell: add env-passing directory;
#### Changed
- kernel: rename kinstall.sh to compile.sh;
- main.mk: multi-suffix prog support 10 and introduce multi-suffix-n;
#### Deprecated
#### Removed
- Remove `cuda_adapter.h`;
- Remove `cuda_compat.h`;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.15] 2026-02-09

#### Breaking Changes
#### Added
- distro: add dnf/rpm directory;
- tigervnc: add server.sh from ostools;
- libguestfs: add guestmount/qcow2.sh, guestfish directory;
- raid: add boardcom/storcli/storcli.sh
- rootfs: add README.md;
- virt-install: add cdrom.sh and links;
- virt-manager: add virt-clone directory;
- tools: add libosinfo directory;
- gnu: add findutils directory;
- template: add compiler/{types,std,m32,check}.mk;
- targets/shell.mk: support `.sh.[1-9]` for test one shell for 10 times;
- cu-bridge: add metax2lingspeed.sh;
- distro: add README.md.check.sh;
- scripts: add kversion.sh, code-count.sh;
- template: add flags.mk;
- template: add nvidia/device.mk;
- podman: add privileged/reboot.sh;
- tools: add cri/crictl.sh
- tools: add containerd/containerd.sh;
- template: add rdma.mk;
- rdma: add kconfig;
- cuda: add cu-bridge and adapt to template/nvidia/cuda.mk;
- cuda/adapter: add cublas.h, cufft.h, cusparse.h, curand.h, cupti.h, cufile.h, nccl.h, cusolver.h, cudnn.h, nvrtc.h, `cuda_fp6.h`, `cuda_fp8.h`, `cuda_bf16.h`, `cuda_runtime.h`, cuda.h, `cuda_runtime_api.h`, `driver_types.h`;
- template/nvidia: add nccl.mk;
- luca: add cu-bridge-envs.sh;
- ai: add models/stella;
- qemu: add compile.sh, gdb.sh from ostools;
- ai: paddle: first commit;
- transformers: First commit;
- cmake: add version.sh, samples directory;
- template: add clang.mk, pytorch.mk, runprog.mk;
- pytorch: add compile script;
#### Changed
- template: Move bits/compiler-feature.mk to compiler/feature.mk;
- Move template/targets/libso.sh to scripts/libso-multiver.sh;
- Move vfs into fs directory;
- Move alternative directory into insn directory;
- Move aio directory into glibc;
- scripts/install-deps.sh: default install nothing;
- template: add nvidia,amd,metax,cestc directory;
#### Deprecated
#### Removed
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.14] 2026-01-26

#### Breaking Changes
- template: only include .mk once;
#### Added
- tput: add allcolor.sh test;
- template: add signum-{arch,generic}.mk;
- cgroup.mk: add `CGROUP_V1/CGROUP_V2`;
- template: add cgroup.mk;
- libcgroup.mk: add `HAVE_LIBCGROUP` and libcgroup-{cflags,ldflags};
- cgroup/v1: add cpu/chrt.sh to test chrt return EPERM;
- tools: add podman directory;
- pytorch: add build/Dockerfile.{fedora,debian};
- cuda: add vpu directory;
- cuda: add mempool.cu;
- cuda: add `cuda_kernel_misc.h`;
- gnome: add version.sh;
- tools: add conda directory;
- vllm: add build/ubuntu.sh;
- kmod: add dkms directory;
- uefi: add secureboot directory;
- sgx: add enclave(飞地) directory;
- openssl: add version.sh;
- template: add intel/linux-sgx.mk;
- security: add security/sgx directory;
- template: add bits/cpu-cache.mk;
- add `__USE_TEST_LINUX_MAKE__` to make definition;
- virt: add virttype.sh;
- add scripts/clang-format.sh from git/hooks/pre-commit;
- Add empty .clang-tidy;
- sglang: add README.md;
- pytest: add README.md;
- nvidia: add gpuname.sh;
- template: add fs/tracefs.mk;
- lingspeed: add gpuname.sh;
- glibc: add assert subdir;
- python: add cupy subdir;
#### Changed
- Rename distributions to distro;
- Move binutils into gnu directory;
- Move gdb into gnu directory;
#### Deprecated
#### Removed
- remove luca/luca-container.sh;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.13] 2026-01-11

#### Breaking Changes
- Obey the linux [.clang-format](https://raw.githubusercontent.com/torvalds/linux/master/.clang-format) rules;
#### Added
- template: add file.mk;
- template: add map.mk;
- add history.sh;
- add kconfig.sh;
- cuda/samples: add rtc.cu;
- luca: add cmake subdir;
- bpftool: add version.sh;
- distributions: add version.sh;
- llvm: add version.sh;
- template/bpf: add libxdp.mk;
- template/bpf: add xdp.mk;
- add .clang-format from https://raw.githubusercontent.com/torvalds/linux/master/.clang-format
- tools: add code-formatter from ostools;
- template: add gcc.mk;
- cuda/samples: add graph.cu;
- gcc: add version.sh;
- gnu: add gcc subdir;
- mm: add cim subdir;
- pahole: add version.sh;
- tools: add vim/version.sh;
- driver: add dri;
- abbrev: add GVM;
- qemu: add version.sh;
- qemu: add support-machine.sh;
- template: add lingspeed.mk;
- bpftrace: add bpftrace.vim;
- template: add targets/helpers.mk;
- template: add Makefile;
- compiler/builtin: add `__builtin_unreachable`;
- cupti: add version.cu;
- nvidia: add driver subdir;
- cupti: add range.cu;
- cupti: add sampling.cu;
- cupti: add activity.cu;
- cuda: add pti subdir;
- python: add pip subdir;
- shell/commands: add arp and ethtool subdir;
- template: add bits/compiler-feature.mk;
- template: add bits/cpu-feature.mk;
- memcpy-stress.c: add `__memcpy_aarch64_simd()`;
#### Changed
- template: move hpcc.mk,cuda.mk,lingspeed.mk,rocm.mk,luca.mk into gpu/;
- copyright 2026;
- template: rename values.mk to defined.mk;
- Move smp into cpu directory;
#### Deprecated
#### Removed
- remove all symlinks `cuda_compat.h`, `cuda_adapter.h`;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.12] 2025-12-17

#### Breaking Changes
- luca: Phase II project tested;
#### Added
- infiniband: add info.sh;
- nvidia: add gpuinfo.sh;
- pciutils: add version.sh;
- pcie: add libpcie.sh;
- git: add version.sh;
- add ai/vllm/nvidia-spark-docker.sh;
- numa: add memory.c from ostools;
- targets/shell.mk: support `SHELL_ENVS_`;
- Support target-bt-y;
- distributions: add kali;
- sysfs: add mounts.sh;
- fs: add sysfs to subdir;
- python/matplotlib: add 3d-demos.py;
- proc: add diskstats.sh;
- nvme: add nvme2pcie.sh;
- dma: add dmaengine directory;
- numactl: add version.sh;
- scripts: add update-copyright;
- gdsio: add `gdsio_awk.sh`;
- python/matplotlib: add 3d subdir;
- template: add libatomic.mk;
- cufile: add gpsio.cu;
- procfs: add Makefiles for subdirs;
- nccl: add `nccl_helpers.h`;
- cuda/file: compile for LUCA and HPCC;
- cuda/file: add hello.cpp test;
- nvidia: introduce GPUDirect Storage;
- nccl: add communicator.cu test;
- git/hooks/prepare-commit-msg: add bpftrace version if need;
- driver: add swiotlb;
- fakeCUDA: add libnccl.so.2, liblccl.so;
- fakeCUDA: add libcusolver.so.12, libhcsolver.so, liblcsolver.so, libhipsolver.so.0;
- fakeCUDA: add librccl.so.1;
- fakeCUDA: support LUCA phase II;
- ai: add os subdir;
#### Changed
- Move io-sched into storage;
- Move kprobes into trace directory;
- Move {ftrace,fentry} into trace directory;
- Move uprobes into trace directory;
- move tracepoint into trace directory;
- numa: move samples/ to numactl directory;
- Move vhost into virt directory;
- Move virtio into virt directory;
- compiler/atomic: remove prefix `__atomic_` of source code files;
- template/targets: rename nvidia.mk to cuda.mk;
- template/targets: rename amd.mk to hip.mk;
- template/targets: rename cestc.mk to luca.mk;
- template/targets: rename metax.mk to hpcc.mk;
#### Deprecated
#### Removed
- Remove ./template/template.drawio;
- Remove `fs/configfs/samples/configfs_sample.c`;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.11] 2025-12-01

#### Breaking Changes
#### Added
- rocm.mk: add `gen_hipcc_macro_hdr()`;
- cuda/dnn: support LUCA;
- cuda/dnn: support HPCC;
- cuda: add dnn subdir;
- os.mk: add `OS_ID` and `OS_VERSION_ID`;
- template: add values.mk;
- amd/rocm.mk: add `HAVE_HIPSOLVER`;
- cuda.mk: add `HAVE_CUDNN`;
- cuda: introduce solver;
- git/hooks/prepare-commit-msg: get ROCm, LUCA, HPCC version;
- cuda/samples: apply template/helpers.mk;
- template/helpers.mk: add `LUCA_HELPERS`, `HPCC_HELPERS`, `HIP_HELPERS`;
- luca: add `libluca_helper.so`;
- hpcc: add `libhpcc_helper.so`;
- amd/rocm: add `libhip_helper.so`;
- cuda: add fft subdir;
- makeself: introduce and test;
- template: add bpf/scx.mk;
- template: add python.mk;
- python: add version.sh;
- top Makefile: add `CHECK_ERROR`;
- template: add shell.mk, string.mk;
- add arch/aarch64/abbrev.md;
- cpp: test `unordered_map.cpp`;
- template/bpf: symlink kfunc.mk to helpers.mk;
- libbpf: test `bpf_cgroup_acquire()` kfunc must pass a good ptr;
- bpf/insn/samples: add `cgroup_acquire.c`, `get_current_cgroup_id.c`, `arena_alloc_pages.c`, `arena_reserve_pages.c`;
- bpf/insn/samples: check for helper supported or not.
- template/bpf: add helper.mk;
- sched: add ext.c test;
- sched-ext: add hello.c sample;
- sched: add deadline.c, rr.c, fifo.c;
#### Changed
- cuda: Split sparse from samples;
- cuda: Split rand from samples;
- cuda: Split blas from samples;
- `pthread_helpers`: rename `sys_affinity_bind` to `thread_affinity_bind_cpu`;
#### Deprecated
#### Removed
- os.mk: Remove OS var;
- remove algorithm/crc32/modules/, it's not my code;
- `sched_helpers`: remove `struct __sched_attr`;
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.10] 2025-11-18

#### Breaking Changes
- luca support .cu suffix.
- metax hpcc support .cu suffix.
- amd rocm hip support .cu suffix.
- profile.d: add `make_tl.sh` to alias system make command;
- template: include pure header for main.mk, etc.;
#### Added
- sched-ext: add ai-scheduler/ and samples/;
- bpf/{insn,kfunc}/samples: test `bpf_get_func_ip()`, `bpf_loop()`;
- bpf/{insn,kfunc}/samples: test `bpf_cgrp_storage_get()`;
- bpf/insn/samples: add `bpf_task_from_pid()` test;
- bpf/insn/samples: add `bpf_cgroup_from_id()` test;
- libbpf: add cgroup.bpf.h to test `bpf_cgroup_from_id()`;
- bpf/btf: add `libbtf_helpers.{a,so}`;
- bpf/kfunc: add `bpf_strncmp()`/`bpf_trace_printk()` test;
- syscall: add empty fadvise(2) to test;
- fs: add f2fs, lustre;
- bpf/kfunc: add samples;
- main.mk: add target-btf-y target;
- bpf: add `libbpf_helpers.so`;
- bpf/insn: add `libbpf_insn_samples.so`;
- bcc: add version.sh;
- cuda: add version.mk and used in git/hooks/prepare-commit-msg;
- template: add bcc.mk;
- git/hooks: add prepare-commit-msg, get-commit-file-list;
- bpf: add insn subdir;
- template: add bpftrace.mk;
- syscall: test `move_pages(2)`;
- targets/nvidia.mk: support static/dynamic library and add `libcuda_helper.so`, `libcuda_helper.a`;
- insn/examples: add syscall.c from libbpf-bootstrap;
- libbpf: `stack_helpers`: add `init_stackmap()` and apply to tracepoint test;
- libbpf: add `stack_helpers`.{c,h,bpf.h}
- blazesym: add capi to subdir;
- bpf: add blazesym to subdir;
- luca: add luca-envs.sh;
- syscall: add samples/execve/;
- mlx5: test macro `MLX5_GET()`;
- virt: add virt-manager/virt-install/uefi.sh;
- cloud-native: add Containerfile/;
- luca: add luca-container.sh;
- compiler: test attribute visibility;
- kallsyms: add `libksym_helpers.{so,a}` and apply to libbpf;
- mmap: add `libmmap_helpers.a`;
- sched: add `libsched_helpers.a`;
- pthread: add `libpthread_helpers.a`;
- helpers.mk and oom support STATIC;
- oom: Makefile: add `liboom_helpers.a`;
- libs: add str.h, constants.h;
- helpers: add libtest-linux-c.so;
- cuda/samples: add memory.cu, mallocHost.cu;
- SR-IOV: add abbrev.md;
- glibc: test `__GLIBC_USE()`;
- shell: add some commands from ostools;
#### Changed
- Move `sched_ext` to bpf/;
- bpf/insn/samples: add `bpf_samples_get_insns_from_string()`;
- log.mk: rename log functions name;
- bpf: add `insn/samples/trace_printk.c` from kprobe.c;
- Move bpf/{bpf.mk,logo.mk} to template/bpf/;
- Move libvirt directory into virt/;
- Split NCCL from cuda/samples/;
- Rename `socket_helpers.a` to `libsocket_helpers.a`;
- Move str2size() from `oom_helpers.c` to libs/str.c;
- libs: Rename macro `TEST` to `TEST_MAIN`;
- pthread: use fhexdump() instead of memshow();
- Move hexdump() from fakeCUDA to libs/memshow.c;
- Move vfio into virt/;
- make: Support NOSUBDIR definition;
#### Deprecated
#### Removed
- Remove target kconfig-display;
- libs/memshow.h: remove memshow() api;
- Remove symlinks of hpc/{amd/rocm,metax}/{samples,intrinsics};
#### Fixed
#### Security
#### Docs
#### Tools


## [v2.3.9] 2025-11-05

#### Breaking Changes
- mk: Rename all `sub-dir` to `subdir-y`;
- mk: Rename all `targets` to `target-y`;
- cuda/samples: Rename code to remove cuda,hip,hc prefix;
#### Added
- ioctl: test BLKGETSIZE, BLKZEROOUT, BLKSSZGET;
- rtos/rtlinux: first commit;
- pushsection: add `btf_ids.c`;
- compiler: add gnu/pushsection/;
- template: add user.mk and apply to libbpf/Makefile;
- libbpf: add task.bpf.h;
- module: add abbrev.md;
- compiler/runtime: add FAQ.md;
- compiler: add info.sh;
- compiler: add runtime/;
- template/targets: add make.sh
- stdc: test c11, c++03, c++11, c++14, c++17, c++20, c++23;
- iso: add ISO/IEC 9899 and ISO/IEC 14882 and symlinks;
- network: add README.OSI.md;
- bpf: add logo.mk;
- bpftrace: add `is_kprobe.bt` test;
- syscall/samples: add write subdirectory;
- cuda/intrinsics: add int.cu, simd.cu;
- c: add `_Float128.c` test;
- syscall: add syscalls.sh;
- bcc: add xdp/bufaddr.py;
- make: add foreach.mk test;
- `libproc_helpers.so`: add `proc_helpers.map`;
- helpers.ko: add `libtrace_helpers.so`;
- helpers.ko: add `liboom_helpers.so`;
- helpers.ko: add `libmmap_helpers.so`;
- luca: add SMI LingSpeed X710-M;
- helpers.mk: add `libsched_helpers.so`;
- helpers.mk: add `libpthread_helpers.so`;
- helpers.mk: add `libsocket_helpers.so`;
- template: add helpers.mk;
- procfs: add `libproc_helpers.{a,so}`;
- distributions: add NixOS;
- luca: align all cuda/intrinsics;
- luca: align all cuda/samples;
- hpc: introduce luca;
- compiler: test `__float128`, `__float80/_Float64x`;
- procfs: add sys/kernel/random/uuid.sh;
- c: add overflow.c;
- cuda/intrinsics: add fp128.cu, double.cu, fp8.cu, fp6.cu, types.h;
- bpftrace/samples: add auxv.bt;
- cuda/intrinsics: add test bfloat16.cu;
- ubuntu: add sources.list.d/ubuntu25.04.sources;
- make: add MAKECMDGOALS.mk, filter-out.mk;
- rootfs: add multistrap.sh to build rootfs for ubuntu;
#### Changed
- helpers.mk: Pretty call;
- compiler.mk: Set all definitions to 'y';
- cuda/samples: Rename cudaGetDeviceProperties.cu to properties.cu;
- Move rootfs/qemu.sh to qemu/qemu-vm.sh;
#### Deprecated
#### Removed
- bpftrace/samples: remove macro.bt;
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
