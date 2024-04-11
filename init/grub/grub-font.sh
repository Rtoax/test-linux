#!/bin/bash
# ref: https://linuxiac.com/how-to-change-grub-menu-font-size/
# font: https://dejavu-fonts.github.io/Download.html

# Download font first
#  https://dejavu-fonts.github.io/Download.html

# convert the font to PF2
sudo grub2-mkfont -s 24 -o /boot/grub2/dejavu-sans-mono.pf2 dejavu-fonts-ttf-2.37/ttf/DejaVuSansMono.ttf

sudo ls /boot/grub2/

# Backup
sudo cp /etc/default/grub /etc/default/grub.bak

# Modify /etc/default/grub
#  Add
#  GRUB_FONT=/boot/grub2/dejavu-sans-mono.pf2
#  GRUB_GFXMODE=1600x1200

# Update
sudo grub2-mkconfig -o /boot/grub2/grub.cfg
