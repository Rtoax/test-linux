#!/bin/bash

sudo virsh net-define vxlan10-bridge.xml
sudo virsh net-start vxlan10-bridge
sudo virsh net-autostart vxlan10-bridge
sudo virsh net-list --all

# Usage:
# virt-install ... --network network=vxlan10-bridge,model=virtio

