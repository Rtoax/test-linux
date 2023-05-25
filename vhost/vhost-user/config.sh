QEMU=/usr/libexec/qemu-kvm
IMG_QCOW2=$PWD/vm.qcow2
IMG_ISO=/home/isos/AlmaLinux-9.0-x86_64-dvd.iso
SOCK_VHOST_PATH=$PWD/vhost.sock

if [[ ! -e ${IMG_QCOW2} ]]; then
	qemu-img create -f qcow2 ${IMG_QCOW2} 10G
fi
