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
	# decompress
	mv initrd.img initrd.img.gz
	gunzip initrd.img.gz
	cat initrd.img.gz | cpio -id

	# compress
	find . | cpio -H newc -o | gzip -9 > initrd.img
}
