NIC
===

# 网卡命名

- `en`: Ethernet
	- `o`: o:Onboard (板载网卡)
	- `p`: p:PCIe
	- `s`: s:Slot, 可热插拔的网卡
	- `f`: f:Function
	- `x`: 使用MAC地址命名的网卡
- `wl`: Wireless Lan (WLAN, WiFi)
	- wlx: 使用MAC地址命名的网卡
- `ww`: Wild Wireless (WWAN)


## 示例

### PCIe

- enp129s0f0np0
```
	81:00.0 Ethernet controller: xxx
	        ^^^^^^^^   en
	^^                 p129
	   ^^              s0
	      ^            f0
```

- enp129s0f1np1
```
	81:00.1 Ethernet controller: xxx
	        ^^^^^^^^   en
	^^                 p129
	   ^^              s0
	      ^            f1
```

### MAC

- enx08c0eb8efbd9
```
	ether 08:c0:eb:8e:fb:d9
```

### Onboard

- eno1


## systemd-udev

- `/usr/lib/systemd/network/99-default.link`
- `/etc/udev/rules.d/`

### udevadm

```
$ udevadm info /sys/class/net/eno1 | grep NAME
```


# ethtool

- 查看网卡固件版本

```bash
$ sudo ethtool -i [Interface]
```

- 关闭发送 checksum

```bash
$ sudo ethtool -K [Interface] tx off
```


# SmartNIC

- Mellanox SmartNIC
- ...

