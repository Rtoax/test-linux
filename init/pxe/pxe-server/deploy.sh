#!/bin/bash
set -x

# Allow incoming connections to the tftp service in the firewall:
sudo firewall-cmd --add-service=tftp

# Configure your DHCP server to use the boot images packaged with shim
sudo cp dhcp/dhcpd.conf /etc/dhcp/dhcpd.conf

sudo mkdir -p /var/lib/tftpboot/{pxelinux,uefi}/

### For bios: pxelinux.0 + ldlinux.c32
pxelinux=$(rpm -ql syslinux-tftpboot | grep -w pxelinux.0)
sudo cp ${pxelinux} /var/lib/tftpboot/pxelinux/
# You'd better use syslinux images in ISO, not from syslinux-tftpboot
# If you use efi64/vesamenu.c32 in syslinux-tftpboot may get error:
#
#  Failed to load COM32 file vesamenu.c32
#
# Or, do not copy and use /tftpboot/efi64/vesamenu.c32
#
#  $ rpm -ql syslinux-tftpboot | grep vesamenu
#  /tftpboot/efi64/vesamenu.c32
#  /tftpboot/vesamenu.c32
#
# See https://code.cestc.cn/rongtao/ostools/-/issues/50
sudo cp $(rpm -ql syslinux-tftpboot | grep -v efi64) /var/lib/tftpboot/pxelinux/

### For efi64: syslinux.efi + ldlinux.e64
sudo mkdir /var/lib/tftpboot/pxelinux/efi64/
sudo cp $(rpm -ql syslinux-tftpboot | grep -w efi64) /var/lib/tftpboot/pxelinux/efi64/

sudo mkdir -p /var/lib/tftpboot/pxelinux/pxelinux.cfg/
sudo cp pxelinux.cfg/default /var/lib/tftpboot/pxelinux/pxelinux.cfg/default
sudo chmod +r /var/lib/tftpboot/pxelinux/pxelinux.cfg/default

# Copy the EFI boot images from your boot directory.
uefi_based() {
	# Copy and rename(must rename to shim.efi)
	local shimx64=$(rpm -ql shim-x64 | grep shimx64.efi)
	sudo cp ${shimx64} /var/lib/tftpboot/uefi/shim.efi

	local grubx64=$(rpm -ql grub2-efi-x64 | grep grubx64.efi)
	sudo cp ${grubx64} /var/lib/tftpboot/uefi/

	sudo cp grub/grub.cfg /var/lib/tftpboot/uefi/grub.cfg
}
uefi_based

sudo mkdir -p /var/lib/tftpboot/images/cclinux/live/
# Then, copy images
sudo cp /home/rongtao/pxe/* /var/lib/tftpboot/images/cclinux/live/
sudo chmod -R ugo+rx /var/lib/tftpboot/images

sudo cp /home/rongtao/pxe/live-rootfs.squashfs.img /var/www/html/
sudo chmod ugo+rw /var/www/html/live-rootfs.squashfs.img

# https://unix.stackexchange.com/questions/31809/permission-denied-trying-to-get-a-file-using-tftp
sudo restorecon -Rv /var/lib/tftpboot/
sudo ls -alZ /var/lib/tftpboot/

sudo tree /var/lib/tftpboot/
sudo chmod -R ugo+r /var/lib/tftpboot/
