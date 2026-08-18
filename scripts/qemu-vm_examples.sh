#!/bin/bash
set -eo pipefail
readonly QEMU_VM_EXAMPLES_ROOT=$(dirname $(realpath $0))
readonly DISK_TYPES=( virtio sata nvme nvdimm scsi )

. ${QEMU_VM_EXAMPLES_ROOT}/liblog.sh

readonly LOG=qemu-vm_examples.sh.log

qemu() {
	echo -e >&2 "\033[1;32m./qemu-vm.sh ${@}\033[m" | tee --append ${LOG}
	./qemu-vm.sh "${@}" | tee --append ${LOG}
}

run() {
	local name=$(mktemp -u vmname-XXXXX)
	qemu --dry-run --name ${name} --kernel vmlinux "${@}"
}

cleanup() {
	local err=$?
	if [[ ${err} != 0 ]]; then
		error "Test qemu-vm failed"
	fi
	exit 0
}
trap cleanup EXIT

rm -f ${LOG}

qemu --help
qemu -V --version
qemu --cxl help
qemu --disk help
qemu --uefi help
qemu list -h
qemu list
qemu list --port

# Test Basic
run
run --memory 4GiB
run --cpu 10
run --cpu nr=10
run --cpu model=base
# Test rootfs
run --rootfs vm.qcow2
run --rootfs vm.qcow2,ro
run --rootfs vm.qcow2,rw
run --rootfs file=vm.qcow2,rw
for dt in ${DISK_TYPES[@]}
do
	run --rootfs file=vm.qcow2,rw,type=${dt}
done
run --initrd=initramfs.img --rdinit=/bin/bash --rootfs vm.qcow2

# Test CXL
readonly CXL_DEVS=( cxl-vmem
		    cxl-vmem-lsa
		    cxl-vmem-4way
		    cxl-vmem-4way-dc
		    cxl-vmem-4way-switch
		    cxl-vmem-4way-switch-dc
		    cxl-pmem
		    cxl-pmem-4way
		    cxl-pmem-4way-switch )

# Test CXL builtin devices
dev_list1=( $(run --cxl device=list) )
dev_list2=( $(run --cxl device=?) )
if [[ "${CXL_DEVS[@]}" != "${dev_list1[@]}" ]] ||
   [[ "${CXL_DEVS[@]}" != "${dev_list2[@]}" ]] ||
   [[ "${dev_list1[@]}" != "${dev_list2[@]}" ]]; then
	error "cxl: get device list failed, expect '${CXL_DEVS[@]}' but get '${dev_list1[@]}' and '${dev_list2[@]}'"
fi
for dev in ${CXL_DEVS[@]}; do
	run --memory 5GiB --cxl device=${dev}
done

# Test CXL custom device
cxl_pxb1() {
	run --cxl pxb=pxb.1 "${@}"
}
cxl_pxb2() {
	cxl_pxb1 --cxl pxb=pxb.2,fmw=1 "${@}"
}
cxl_pxb4() {
	cxl_pxb2 \
		--cxl pxb=pxb.3,fixed-memory-window=2 \
		--cxl pxb=pxb.4,fixed-memory-window=4 \
		"${@}"
}
cxl_pxb4_rp4() {
	cxl_pxb4 \
		--cxl rp=rp.1,bus=pxb.1,port=1 \
		--cxl root-port=rp.2,bus=pxb.2,port=1 \
		--cxl root-port=rp.3,bus=pxb.3,port=1 \
		--cxl root-port=rp.4,bus=pxb.4,port=1 \
		"${@}"
}
cxl_pxb4_rp4_sw4() {
	cxl_pxb4_rp4 \
		--cxl switch,bus=rp.1,nport=4,portprefix=sw1 \
		--cxl switch,bus=rp.2,nport=4,portprefix=sw2 \
		--cxl switch,bus=rp.3,nport=4,portprefix=sw3 \
		--cxl switch,bus=rp.4,nport=4,portprefix=sw4 \
		"${@}"
}
cxl_pxb4_rp4_sw4_pmem4() {
	cxl_pxb4_rp4_sw4 \
		--cxl pmem=pmem.1,bus=sw1.1,lsa=pmem.1.lsa,size=2G \
		--cxl pmem=pmem.2,bus=sw1.2,lsa=pmem.2.lsa,size=2G \
		--cxl pmem=pmem.3,bus=sw1.3,lsa=pmem.3.lsa,size=2G \
		--cxl pmem=pmem.4,bus=sw1.4,lsa=pmem.4.lsa,size=2G \
		"${@}"
}
cxl_pxb4_rp4_pmem4() {
	cxl_pxb4_rp4 \
		--cxl pmem=pmem.1,bus=rp.1,lsa=pmem.1.lsa,size=2G \
		--cxl pmem=pmem.2,bus=rp.2,lsa=pmem.2.lsa,size=2G \
		--cxl pmem=pmem.3,bus=rp.3,lsa=pmem.3.lsa,size=2G \
		--cxl pmem=pmem.4,bus=rp.4,lsa=pmem.4.lsa,size=2G \
		"${@}"
}
cxl_pxb4_rp4_vmem4() {
	cxl_pxb4_rp4 \
		--cxl vmem=vmem.1,bus=rp.1,size=2G \
		--cxl vmem=vmem.2,bus=rp.2,size=2G \
		--cxl vmem=vmem.3,bus=rp.3,lsa=vmem.3.lsa,size=2G \
		--cxl vmem=vmem.4,bus=rp.4,lsa=vmem.4.lsa,size=2G \
		"${@}"
}
cxl_pxb4_rp4_sw4_vmem4() {
	cxl_pxb4_rp4_sw4 \
		--cxl vmem=vmem.1,bus=sw1.1,size=2G \
		--cxl vmem=vmem.2,bus=sw1.2,size=2G \
		--cxl vmem=vmem.3,bus=sw1.3,lsa=vmem.3.lsa,size=2G \
		--cxl vmem=vmem.4,bus=sw1.4,lsa=vmem.4.lsa,size=2G \
		"${@}"
}
cxl_pxb4_rp4_sw4_vmem4_dc() {
	cxl_pxb4_rp4_sw4 \
		--cxl vmem=vmem.1,bus=sw1.1,size=2G,dc \
		--cxl vmem=vmem.2,bus=sw1.2,size=2G,dc \
		--cxl vmem=vmem.3,bus=sw1.3,lsa=vmem.3.lsa,size=2G,dynamic-capacity \
		--cxl vmem=vmem.4,bus=sw1.4,lsa=vmem.4.lsa,size=2G,dynamic-capacity \
		"${@}"
}

cxl_pxb1
cxl_pxb2
cxl_pxb4
cxl_pxb4_rp4
cxl_pxb4_rp4_sw4
cxl_pxb4_rp4_pmem4
cxl_pxb4_rp4_sw4_pmem4
cxl_pxb4_rp4_vmem4
cxl_pxb4_rp4_sw4_vmem4
cxl_pxb4_rp4_sw4_vmem4_dc

echo -e "\nDONE"
