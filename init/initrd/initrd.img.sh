#!/bin/bash
set -e

# RHEL 6.0 - <6.2 same as RHEL 5.0
# RHEL >=6.2: LZMA
# initrd.img: LZMA compressed data, streamed
initrd_img_xz()
{
	# decompress
	xz -dc initrd.img | cpio -id

	# compress
	find . | cpio -c -o | xz -9 --format=lzma > initrd.img
}

# RHEL 5.0
initrd_img_gunzip()
{
	mv initrd.img initrd.img.gz
	gunzip initrd.img.gz
	file initrd.img
	# initrd.img: ASCII cpio archive (SVR4 with no CRC)
}
