#!/bin/bash

bridge_name=Bridge0
bridge_ifname=br0
bridge_ip4=10.255.94.21/27
bridge_gw4=10.255.94.30

bond_name=Bond0
bond_ifname=bond0

vlan_name=Vlan0
vlan_id=1091
vlan_ifname=bond0.${vlan_id}

slave0_name=Slave0
slave0_ifname=eno0

slave1_name=Slave1
slave1_ifname=eno1


delete() {
	sudo nmcli connection delete ${bridge_name} ${bond_name} ${slave0_name} ${slave1_name} ${vlan_name}
	sudo nmcli connection show
}

create() {
	delete

	# Mode=0(balance-rr) 表示负载分担round-robin，和交换机的聚合强制不协商的方式配合。
	# Mode=1(active-backup) 表示主备模式，只有一块网卡是active,另外一块是备的standby，这时如果交换机配的是捆绑，将不能正常工作，因为交换机往两块网卡发包，有一半包是丢弃的。
	# Mode=2(balance-xor) 表示XOR Hash负载分担，和交换机的聚合强制不协商方式配合。（需要xmit_hash_policy）
	# Mode=3(broadcast) 表示所有包从所有interface发出，这个不均衡，只有冗余机制...和交换机的聚合强制不协商方式配合。
	# Mode=4(802.3ad) 表示支持802.3ad协议，和交换机的聚合LACP方式配合（需要xmit_hash_policy）
	# Mode=5(balance-tlb) 是根据每个slave的负载情况选择slave进行发送，接收时使用当前轮到的slave
	# Mode=6(balance-alb) 在5的tlb基础上增加了rlb。
	sudo nmcli connection add type bond con-name ${bond_name} \
		ifname ${bond_ifname} \
		mode 4 ipv4.method disabled ipv6.method ignore

	sudo nmcli connection add type bond-slave con-name ${slave0_name} \
		ifname ${slave0_ifname} master ${bond_ifname}

	sudo nmcli connection add type bond-slave con-name ${slave1_name} \
		ifname ${slave1_ifname} master ${bond_ifname}

	bridge() {
		sudo nmcli connection add type bridge con-name ${bridge_name} \
			ifname ${bridge_ifname} \
			ip4 ${bridge_ip4} \
			gw4 ${bridge_gw4} \
			ipv6.method=disabled ipv4.method=manual

		sudo nmcli connection add type vlan con-name ${vlan_name} \
			ifname ${vlan_ifname} \
			dev ${bond_ifname} \
			id ${vlan_id} \
			master ${bridge_name}

		sudo nmcli connection up ${bridge_name}
	}

	# Bridge BPDU will make switch port down.
	no_bridge() {
		sudo nmcli connection add type vlan con-name ${vlan_name} \
			ifname ${vlan_ifname} \
			dev ${bond_ifname} \
			id ${vlan_id} \
			ip4 ${bridge_ip4} \
			gw4 ${bridge_gw4} \
			ipv6.method=disabled ipv4.method=manual
	}

	# Bridge or no-bridge
	no_bridge

	sudo systemctl restart NetworkManager
	sudo nmcli connection show
}

case $1 in
create)
	create
;;
delete)
	delete
;;
*)
	echo "$0 [delete|create]"
;;
esac

