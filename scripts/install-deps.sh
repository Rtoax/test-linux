#!/bin/bash
# This script use to install packages on Debian/RHEL like operate system.
#
# This script is part of test-linux [1], of course, you could run this script
# anywhere, not only in test-linux.
#
# [1] https://github.com/rtoax/test-linux.git
#
set -e

. /etc/os-release

readonly prog=inst-deps

declare -a dnf_args apt_args
declare -a pkgs pkgs_compiler pkgs_desktop pkgs_bench pkgs_math pkgs_db
declare -a pkgs_storage pkgs_net pkgs_container pkgs_virt pkgs_base pkgs_fs
declare -a pkgs_media pkgs_build pkgs_devel pkgs_docs
declare -a pip_whls

declare -a pkgs_skip

verbose=
dry_run=
force=

readonly OS=${ID}
readonly OS_VERSION=${VERSION_ID}
readonly VIRT_TYPE=$(systemd-detect-virt 2>/dev/null || :)
readonly IS_PHY=$( [[ ${VIRT_TYPE} == none ]] && echo YES || :)
readonly IS_DNF5="$(dnf --version 2>/dev/null | grep -woi dnf5 | uniq)"

echo "OS: ${OS}"
echo "VIRT: ${VIRT_TYPE} (IS_PHY: ${IS_PHY})"

have_base=YES
have_upgrade=YES
have_fs=
have_pip=
have_compiler=
have_build=
have_docs=
have_devel=
have_container=
have_virt=
have_desktop=
have_math=
have_media=
have_bench=
have_db=
have_storage=
have_net=

have_3rd_party=

enable_all()
{
	have_compiler=YES
	have_build=YES
	have_docs=YES
	have_devel=YES
	have_container=YES
	have_virt=YES
	have_pip=YES
	have_desktop=YES
	have_math=YES
	have_media=YES
	have_bench=YES
	have_net=YES
	have_fs=YES
	have_db=YES
	have_storage=YES
	have_3rd_party=YES
}

goodbye()
{
	local ret=$?
	if [[ ${ret} != 0 ]]; then
		echo >&2 -e "\033[1;31mRunning ${prog} failed!\033[m"
		exit ${ret}
	else
		echo >&2 -e "\033[1;32mRunning ${prog} success!\033[m"
		exit 0
	fi
}
trap goodbye EXIT

inst_eval()
{
	if [[ -z ${dry_run} ]]; then
		echo >&2 -e "\033[1;32mStartup: $@\033[m"
		eval "$@"
		echo >&2 -e "\033[1;33mDone: $@\033[m"
	else
		echo "$@"
	fi
}

dnf_upgrade()
{
	inst_eval sudo dnf up ${dnf_args[@]} -y --allowerasing --nobest || {
		echo "WARNING: Failed to upgrade"
		true
	}
}

apt_upgrade()
{
	inst_eval sudo apt update -y || :
	inst_eval sudo apt list --upgradable || :
	inst_eval sudo apt upgrade --fix-missing -y || {
		echo "WARNING: Failed to upgrade"
		true
	}
	inst_eval sudo apt autoremove || :
}

dnf_install()
{
	inst_eval sudo dnf install -y ${dnf_args[@]} ${@}
}

apt_install()
{
	inst_eval sudo apt install -y ${apt_args[@]} ${@}
}

dnf_remove()
{
	local ARGS=$(echo ${dnf_args[@]} | sed 's/--allowerasing//g' \
			| sed 's/--skip-broken//g')
	inst_eval sudo dnf remove -y ${ARGS} ${@}
}

apt_remove()
{
	inst_eval sudo apt remove -y ${apt_args[@]} ${@}
}

os_operator()
{
	local operator=$1
	shift

	local _os_=${OS}

	case ${_os_} in
	cclinux|fedora|centos|rhel|openEuler|almalinux|opencloudos|kylin)
		case ${operator} in
		upgrade) dnf_upgrade ;;
		install) dnf_install "${@}" ;;
		remove) dnf_remove "${@}" ;;
		packages) dnf_add_packages "${@}" ;;
		esac
		;;
	debian|ubuntu)
		case ${operator} in
		upgrade) apt_upgrade ;;
		install) apt_install "${@}" ;;
		remove) apt_remove "${@}" ;;
		packages) apt_add_packages "${@}" ;;
		esac
		;;
	*)
		echo "ERROR: Unknown OS ${OS}"
		exit 1
		;;
	esac
}

is_os()
{
	local oss=( $@ )
	for os in ${oss[@]}
	do
		if [[ ${OS} = ${os} ]]; then
			echo YES
			break
		fi
	done
	return 0
}

os_upgrade()
{
	os_operator upgrade "${@}"
}

os_install()
{
	os_operator install "${@}"
}

os_remove()
{
	os_operator remove "${@}"
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
	${prog} - Install depends for test-linux or deploy

SYNOPSIS
	${prog} [--dry-run] [--all]

DESCRIPTION
	Install various dependencies.

ARGUMENT
	--all

	--compilers        install compilers, such as rust java
	--build            install package builders, such as meson ninja
	--docs             install document packages, such as python3-sphinx
	--devel            install development packages, such as zlib-devel
	--container        install container relate packages, such as podman
	--desktop          install desktop relate packages
	--math             install math relate packages
	--media            install media relate packages
	--bench            install benchmark relate packages
	--db               install database relate packages
	--storage          install storage relate packages
	--net              install network relate packages
	--virt             install virtualization relate packages
	--fs               install filesystem relate packages

	--3rd              get third party software packages above

	--nobase           skip basic packages
	--noup             skip upgrade

	--pip, --nopip     install python pip wheel packages or skip even --all

	-k, --skip-pkg     skip package (maybe list mutiple)
	-u, --dry-run      only show commands

	-v, --verbose      show verbose information
	-h, --help         show this help information
	-f, --force        force install

SEE ALSO
	gcc(1), etc.
"
	exit ${1-0}
}

TEMP=$(getopt --options uvhfk: \
	--long all \
	--long nobase \
	--long noup \
	--long fs \
	--long compilers \
	--long build \
	--long docs \
	--long devel \
	--long container \
	--long virt \
	--long pip --long nopip \
	--long desktop \
	--long math \
	--long media \
	--long bench \
	--long db \
	--long storage \
	--long net \
	--long skip-pkg: \
	--long dry-run \
	--long verbose \
	--long help \
	--long force \
	--name ${prog} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$TEMP"

while true; do
	case $1 in
	-h | --help)
		shift
		__usage__
		;;
	--all)
		shift
		enable_all
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
	--build)
		shift
		have_build=YES
		;;
	--docs)
		shift
		have_docs=YES
		;;
	--devel)
		shift
		have_devel=YES
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
	--media)
		shift
		have_media=YES
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
	--3rd)
		shift
		have_3rd_party=YES
		;;
	--pip)
		shift
		have_pip=YES
		;;
	--nopip)
		shift
		have_pip=
		;;
	-k | --skip-pkg)
		shift
		pkgs_skip+=( $1 )
		shift
		;;
	-u | --dry-run)
		shift
		dry_run=YES
		;;
	-f | --force)
		shift
		force=YES
		dnf_args+=( --allowerasing )
		dnf_args+=( --nobest )
		dnf_args+=( --skip-broken )
		;;
	-v | --verbose)
		shift
		verbose=YES
		;;
	--)
		shift
		break
		;;
	esac
done

if [[ ${verbose} ]]; then
	export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
	set -x
fi

# Install extra software package repo
case ${OS} in
centos|rhel|almalinux)
	os_install epel-release
	;;
fedora)
	os_install apt
	# I don't like use nano editor
	os_remove nano-default-editor
	;;
esac

pkgs_base+=( acpi )
pkgs_base+=( acpica-tools )
pkgs_base+=( aha )
pkgs_base+=( autoconf-archive )
pkgs_base+=( bash-completion )
pkgs_base+=( bat )                  # highlight cat(1)
pkgs_base+=( bc )
pkgs_base+=( blktrace )
pkgs_base+=( bpftool )
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
pkgs_base+=( hostname )
pkgs_base+=( htop )
pkgs_base+=( hwloc )                # lstopo
pkgs_base+=( indent )
pkgs_base+=( inotify-tools )        # inotifywatch, ...
pkgs_base+=( jq )
pkgs_base+=( lshw )                 # lshw
pkgs_base+=( make cmake )
pkgs_base+=( nasm )                 # nasm
if [[ ${OS} == fedora ]] && [[ ${OS_VERSION} -ge 41 ]]; then
	pkgs_base+=( fastfetch )
else
	pkgs_base+=( neofetch )
fi
pkgs_base+=( numactl )              # numastat
pkgs_base+=( opencl-headers )
pkgs_base+=( openssl )
pkgs_base+=( parallel )
pkgs_base+=( powertop ) # power consumption and power management diagnosis tool
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
pkgs_base+=( yq )

pkgs_compiler+=( automake )
pkgs_compiler+=( bison )
pkgs_compiler+=( byacc )
pkgs_compiler+=( clang )
pkgs_compiler+=( flex )
pkgs_compiler+=( gcc )
pkgs_compiler+=( golang )
pkgs_compiler+=( lld )                    # ELF linker from the LLVM project
pkgs_compiler+=( llvm )                   # llvm-as llvm-dis llc
pkgs_compiler+=( mold )                   # a modern linker
if [[ $(uname -m) != aarch64 ]]; then
	pkgs_compiler+=( binutils-aarch64-linux-gnu )
	pkgs_compiler+=( gcc-aarch64-linux-gnu )
fi
if [[ $(uname -m) != x86_64 ]]; then
	pkgs_compiler+=( binutils-x86_64-linux-gnu )
	pkgs_compiler+=( gcc-x86_64-linux-gnu )
fi

pkgs_build+=( meson )
pkgs_build+=( ninja-build )

pkgs_docs+=( python3-sphinx )

pkgs_container+=( buildah )
pkgs_container+=( conmon )
pkgs_container+=( containerd )
pkgs_container+=( crun )
pkgs_container+=( debootstrap ) # make rootfs
pkgs_container+=( lxc )
pkgs_container+=( podman )
pkgs_container+=( podman-docker )
pkgs_container+=( runc )
pkgs_container+=( skopeo )
pkgs_container+=( systemd-container )

pkgs_virt+=( qemu-user )
pkgs_virt+=( qemu-user-static )
pkgs_virt+=( vagrant )
pkgs_virt+=( virt-manager )

# Benchmark
pkgs_bench+=( iperf iperf3 )
pkgs_bench+=( fio )

pkgs_media+=( vlc )
# https://motrix.app/download
# https://code.visualstudio.com/docs/setup/linux
# https://www.drawio.com/, https://github.com/jgraph/drawio-desktop/releases/
pkgs_media_3rd+=()

# Desktop Packages
pkgs_desktop+=( terminator )
pkgs_desktop+=( thunderbird )
pkgs_desktop+=( gimp )
pkgs_desktop+=( gitk )
pkgs_desktop+=( gnome-tweaks )
pkgs_desktop+=( gnuplot )
# openshot: Crashed at first time
#pkgs_desktop+=( openshot )
pkgs_desktop+=( python3-matplotlib )

# Database
pkgs_db+=( postgresql )

# Filesystem
pkgs_fs+=( attr )
pkgs_fs+=( xfsprogs )

# Storage
pkgs_storage+=( iotop )
pkgs_storage+=( mdadm ) # manage MD devices aka Linux Software RAID

pkgs_net+=( ethtool )
pkgs_net+=( net-tools ) # netstat
pkgs_net+=( rsync )
pkgs_net+=( tcpdump )

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
	pkgs_base+=( bcc-devel )
	pkgs_base+=( binutils-devel )
	pkgs_base+=( binutils-gold )
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
	pkgs_base+=( libattr-devel )
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
	pkgs_base+=( which )
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
	pkgs_compiler+=( gcc-c++ )
	pkgs_compiler+=( libatomic )
	pkgs_compiler+=( lua )

	pkgs_compiler+=( java-1.8.0-openjdk-devel )
	pkgs_compiler+=( libgccjit-devel )
	pkgs_compiler+=( rust )

	pkgs_build+=( rpm-build )

	pkgs_container+=( cri-tools )
	pkgs_container+=( cri-o )
	pkgs_container+=( criu )
	pkgs_container+=( libcgroup-devel )
	pkgs_container+=( libcgroup-tools )
	pkgs_container+=( udica )

	pkgs_desktop+=( gtk3 )
	pkgs_desktop+=( gtk3-devel )
	pkgs_desktop+=( tigervnc )

	pkgs_devel+=( cyrus-sasl-devel )
	pkgs_devel+=( device-mapper-multipath-devel )
	pkgs_devel+=( glib2-devel )
	pkgs_devel+=( gnutls-devel )
	pkgs_devel+=( libaio-devel )
	pkgs_devel+=( libattr-devel )
	pkgs_devel+=( libblkio-devel )
	pkgs_devel+=( libbpf-devel )         # libbpf
	pkgs_devel+=( libcap-devel )
	pkgs_devel+=( libcap-ng-devel )
	pkgs_devel+=( libcurl-devel )
	pkgs_devel+=( libdwarf-devel )
	pkgs_devel+=( libfdt-devel )
	pkgs_devel+=( libiscsi-devel )
	pkgs_devel+=( libpmem-devel )
	pkgs_devel+=( libpng-devel )
	pkgs_devel+=( librbd-devel )
	pkgs_devel+=( libseccomp-devel )
	pkgs_devel+=( libslirp-devel )
	pkgs_devel+=( libssh-devel )
	pkgs_devel+=( libxdp-devel )
	pkgs_devel+=( lzo-devel )
	pkgs_devel+=( numactl-devel )        # numaif.h
	pkgs_devel+=( pixman-devel )
	pkgs_devel+=( python3-devel )
	pkgs_devel+=( rdma-core-devel )
	pkgs_devel+=( snappy-devel )
	pkgs_devel+=( systemd-devel )
	pkgs_devel+=( systemtap-sdt-devel )
	pkgs_devel+=( usbredir-devel )
	pkgs_devel+=( zlib-devel )

	pkgs_docs+=( python3-sphinx_rtd_theme )

	pkgs_math+=( fftw-devel )

	pkgs_media+=( ffmpeg-free )
	[[ ${have_3rd_party} ]] && pkgs_media+=( ${pkgs_media_3rd[@]} )

	pkgs_db+=( libpq-devel )

	pkgs_storage+=( device-mapper )
	pkgs_storage+=( device-mapper-multipath )

	pkgs_virt+=( edk2-ovmf )
	pkgs_virt+=( libvirt )
	pkgs_virt+=( qemu-kvm )
	# Add more
	if [[ $(is_os fedora) ]]; then
		pkgs_virt+=( qemu-system-loongarch64 edk2-loongarch64 )
		pkgs_virt+=( qemu-system-riscv edk2-riscv64 )
	fi

	pkgs_net+=( httpd )
	pkgs_net+=( libxdp libxdp-static )

	if [[ ${IS_DNF5} ]] && [[ ${force} ]]; then
		dnf_args+=( --skip-unavailable )
	fi
	[[ ${force} ]] && dnf_args+=( --skip-broken )
	[[ ${force} ]] && dnf_args+=( --nogpgcheck )

	return 0
}

apt_add_packages()
{
	if [[ $(uname -m) == x86_64 ]]; then
		pkgs_base+=( libc6-dev-i386 )
	fi
	pkgs_base+=( binutils-dev )
	pkgs_base+=( bpfcc-tools )
	pkgs_base+=( build-essential )
	pkgs_base+=( clang-format )
	pkgs_base+=( dwarfdump )
	pkgs_base+=( iproute2 )             # ss, tc
	pkgs_base+=( libaio-dev )           # aio
	pkgs_base+=( libbpfcc )
	pkgs_base+=( libbpfcc-dev )
	pkgs_base+=( libcapstone-dev )
	pkgs_base+=( libc6-dev )
	pkgs_base+=( libc-bin )
	pkgs_base+=( libgmp-dev )
	pkgs_base+=( libmpfr-dev )
	pkgs_base+=( libmpich-dev )         # MPI
	pkgs_base+=( libncurses-dev )
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
	pkgs_base+=( gnu-which )

	pkgs_net+=( apache2 )
	pkgs_net+=( libxdp1 )

	pkgs_compiler+=( build-essential )
	pkgs_compiler+=( gcc-doc )
	pkgs_compiler+=( gcc-multilib )
	pkgs_compiler+=( libatomic1 )
	pkgs_compiler+=( lua5.4 )
	pkgs_compiler+=( rust-all )

	pkgs_devel+=( cyrus-dev )
	pkgs_devel+=( libaio-dev )
	pkgs_devel+=( libattr1-dev )
	pkgs_devel+=( libblockdev-mpath-dev )
	pkgs_devel+=( libbpf-dev )           # libbpf
	pkgs_devel+=( libcap-dev )
	pkgs_devel+=( libcap-ng-dev )
	pkgs_devel+=( libfdt-dev )
	pkgs_devel+=( libglib2.0-dev )
	pkgs_devel+=( libiscsi-dev )
	pkgs_devel+=( liblzo2-dev )
	pkgs_devel+=( libnuma-dev )
	pkgs_devel+=( libpng-dev )
	pkgs_devel+=( librbd-dev )
	pkgs_devel+=( libseccomp-dev )
	pkgs_devel+=( libselinux1-dev )
	pkgs_devel+=( libslirp-dev )
	pkgs_devel+=( libsnappy-dev )
	pkgs_devel+=( libssh-dev )
	pkgs_devel+=( libusbredirhost-dev )
	pkgs_devel+=( libpmem-dev )
	pkgs_devel+=( libpixman-1-dev )
	pkgs_devel+=( librdmacm-dev )
	pkgs_devel+=( libxdp-dev )
	pkgs_devel+=( python3-dev )
	pkgs_devel+=( python3-systemd )
	pkgs_devel+=( systemtap-sdt-dev )
	pkgs_devel+=( zlib1g-dev )

	pkgs_docs+=( python3-sphinx-rtd-theme )

	pkgs_fs+=( unionfs-fuse )

	pkgs_math+=( fftw-dev )

	pkgs_media+=( ffmpeg )

	pkgs_container+=( cgroup-tools )
	pkgs_container+=( libcgroup-dev )

	pkgs_storage+=( libdevmapper-dev )

	pkgs_virt+=( binfmt-support )
	pkgs_virt+=( libvirt0 )
	pkgs_virt+=( qemu-system )
	pkgs_virt+=( qemu-system-misc )

	pkgs_desktop+=( libgtk-3-dev )
	pkgs_desktop+=( tigervnc-common )
	pkgs_desktop+=( tigervnc-standalone-server )
	pkgs_desktop+=( tigervnc-viewer )

	[[ ${force} ]] && apt_args+=( --fix-missing )
	[[ ${force} ]] && apt_args+=( -f )

	return 0
}

# __main__

if [[ $(is_os centos) ]]; then
	dnf_args+=( --enablerepo=crb,powertools )
fi

os_packages

[[ ${have_base} ]] && pkgs+=( ${pkgs_base[@]} )
[[ ${have_fs} ]] && pkgs+=( ${pkgs_fs[@]} )
[[ ${have_compiler} ]] && pkgs+=( ${pkgs_compiler[@]} )
[[ ${have_build} ]] && pkgs+=( ${pkgs_build[@]} )
[[ ${have_docs} ]] && pkgs+=( ${pkgs_docs[@]} )
[[ ${have_devel} ]] && pkgs+=( ${pkgs_devel[@]} )
[[ ${have_container} ]] && pkgs+=( ${pkgs_container[@]} )
[[ ${have_virt} ]] && pkgs+=( ${pkgs_virt[@]} )
[[ ${IS_PHY} ]] && [[ ${have_desktop} ]] && pkgs+=( ${pkgs_desktop[@]} )
[[ ${have_math} ]] && pkgs+=( ${pkgs_math[@]} )
[[ ${have_media} ]] && pkgs+=( ${pkgs_media[@]} )
[[ ${have_bench} ]] && pkgs+=( ${pkgs_bench[@]} )
[[ ${have_db} ]] && pkgs+=( ${pkgs_db[@]} )
[[ ${have_storage} ]] && pkgs+=( ${pkgs_storage[@]} )
[[ ${have_net} ]] && pkgs+=( ${pkgs_net[@]} )

# Filter out skip packages
for p in ${pkgs_skip[@]}
do
	for ((i = 0; i < ${#pkgs[@]}; i++))
	do
		if [[ ${p} == ${pkgs[i]} ]]; then
			unset pkgs[i] 2>&1 >/dev/null
		fi
	done
done

if [[ ! -z "${pkgs[@]}" ]]; then
	os_install $(echo ${pkgs[@]} | sort | uniq)
fi

# Install python3 pip wheels
if [[ ${have_pip} ]] && [[ -e /usr/bin/pip3 ]]; then
	inst_eval pip3 install "${pip_whls[@]}"
fi
