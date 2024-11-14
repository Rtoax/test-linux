#!/bin/bash
set -e

prog=inst-deps

declare -a dnf_args apt_args
declare -a pkgs pkgs_compiler pkgs_desktop pkgs_bench pkgs_math pkgs_db
declare -a pkgs_storage pkgs_net pkgs_container pkgs_virt pkgs_base pkgs_fs
declare -a pip_whls

have_base=YES
have_upgrade=YES
have_fs=
have_pip=
have_compiler=
have_container=
have_virt=
have_desktop=
have_math=
have_bench=
have_db=
have_storage=
have_net=

dry_run=

. /etc/os-release

OS=${ID}

inst_eval() {
	if [[ -z ${dry_run} ]]; then
		eval "$@"
	else
		echo "$@"
	fi
}

dnf_upgrade()
{
	inst_eval sudo dnf up -y --allowerasing --nobest || {
		echo "WARNING: Failed to upgrade"
		true
	}
}

apt_upgrade()
{
	inst_eval sudo apt update -y
	inst_eval sudo apt list --upgradable
	inst_eval sudo apt upgrade --fix-missing -y
}

dnf_install()
{
	inst_eval sudo dnf install -y ${dnf_args[@]} ${@}
}

apt_install()
{
	inst_eval sudo apt install -y ${apt_args[@]} ${@}
}

os_operator()
{
	local operator=$1
	shift

	case ${OS} in
	cclinux|fedora|centos|rhel|openEuler|almalinux|opencloudos)
		case ${operator} in
		upgrade) dnf_upgrade ;;
		install) dnf_install "${@}" ;;
		packages) dnf_add_packages "${@}" ;;
		esac
		;;
	debian|ubuntu)
		case ${operator} in
		upgrade) apt_upgrade ;;
		install) apt_install "${@}" ;;
		packages) apt_add_packages "${@}" ;;
		esac
		;;
	*)
		echo "ERROR: Unknown OS ${OS}"
		;;
	esac
}

os_upgrade()
{
	os_operator upgrade "${@}"
}

os_install()
{
	os_operator install "${@}"
}

os_packages()
{
	os_operator packages "${@}"
}

[[ ! -e /etc/os-release ]] && echo "ERROR: No /etc/os-release found" && exit 1
[[ ! -e /usr/bin/sudo ]] && echo "ERROR: Not found sudo, please install sudo first" && exit 1
[[ ! -e /usr/bin/getopt ]] && echo "WARNING: Not found getopt, try install util-linux first" && {
	os_install util-linux
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
	--container        install container relate packages, such as podman
	--desktop          install desktop relate packages
	--math             install math relate packages
	--bench            install benchmark relate packages
	--db               install database relate packages
	--storage          install storage relate packages
	--net              install network relate packages
	--virt             install virtualization relate packages
	--fs               install filesystem relate packages

	--nobase           skip basic packages
	--noup             skip upgrade

	--pip              install python pip wheel packages

	--dry-run          only show commands

	--allowerasing     allow erasing of installed packages to resolve dependencies

	-h, --help         show this help information

SEE ALSO
"
	exit ${1-0}
}

TEMP=$(getopt --options h \
	--long all \
	--long nobase \
	--long noup \
	--long fs \
	--long compilers \
	--long container \
	--long virt \
	--long pip \
	--long desktop \
	--long math \
	--long bench \
	--long db \
	--long storage \
	--long net \
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
		have_container=YES
		have_virt=YES
		have_pip=YES
		have_desktop=YES
		have_math=YES
		have_bench=YES
		have_fs=YES
		;;
	--noup)
		shift
		have_upgrade=""
		;;
	--nobase)
		shift
		have_base=""
		;;
	--fs)
		shift
		have_fs=YES
		;;
	--compilers)
		shift
		have_compiler=YES
		;;
	--container)
		shift
		have_container=YES
		;;
	--virt)
		shift
		have_virt=YES
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
	--net)
		shift
		have_net=YES
		;;
	--pip)
		shift
		have_pip=YES
		;;
	--dry-run)
		shift
		dry_run=YES
		;;
	--allowerasing)
		shift
		dnf_args+=( --allowerasing --nobest )
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
	os_install epel-release
	;;
fedora)
	;;
esac

pkgs_base+=( aha )
pkgs_base+=( autoconf-archive )
pkgs_base+=( bash-completion )
pkgs_base+=( bc )
pkgs_base+=( blktrace )
pkgs_base+=( bpftrace bcc )         # eBPF
pkgs_base+=( cargo )                # The Rust package manager
pkgs_base+=( cloc )
pkgs_base+=( codespell )
pkgs_base+=( cscope )
pkgs_base+=( dialog kdialog )
pkgs_base+=( dwz )                  # DWARF optimization and duplicate removal tool
pkgs_base+=( dwarves )              # pahole
pkgs_base+=( efibootmgr )           # UEFI
pkgs_base+=( efivar mokutil )       # UEFI
pkgs_base+=( elfutils )             # eu- prefix tools
pkgs_base+=( gdb cgdb )
pkgs_base+=( git )
pkgs_base+=( git-email )
pkgs_base+=( gnupg2 )               # gpg
pkgs_base+=( gperf )
pkgs_base+=( hwloc )                # lstopo
pkgs_base+=( indent )
pkgs_base+=( inotify-tools )        # inotifywatch, ...
pkgs_base+=( jq )
pkgs_base+=( lshw )                 # lshw
pkgs_base+=( make cmake )
pkgs_base+=( nasm )                 # nasm
pkgs_base+=( numactl )              # numastat
pkgs_base+=( opencl-headers )
pkgs_base+=( openssl )
pkgs_base+=( parallel )
pkgs_base+=( python3-pip )          # pip wheel
pkgs_base+=( python3-pyroute2 )     # pyroute2
pkgs_base+=( python3-scapy )
pkgs_base+=( smem )
pkgs_base+=( socat )
pkgs_base+=( sparse )               # sparse
pkgs_base+=( strace )
pkgs_base+=( smartmontools )        # smartctl
pkgs_base+=( sysstat )
pkgs_base+=( texinfo )
pkgs_base+=( tmux )
pkgs_base+=( trace-cmd )
pkgs_base+=( tree )
pkgs_base+=( util-linux )           # wipefs, etc.
pkgs_base+=( vim )
pkgs_base+=( which )
pkgs_base+=( yq )

pkgs_compiler+=( bison )
pkgs_compiler+=( byacc )
pkgs_compiler+=( clang )
pkgs_compiler+=( flex )
pkgs_compiler+=( gcc )
pkgs_compiler+=( golang )
pkgs_compiler+=( llvm )                   # llvm-as llvm-dis llc

pkgs_container+=( buildah )
pkgs_container+=( conmon )
pkgs_container+=( containerd )
pkgs_container+=( crun )
pkgs_container+=( debootstrap )
pkgs_container+=( lxc )
pkgs_container+=( podman )
pkgs_container+=( podman-docker )
pkgs_container+=( runc )
pkgs_container+=( skopeo )
pkgs_container+=( systemd-container )

pkgs_virt+=( qemu-user )
pkgs_virt+=( vagrant )
pkgs_virt+=( virt-manager )

# Benchmark
pkgs_bench+=( iperf iperf3 )
pkgs_bench+=( fio )

# Desktop Packages
pkgs_desktop+=( terminator )
pkgs_desktop+=( thunderbird )
pkgs_desktop+=( gimp )
pkgs_desktop+=( gnome-tweaks )
pkgs_desktop+=( gnuplot )
pkgs_desktop+=( python3-matplotlib )

# Database
pkgs_db+=( postgresql )

# Filesystem
pkgs_fs+=( xfsprogs )

# Storage
pkgs_storage+=( device-mapper )
pkgs_storage+=( device-mapper-multipath )
pkgs_storage+=( iotop )
pkgs_storage+=( mdadm ) # manage MD devices aka Linux Software RAID

pkgs_net+=( rsync )
pkgs_net+=( net-tools ) # netstat

pip_whls+=( numpy pyyaml )
pip_whls+=( tqdm )
pip_whls+=( "\"mkdocs>=1.5.2\"" )
pip_whls+=( "\"mkdocs-material>=9.2.6\"" )
pip_whls+=( "\"mkdocstrings[python]>=0.22.0\"" )
pip_whls+=( "\"mkdocs-static-i18n>=1.0.2\"" )
pip_whls+=( "\"mkdocs-include-markdown-plugin>=6.0.1\"" )


if [[ ${have_upgrade} ]]; then
	os_upgrade
fi

dnf_add_packages()
{
	if [[ $(uname -m) == x86_64 ]]; then
		pkgs_base+=( glibc.i686 )
		pkgs_base+=( glibc-devel.i686 )
		pkgs_base+=( glibc-static.i686 )
		pkgs_bench+=( memtest86+ )
	fi
	pkgs_base+=( acpi acpica-tools )
	pkgs_base+=( bcc-devel )
	pkgs_base+=( binutils-devel )
	pkgs_base+=( bpftool )
	pkgs_base+=( capstone-devel )       # Capstone is a disassembly framework
	pkgs_base+=( cereal-devel )
	pkgs_base+=( clang-devel )
	pkgs_base+=( crash )
	pkgs_base+=( dbus-devel )           # D-Bus
	pkgs_base+=( dtc )                  # device tree
	pkgs_base+=( elfutils-devel )
	pkgs_base+=( elfutils-libelf-devel )
	pkgs_base+=( git-clang-format )
	pkgs_base+=( glibc-common )
	pkgs_base+=( glibc-static )
	pkgs_base+=( glibc-utils )
	pkgs_base+=( gmp-devel )
	pkgs_base+=( golang-github-cilium-ebpf )
	pkgs_base+=( gperftools-devel )
	pkgs_base+=( grub2-tools-minimal grub2-tools-extra )
	pkgs_base+=( gtest-devel gmock-devel )
	pkgs_base+=( iproute )              # ss
	pkgs_base+=( iproute-tc )           # tc
	pkgs_base+=( iptables-devel )
	pkgs_base+=( jemalloc-devel )
	pkgs_base+=( kernel-devel )         # kernel
	pkgs_base+=( kernel-headers )       # kernel
	pkgs_base+=( kernel-modules )       # modules
	pkgs_base+=( kernel-modules-extra ) # modules, ocfs2, etc.
	pkgs_base+=( libaio-devel )         # aio
	pkgs_base+=( libattr-devel )
	pkgs_base+=( libbpf-devel )         # libbpf
	pkgs_base+=( libcap-ng-devel )
	pkgs_base+=( libcap-ng-utils )
	pkgs_base+=( libdwarf-tools )       # dwarfdump
	pkgs_base+=( libedit-devel )
	pkgs_base+=( libpcap-devel )
	pkgs_base+=( libseccomp-devel )
	pkgs_base+=( libselinux-devel )     # SELinux
	pkgs_base+=( libunwind-devel )      # Unwind
	pkgs_base+=( liburing-devel )       # uring
	pkgs_base+=( libxml2-devel )
	pkgs_base+=( lksctp-tools-devel )   # SCTP
	pkgs_base+=( lldb-devel )
	pkgs_base+=( llvm-devel )
	pkgs_base+=( lsb_release )
	pkgs_base+=( ltrace )               # ltrace
	pkgs_base+=( mmc )                  # mmc
	pkgs_base+=( mpich mpich-devel )    # mpi
	pkgs_base+=( mpfr-devel )
	pkgs_base+=( ncurses-devel )
	pkgs_base+=( numactl-devel )        # numaif.h
	pkgs_base+=( nvme-cli )             # nvme
	pkgs_base+=( openssl-devel )
	pkgs_base+=( pam )                  # /etc/security/limits.conf
	pkgs_base+=( pam-devel )
	pkgs_base+=( perf )
	pkgs_base+=( procps-ng )            # pidof, top, etc.
	pkgs_base+=( readline-devel )
	pkgs_base+=( scl-utils )
	pkgs_base+=( sg3_utils )            # sg_inq, etc.
	pkgs_base+=( systemd-udev )         # coredumpctl
	pkgs_base+=( systemtap-sdt-devel )  # sdt.h
	pkgs_base+=( vim-default-editor )
	pkgs_base+=( xz-devel )

	pkgs_bench+=( rtla )
	pkgs_bench+=( sysbench )

	# Filesystem
	pkgs_fs+=( e2fsprogs )              # badblocks
	pkgs_fs+=( ocfs2-tools )
	pkgs_fs+=( overlayfs-tools )
	pkgs_fs+=( xfsprogs-devel )         # xfs
	pkgs_fs+=( funionfs )

	# Cross compile packages
	pkgs_compiler+=( binutils-aarch64-linux-gnu )
	pkgs_compiler+=( binutils-x86_64-linux-gnu )
	pkgs_compiler+=( gcc-aarch64-linux-gnu )
	pkgs_compiler+=( gcc-c++ )
	pkgs_compiler+=( gcc-x86_64-linux-gnu )
	pkgs_compiler+=( libatomic )
	pkgs_compiler+=( lua )

	pkgs_compiler+=( java-1.8.0-openjdk-devel )
	pkgs_compiler+=( libgccjit-devel )
	pkgs_compiler+=( rust )

	pkgs_container+=( cri-tools )
	pkgs_container+=( cri-o )
	pkgs_container+=( criu )
	pkgs_container+=( libcgroup-tools )
	pkgs_container+=( udica )

	pkgs_desktop+=( glib2-devel )
	pkgs_desktop+=( gtk3 )
	pkgs_desktop+=( gtk3-devel )
	pkgs_desktop+=( tigervnc )

	pkgs_math+=( fftw-devel )

	pkgs_db+=( libpq-devel )

	pkgs_virt+=( edk2-ovmf )
	pkgs_virt+=( libvirt )
	pkgs_virt+=( qemu-kvm )

	pkgs_net+=( httpd )

	dnf_args+=( --skip-broken )
	dnf_args+=( --nogpgcheck )
}

apt_add_packages()
{
	pkgs_base+=( binutils-dev )
	pkgs_base+=( bpfcc-tools )
	pkgs_base+=( build-essential )
	pkgs_base+=( clang-format )
	pkgs_base+=( dwarfdump )
	pkgs_base+=( libaio-dev )           # aio
	pkgs_base+=( libbpf-dev )           # libbpf
	pkgs_base+=( libbpfcc )
	pkgs_base+=( libbpfcc-dev )
	pkgs_base+=( libcapstone-dev )
	pkgs_base+=( libc6-dev )
	pkgs_base+=( libc-bin )
	pkgs_base+=( libgmp-dev )
	pkgs_base+=( libmpfr-dev )
	pkgs_base+=( libmpich-dev )         # MPI
	pkgs_base+=( libncurses-dev )
	pkgs_base+=( libnuma-dev )
	pkgs_base+=( libpam0g )
	pkgs_base+=( libpam0g-dev )
	pkgs_base+=( libssl-dev )
	pkgs_base+=( libunwind-dev )
	pkgs_base+=( liburing-dev )
	pkgs_base+=( linux-headers-$(uname -r) )
	pkgs_base+=( linux-libc-dev )
	pkgs_base+=( linux-perf )
	pkgs_base+=( lsb-release )
	pkgs_base+=( procps )
	pkgs_base+=( sg3-utils )            # sg_inq, etc.
	pkgs_base+=( systemtap-sdt-dev )    # sdt.h
	if [[ ${OS} == ubuntu ]]; then
		pkgs_base+=( linux-tools-common )
	fi

	pkgs_net+=( apache2 )

	pkgs_compiler+=( build-essential )
	pkgs_compiler+=( gcc-doc )
	pkgs_compiler+=( gcc-multilib )
	pkgs_compiler+=( libatomic1 )
	pkgs_compiler+=( lua5.4 )
	pkgs_compiler+=( rust-all )

	pkgs_fs+=( unionfs-fuse )

	pkgs_math+=( fftw-dev )

	pkgs_container+=( cgroup-tools )

	pkgs_virt+=( libvirt0 )
	pkgs_virt+=( qemu-system )

	pkgs_desktop+=( libgtk-3-dev )
	pkgs_desktop+=( tigervnc-common )
	pkgs_desktop+=( tigervnc-standalone-server )
	pkgs_desktop+=( tigervnc-viewer )

	apt_args+=( --fix-missing )
	apt_args+=( -f )
}

os_packages

[[ ${have_base} ]] && pkgs+=( ${pkgs_base[@]} )
[[ ${have_fs} ]] && pkgs+=( ${pkgs_fs[@]} )
[[ ${have_compiler} ]] && pkgs+=( ${pkgs_compiler[@]} )
[[ ${have_container} ]] && pkgs+=( ${pkgs_container[@]} )
[[ ${have_virt} ]] && pkgs+=( ${pkgs_virt[@]} )
[[ ${have_desktop} ]] && pkgs+=( ${pkgs_desktop[@]} )
[[ ${have_math} ]] && pkgs+=( ${pkgs_math[@]} )
[[ ${have_bench} ]] && pkgs+=( ${pkgs_bench[@]} )
[[ ${have_db} ]] && pkgs+=( ${pkgs_db[@]} )
[[ ${have_storage} ]] && pkgs+=( ${pkgs_storage[@]} )
[[ ${have_net} ]] && pkgs+=( ${pkgs_net[@]} )


if [[ ! -z "${pkgs[@]}" ]]; then
	os_install ${pkgs[@]}
fi

# Install python3 pip wheels
if [[ ${have_pip} ]] && [[ -e /usr/bin/pip3 ]]; then
	inst_eval pip3 install "${pip_whls[@]}"
fi
