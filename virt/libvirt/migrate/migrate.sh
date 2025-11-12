#!/bin/bash
set -ex

dom_name=almalinux9
target_ip=10.253.12.70

# Set max downtime 500ms
sudo virsh migrate-setmaxdowntime ${dom_name} 500

# Set network bandwidth 500Mbps
sudo virsh migrate-setspeed ${dom_name} --bandwidth 500
sudo virsh migrate-getspeed ${dom_name}

# Set compress method zstd
sudo virsh qemu-monitor-command ${dom_name} \
	'{ "execute": "migrate-set-parameters", "arguments": {"compress-method": "zstd"}}'

# Query parameters
sudo virsh qemu-monitor-command ${dom_name} '{ "execute": "query-migrate-parameters"}' | jq

# Shared Storage Scenario
sudo virsh migrate --live --unsafe --tls --domain ${dom_name} --desturi qemu+ssh://${target_ip}/system

# Non-Shared Storage Scenario
sudo virsh domblklist ${dom_name}
sudo virsh migrate --live  --unsafe --copy-storage-all --migrate-disks vda ${dom_name} qemu+ssh://${target_ip}/system

# Encrypted Transmission
# TODO
