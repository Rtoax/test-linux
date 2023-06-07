#!/bin/bash

mkimg_bootcd()
{
	echo Creating bootable CD image...

	local curr_dir=$PWD
	local root_dir=$(mktemp -u tmp-XXXXXXX)

	mkdir -p ${root_dir}

	cd ${root_dir}

	mkdir -p bin
	mkdir -p boot

	cp ${curr_dir}/configs/grub-kernel.cfg boot/grub.cfg
	cp /boot/vmlinuz-$(uname -r) bin/kernel

	local modules=(
		loadenv biosdisk part_msdos part_gpt fat ntfs
		ext2 ntfscomp iso9660 loopback search linux boot minicmd cat cpuid chain
		halt help ls reboot echo test configfile normal sleep memdisk tar font
		gfxterm gettext true vbe vga video_bochs video_cirrus multiboot multiboot2
	)

	local grub_lib_dir=/usr/lib/grub/i386-pc/

	if [[ ! -e ${grub_lib_dir} ]]; then
		sudo dnf install grub2-pc-modules
	fi

	grub2-mkimage \
		--format=i386-pc \
		--prefix="(cd)" \
		--directory=${grub_lib_dir} \
		--output=bin/core.img \
		--config="boot/grub.cfg" \
		${modules[@]}

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

	echo -e "
Now you can runing

\033[1;02m # running directly \033[m
\033[1;32m $ /usr/libexec/qemu-kvm -cdrom bootcd.iso \033[m
\033[1;02m # running with gdb port \033[m
\033[1;32m $ /usr/libexec/qemu-kvm -cdrom bootcd.iso -s -S \033[m

more to see <https://www.cnblogs.com/coryxie/archive/2013/03/12/2956807.html>
"
}

mkimg_bootcd
