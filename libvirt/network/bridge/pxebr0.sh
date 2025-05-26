#!/bin/bash
sudo virsh net-define pxebr0.xml
sudo virsh net-start pxebr0
sudo virsh net-list --all
sudo ip addr show dev pxebr0

remove() {
	sudo virsh net-destroy pxebr0
	sudo virsh net-undefine pxebr0
}

