#!/bin/bash
# 见 <Linux开源网络全栈讲解> P38
# 荣涛 2021年7月27日

sudo ip netns add ns1
# 会出现在 /var/run/netns
sudo ip netns list

# 在 namespace 下运行命令
sudo ip netns exec ns1 ip addr

# 也可以运行多条指令
function multi_cmd() {
	sudo ip netns exec ns1 bash
	sudo ip link set dev lo up
	ip address
	exit
}

sudo ip netns del ns1
