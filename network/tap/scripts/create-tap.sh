#!/bin/bash

# create tap
ip tuntap add dev tap0 mode tap
# create tun
ip tuntap add dev tun0 mode tun

# delete tap
ip tuntap del dev tap0 mode tap
# delete tun
ip tuntap del dev tun0 mode tun

# after tun/tap device created, it could be used as NIC, thus, we could modify
# it with 'ip link' command. like:
ip link del tap0
ip link del tun0
