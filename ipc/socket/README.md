Socket
===========

# Syscall

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


# Socket-Level Options

- `SOL_SOCKET`

