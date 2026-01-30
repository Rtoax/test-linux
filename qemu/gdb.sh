#!/bin/bash
# Copyright (C) 2022-2026 Rong Tao
#
set -e

declare -a qemu_kvm_args
declare qemu_kvm=""

qemu_kvm_possible_emulators=(
	/usr/libexec/qemu-kvm
	/usr/libexec/qemu-system-$(uname -m)
	/usr/bin/qemu-system-$(uname -m)
	/usr/local/bin/qemu-system-sw64
)

for b in ${qemu_kvm_possible_emulators[@]}
do
	if [[ -e ${b} ]]; then
		qemu_kvm=${b}
		break
	fi
done

if [[ -z ${qemu_kvm} ]]; then
	echo "ERROR: Not found any qemu-kvm emulator"
	exit 1
fi

if [[ $(uname -i) == sw_64 ]]; then
	qemu_kvm_args+=( -machine core3 )
fi

qcow2_file=""
vnc_no=1

vmlinux_file=""
bzImage_file=""

initrd_file=""
kernel_sym_file=kernel.sym

RUNNING_TYPE_VMLINUX="vmlinux"
RUNNING_TYPE_BZIMAGE="bzImage"
RUNNING_TYPE_QCOW2="Qcow2"
running_type=""

# $1 - prefix
echo_bzimage_demo()
{
	local prefix=$1
	echo "
$prefix# Start with bzImage and initramfs.img
$prefix$ ./ostools.sh qemu-gdb \\
$prefix     --bzImage /path/to/bzImage \\
$prefix     --initrd /path/to/initramfs.img
"
}

echo_qcow2_demo()
{
	local prefix=$1
	echo "
$prefix# Start with qcow2
$prefix$ ./ostools.sh qemu-gdb \\
$prefix     --qcow2 /patch/to/image.qcow2
"
}

echo_gdb_vmlinux()
{
	local prefix=$1
	echo "
$prefix$ gdb -q vmlinux
$prefix...
$prefix(gdb) target remote :1234
$prefix(gdb) hbreak start_kernel
$prefix(gdb) c
"
}

__usage__()
{
	echo -e "
$ANSI_BOLD
NAME
$ANSI_RESET
    qemu-gdb - debug Linux Kernel with Qemu+GDB
$ANSI_BOLD
SYNOPSIS
$ANSI_RESET
    qemu-gdb [options]
$ANSI_BOLD
DESCRIPTION
$ANSI_RESET
    Debug Linux Kernel with Qemu+GDB.
$ANSI_BOLD
ARGUMENT
$ANSI_RESET

$ANSI_BOLD  Qemu/KVM argument:$ANSI_RESET

   --qemu-kvm [ELF]   specify qemu-kvm to execute, default: $qemu_kvm

   --qcow2-path [PATH]
                      specify a virtual machine qcow2 file.

$ANSI_BOLD  Kernel relate argument:$ANSI_RESET

   --vmlinux [VMLINUX]
                      specify kernel vmlinux file.
   --bzImage [IMG]    specify kernel bzImage file.

   --initrd [INITRD]  specify initrd/ramdisk/initramfs file.

$ANSI_BOLD  Common argument:$ANSI_RESET

   -h, --help         show this help information

$ANSI_BOLD
DEMOSTRATION
$ANSI_RESET
 $ANSI_UNDERLINE 1.Starting kernel:$ANSI_RESET
$ANSI_GRAY $(echo_bzimage_demo "    ")$ANSI_RESET

 $ANSI_UNDERLINE 2.Running gdb:$ANSI_RESET
$ANSI_GRAY $(echo_gdb_vmlinux "    ")$ANSI_RESET
$(echo_help_copyright)
$ANSI_BOLD
SEE ALSO
$ANSI_RESET
    qemu-kvm(1), gdb(1)
" | more

	exit ${1-0}
}

__main__()
{
	TEMP=$(getopt \
		--options h \
		--long qemu-kvm: \
		--long qcow2-path: \
		--long vmlinux: \
		--long bzImage: \
		--long initrd: \
		--long help \
		-n qemu-gdb -- "$@")

	test $? != 0 && __usage__ 1

	eval set -- "$TEMP"

	echo "$? $TEMP"

	while true; do
		case $1 in
		--qemu-kvm)
			shift
			qemu_kvm=$1
			shift
			;;
		--qcow2-path)
			shift
			qcow2_file=$1
			running_type=$RUNNING_TYPE_QCOW2
			shift
			;;
		--vmlinux)
			shift
			vmlinux_file=$1
			running_type=$RUNNING_TYPE_VMLINUX
			shift
			;;
		--bzImage)
			shift
			bzImage_file=$1
			running_type=$RUNNING_TYPE_BZIMAGE
			shift
			;;
		--initrd)
			shift
			initrd_file=$1
			shift
			;;
		-h|--help)
			shift
			__usage__
			;;
		--)
			shift
			break
			;;
		esac
	done
}

check_qcow2_file()
{
	test -z $qcow2_file && echo "Must specify --qcow2-path" && exit 1
	test ! -f $qcow2_file && echo "$qcow2_file not exist" && exit 1
	qcow2_file=$(realpath $qcow2_file)
}

check_vmlinux_file()
{
	test -z $vmlinux_file && echo "Must specify --vmlinux" && exit 1
	test ! -f $vmlinux_file && echo "$vmlinux_file not exist" && exit 1
	vmlinux_file=$(realpath $vmlinux_file)
}

check_bzimage_file()
{
	test -z $bzImage_file && echo "Must specify --bzImage" && exit 1
	test ! -f $bzImage_file && echo "$bzImage_file not exist" && exit 1
	bzImage_file=$(realpath $bzImage_file)
}

check_initrd_file()
{
	test -z $initrd_file && echo "Must specify --initrd" && exit 1
	test ! -f $initrd_file && echo "$initrd_file not exist" && exit 1
	initrd_file=$(realpath $initrd_file)
}

qemu_kvm_qcow2_gdb()
{
	local gdb_dev=gdb0

	check_qcow2_file

	# -S stops qemu waiting gdb
	# -s makes gdb be able to attach through localhost:1234
	#
	# TODO
	#
	sudo $qemu_kvm \
		-s -S \
		-smp 4 \
		-m 4096 \
		-chardev stdio,id=$gdb_dev \
		-drive if=virtio,file=$qcow2_file,cache=none \
		-device isa-debugcon,iobase=0x402,chardev=$gdb_dev,id=d1 \
		-vga virtio \
		-enable-kvm \
		-vnc :$vnc_no \
		${qemu_kvm_args[@]}
}

qemu_kvm_vmlinux_gdb()
{
	check_vmlinux_file
	check_initrd_file

	# ref: https://kernelgo.org/kernel-debug-using-qemu.html
	# -kernel $vmlinux_file
	# -append "nokaslr earlyprintk=ttyS0 console=ttyS0 tsc=realiable root=/dev/vda rw"
	#
	# TODO
	#
	sudo $qemu_kvm \
		-kernel $vmlinux_file \
		-initrd $initrd_file \
		-nographic \
		-append "console=ttyS0 nokaslr" \
		-smp 4 \
		-m 4096 \
		-enable-kvm \
		-cpu host \
		-s -S \
		${qemu_kvm_args[@]}
}

qemu_kvm_bzImage_gdb()
{
	check_bzimage_file
	check_initrd_file

	sudo $qemu_kvm \
		-cpu host \
		-smp 4 \
		-m 4G \
		-kernel $bzImage_file \
		-initrd $initrd_file \
		-append "root=/dev/vda console=ttyS0 nokaslr other-paras-here-if-needed" \
		-nographic \
		-enable-kvm \
		-net nic,model=virtio \
		-net user,hostfwd=tcp::10022-:22 \
		-s -S \
		-vnc :$vnc_no \
		${qemu_kvm_args[@]}
}

gen_kernel_sym()
{
	objcopy --only-keep-debug $vmlinux_file $kernel_sym_file
}


cmd_qemu_gdb()
{
	__main__ "$@"

	case $running_type in
	$RUNNING_TYPE_BZIMAGE)
		echo ""
		;;
	$RUNNING_TYPE_QCOW2)
		echo ""
		;;
	$RUNNING_TYPE_VMLINUX)
		echo ""
		;;
	*)
		echo "Not support run-type, check with -h"
		exit 1
		;;
	esac

	cat <<-END
RunningType   $running_type
Qemu-kvm      $qemu_kvm

Qcow2         $qcow2_file
vmlinux       $vmlinux_file
bzImage       $bzImage_file
initrd        $initrd_file

END
	echo ""
	read -r -p "Press any key to continue..."

	case $running_type in
	$RUNNING_TYPE_BZIMAGE)
		qemu_kvm_bzImage_gdb
		;;
	$RUNNING_TYPE_QCOW2)
		qemu_kvm_qcow2_gdb
		;;
	$RUNNING_TYPE_VMLINUX)
		qemu_kvm_vmlinux_gdb
		;;
	*)
		__usage__ 0
		;;
	esac

	return 0
}

cmd_qemu_gdb "${@}"
