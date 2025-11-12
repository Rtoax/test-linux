#!/bin/bash
set -e

dom=almalinux9

cat>tmp-new-device.xml<<-EOF
<disk type='file' device='disk'>
	<driver name='qemu' type='qcow2' cache='none'/>
	<source file='/home/qcow2s/disk-1.qcow2'/>
	<target dev='vdc' bus='virtio'/>
</disk>
EOF

# Attach
sudo virsh attach-device ${dom} tmp-new-device.xml
# Detach
sudo virsh detach-device ${dom} tmp-new-device.xml
