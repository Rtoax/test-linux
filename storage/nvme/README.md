NVMe - Non-Volatile Memory Express
==================================

NVMe，又叫非易失性存储主机控制器接口规范（NVMHCIS），是一种开放的逻辑设备接口
规范，用于访问计算机中的非易失性存储介质，通常是通过PCIe总线连接的。

> NVMe是逻辑设备接口规范。


# 物理规格

- AIC(PCIe卡)
- M.2
- U.2/U.3(SFF-8639)
- E1(EDSFF)

除了M.2以外的其它三种物理设备都支持热插拔。


## 热插拔

```bash
$ echo 1 > /sys/bus/pci/devices/0000:e3:00.0/remove
$ echo 1 > /sys/bus/pci/rescan
```

## 命名空间

- /dev/nvme0n1
	- 0: 控制器
	- 1: 命名空间 (sudo nvme id-ns /dev/nvme0n1)


# NVMe-oF (over Fabrics)

> Fabrics: 织品，构造，结构，布；

- NVMe-oF
	- Fibre Channel
	- RDMA
		- InfiniBand
		- RoCE
			- RoCEv1: 以太网链路层协议（以太网 0x8915）
			- RoCEv2: UDP/IP, 默认端口 4791
		- iWARP
	- TCP
	- Next Gen Fabrics


# Links

- https://nvmexpress.org/
- https://en.wikipedia.org/wiki/NVM_Express

