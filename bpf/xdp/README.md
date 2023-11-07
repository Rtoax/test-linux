XDP - eXpress Data Path
=======================

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

# XDP front end 'ip'

```bash
# Command 'ip' as XDP front end.
ip link set dev eth0 xdp obj program.o sec mysection
```


# Links

- [A Beginners Guide to eBPF Programming for Networking](https://www.youtube.com/watch?v=l5l2EckwWME)
  - [Bilibili](https://www.bilibili.com/video/BV1vg4y1X7jP/)
