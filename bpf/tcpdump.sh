#!/bin/bash
set -e

# Ethernet Frame
# |       0-6       |      6-12       |     12-14       |
# +-----------------+-----------------+-----------------+----------------------+--------------------+
# | Dst MAC(6Bytes) | Src MAC(6Bytes) | EthType(2Bytes) |   Data(46-1500Bytes) | FrameChech(4Bytes) |
# +-----------------+-----------------+-----------------+----------------------+--------------------+
# |                 Packet Header                       |            Data and CRC                   |
#
# $ sudo tcpdump -d ip and tcp port 80
# (000) ldh      [12]				--累加器在偏移量12处加载一个 16位(以太网类型字段)
# (001) jeq      #0x800           jt 2	jf 12	--返回当前的以太网类型字段，0x800是IPv4，成功则跳转到2
# (002) ldb      [23]				--14+9：IPv4头的协议位置
# (003) jeq      #0x6             jt 4	jf 12	--0x6是TCP
# (004) ldh      [20]				--段偏移量，flags+fragment_offset
# (005) jset     #0x1fff          jt 12	jf 6	--查看最后13比特（分片位），如果非0，说明是分片包，丢弃(跳转到12)
# (006) ldxb     4*([14]&0xf)			--计算IP头长度，设置X寄存器为TCP头
# (007) ldh      [x + 14]			--加载源端口
# (008) jeq      #0x50            jt 11	jf 9	--80端口
# (009) ldh      [x + 16]			--加载目的端口
# (010) jeq      #0x50            jt 11	jf 12	--80端口
# (011) ret      #262144			--返回0x40000，捕获整个数据包
# (012) ret      #0
sudo tcpdump -d ip and tcp port 80

# Test with:
# server: nc -l 80
# client: nc 10.56.52.9 80
