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
