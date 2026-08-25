include fs/e2fsprogs.mk

subdir-y += e2fsprogs

prog-y += mkfs.ext4.sh
prog-y += mkfs.ext4.sh.1
prog-y += mkfs.ext4.sh.2

PROG_ARGS_mkfs.ext4.sh.1 := fstype ext3
PROG_ARGS_mkfs.ext4.sh.2 := fstype ext2
