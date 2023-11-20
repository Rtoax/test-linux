#!/bin/bash

sudo systemctl start openvswitch.service

sudo ovs-vsctl add-br br0 -- set Bridge br0 fail-mode=secure
sudo ovs-vsctl add-port br0 enp7s0 -- set Interface enp7s0 ofport_request=1
sudo ovs-vsctl add-port br0 enp8s0 -- set Interface enp8s0 ofport_request=1
sudo ovs-ofctl mod-port br0 enp8s0 up
sudo ovs-ofctl mod-port br0 enp7s0 up
sudo ovs-vsctl show
sudo ovs-ofctl show br0

# Delete
sudo ovs-vsctl del-br br0
sudo systemctl stop openvswitch.service

