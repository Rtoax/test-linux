
* [linux-observability-with-bpf:packet-filtering-raw-sockets](https://github.com/bpftools/linux-observability-with-bpf/tree/master/code/chapter-6/packet-filtering-raw-sockets)

```
sudo ./loader.out bpf_program.o 
```

It will show something like this, ten results, one every second for ten seconds:

```
TCP 0 UDP 0 ICMP 0 packets
TCP 0 UDP 0 ICMP 0 packets
TCP 0 UDP 0 ICMP 0 packets
TCP 0 UDP 0 ICMP 0 packets
TCP 0 UDP 0 ICMP 4 packets
TCP 0 UDP 0 ICMP 8 packets
TCP 0 UDP 0 ICMP 12 packets
TCP 0 UDP 0 ICMP 16 packets
TCP 0 UDP 0 ICMP 16 packets
TCP 0 UDP 0 ICMP 16 packets
```

Since the program is attached to the loopback interface `lo` (see `loader.c` line 30) we need to generate traffic on
that interface to show the packets flow.

You can simply do a ping to localhost in the VM while the program is running.

```
ping 127.0.0.1
```
