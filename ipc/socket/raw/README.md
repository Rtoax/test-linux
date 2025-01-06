RAW Socket
==========


- `socket(AF_INET, SOCK_RAW, IPPROTO_XXX)`: 网络层IP数据包
- `socket(PF_PACKET, SOCK_RAW, htons(ETH_P_XXX))`: 链路层数据帧(目前只有linux支持)
- `socket(AF_INET, SOCK_PACKET, htons(ETH_P_XXX))`: 过时的

