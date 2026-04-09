#!/bin/bash
# Copyright (C) 2022-2026 Rong Tao
#
set -e

. /etc/os-release

target_lists=(
	aarch64_be-linux-user
	aarch64-linux-user alpha-linux-user armeb-linux-user
	arm-linux-user cris-linux-user hexagon-linux-user
	hppa-linux-user i386-linux-user
	loongarch64-linux-user m68k-linux-user
	microblazeel-linux-user microblaze-linux-user
	mips64el-linux-user mips64-linux-user
	mipsel-linux-user mips-linux-user
	mipsn32el-linux-user mipsn32-linux-user
	or1k-linux-user ppc64le-linux-user ppc64-linux-user
	ppc-linux-user riscv32-linux-user riscv64-linux-user
	s390x-linux-user sh4eb-linux-user sh4-linux-user
	sparc32plus-linux-user sparc64-linux-user
	sparc-linux-user x86_64-linux-user
	xtensaeb-linux-user xtensa-linux-user
	aarch64-softmmu alpha-softmmu arm-softmmu
	avr-softmmu cris-softmmu hppa-softmmu i386-softmmu
	loongarch64-softmmu m68k-softmmu
	microblazeel-softmmu microblaze-softmmu
	mips64el-softmmu mips64-softmmu mipsel-softmmu
	mips-softmmu or1k-softmmu ppc64-softmmu ppc-softmmu
	riscv32-softmmu riscv64-softmmu rx-softmmu
	s390x-softmmu sh4eb-softmmu sh4-softmmu
	sparc64-softmmu sparc-softmmu tricore-softmmu
	x86_64-softmmu xtensaeb-softmmu xtensa-softmmu
)

target_list="$(uname -m)-softmmu"

qemu_rootdir=
qemu_builddir=build

# -ba: build for all
# -bd: install depends
# -bc: configure
# -bm: make
build_run_item=a

compiler=gcc
compiler_cc=

make_exe=
declare -a make_args
make_noerr=

# arguments of configure
declare -a config_args

jobs=
declare -a dnf_args

declare -a rpm_deps deb_deps

builddeps_only=

verbose=

disable_lto=

dry_run=
__eval__() {
	if [[ ${dry_run} ]]; then
		echo CMD: "$@"
	else
		eval "$@"
	fi
}

readonly basearch=$(uname -m)

# qemu feature, if got features, replace disable_everything with FEATUREs
# GET: ../configure -h | grep '^  [a-z]' | awk '{print $1}'
# REPLACE:
#   feature: vhost-net
#   disable format: --disable-vhost-net
#   enable format:  --enable-vhost-net
declare -a all_support_features

# qemu configure --disable-FEATURE
# GET: ../configure -h | grep "^  \--disable" | awk '{print $1}'
declare -a can_disable_features


declare -a disable_everything
disable_everything+=("--disable-alsa")
disable_everything+=("--disable-attr")
disable_everything+=("--disable-auth-pam")
disable_everything+=("--disable-avx2")
disable_everything+=("--disable-avx512f")
disable_everything+=("--disable-blkio")
disable_everything+=("--disable-block-drv-whitelist-in-tools")
disable_everything+=("--disable-bochs")
disable_everything+=("--disable-bpf")
disable_everything+=("--disable-brlapi")
disable_everything+=("--disable-bsd-user")
disable_everything+=("--disable-bzip2")
disable_everything+=("--disable-cap-ng")
disable_everything+=("--disable-capstone")
disable_everything+=("--disable-cfi")
disable_everything+=("--disable-cfi-debug")
disable_everything+=("--disable-cloop")
disable_everything+=("--disable-cocoa")
disable_everything+=("--disable-coreaudio")
disable_everything+=("--disable-coroutine-pool")
disable_everything+=("--disable-crypto-afalg")
disable_everything+=("--disable-curl")
disable_everything+=("--disable-curses")
disable_everything+=("--disable-dbus-display")
disable_everything+=("--disable-debug-info")
disable_everything+=("--disable-debug-mutex")
disable_everything+=("--disable-debug-tcg")
disable_everything+=("--disable-dmg")
disable_everything+=("--disable-docs")
disable_everything+=("--disable-dsound")
disable_everything+=("--disable-fdt")
disable_everything+=("--disable-fuse")
disable_everything+=("--disable-fuse-lseek")
disable_everything+=("--disable-gcrypt")
disable_everything+=("--disable-gettext")
disable_everything+=("--disable-gio")
disable_everything+=("--disable-glusterfs")
disable_everything+=("--disable-gnutls")
disable_everything+=("--disable-gtk")
disable_everything+=("--disable-guest-agent")
disable_everything+=("--disable-guest-agent-msi")
disable_everything+=("--disable-hax")
disable_everything+=("--disable-hvf")
disable_everything+=("--disable-iconv")
disable_everything+=("--disable-jack")
disable_everything+=("--disable-kvm")
disable_everything+=("--disable-l2tpv3")
disable_everything+=("--disable-libdaxctl")
disable_everything+=("--disable-libiscsi")
disable_everything+=("--disable-libnfs")
disable_everything+=("--disable-libpmem")
disable_everything+=("--disable-libssh")
disable_everything+=("--disable-libudev")
disable_everything+=("--disable-libusb")
disable_everything+=("--disable-linux-aio")
disable_everything+=("--disable-linux-io-uring")
disable_everything+=("--disable-linux-user")
disable_everything+=("--disable-live-block-migration")
disable_everything+=("--disable-lto")
disable_everything+=("--disable-lzfse")
disable_everything+=("--disable-lzo")
disable_everything+=("--disable-malloc-trim")
disable_everything+=("--disable-membarrier")
disable_everything+=("--disable-modules")
disable_everything+=("--disable-module-upgrades")
disable_everything+=("--disable-mpath")
disable_everything+=("--disable-multiprocess")
disable_everything+=("--disable-netmap")
disable_everything+=("--disable-nettle")
disable_everything+=("--disable-numa")
disable_everything+=("--disable-nvmm")
disable_everything+=("--disable-opengl")
disable_everything+=("--disable-oss")
disable_everything+=("--disable-pa")
disable_everything+=("--disable-parallels")
disable_everything+=("--disable-pie")
disable_everything+=("--disable-pvrdma")
disable_everything+=("--disable-qcow1")
disable_everything+=("--disable-qed")
disable_everything+=("--disable-qga-vss")
disable_everything+=("--disable-qom-cast-debug")
disable_everything+=("--disable-rbd")
disable_everything+=("--disable-rdma")
disable_everything+=("--disable-replication")
disable_everything+=("--disable-rng-none")
disable_everything+=("--disable-safe-stack")
disable_everything+=("--disable-sanitizers")
disable_everything+=("--disable-sdl")
disable_everything+=("--disable-sdl-image")
disable_everything+=("--disable-seccomp")
disable_everything+=("--disable-selinux")
disable_everything+=("--disable-slirp")
disable_everything+=("--disable-slirp-smbd")
disable_everything+=("--disable-smartcard")
disable_everything+=("--disable-snappy")
disable_everything+=("--disable-sndio")
disable_everything+=("--disable-sparse")
disable_everything+=("--disable-spice")
disable_everything+=("--disable-spice-protocol")
disable_everything+=("--disable-strip")
disable_everything+=("--disable-system")
disable_everything+=("--disable-tcg")
disable_everything+=("--disable-tools")
disable_everything+=("--disable-tpm")
disable_everything+=("--disable-u2f")
disable_everything+=("--disable-usb-redir")
disable_everything+=("--disable-user")
disable_everything+=("--disable-vde")
disable_everything+=("--disable-vdi")
disable_everything+=("--disable-vhost-crypto")
disable_everything+=("--disable-vhost-kernel")
disable_everything+=("--disable-vhost-net")
disable_everything+=("--disable-vhost-user")
disable_everything+=("--disable-vhost-user-blk-server")
disable_everything+=("--disable-vhost-vdpa")
disable_everything+=("--disable-virglrenderer")
disable_everything+=("--disable-virtfs")
disable_everything+=("--disable-virtiofsd")
disable_everything+=("--disable-vnc")
disable_everything+=("--disable-vnc-jpeg")
disable_everything+=("--disable-png")
disable_everything+=("--disable-vnc-sasl")
disable_everything+=("--disable-vte")
disable_everything+=("--disable-vvfat")
disable_everything+=("--disable-werror")
disable_everything+=("--disable-whpx")
disable_everything+=("--disable-xen")
disable_everything+=("--disable-xen-pci-passthrough")
disable_everything+=("--disable-xkbcommon")
disable_everything+=("--disable-zstd")
disable_everything+=("--with-git-submodules=ignore")
disable_everything+=("--without-default-devices")

declare -a enable_list
declare -a remove_features
declare -a add_features

update_enable_list()
{
	enable_list+=("--enable-attr")
	enable_list+=("--enable-cap-ng")
	enable_list+=("--enable-capstone")
	enable_list+=("--enable-coroutine-pool")
	enable_list+=("--enable-curl")
	enable_list+=("--enable-debug-info")
	enable_list+=("--enable-docs")
	enable_list+=("--enable-fdt=system")
	enable_list+=("--enable-gnutls")
	enable_list+=("--enable-guest-agent")
	enable_list+=("--enable-iconv")
	enable_list+=("--enable-kvm")
	enable_list+=("--enable-libssh")
	enable_list+=("--enable-libusb")
	enable_list+=("--enable-libudev")
	enable_list+=("--enable-linux-aio")
	enable_list+=("--enable-lzo")
	enable_list+=("--enable-malloc-trim")
	enable_list+=("--enable-modules")
	enable_list+=("--enable-mpath")
	enable_list+=("--enable-numa")
	enable_list+=("--enable-opengl")
	enable_list+=("--enable-pa")
	enable_list+=("--enable-pie")
	enable_list+=("--enable-rbd")
	enable_list+=("--enable-rdma")
	enable_list+=("--enable-seccomp")
	enable_list+=("--enable-selinux")
	enable_list+=("--enable-slirp")
	enable_list+=("--enable-snappy")
	enable_list+=("--enable-spice-protocol")
	enable_list+=("--enable-system")
	enable_list+=("--enable-tcg")
	enable_list+=("--enable-tools")
	enable_list+=("--enable-tpm")
	enable_list+=("--enable-usb-redir")
	enable_list+=("--enable-vdi")
	enable_list+=("--enable-virtiofsd")
	enable_list+=("--enable-vhost-kernel")
	enable_list+=("--enable-vhost-net")
	enable_list+=("--enable-vhost-user")
	enable_list+=("--enable-vhost-user-blk-server")
	enable_list+=("--enable-vhost-vdpa")
	enable_list+=("--enable-vnc")
	enable_list+=("--enable-pixman")
	enable_list+=("--enable-png")
	enable_list+=("--enable-vnc-sasl")
	enable_list+=("--enable-werror")
	enable_list+=("--enable-xkbcommon")

	# Arch
	if [[ "$basearch" == "x86_64" ]]; then
	enable_list+=("--enable-avx2")
	enable_list+=("--enable-libpmem")
	fi
}

# See redhat-rpm-config:/usr/lib/rpm/redhat/macros
declare -a extra_ldflags

# Common
extra_ldflags+=("-Wl,-z,relro")
extra_ldflags+=("-Wl,--as-needed")
extra_ldflags+=("-Wl,-z,now")
extra_ldflags+=("-Wl,--build-id=sha1")

update_extra_ldflags()
{
	case $compiler in
	# GCC toolchain
	gcc)
	extra_ldflags+=("-specs=/usr/lib/rpm/redhat/redhat-hardened-ld")
	extra_ldflags+=("-specs=/usr/lib/rpm/redhat/redhat-annobin-cc1")
	extra_ldflags+=("-specs=/usr/lib/rpm/redhat/redhat-package-notes")
	;;
	# Clang toolchain
	clang)
	[[ -z $disable_lto ]] && extra_ldflags+=("-flto")
	extra_ldflags+=("-fno-openmp-implicit-rpath")
	;;
	esac
}

# See redhat-rpm-config:/usr/lib/rpm/redhat/rpmrc
declare -a extra_cflags

# Common
extra_cflags+=("-O2")
extra_cflags+=("-fexceptions")
extra_cflags+=("-g")
extra_cflags+=("-grecord-gcc-switches")
extra_cflags+=("-pipe")
extra_cflags+=("-Wall")
extra_cflags+=("-Werror=format-security")
extra_cflags+=("-Wp,-D_FORTIFY_SOURCE=2")
extra_cflags+=("-Wp,-D_GLIBCXX_ASSERTIONS")
extra_cflags+=("-fstack-protector-strong")
extra_cflags+=("-m64")
if [[ "$basearch" == "x86_64" ]]; then
extra_cflags+=("-march=x86-64-v2")
fi
extra_cflags+=("-mtune=generic")
extra_cflags+=("-mbranch-protection=standard")
extra_cflags+=("-fasynchronous-unwind-tables")
extra_cflags+=("-fstack-clash-protection")
extra_cflags+=("-Wno-string-plus-int")

update_extra_cflags()
{
	case $compiler in
	# GCC toolchain
	gcc)
	[[ -z $disable_lto ]] && extra_cflags+=("-flto=auto")
	[[ -z $disable_lto ]] && extra_cflags+=("-ffat-lto-objects")
	extra_cflags+=("-specs=/usr/lib/rpm/redhat/redhat-hardened-cc1")
	extra_cflags+=("-fcf-protection")
	;;
	# Clang toolchain
	clang)
	extra_cflags+=("\--config /usr/lib/rpm/redhat/redhat-hardened-clang.cfg")
	;;
	esac
}

# $1 - feature name, such as vhost-net
# echo: 0-have, 1-don't have
have_feature()
{
	local feature=$1

	# FIXME: skip some necessary feature, find a good way
	for skip in ${can_disable_features[@]} '*=*'
	do
		if [[ $feature == $skip ]]; then
			echo 0
			return 0
		fi
	done

	# For each support features
	for support in ${all_support_features[@]}
	do
		# Found in support features
		if [[ $feature == $support ]]; then
			echo 0
			return 0
		fi
	done

	# Not found
	echo 1
	return 0
}

update_features()
{
	[[ ! -e ../configure ]] && \
		echo "No ../configure in $(realpath .), root: ${rootdir}" && \
		exit 1

	# qemu feature, if got features, replace disable_everything with FEATUREs
	# GET: ../configure -h | grep '^  [a-z]' | awk '{print $1}'
	#   feature: vhost-net
	local features=$(../configure -h | grep '^  [a-z]' | awk '{print $1}')

	# GET: ../configure -h | grep "^  \--disable" | awk '{print $1}'
	# format: --disable-werror
	local disables=$(../configure -h | grep "^  \--disable" | awk '{print $1}')


	# Update ALL features
	for feature in ${features}
	do
		all_support_features+=( "${feature}" )
	done

	# Update CAN disable features
	for feature in ${disables}
	do
		# format: --disable-werror
		# 10 means: --disable-werror to werror
		can_disable_features+=( "${feature:10}" )
	done


	# Update disable features
	#  1. make it empty
	[[ ! -z ${all_support_features} ]] && disable_everything=()
	#  2. Update
	for ((i = 0; i < ${#all_support_features[@]}; i++))
	do
		disable_everything+=( "--disable-${all_support_features[$i]}" )
	done

	# Update enable features
	local i
	local nr_list=${#enable_list[@]}
	for ((i = 0; i < ${nr_list}; i++))
	do
		# --enable-vhost-net -> vhost-net
		local f=${enable_list[$i]:9}
		local ret=$(have_feature ${f})
		case $ret in
		0)
			# Has feature, do nothing
			;;
		1)
			# Delete this feature
			unset enable_list[$i]
			;;
		esac
	done

	# Remove features
	local _i_ _j_
	local nr_list=${#enable_list[@]}
	for ((_i_ = 0; _i_ < ${nr_list}; _i_++))
	do
		for ((_j_ = 0; _j_ < ${#remove_features[@]}; _j_++))
		do
			# --enable-vhost-net -> vhost-net
			local enable_feature=${enable_list[$_i_]:9}
			local remove_feature=${remove_features[$_j_]}

			if [[ $enable_feature == $remove_feature ]]; then
				unset enable_list[$_i_]
				break
			fi
		done
	done

	# Add features
	for feature in ${add_features[@]}
	do
		enable_list+=( "--enable-${feature}" )
	done

	# Print debug information
	echo "ALL FEATUREs: ${all_support_features[@]}"
	echo "CAN Disable Fearute: ${can_disable_features[@]}"
	echo "Disable Everything: ${disable_everything[@]}"
	echo "Enable FEATUREs: ${enable_list[@]}"
}

run_configure()
{
	local blkdrv_rw_list="qcow2,raw,file,host_device,nbd,iscsi,rbd,blkdebug,luks,null-co,nvme,copy-on-read,throttle,compress"
	local blkdrv_ro_list="vdi,vmdk,vhdx,vpc,https,ssh"

	[[ -z $compiler_cc ]] && compiler_cc=${compiler}

	# see upstream qemu commit 66e2c6cbacea("configure: use 'mkvenv ensure
	# meson' to bootstrap meson")
	if [[ ! -z "$(../configure --help | grep  '\-\-meson' 2>/dev/null)" ]]; then
		config_args+=( --meson=/usr/bin/meson )
	fi

	local with_git=$( ../configure  --help 2>&1 | grep with-git || true )
	if [[ ! -z ${with_git} ]]; then
		config_args+=( --with-git=git )
	fi

	__eval__ \
	../configure \
	--cc=${compiler_cc} \
	--cxx=/bin/false \
	--prefix=/usr \
	--libdir=/usr/lib64 \
	--datadir=/usr/share \
	--sysconfdir=/etc \
	--interp-prefix=/usr/qemu-%M \
	--localstatedir=/var \
	--docdir=/usr/share/doc \
	--libexecdir=/usr/libexec \
	--extra-ldflags="${extra_ldflags[@]}" \
	--extra-cflags="${extra_cflags[@]}" \
	--with-suffix=qemu-kvm \
	--firmwarepath=/usr/share/qemu-firmware:/usr/share/ipxe/qemu:/usr/share/seavgabios:/usr/share/seabios \
	--with-coroutine=ucontext \
	--tls-priority=@QEMU,SYSTEM \
	${disable_everything[@]} \
	--target-list=$target_list \
	--block-drv-rw-whitelist=${blkdrv_rw_list} \
	--block-drv-ro-whitelist=${blkdrv_ro_list} \
	${enable_list[@]} \
	${config_args[@]}

    echo "config-host.mak contents:"
    echo "==="
    cat config-host.mak
    echo "==="
}

rpm_deps+=("alsa-lib-devel")
rpm_deps+=("brlapi-devel")
rpm_deps+=("bzip2-devel")
rpm_deps+=("capstone-devel")
rpm_deps+=("clang")
rpm_deps+=("cyrus-sasl-devel")
rpm_deps+=("daxctl-devel")
rpm_deps+=("device-mapper-multipath-devel")
rpm_deps+=("fuse3-devel")
rpm_deps+=("fuse-devel")
rpm_deps+=("gcc")
rpm_deps+=("gettext")
rpm_deps+=("git")
rpm_deps+=("glib2-devel")
rpm_deps+=("glib2-static")
rpm_deps+=("glibc-static")
rpm_deps+=("glusterfs-api-devel")
rpm_deps+=("gnutls-devel")
rpm_deps+=("gtk3-devel")
rpm_deps+=("hostname")
rpm_deps+=("libaio-devel")
rpm_deps+=("libattr-devel")
rpm_deps+=("libbpf-devel")
rpm_deps+=("libcacard-devel")
rpm_deps+=("libcap-ng-devel")
rpm_deps+=("libcurl-devel")
rpm_deps+=("libfdt-devel")
rpm_deps+=("libiscsi-devel")
rpm_deps+=("libjpeg-devel")
rpm_deps+=("libnfs-devel")
if [[ "$basearch" == "x86_64" ]]; then
rpm_deps+=("libpmem-devel")
fi
rpm_deps+=("libpng-devel")
rpm_deps+=("librbd-devel")
rpm_deps+=("libseccomp-devel")
rpm_deps+=("libselinux-devel")
rpm_deps+=("libslirp-devel")
rpm_deps+=("libssh-devel")
rpm_deps+=("libtasn1-devel")
rpm_deps+=("libudev-devel")
rpm_deps+=("liburing-devel")
rpm_deps+=("libusbx-devel")
rpm_deps+=("libzstd-devel")
rpm_deps+=("lzo-devel")
rpm_deps+=("make")
rpm_deps+=("meson")
rpm_deps+=("ncurses-devel")
rpm_deps+=("numactl-devel")
rpm_deps+=("pam-devel")
rpm_deps+=("pcre2-static")
rpm_deps+=("perl-Test-Harness")
rpm_deps+=("pixman-devel")
rpm_deps+=("pipewire-jack-audio-connection-kit-devel")
rpm_deps+=("libepoxy-devel")
rpm_deps+=("mesa-libgbm-devel")
rpm_deps+=("libdrm-devel")
rpm_deps+=("libxkbcommon-devel")
rpm_deps+=("pulseaudio-libs-devel")
rpm_deps+=("python3-devel")
rpm_deps+=("python3-sphinx")
rpm_deps+=("python3-sphinx_rtd_theme")
rpm_deps+=("rdma-core-devel")
rpm_deps+=("SDL2-devel")
rpm_deps+=("SDL2_image-devel")
rpm_deps+=("snappy-devel")
rpm_deps+=("spice-protocol")
rpm_deps+=("spice-server-devel")
rpm_deps+=("systemd-devel")
rpm_deps+=("systemtap")
rpm_deps+=("systemtap-sdt-devel")
rpm_deps+=("texinfo")
rpm_deps+=("usbredir-devel")
rpm_deps+=("virglrenderer-devel")
rpm_deps+=("vte291-devel")
rpm_deps+=("xen-devel")
rpm_deps+=("zlib-devel")
rpm_deps+=("zlib-static")

deb_deps+=( libpulse-dev )
deb_deps+=( libspice-protocol-dev )
deb_deps+=( resource-agents-extra )

install_deps()
{
	if [[ " ubuntu " =~ " ${ID} " ]]; then
		__eval__ sudo apt install -y ${deb_deps[@]}
	else
		__eval__ sudo dnf install ${dnf_args[@]} -y ${rpm_deps[@]}
	fi
}

__usage__()
{
	echo -e "
NAME
    qemu-compile - compile qemu

BUILDING
    qemu-compile [-ba|-bd|-bc|-bm] [args]

ARGUMENT

   -b, --build [a|d|c|m]
                      build options, default: $build_run_item

       -ba            Perform a full build (default)
       -bd            builddeps, same as --builddeps
       -bc            configure
       -bm            compile code

       --builddeps    only install depends and return
       --skip-broken  see dnf(8)
       --allowerasing see dnf(8)

   -t, --target [TARGET]
                      set target list (default: ${target_list})
                      (may be listed multiple times, support target see --target-list)
       --target-list  show target list

   -r, --rootdir [DIR]
                      qemu source code directory
       --builddir [DIR]
                      qemu build directory, default: $qemu_builddir

   -c, --compiler [COMPILER]
                      specify compiler, gcc or clang, default: $compiler
       --cc           specify compiler cc execution, same as 'configure --cc'
                      default: $compiler_cc (equal to -c,--compiler)

   -j, --jobs [NUM]   how many processes use to make

   -m, --make [CMD]   specify 'make' execution, example: --make mymake
\033[2m
                      $ cat mymake
                      #!/bin/bash
                      make \"\$@\"
\033[m

   --make-arg [ARG]   add extra arguments for make/-m,--make
                      (may be listed multiple times)
   --make-noerr       'set +e' during make or custom make

   --disable-lto      disable LTO

   --disable [ATTR]   disable an feature (may be listed multiple times)
                      for example:
                      \033[2m--disable=kvm --disable=attr\033[m

   --enable [ATTR]    enable an feature (may be listed multiple times)
                      for example:
                      \033[2m--enable=kvm --enable=safe-stack\033[m

   -d, --dry-run      only print commands
   -v, --verbose      show detail when make
   -h, --help         show this help information

SEE ALSO
    ninja, make
" | more

	exit ${1-0}
}

set_build_run_item()
{
	local item=$1

	[[ -z $item ]] && echo "ERROR: Must set build option by -b." && exit 1

	case $item in
	# All, configure, make
	a | c | m)
		[[ -z $qemu_rootdir ]] && echo "Need rootdir: -r, --rootdir" && exit 1
		;;
	# depends
	d)
		builddeps_only=YES
		;;
	*)
		echo "Unknown build option <$item>, see -h"
		exit 1
		;;
	esac

	build_run_item=$item
}

__main__()
{
	TEMP=$(getopt \
		--options hvdr:j:c:b:m:t: \
		--long help \
		--long verbose \
		--long dry-run \
		--long rootdir: \
		--long build: \
		--long builddir: \
		--long jobs: \
		--long make: \
		--long make-arg: \
		--long make-noerr \
		--long compiler: \
		--long cc: \
		--long builddeps \
		--long skip-broken \
		--long allowerasing \
		--long disable-lto \
		--long disable: \
		--long enable: \
		--long target: \
		--long target-list \
		-n qemu-compile -- "$@")

	test $? != 0 && __usage__ 1

	eval set -- "$TEMP"

	local tmp_build_run_item

	while true; do
		case $1 in
		-h | --help)
			shift
			__usage__
			;;
		-v | --verbose)
			shift
			verbose="YES"
			;;
		-d | --dry-run)
			shift
			dry_run="YES"
			;;
		-r | --rootdir)
			shift
			qemu_rootdir=$1
			[[ ! -d $qemu_rootdir ]] && \
				echo "Invalide rootdir: ${qemu_rootdir}" && exit 1
			shift
			;;
		--builddir)
			shift
			qemu_builddir=$1
			shift
			;;
		-j | --jobs)
			shift
			jobs=$1
			shift
			;;
		-m | --make)
			shift
			make_exe=$1
			shift
			;;
		--make-arg)
			shift
			make_args+=( "$1" )
			shift
			;;
		--make-noerr)
			shift
			make_noerr="YES"
			;;
		-c | --compiler)
			shift
			compiler=$1
			shift
			;;
		--cc)
			shift
			compiler_cc=$1
			shift
			;;
		-b | --build)
			shift
			tmp_build_run_item=$1
			shift
			;;
		-t | --target)
			shift
			target_list=${target_list},$1
			shift
			;;
		--target-list)
			shift
			echo "${target_lists[@]}"
			exit 0
			;;
		--builddeps)
			shift
			builddeps_only=YES
			;;
		--skip-broken)
			shift
			dnf_args+=("--skip-broken")
			;;
		--allowerasing)
			shift
			dnf_args+=("--allowerasing")
			;;
		--disable-lto)
			shift
			disable_lto="YES"
			;;
		--disable)
			shift
			remove_features+=( "$1" )
			shift
			;;
		--enable)
			shift
			add_features+=( "$1" )
			shift
			;;
		--)
			shift
			break
			;;
		esac
	done

	set_build_run_item $tmp_build_run_item

	# builddeps
	if [[ $build_run_item == a ]] || \
		[[ $build_run_item == d ]] || \
		[[ ! -z $builddeps_only ]]; then
		install_deps
		[[ ! -z $builddeps_only ]] && exit 0
	fi

	return 0
}

cmd_qemu_compile()
{
	__main__ "$@"

	update_enable_list
	update_extra_ldflags
	update_extra_cflags

	local BUILDDIR=${qemu_rootdir}/${qemu_builddir}

	[[ ! -d ${BUILDDIR} ]] && mkdir -p ${BUILDDIR}

	pushd ${BUILDDIR}

	# configure
	if [[ $build_run_item == a ]] || [[ $build_run_item == c ]]; then
		update_features
		run_configure
	fi

	popd

	# make
	if [[ $build_run_item == a ]] || [[ $build_run_item == m ]]; then

		local MAKE

		[[ ! -z $make_exe ]] && MAKE=$make_exe
		[[ -z $MAKE ]] && MAKE=make

		# make no error
		[[ ! -z ${make_noerr} ]] && set +e

		__eval__ ${MAKE} \
			${make_args[@]} \
			-C ${BUILDDIR} \
			${jobs:+-j${jobs}} \
			${verbose:+V=1}

		# resume make no error
		[[ ! -z ${make_noerr} ]] && set -e
	fi

	return 0
}

# Start...
case $1 in
-v | --verbose)
	shift
	set -x
	;;
-vv)
	shift
	export PS4='+${BASH_SOURCE}: '
	set -x
	;;
-vvv)
	shift
	export PS4='+${BASH_SOURCE}:${LINENO}: '
	set -x
	;;
-vvvv)
	shift
	export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
	set -x
	;;
esac

cmd_qemu_compile "$@"
