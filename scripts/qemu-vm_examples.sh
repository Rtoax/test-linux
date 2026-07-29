#!/bin/bash
set -e
readonly QEMU_VM_EXAMPLES_ROOT=$(dirname $(realpath $0))

. ${QEMU_VM_EXAMPLES_ROOT}/liblog.sh

qemu() {
	echo -e >&2 "\033[1;32m./qemu-vm.sh ${@}\033[m"
	./qemu-vm.sh "${@}"
}

run() {
	local name=$(mktemp -u vmname-XXXXX)
	qemu --dry-run --name ${name} --kernel vmlinux "${@}"
}

qemu --help
qemu -V --version
qemu --cxl help
qemu --disk help
qemu --uefi help

# Test Basic
run
run --memory 4GiB
run --cpu 10
run --cpu nr=10
run --cpu model=base
run --initrd=initramfs.img --rdinit=/bin/bash --rootfs vm.qcow2

# Test CXL
readonly CXL_DEVS=( cxl-vmem cxl-vmem-lsa cxl-vmem-4way cxl-vmem-4way-switch
			cxl-pmem cxl-pmem-4way cxl-pmem-4way-switch )

run --cxl pxb=pxb.1
run --cxl pxb=pxb.1 --cxl pxb=pxb.2,fmw=1
run --cxl pxb=pxb.1 --cxl pxb=pxb.2,fmw=1 \
	--cxl pxb=pxb.3,fixed-memory-window=2 \
	--cxl pxb=pxb.4,fixed-memory-window=4
run --cxl pxb=pxb.1 --cxl pxb=pxb.2,fmw=1 \
	--cxl pxb=pxb.3,fixed-memory-window=2 \
	--cxl pxb=pxb.4,fixed-memory-window=4 \
	--cxl rp=rp.1,bus=pxb.1,port=1 \
	--cxl root-port=rp.2,bus=pxb.2,port=1

dev_list1=( $(run --cxl device=list) )
dev_list2=( $(run --cxl device=?) )
if [[ "${CXL_DEVS[@]}" != "${dev_list1[@]}" ]] ||
   [[ "${CXL_DEVS[@]}" != "${dev_list2[@]}" ]] ||
   [[ "${dev_list1[@]}" != "${dev_list2[@]}" ]]; then
	error "cxl: get device list failed, expect '${CXL_DEVS[@]}' but get '${dev_list1[@]}' and '${dev_list2[@]}'"
fi
