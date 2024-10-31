#!/bin/bash

sudo ip netns add namespace1
sudo ip netns add namespace2
sudo ip netns list

# Then create a pair of interconnected virtual ethernet devices:
sudo ip link add veth1 type veth peer name veth2

# Link each device to a namespace respectively:
sudo ip link set veth1 netns namespace1
sudo ip link set veth2 netns namespace2

# Bring up the devices while assigning them IP addresses:
sudo ip netns exec namespace1 ip link set dev veth1 up
sudo ip netns exec namespace2 ip link set dev veth2 up
sudo ip netns exec namespace1 ip addr add 192.168.1.1/24 dev veth1
sudo ip netns exec namespace2 ip addr add 192.168.1.2/24 dev veth2

sudo ip netns exec namespace1 ip addr
# Or multi-cmd
multi_cmd() {
	sudo ip netns exec namespace1 bash
	sudo ip link set dev lo up
	ip address
	exit
}

# And now verify the connectivity between the two namespaces as it is enabled
# by the veth pair tunnel.From the first namespace we should be able to ping
# the second one, and from the second namespace weshould be able to ping the
# first one:
sudo ip netns exec namespace1 ping -c5 192.168.1.2
sudo ip netns exec namespace2 ping -c5 192.168.1.1

sudo ip netns delete namespace1
sudo ip netns delete namespace2

sudo ip netns list
