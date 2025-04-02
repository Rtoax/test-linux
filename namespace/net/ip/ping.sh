#!/bin/bash
set -ex

ns1_veth1_ipv4=192.168.1.1
ns2_veth2_ipv4=192.168.1.2

cleanup()
{
	echo "Cleanup!!!"
	sudo ip netns delete ns1 || true
	sudo ip netns delete ns2 || true
	sudo ip netns list
}
trap "cleanup" EXIT

sudo ip netns add ns1
sudo ip netns add ns2
sudo ip netns list

# Then create a pair of interconnected virtual ethernet devices:
sudo ip link add veth1 type veth peer name veth2

# Link each device to a namespace respectively:
sudo ip link set veth1 netns ns1
sudo ip link set veth2 netns ns2

# Bring up the devices while assigning them IP addresses:
sudo ip netns exec ns1 ip link set dev veth1 up
sudo ip netns exec ns2 ip link set dev veth2 up
sudo ip netns exec ns1 ip addr add ${ns1_veth1_ipv4}/24 dev veth1
sudo ip netns exec ns2 ip addr add ${ns2_veth2_ipv4}/24 dev veth2

sudo ip netns exec ns1 ip addr
sudo ip netns exec ns2 ip addr
# Or multi-cmd
multi_cmd() {
	sudo ip netns exec ns1 bash
	sudo ip link set dev lo up
	ip address
	exit
}

# And now verify the connectivity between the two namespaces as it is enabled
# by the veth pair tunnel.From the first namespace we should be able to ping
# the second one, and from the second namespace weshould be able to ping the
# first one:
sudo ip netns exec ns1 ping -c2 ${ns2_veth2_ipv4}
sudo ip netns exec ns2 ping -c2 ${ns1_veth1_ipv4}

