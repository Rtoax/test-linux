#!/bin/bash
# ref: https://github.com/pmem/run_qemu
#
# usage: [DEP=1] [GDB=1] [GITFS=1] [QEMU=/path/to/qemu-kvm] vm.sh
#
set -e
. /etc/os-release

initramfs=${HOME}/cxl/initramfs.img
vmlinuz=${HOME}/cxl/vmlinuz
qcow2=${HOME}/cxl/vm.qcow2

declare -a qargs

if [[ ${DEP} ]]; then
	case ${ID} in
	fedora|rhel)
		sudo dnf install -y cxl-cli dracut edk2-ovmf
		;;
	debian|ubuntu)
		sudo apt install -u ndctl dracut ovmf
		;;
	*)
		echo >&2 "ERROR: not support ${ID}"
		;;
	esac
fi

[[ ! -e ${vmlinuz} ]] && sudo cp /boot/vmlinuz-$(uname -r) ${vmlinuz}

if ! [[ -e ${initramfs} ]]; then
	sudo dracut --kver $(uname -r) --no-hostonly --verbose --force \
		--install 'insmod rmmod modprobe lspci ndctl cxl lsblk dmidecode tree' \
		--add 'bash systemd kernel-modules fs-lib' \
		--add-drivers 'cxl_acpi cxl_core cxl_mem cxl_pci cxl_pmem cxl_pmu cxl_port' \
		${initramfs}
fi

if ! [[ -e ${qcow2} ]]; then
	sudo ../scripts/rootfs/fedora.sh --rootfs vm.rootfs/ --image ${qcow2} \
		-i cxl-cli -i cxl-libs -i ndctl -i daxctl \
		-i dmidecode -i kmod -i util-linux -i pciutils \
		-i kernel-$(uname -r) \
		-i kernel-modules-$(uname -r) \
		-i kernel-modules-core-$(uname -r) \
		-i kernel-modules-extra-$(uname -r)
fi

# Mount in guest
# $ sudo mount -t virtiofs Git /mnt
if [[ ${GITFS} ]]; then
	sudo /usr/libexec/virtiofsd --socket-path=/var/run/vhost-fs-git.sock -o source=/home/rongtao/Git/ &
	qargs+=( --virtio-fs-sock=/var/run/vhost-fs-git.sock --virtio-fs-tag Git )
fi

qargs+=( --name vm-test-cxl --memory 8GiB )
qargs+=( --kernel ${vmlinuz} )
qargs+=( --initrd ${initramfs} )
[[ ${QEMU} ]] && qargs+=( --qemu ${QEMU} )
[[ ${GDB} ]] && qargs+=( --gdb )
qargs+=( --rootfs ${qcow2} )
qargs+=( --stdio )

qargs+=( --cxl pxb=pxb.1 )
qargs+=( --cxl pxb=pxb.2 )
qargs+=( --cxl rp=rp.1,bus=pxb.1,port=1 )
qargs+=( --cxl rp=rp.2,bus=pxb.2,port=1 )
qargs+=( --cxl switch,bus=rp.1,nport=2,portprefix=sw1 )
qargs+=( --cxl switch,bus=rp.2,nport=2,portprefix=sw2 )
qargs+=( --cxl pmem=pmem.1,bus=sw1.1,lsa=pmem.1.lsa )
qargs+=( --cxl pmem=pmem.2,bus=sw1.2,lsa=pmem.2.lsa )
qargs+=( --cxl vmem=vmem.1,bus=sw2.1,lsa=vmem.1.lsa )
qargs+=( --cxl vmem=vmem.2,bus=sw2.2 ) # vmem could not set lsa

qargs+=( --cxl device=cxl-vmem-4way )

sudo ../scripts/qemu-vm.sh ${qargs[@]} "${@}"

wait
