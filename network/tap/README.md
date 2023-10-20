TAP/TUN
========

# TAP/TUN

TAP 设备与 TUN 设备工作方式完全相同, 区别在于：

* `TUN` 设备是一个`三层设备`，它只模拟到了 IP 层，即网络层 我们可以通过 `/dev/tunX` 文件收发 IP 层数据包，它无法与物理网卡做 bridge，但是可以通过三层交换（如 `ip_forward`）与物理网卡连通。可以使用ifconfig之类的命令给该设备设定 IP 地址。
* `TAP` 设备是一个`二层设备`，它比 `TUN` 更加深入，通过 `/dev/tapX` 文件可以收发 MAC 层数据包，即数据链路层，拥有 MAC 层功能，可以与物理网卡做 bridge，支持 MAC 层广播。同样的，我们也可以通过ifconfig之类的命令给该设备设定 IP 地址，可以给它设定 MAC 地址。

tun 和 tap 设备都是通过 Linux 内核中的 tun 驱动创建的，tun 驱动在初始化的时候会注册一个 misc 设备，路径为 `/dev/net/tun`，用来作为向用户态导出的接口，所有对 `tun/tap` 设备的操作都必须首先打开 `/dev/net/tun` 得到一个 fd，然后对 fd 做操作。


# Links

- https://wiki.qemu.org/Documentation/Networking

