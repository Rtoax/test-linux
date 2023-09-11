U-Boot: Universal Boot Loader
=============================


# 测试步骤

- compile-kernel.sh
- compile-uboot.sh
- ubootdish.sh or makeimg.sh
- qemu.sh

## 例

```bash
$ ./compile-uboot.sh cross-arm-vexpress_ca9x4
$ ./ubootdisk.sh
$ ./qemu.sh -a arm
```

# UEFI on U-Boot

- [UEFI on U-Boot](https://u-boot.readthedocs.io/en/latest/develop/uefi/uefi.html)

```
=> nvme info
Device 0: Vendor: 0x1b36 Rev: 8.1.0    Prod: nvme-1
            Type: Hard Disk
            Capacity: 1024.0 MB = 1.0 GB (2097152 x 512)

=> fatls nvme 0:1
            images/
  2643600   grubaa64.efi
     1509   grub.cfg
        0   hello.txt

3 file(s), 1 dir(s)

=> load nvme 0:1 ${kernel_addr_r} /grubaa64.efi
2643600 bytes read in 4 ms (630.3 MiB/s)

=> bootefi ${kernel_addr_r}
...
```
