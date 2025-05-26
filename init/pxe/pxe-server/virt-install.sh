#!/bin/bash
set -x

declare -a args

create_vm()
{
	sudo virt-install \
		--virt-type=kvm \
		--name fedora-live \
		--memory 8192 \
		--vcpus 8 \
		--os-variant=generic \
		--pxe \
		--network bridge=pxebr0,model=virtio \
		--check all=off \
		${args[@]}
}

echo "Usage: $0 [ignition] [uefi]"

while true
do
	case $1 in
	ignition)
		shift
		# Generate cidata.iso with:
		# ../../cloud/configdrive.sh test gen-cfgdrv-iso -t ignition-ceaos-openstack
		args+=( --disk $PWD/cidata.iso,device=cdrom,bus=sata,format=raw )
		;;
	uefi)
		# If dhcp/pxe use UEFI (grubx64.efi), the vm must be boot from
		# UEFI, otherwise, whatever use shim.efi or grubx64.efi, will
		# get 'Could not boot image: Exec format error' error during
		# PXE booting.
		# At the same time, ture off secure boot is a good chiose for
		# Testing.
		args+=( --boot uefi,firmware.feature0.name=secure-boot,firmware.feature0.enabled=no )
		shift
		;;
	*)
		# If not specify 'ignition', give none disk.
		args+=( --disk none )
		break
		;;
	esac
done

create_vm
