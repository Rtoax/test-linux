#!/bin/bash
# The genisoimage program is used as a pre-mastering program; i.e., it
# generates the ISO9660 file-system. Genisoimage takes a snapshot of
# a given directory tree and generates a binary image of the tree
# which will correspond to an ISO9660 file-system when written to
# a block device. Genisoimage is used for writing CD-ROMs, and includes
# support for creating boot-able El Torito CD-ROMs.
#
# Install the genisoimage package if you need a program for writing
# CD-ROMs.

aarch64() {
	SRC_DIR=CentOS-Stream-9-20220107.0-aarch64-dvd1
	DST_ISO=CC-aarch64-dvd1.iso
	LABEL=CC-aarch64
	#LABEL=CentOS-Stream-9-BaseOS-aarch64

	genisoimage -r -J -T -v \
		-V $LABEL \
		-c boot.catalog \
		-hide boot.catalog \
		-e images/efiboot.img \
		-no-emul-boot \
		-o $DST_ISO \
		$SRC_DIR

	implantisomd5 ./$DST_ISO

	echo > $DST_ISO.manifest
	for f in `find $SRC_DIR`
	do
		echo ${f:${#SRC_DIR}} >> $DST_ISO.manifest
	done
}

x86_64() {
	SRC_DIR=CentOS-Stream-9-20220107.0-x86_64-dvd1
	DST_ISO=CC-x86_64-dvd1.iso
	LABEL=CC-x86_64

	genisoimage -r -J -T -v \
		-V $LABEL \
		-b isolinux/isolinux.bin \
		-c isolinux/boot.cat \
		-no-emul-boot \
		-boot-load-size 4 \
		-boot-info-table -eltorito-alt-boot \
		-e images/efiboot.img \
		-no-emul-boot \
		-o  ./$DST_ISO \
		./$SRC_DIR

	implantisomd5 ./$DST_ISO

	echo > $DST_ISO.manifest
	for f in `find $SRC_DIR`
	do
		echo ${f:${#SRC_DIR}} >> $DST_ISO.manifest
	done
}
