Socket
===========

# Syscall

## socket(2)

```
int socket(int domain, int type, int protocol);
```

- domain:
	- `PF_INET`, `AF_INET`: IPv4网络协议
	- `PF_INET6`, `AF_INET6`: IPv6网络协议
	- `PF_LOCAL`, `AF_LOCAL`: UNIX协议

- type:
	- `SOCK_STREAM`: 提供面向连接的稳定数据传输，即TCP
	- `OOB`: 在所有数据传输前必须使用connect()来建立连接状态
	- `SOCK_DGRAM`: 使用不连续不可靠的数据包连接
	- `SOCK_SEQPACKET`: 提供连续可靠的数据包连接
	- `SOCK_RAW`: 提供原始网络协议存取
	- `SOCK_RDM`: 提供可靠的数据包连接
	- `SOCK_PACKET`: 与网络驱动程序直接通信


## recv(2), recvfrom(2), recvmsg(2), send(2), sendto(2), sendmsg(2)

- flags
	- `MSG_OOB`: 用于传输带外的数据
	- `MSG_PEEK`: 验证输入缓冲中是否存在接收的数据
	- `MSG_DONTROUTE`: 数据传输过程中不参照路由表，在本地网络中寻找目的地
	- `MSG_DONTWAIT`: 调用IO函数时不阻塞
	- `MSG_WAITALL`: 防止函数返回，直到接收请求的全部的字节数


# Socket-Level Options

- `SOL_SOCKET`

