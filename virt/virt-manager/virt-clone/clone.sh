#!/bin/bash
set -e

sudo virt-clone --original centos-stream-9-2 \
	--name centos-stream-9-2 \
	--file /home/libvirt-qcow2-images/centos-stream-9-2.qcow2
