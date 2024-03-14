NIC
===

# 网卡命名

- en: Ethernet
- wl: Wireless (WiFi)
- ww: Wild Wireless
- eno: o:Onboard (板载网卡)
- ens: 可热插拔的网卡
- enp: p:PCIe
- enx/wlx: 使用MAC地址命名的网卡


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

