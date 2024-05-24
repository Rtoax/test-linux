#!/bin/bash

set -ex

. ../../libs/qemu.sh

goodbye()
{
	echo "Exit..."
	rm -rf tmp-*
}
trap "goodbye" EXIT

mkimg_bootcd()
{
	local curr_dir=$PWD
	local root_dir=$(mktemp -u tmp-XXXXXXX)
	local modules

	echo Creating bootable CD image...

	mkdir -p ${root_dir}

	cd ${root_dir}

	mkdir -p bin
	mkdir -p boot

	cp ${curr_dir}/configs/grub-kernel.cfg boot/grub.cfg
	cp /boot/vmlinuz-$(uname -r) bin/kernel

	if [[ $(uname -m) == x86_64 ]]; then
		modules=(
			loadenv biosdisk part_msdos part_gpt fat ntfs
			ext2 ntfscomp iso9660 loopback search linux boot minicmd cat cpuid chain
			halt help ls reboot echo test configfile normal sleep memdisk tar font
			gfxterm gettext true vbe vga video_bochs video_cirrus multiboot multiboot2
		)
	elif [[ $(uname -m) == aarch64 ]]; then
		modules=(
			loadenv part_msdos part_gpt fat ntfs
			ext2 ntfscomp iso9660 loopback search linux boot minicmd cat chain
			halt help ls reboot echo test configfile normal sleep memdisk tar font
			gfxterm gettext true
		)
	elif [[ $(uname -m) == sw_64 ]]; then
		modules=(
			acpi adler32 affs afs afsplitter all_video archelp bfs bitmap bitmap_scale
			blocklist boot bswap_test btrfs bufio cat cbfs chain cmdline_cat_test cmp
			cmp_test configfile cpio_be cpio crc64 cryptodisk crypto ctz_test datehook
			date datetimediskfilter disk div div_test dm_nv echo efifwsetup efi_gop
			efinet elf eval exfat exfctest ext2 extcmd f2fs fat fdt file font fshelp
			functional_test gcry_arcfour gcry_blowfish gcry_camellia gcry_cast5 gcry_crc
			gcry_des gcry_dsa gcry_idea gcry_md4 gcry_md5 gcry_rfc2268 gcry_rijndael
			gcry_rmd160 gcry_rsa gcry_seed gcry_serpent gcry_sha1 gcry_sha256 gcry_sha512
			gcry_tiger gcry_twofish gcry_whirlpool geli gettext gfxmenu gfxterm_background
			gfxterm_menu gfxterm gptsync gzio halt hashsum hello help hexdump hfs
			hfspluscomp hfsplus http iso9660 jfs jpeg json keystatus ldm linux loadenv
			loopback lsacpi lsefimmap lsefi lsefisystab lsmmap ls lssal luks2 luks lvm
			lzopio macbless macho mdraid09_be mdraid09 mdraid1x memdisk memrw minicmd
			minix2_be minix2 minix3_be minix3 minix_be minix mmap mpi msdospart mul_test
			net newc nilfs2 normal ntfscomp ntfs odc offsetio part_acorn part_amigapart_apple
			part_bsd part_dfly part_dvh part_gpt part_msdos part_plan part_sun part_sunpc
			parttool password password_pbkdf2 pbkdf2 pbkdf2_test pgp png priority_queue
			probe procfs progress raid5rec raid6rec read reboot regexp reiserfs romfs scsi
			search_fs_file search_fs_uuid search_label search serial setjmp setjmp_test sfs
			shift_test signature_test sleep sleep_test smbios squash4 strtoull_test
			syslinuxcfg tar terminal terminfo test_blockarg testload test testspeed tftp
			tga time tpm trig tr true udf ufs1_be ufs1 ufs2 video_colors video_fb videoinfo
			video videotest_checksum videotest xfs xnu_uuid xnu_uuid_test xzio zfscrypt
			zfsinfo zfs zstd
		)
	else
		echo "ERROR: Unsupport arch $(uname -m)"
		exit 1
	fi


	local grub_lib_dir=
	local grub_format=

	if [[ $(uname -m) == aarch64 ]]; then
		grub_lib_dir=/usr/lib/grub/arm64-efi/
		grub_format=arm64-efi
	elif [[ $(uname -m) == x86_64 ]]; then
		grub_lib_dir=/usr/lib/grub/i386-pc/
		grub_format=i386-pc
	elif [[ $(uname -m) == sw_64 ]]; then
		grub_lib_dir=/usr/lib/grub/sw64-efi/
		grub_format=sw64-efi
	else
		echo "ERROR: Unsupport arch $(uname -m)"
		exit 1
	fi

	if [[ ! -e ${grub_lib_dir} ]]; then
		if [[ $(uname -m) == x86_64 ]]; then
			sudo dnf install grub2-pc-modules
		elif [[ $(uname -m) == aarch64 ]]; then
			sudo dnf install grub2-efi-aa64-modules
		fi
	fi

	grub2-mkimage \
		--format=${grub_format} \
		--prefix="(cd)" \
		--directory=${grub_lib_dir} \
		--output=bin/core.img \
		--config="boot/grub.cfg" \
		${modules[@]}

	# FIXME: aarch64: cat: /usr/lib/grub/arm64-efi//cdboot.img: No such file or directory
	cat ${grub_lib_dir}/cdboot.img bin/core.img > bin/grub.img

	genisoimage \
		-graft-points \
		-input-charset utf8 \
		-A "grub2" \
		-quiet -R -b \
		boot/grub/grub.img \
		-no-emul-boot \
		-boot-load-size 4 \
		-boot-info-table \
		-o bootcd.iso \
		boot/kernel=bin/kernel \
		boot/grub/grub.cfg=boot/grub.cfg \
		boot/grub/grub.img=bin/grub.img

	mv bootcd.iso ${curr_dir}/

	cd ${curr_dir}

	rm -rf ${root_dir}

	local qemu_kvm=$(get_qemu_kvm_emulator)
	echo -e "
Now you can runing

\033[1;02m # running directly \033[m
\033[1;32m $ ${qemu_kvm} -cdrom bootcd.iso \033[m
\033[1;02m # running with gdb port \033[m
\033[1;32m $ ${qemu_kvm} -cdrom bootcd.iso -s -S \033[m

more to see <https://www.cnblogs.com/coryxie/archive/2013/03/12/2956807.html>
"
}

mkimg_bootcd

