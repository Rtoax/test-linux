ip conntrack
============

连接跟踪（connection tracking，conntrack，CT），连接跟踪是许多网络应用的基础。
例如，Kubernetes Service、 四层 LVS/IPVS、Docker network、OVS、iptables 主机防
火墙等等。

- 从数据包中提取信息，数据流（flow）和对应的连接（conn）
- 为连接维护一个状态表（conntrack table），例如连接的创建时间、发送包数、发送字节数等
- 回收过期连接
- 为更上层（例如 NAT）提供服务

