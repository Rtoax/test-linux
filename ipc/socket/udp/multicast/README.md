多播
======

## 设置生存时间TTL

```
#include<sys/socket.h>
#include<arpa/inet.h>

int sock = socket(PF_INET, SOCK_DGRAM, 0);

int timeLive = 64;

setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (void*)&timeLive, sizeof(timeLive));
```

> TTL 即Time To Live（生存时间）,决定了数据包传递的距离；TTL用整数表示，数据包每经过一个路由器时TTL就减一，当TTL为0时销毁数据包。

## 加入多播组

```
#include<sys/socket.h>
#include<arpa/inet.h>

int sock = socket(PF_INET, SOCK_DGRAM, 0);

struct ip_mreq joinAddr;
joinAddr.imr_multiaddr.s_addr = "多播组地址信息"
joinAddr.imr_interface.s_addr = "本机地址信息"

setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*)&joinAddr, sizeof(joinAddr));
```
```
struct ip_mreq
{
    struct in_addr imr_multiaddr;
    struct in_addr imr_interface;
}
```

