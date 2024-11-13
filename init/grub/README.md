GRUB - GRand Unified Bootloader
===============================


# Introduce

```
$ lsblk  -o name,fstype,type,mountpoint
NAME            FSTYPE      TYPE MOUNTPOINT
nvme0n1                     disk
├─nvme0n1p1     vfat        part /boot/efi
├─nvme0n1p2     xfs         part /boot
└─nvme0n1p3     LVM2_member part
```


# Boot Linux

```
(grub)> set debug=all
(grub)> ls
... (hd1,gpt1) (hd1,gpt2) (hd1,gpt3) ...
(grub)> ls (hd1,gpt3)
boot/ usr/ ...
(grub)> ls (hd1,gpt3)/boot/
intiramfs-xxx vmlinuz-xxx
(grub)> linux (hd1,gpt3)/boot/vmlinuz-xxx root=UUID=xxx
(grub)> initrd (hd1,gpt3)/boot/initramfs-xxx.img
(grub)> boot
```

# Re-Boot Linux

```
(grub)> reboot
```

# Default Entry

/boot/grub2/grubenv


# Links

- https://www.gnu.org/software/grub/
- https://www.gnu.org/software/grub/grub-download.html

