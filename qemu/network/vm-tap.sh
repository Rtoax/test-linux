#!/bin/bash
#
#    +-----------+
#    |    VM     |
#    | +-------+ |
#    | |  ethX | |
#    | +-+-----+ |
#    +---|-------+
#        |
#        |
#    +---|-----------------------+
#    |   |            Host OS    |
#    | +-v-----+       +-------+ |
#    | |  TAP  |       |  ethX | |
#    | +-------+       +-------+ |
#    +---------------------------+


vm_img=/home/qcow2s/fedora.qcow2
tap_name=mytap0

clean() {
	echo "Exiting."
	sudo ip tuntap del dev ${tap_name} mode tap
}
trap clean EXIT

sudo ip tuntap add ${tap_name} mode tap
sudo ip link set ${tap_name} up
sudo ip addr add 192.168.10.1/24 dev ${tap_name}
ifconfig ${tap_name}

sudo qemu-kvm -m 1G \
	-drive file=${vm_img},if=virtio,driver=qcow2 \
	-netdev type=tap,ifname=${tap_name},id=net0,script=no \
	-device virtio-net-pci,netdev=net0,mac=aa:00:00:11:76:f0 \
	-serial stdio

# Then, in guest os:
# $ sudo ip link set eth0 up
# $ sudo ip addr add 192.168.10.2/24 dev eth0
# $ ping -c 5 192.168.10.1

