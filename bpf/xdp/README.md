
# XDP Type and Load/Attach

1. **Native XDP**: Runs directly on the network driver, providing higher performance.
  - BCC: `b.attach_xdp("eth0", fn, flags=BPF.XDP_FLAGS_DRV_MODE)`
  - iproute:
    - attach: `ip link set dev [IF] xdp obj xdp_program.o sec xdp`
    - detach: `ip link set dev [IF] xdp off`
  - bpftool:
    - load:   `bpftool prog load proto.o /sys/fs/bpf/proto`
    - attach: `bpftool net attach xdpdrv pinned /sys/fs/bpf/proto dev [IF]`
    - detach: `bpftool net detach xdpdrv dev [IF]`
    - unload: `rm -f /sys/fs/bpf/proto`
  - libbpf: `bpf_xdp_attach(XDP_FLAGS_DRV_MODE)`, `bpf_set_link_xdp_fd(XDP_FLAGS_DRV_MODE)`
2. **Offloaded XDP**:
  - BCC: `b.attach_xdp("eth0", fn, flags=BPF.XDP_FLAGS_HW_MODE)`
  - iproute: `ip link set dev [IF] xdp offload obj xdp_program.o sec xdp`
  - bpftool:
    - load:   `bpftool prog load proto.o /sys/fs/bpf/proto`
    - attach: `bpftool net attach xdpoffload pinned /sys/fs/bpf/proto dev [IF]`
    - detach: `bpftool net detach xdpoffload dev [IF]`
    - unload: `rm -f /sys/fs/bpf/proto`
  - libbpf: `bpf_xdp_attach(XDP_FLAGS_HW_MODE)`, `bpf_set_link_xdp_fd(XDP_FLAGS_HW_MODE)`
3. **Generic XDP**: Runs on the kernel's network stack, providing compatibility with all network drivers but with lower performance.
  - BCC: `b.attach_xdp("eth0", fn, flags=BPF.XDP_FLAGS_SKB_MODE)`
  - iproute: `ip link set dev [IF] xdpgeneric obj xdp_program.o sec xdp`
  - bpftool:
    - load:   `bpftool prog load proto.o /sys/fs/bpf/proto`
    - attach: `bpftool net attach xdpgeneric pinned /sys/fs/bpf/proto dev [IF]`
    - detach: `bpftool net detach xdpgeneric dev [IF]`
    - unload: `rm -f /sys/fs/bpf/proto`
  - libbpf: `bpf_xdp_attach(XDP_FLAGS_SKB_MODE)`, `bpf_set_link_xdp_fd(XDP_FLAGS_SKB_MODE)`


# XDP Action

```c
/* User return codes for XDP prog type.
 * A valid XDP program must return one of these defined values. All other
 * return codes are reserved for future use. Unknown return codes will
 * result in packet drops and a warning via bpf_warn_invalid_xdp_action().
 */
enum xdp_action {
	XDP_ABORTED = 0,
	XDP_DROP,
	XDP_PASS,
	XDP_TX,
	XDP_REDIRECT,
};
```

```
                                                                   Network
                                                                    stack
                    +---------+                                  +----------+
                    |Userspace|                                  |          |
                    | AF_XDP  |                                  |----------|
                    +---------+                                  |          |
                         ^                                       |----------|
                         |                                       |          |
                   XDP_REDIRECT                                  |          |
                         |                                       |          |
                         |                                       |          |
                         |    XDP_PASS                           |          |
+---------+           +--+---+        +-------+     +-------+    |----------|    +-------+    +---------+
|   NIC   +---------->|  XDP +------->|SK_BUFF+---->|ingress+--->|          |--->|egress +--->|Interface|
|  Driver |<----------| eBPF |        +-------+     |(qdisc)|    |          |    |(qdisc)|    | output  |
+---------+   XDP_TX  +-+---++       alloc_skb()    +-------+    +----------+    +-------+    +---------+
     ^                  |   |                                                                      ^
     |                  |   |                                                                      |
+----+----+             |   | XDP_REDIRECT                                                         |
| RX_RING |             |   +----------------------------------------------------------------------+
+---------+             |
     ^                  |
     |          XDP_DROP/XDP_ABORTED
+----+----+             |
|   NIC   |             |
+---------+             v
```


## AF_XDP

Examples of such use cases are:

- Custom protocol implementations
- DDoS protection
- Application specific optimization


# XDP front end 'ip'

```bash
# Command 'ip' as XDP front end.
sudo ip link set dev eth0 xdp obj program.o sec mysection

# Check Current XDP Programs:
sudo ip -details link show dev eth0

# Unload xdp:
sudo ip -details link set eth0 xdpgeneric off
sudo ip -details link set eth0 xdp off
```


# Links

- [A Beginners Guide to eBPF Programming for Networking](https://www.youtube.com/watch?v=0p987hCplbk)
  - [Bilibili](https://www.bilibili.com/video/BV1vg4y1X7jP/)
- https://en.wikipedia.org/wiki/Express_Data_Path
- https://upload.wikimedia.org/wikipedia/commons/3/37/Netfilter-packet-flow.svg
- https://github.com/xdp-project
  - [libxdp](https://github.com/xdp-project/xdp-tools/tree/master/lib/libxdp)
- [AF_XDP](https://docs.ebpf.io/linux/concepts/af_xdp/)
