possible_qemu_emulator=(
	/usr/libexec/qemu-kvm
	/usr/bin/qemu-system-$(uname -m)
)

QEMU=
IMG_QCOW2=$PWD/vm.qcow2
IMG_ISO=/home/isos/AlmaLinux-9.0-x86_64-dvd.iso
SOCK_VHOST_PATH=$PWD/vhost.sock

for q in ${possible_qemu_emulator[@]}
do
	if [[ -e ${q} ]]; then
		QEMU=${q}
	fi
done

[[ -z ${QEMU} ]] && echo "Not found Qemu/kvm emulator" && exit 1

if [[ ! -e ${IMG_QCOW2} ]]; then
	qemu-img create -f qcow2 ${IMG_QCOW2} 10G
fi
