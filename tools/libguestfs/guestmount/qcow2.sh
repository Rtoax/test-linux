#!/bin/bash
# 《如何修改 qcow2 中的 initramfs》
#
# 2022-11-19	荣涛

# 1. 创建目录，挂载 qcow2
# 可能需要 export LIBGUESTFS_BACKEND=direct
mkdir qcow2-dir
guestmount -a linux-os.qcow2 -i -w qcow2-dir

# 2. 拷贝出 initramfs
cp qcow2-dir/boot/initramfs-xxx.img /home/USER
cd /home/USER

# 3. 解压 initramfs
# initramfs 可能是 gz 压缩的 cpio，所以可能多个 gz 步骤
mkdir initramfs
mv initramfs-xxx.img initramfs
cd initramfs
# 这两步可能不需要(CCLinux 的 initramfs 需要gz压缩)
mv initramfs-xxx.img initramfs-xxx.img.gz
gunzip initramfs-xxx.img.gz
cpio -dim < initramfs-xxx.img
rm initramfs-xxx.img
# 此时获取到 initramfs 的文件树结构

# 4. 修改任意内容

# 5. 归档 initramfs 目录树为 cpio
#    如果必要则进行 gz 压缩(CCLinux需要)
find . 2>/dev/null | cpio -c -o > /home/USER/initramfs-xxx.img
cd /home/USER
gzip initramfs-xxx.img
mv initramfs-xxx.img.gz initramfs-xxx.img

# 6. 替换 qcow2 中的 initramfs
rm qcow2-dir/boot/initramfs-xxx.img
cp initramfs-xxx.img  qcow2-dir/boot/

# 7. unmount
guestunmount qcow2-dir

# 此时，linux-os.qcow2 就是自定义 initramfs 后的 qcow2 镜像了.

