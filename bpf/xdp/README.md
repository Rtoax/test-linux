XDP - eXpress Data Path
=======================

# XDP Type

- `Native XDP`: Runs directly on the network driver, providing higher performance.
- `Generic XDP`: Runs on the kernel's network stack, providing compatibility with all network drivers but with lower performance.


# XDP action

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
                     +---------+                                   +----------+
                     |Userspace|                                   |          |
                     | AF_XDP  |                                   |----------|
                     +---------+                                   |          |
                       ^                                           |----------|
                       |XDP_REDIRECT                               |          |
                       |                                           |          |
                       |                                           |          |
                       |                                           |          |
                       |    XDP_PASS                               |          |
+---------+         +--+---+        +-----------+     +-------+    |----------|    +-------+    +---------+
|Interface|-------->|  XDP |------->|alloc_skb()|---->|ingress|--->|          |--->|egress |--->|Interface|
|  rx     |<--------| eBPF |        +-----------+     |(qdisc)|    |          |    |(qdisc)|    | output  |
+---------+ XDP_TX  +-+---++                          +-------+    +----------+    +-------+    +---------+
                      |   |                                                                          ^
                      |   |                                                                          |
                      |   | XDP_REDIRECT                                                             |
                      |   +--------------------------------------------------------------------------+
                      |
                      |
                      |
                      |
                      |XDP_DROP/XDP_ABORTED
                      v
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

