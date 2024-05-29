#!/bin/bash
set -e

prog=inst-deps

declare -a dnf_args
declare -a pkgs pkgs_compiler pkgs_desktop whls pkgs_bench pkgs_math pkgs_db
declare -a pkgs_storage

have_upgrade=YES
have_whls=
have_compiler=
have_desktop=
have_math=
have_bench=
have_db=
have_storage=

dry_run=

[[ ! -e /etc/os-release ]] && echo "ERROR: No /etc/os-release found" && exit 1

. /etc/os-release

OS=${ID}

inst_eval() {
	if [[ -z ${dry_run} ]]; then
		eval "$@"
	else
		echo "$@"
	fi
}

__usage__()
{
	echo -e "
NAME
	$prog - Install depends

SYNOPSIS
	$prog [--dry-run] [--all]

DESCRIPTION
	Install various dependencies.

ARGUMENT
	--all

	--compilers        install extra compilers, such as rust java
	--whls             install python pip wheel packages
	--desktop          install desktop relate packages
	--math             install math relate packages
	--bench            install benchmark relate packages
	--db               install database relate packages
	--storage          install storage relate packages

	--noup             skip upgrade

	--dry-run          only show commands

	--allowerasing     allow erasing of installed packages to resolve dependencies

	-h, --help         show this help information

SEE ALSO
"
	exit ${1-0}
}

TEMP=$(getopt --options h \
	--long all \
	--long noup \
	--long compilers \
	--long whls \
	--long desktop \
	--long math \
	--long bench \
	--long db \
	--long storage \
	--long dry-run \
	--long allowerasing \
	--long help \
	--name $prog -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$TEMP"

while true; do
	case $1 in
	-h|--help)
		shift
		__usage__
		;;
	--all)
		shift
		have_compiler=YES
		have_whls=YES
		have_desktop=YES
		have_math=YES
		have_bench=YES
		;;
	--noup)
		shift
		have_upgrade=""
		;;
	--compilers)
		shift
		have_compiler=YES
		;;
	--desktop)
		shift
		have_desktop=YES
		;;
	--math)
		shift
		have_math=YES
		;;
	--bench)
		shift
		have_bench=YES
		;;
	--db)
		shift
		have_db=YES
		;;
	--storage)
		shift
		have_storage=YES
		;;
	--whls)
		shift
		have_whls=YES
		;;
	--dry-run)
		shift
		dry_run=YES
		;;
	--allowerasing)
		shift
		dnf_args+=( --allowerasing )
		;;
	--)
		shift
		break
		;;
	esac
done

echo "OS: ${OS}"

# Install extra software package repo
case ${OS} in
centos|rhel|almalinux)
	inst_eval sudo dnf install ${dnf_args[@]} -y epel-release
	;;
fedora)
	;;
esac

pkgs+=( acpi acpica-tools )
pkgs+=( autoconf-archive )
pkgs+=( blktrace )
pkgs+=( bpftrace bcc )         # eBPF
pkgs+=( cargo )                # The Rust package manager
pkgs+=( crash )
pkgs+=( criu )
pkgs+=( dialog kdialog )
pkgs+=( dwz )                  # DWARF optimization and duplicate removal tool
pkgs+=( dwarves )              # pahole
pkgs+=( efibootmgr )           # UEFI
pkgs+=( efivar mokutil )       # UEFI
pkgs+=( gdb cgdb )
pkgs+=( gnupg2 )               # gpg
pkgs+=( hwloc )                # lstopo
pkgs+=( inotify-tools )        # inotifywatch, ...
pkgs+=( llvm )                 # llvm-as llvm-dis llc
pkgs+=( lshw )                 # lshw
pkgs+=( make cmake )
pkgs+=( nasm )                 # nasm
pkgs+=( net-tools )            # netstat
pkgs+=( numactl )              # numastat
pkgs+=( opencl-headers )
pkgs+=( openssl )
pkgs+=( parallel )
pkgs+=( python3-pip )          # pip wheel
pkgs+=( python3-pyroute2 )     # pyroute2
pkgs+=( python3-scapy )
pkgs+=( qemu-kvm qemu-user )
pkgs+=( socat )
pkgs+=( sparse )               # sparse
pkgs+=( strace )
pkgs+=( smartmontools )        # smartctl
pkgs+=( sysstat )
pkgs+=( tree )
pkgs+=( vim vim-default-editor )

pkgs_compiler+=( clang )
pkgs_compiler+=( gcc-aarch64-linux-gnu )
pkgs_compiler+=( gcc gcc-c++ )
pkgs_compiler+=( golang )
pkgs_compiler+=( lua )

# Benchmark
pkgs_bench+=( iperf iperf3 )
pkgs_bench+=( fio )
pkgs_bench+=( sysbench )

# Desktop Packages
pkgs_desktop+=( terminator )
pkgs_desktop+=( gimp )
pkgs_desktop+=( gnuplot )
pkgs_desktop+=( gtk3 gtk3-devel )
pkgs_desktop+=( python3-matplotlib )

# Database
pkgs_db+=( postgresql )

# Storage
pkgs_storage+=( device-mapper )
pkgs_storage+=( device-mapper-multipath )
pkgs_storage+=( iotop )
pkgs_storage+=( mdadm ) # manage MD devices aka Linux Software RAID

whls+=( numpy pyyaml )
whls+=( tqdm )
whls+=( "\"mkdocs>=1.5.2\"" )
whls+=( "\"mkdocs-material>=9.2.6\"" )
whls+=( "\"mkdocstrings[python]>=0.22.0\"" )
whls+=( "\"mkdocs-static-i18n>=1.0.2\"" )
whls+=( "\"mkdocs-include-markdown-plugin>=6.0.1\"" )

case ${OS} in
cclinux|fedora|centos|rhel|openEuler|almalinux)
	if [[ $(uname -m) == x86_64 ]]; then
		pkgs+=( glibc-devel.i686 )
	fi
	pkgs+=( bcc-devel )
	pkgs+=( binutils-devel )
	pkgs+=( bpftool )
	pkgs+=( capstone-devel )       # Capstone is a disassembly framework
	pkgs+=( cereal-devel )
	pkgs+=( clang-devel )
	pkgs+=( dbus-devel )           # D-Bus
	pkgs+=( dtc )                  # device tree
	pkgs+=( elfutils-libelf-devel )
	pkgs+=( glibc-common )
	pkgs+=( glibc-utils )
	pkgs+=( git-clang-format )
	pkgs+=( golang-github-cilium-ebpf )
	pkgs+=( gperftools-devel )
	pkgs+=( grub2-tools-minimal grub2-tools-extra )
	pkgs+=( gtest-devel gmock-devel )
	pkgs+=( iproute-tc )           # tc
	pkgs+=( iptables-devel )
	pkgs+=( jemalloc-devel )
	pkgs+=( kernel-devel )         # kernel
	pkgs+=( kernel-headers )       # kernel
	pkgs+=( libaio-devel )         # aio
	pkgs+=( libattr-devel )
	pkgs+=( libbpf-devel )         # libbpf
	pkgs+=( libcap-ng-devel )
	pkgs+=( libcap-ng-utils )
	pkgs+=( libdwarf-tools )       # dwarfdump
	pkgs+=( libedit-devel )
	pkgs+=( libpcap-devel )
	pkgs+=( libseccomp-devel )
	pkgs+=( libselinux-devel )     # SELinux
	pkgs+=( libunwind-devel )      # Unwind
	pkgs+=( liburing-devel )       # uring
	pkgs+=( libxml2-devel )
	pkgs+=( lksctp-tools-devel )   # SCTP
	pkgs+=( llvm-devel )
	pkgs+=( lsb_release )
	pkgs+=( ltrace )               # ltrace
	pkgs+=( mmc )                  # mmc
	pkgs+=( mpich mpich-devel )    # mpi
	pkgs+=( numactl-devel )        # numaif.h
	pkgs+=( nvme-cli )             # nvme
	pkgs+=( overlayfs-tools )
	pkgs+=( pam-devel )
	pkgs+=( procps-ng )            # pidof, top, etc.
	pkgs+=( scl-utils )
	pkgs+=( sg3_utils )            # sg_inq, etc.
	pkgs+=( systemtap-sdt-devel )  # sdt.h
	pkgs+=( xfsprogs-devel )       # xfs

	# Cross compile packages
	pkgs_compiler+=( binutils-aarch64-linux-gnu )
	pkgs_compiler+=( binutils-x86_64-linux-gnu )
	pkgs_compiler+=( gcc-aarch64-linux-gnu )
	pkgs_compiler+=( gcc-x86_64-linux-gnu )

	pkgs_compiler+=( java-1.8.0-openjdk-devel )
	pkgs_compiler+=( libgccjit-devel )
	pkgs_compiler+=( rust )

	pkgs_math+=( fftw-devel )

	pkgs_db+=( libpq-devel )

	args=( --skip-broken )
	args+=( --nogpgcheck )

	[[ ${have_compiler} ]] && pkgs+=( ${pkgs_compiler[@]} )
	[[ ${have_desktop} ]] && pkgs+=( ${pkgs_desktop[@]} )
	[[ ${have_math} ]] && pkgs+=( ${pkgs_math[@]} )
	[[ ${have_bench} ]] && pkgs+=( ${pkgs_bench[@]} )
	[[ ${have_db} ]] && pkgs+=( ${pkgs_db[@]} )
	[[ ${have_storage} ]] && pkgs+=( ${pkgs_storage[@]} )

	if [[ ${have_upgrade} ]]; then
		inst_eval sudo dnf up ${dnf_args[@]} -y
	fi
	inst_eval sudo dnf install ${dnf_args[@]} ${args[@]} -y ${pkgs[@]}
	;;
debian|ubuntu)
	pkgs+=( binutils-dev )
	pkgs+=( clang-format )
	pkgs+=( libaio-dev )           # aio
	pkgs+=( libc6-dev )
	pkgs+=( libmpich-dev )         # MPI
	pkgs+=( libunwind-dev )
	pkgs+=( linux-libc-dev )
	pkgs+=( linux-tools-common )
	pkgs+=( lsb-release )
	pkgs+=( procps )
	pkgs+=( sg3-utils )            # sg_inq, etc.

	pkgs_compiler+=( rust-all )

	pkgs_math+=( fftw-dev )

	[[ ${have_compiler} ]] && pkgs+=( ${pkgs_compiler[@]} )
	[[ ${have_desktop} ]] && pkgs+=( ${pkgs_desktop[@]} )
	[[ ${have_math} ]] && pkgs+=( ${pkgs_math[@]} )
	[[ ${have_bench} ]] && pkgs+=( ${pkgs_bench[@]} )
	[[ ${have_db} ]] && pkgs+=( ${pkgs_db[@]} )
	[[ ${have_storage} ]] && pkgs+=( ${pkgs_storage[@]} )

	args=( --fix-missing )

	if [[ ${have_upgrade} ]]; then
		inst_eval sudo apt update -y
		inst_eval sudo apt list --upgradable
		inst_eval sudo apt upgrade -y
	fi
	inst_eval sudo apt install ${args[@]} ${pkgs[@]} -y
	;;
*)
	echo "ERROR: Unknown OS ${OS}"
	;;
esac

# Install python3 pip wheels
if [[ ${have_whls} ]] && [[ -e /usr/bin/pip3 ]]; then
	inst_eval pip3 install "${whls[@]}"
fi
