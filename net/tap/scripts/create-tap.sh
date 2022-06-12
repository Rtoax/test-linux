#!/bin/bash

# 创建 tap
ip tuntap add dev tap0 mode tap
# 创建 tun
ip tuntap add dev tun0 mode tun

# 删除 tap
ip tuntap del dev tap0 mode tap
# 删除 tun
ip tuntap del dev tun0 mode tun

# tun/tap 设备创建成功后可以当作普通的网卡一样使用，
# 因此我们也可以通过ip link命令来操作它。
# 例如: 使用ip link命令也可以删除tun/tap设备
ip link del tap0
ip link del tun0
