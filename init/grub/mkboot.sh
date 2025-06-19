#!/bin/bash
set -e

curr_dir=$PWD
root_dir=$(mktemp -u tmp-XXXXXXX)
grub_lib_dir=
grub_format=
grub_bootefi=
grub_mkimage=

declare -a modules exist_modules

if [[ -e /usr/bin/grub-mkimage ]]; then
	grub_mkimage=grub-mkimage
elif [[ -e /usr/bin/grub2-mkimage ]]; then
	grub_mkimage=grub2-mkimage
else
	echo "ERROR: Not found any grub mkimage ELF" >&2
	exit 1
fi

clean_all()
{
	echo "Exiting..."
	sudo rm -rf ${root_dir}
}
trap "clean_all" EXIT

if [[ $(uname -m) == x86_64 ]]; then
	modules=(
		gzio loadenv biosdisk part_msdos part_gpt fat ntfs efi_gop efi_uga
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
		date disk div div_test dm_nv echo efifwsetup efi_gop
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
		net newc nilfs2 normal ntfscomp ntfs odc offsetio part_acorn
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
	echo "ERROR: Unsupport arch $(uname -m)" >&2
	exit 1
fi

if [[ $(uname -m) == aarch64 ]]; then
	grub_lib_dir=/usr/lib/grub/arm64-efi/
	grub_format=arm64-efi
	grub_bootefi=BOOTAA64.EFI
elif [[ $(uname -m) == x86_64 ]]; then
	grub_lib_dir=/usr/lib/grub/i386-pc/
	grub_format=i386-pc
	grub_bootefi=BOOTX64.EFI
elif [[ $(uname -m) == sw_64 ]]; then
	grub_lib_dir=/usr/lib/grub/sw64-efi/
	grub_format=sw64-efi
	grub_bootefi=BOOTSW64.EFI
else
	echo "ERROR: Unsupport arch $(uname -m)" >&2
	exit 1
fi

for ((i = 0; i < ${#modules[@]}; i++))
do
	# echo "${grub_lib_dir}/${modules[$i]}.mod"
	if [[ -e ${grub_lib_dir}/${modules[$i]}.mod ]]; then
		exist_modules+=( ${modules[$i]} )
	fi
done

if [[ ! -e ${grub_lib_dir} ]]; then
	if [[ $(uname -m) == x86_64 ]]; then
		sudo dnf install -y grub2-pc-modules
	elif [[ $(uname -m) == aarch64 ]]; then
		sudo dnf install -y grub2-efi-aa64-modules
	fi
fi

mkdir -p ${root_dir}
pushd ${root_dir}

mkdir -p boot

cp ${curr_dir}/configs/grub.cfg boot/grub.cfg

${grub_mkimage} \
	--format=${grub_format} \
	--prefix="(cd)" \
	--directory=${grub_lib_dir} \
	--output=${grub_bootefi} \
	--config="boot/grub.cfg" \
	${exist_modules[@]}

cp ${grub_bootefi} ${curr_dir}/
cp ${grub_bootefi} ${curr_dir}/core.img

if [[ $(uname -m) == x86_64 ]] && [[ "BIOS" ]]; then
	cat ${grub_lib_dir}/cdboot.img ${curr_dir}/core.img > ${curr_dir}/grub.img
else
	echo "TODO"
fi

popd
