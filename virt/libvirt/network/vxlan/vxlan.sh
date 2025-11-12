#!/bin/bash

# 创建网桥 br0
# 此命令在网桥设备上设置没有 IPv4 和 IPv6 地址，因为此网桥在第 2 层工作
sudo nmcli connection add type bridge con-name br0 ifname br0 ipv4.method disabled ipv6.method disabled

# 创建 VXLAN 接口，并将其附加到 br0
# - ID 10 ：设置 VXLAN 标识符。
# - local 198.51.100.2 ：设置传出数据包的源 IP 地址。
# - remote 203.0.113.1 ：当目的地链路层地址在 VXLAN 设备转发数据库中未知时，设
#   置要在传出数据包中使用的单播或多播IP地址。
# - Master br0 ：将要创建的此 VXLAN 连接设为 br0 连接中的一个端口。
# - ipv4.method disabled 和 ipv6.method disabled: 在网桥上禁用 IPv4 和 IPv6。
sudo nmcli connection add type vxlan slave-type bridge \
	con-name br0-vxlan10 \
	ifname vxlan10 id 10 local 198.51.100.2 remote 203.0.113.1 master br0

# 激活 br0 连接配置文件
sudo nmcli connection up br0

# 在本地防火墙中为进入 UDP 连接打开端口 8472
sudo firewall-cmd --permanent --add-port=8472/udp
sudo firewall-cmd --reload

# 显示转发表
sudo bridge fdb show dev vxlan10

