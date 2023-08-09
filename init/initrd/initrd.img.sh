#!/bin/bash


# RHEL 6.2 版本
# RHEL 6.0 - 6.2 都采用与RHEL 5.0 相同的格式进行打包，但从6.2版本开始，改用LZMA 进行压缩
# initrd.img: LZMA compressed data, streamed
initrd_img_xz()
{
	# 解压
	xz -dc initrd.img | cpio -id

	# 压缩
	find . | cpio -c -o | xz -9 --format=lzma > initrd.img
}

# RHEL 5.0 版本
initrd_img_gunzip()
{
	mv initrd.img initrd.img.gz
	gunzip initrd.img.gz
	file initrd.img
	# initrd.img: ASCII cpio archive (SVR4 with no CRC)
}
