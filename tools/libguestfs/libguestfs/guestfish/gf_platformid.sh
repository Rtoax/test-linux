#!/bin/bash

. $PWD/libguestfish.sh


gf_platformid()
{
	local qcow2_img=$1
	local dest=$2
	local platformid=$3


	tmpd=$(mktemp -tdp "$(dirname "${dest}")" gf-platformid.XXXXXX)
	tmp_dest=${tmpd}/box.img

	cp -a --reflink=never $qcow2_img $tmp_dest

	chmod u+w $tmp_dest

	gf_run_mount ro $tmp_dest

	# # We just mount the boot partition writable
	gf remount /boot rw:true

	# TODO: download -> modify -> upload

	gf_shutdown

	mv $tmp_dest $dest
	rm -rf $tmpd
}

gf_platformid /home/rongtao/coreos.qcow2 coreos-openstack.qcow2 openstack

