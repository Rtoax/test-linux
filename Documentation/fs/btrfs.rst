btrfs
======

BTRFS（通常念成Butter FS），由Oracle于2007年宣布并进行中的COW(copy-on-write式)文件系统。目标是取代Linuxext3文件系统，改善ext3的限制，特别是单一文件大小的限制，总文件系统大小限制以及加入文件校验和特性。加入ext3/4未支持的一些功能，例如可写的磁盘快照(snapshots)，以及支持递归的快照(snapshots of snapshots)，内建磁盘阵列（RAID）支持，支持子卷(Subvolumes)的概念，允许在线调整文件系统大小。
