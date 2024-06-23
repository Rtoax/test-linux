vhost-net
===========

vhost协议可以将允许VMM将virtio的数据面offload到另一个组件上，而这个组件正是vhost-net。
QEMU会打开并初始化字符设备`/dev/vhost-net`，并调用ioctl来与vhost-net进行控制面通信。

