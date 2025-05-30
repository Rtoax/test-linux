#!/bin/bash
set -ex

. ../../qemu/libqemu.sh

qemu_kvm=$(get_qemu_kvm_emulator)

goodbye()
{
	echo "Exit..."
	rm -rf tmp-* boot/
}
trap "goodbye" EXIT

rm -rf boot/
mkdir boot/

./mkboot.sh

cp configs/grub.cfg boot/grub.cfg
cp /boot/vmlinuz-$(uname -r) boot/kernel
sudo cp /boot/initramfs-$(uname -r).img boot/initrd.img
sudo chmod +rw boot/initrd.img
mv grub.img boot/

sudo genisoimage \
	-graft-points \
	-input-charset utf8 \
	-A "grub2" \
	-V "grub2" \
	-quiet -R -b \
	boot/grub/grub.img \
	-no-emul-boot \
	-boot-load-size 4 \
	-boot-info-table \
	-o bootcd.iso \
	boot/kernel=boot/kernel \
	boot/initrd.img=boot/initrd.img \
	boot/grub/grub.cfg=boot/grub.cfg \
	boot/grub/grub.img=boot/grub.img

echo -e "
Now you can runing

\033[1;02m # running directly \033[m
\033[1;32m $ ${qemu_kvm} -m 1024 -cdrom bootcd.iso \033[m
\033[1;02m # running with gdb port \033[m
\033[1;32m $ ${qemu_kvm} -m 1024 -cdrom bootcd.iso -s -S \033[m

more to see <https://www.cnblogs.com/coryxie/archive/2013/03/12/2956807.html>
"

