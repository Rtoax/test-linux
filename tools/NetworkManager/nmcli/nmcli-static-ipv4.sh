#!/bin/bash
# 如果想要在局域网中用PC当作DHCP服务器，需要给网口先配置一个IPv4地址，
# 但是这个地址没有网关
sudo nmcli connection modify enp4s0 ipv4.addresses 192.168.1.100/24 ipv4.method manual

sudo nmcli connection modify eno1   ipv4.addresses 173.117.19.2/18 gw4 173.117.0.1 ipv4.method manual

# TODO: with vLAN
sudo nmcli connection add type vlan con-name vlan91 ifname enP4s22f0 dev enP4s22f0 id 91 ipv4.addresses 10.252.20.29/27 ipv4.gateway 10.252.20.30 ipv4.method manual
