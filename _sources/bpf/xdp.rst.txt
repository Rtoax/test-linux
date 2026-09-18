=======================
XDP (eXpress Data Path)
=======================


XDP Action
----------

.. code-block:: c

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


- :ref:`xdp_action`

.. _xdp_action:

.. code-block:: text
   :caption: XDP Action

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


XDP Type and Load/Attach
------------------------

1. **Native XDP**: Runs directly on the network driver, providing higher performance.
    - BCC: :code:`b.attach_xdp("eth0", fn, flags=BPF.XDP_FLAGS_DRV_MODE)`
    - iproute:
        - attach: :code:`ip link set dev [IF] xdp obj xdp_program.o sec xdp`
        - show: :code:`sudo ip -details link show dev [IF]`
        - detach: :code:`ip link set dev [IF] xdp off`
    - bpftool:
        - load:   :code:`bpftool prog load proto.o /sys/fs/bpf/proto`
        - attach: :code:`bpftool net attach xdpdrv pinned /sys/fs/bpf/proto dev [IF]`
        - detach: :code:`bpftool net detach xdpdrv dev [IF]`
        - unload: :code:`rm -f /sys/fs/bpf/proto`
    - libbpf: :code:`bpf_xdp_attach(XDP_FLAGS_DRV_MODE)`, :code:`bpf_set_link_xdp_fd(XDP_FLAGS_DRV_MODE)`
2. **Offloaded XDP**:
    - BCC: :code:`b.attach_xdp("eth0", fn, flags=BPF.XDP_FLAGS_HW_MODE)`
    - iproute: :code:`ip link set dev [IF] xdp offload obj xdp_program.o sec xdp`
    - bpftool:
        - load:   :code:`bpftool prog load proto.o /sys/fs/bpf/proto`
        - attach: :code:`bpftool net attach xdpoffload pinned /sys/fs/bpf/proto dev [IF]`
        - detach: :code:`bpftool net detach xdpoffload dev [IF]`
        - unload: :code:`rm -f /sys/fs/bpf/proto`
    - libbpf: :code:`bpf_xdp_attach(XDP_FLAGS_HW_MODE)`, :code:`bpf_set_link_xdp_fd(XDP_FLAGS_HW_MODE)`
3. **Generic XDP**: Runs on the kernel's network stack, providing compatibility with all network drivers but with lower performance.
    - BCC: :code:`b.attach_xdp("eth0", fn, flags=BPF.XDP_FLAGS_SKB_MODE)`
    - iproute: :code:`ip link set dev [IF] xdpgeneric obj xdp_program.o sec xdp`
    - bpftool:
        - load:   :code:`bpftool prog load proto.o /sys/fs/bpf/proto`
        - attach: :code:`bpftool net attach xdpgeneric pinned /sys/fs/bpf/proto dev [IF]`
        - detach: :code:`bpftool net detach xdpgeneric dev [IF]`
        - unload: :code:`rm -f /sys/fs/bpf/proto`
    - libbpf: :code:`bpf_xdp_attach(XDP_FLAGS_SKB_MODE)`, :code:`bpf_set_link_xdp_fd(XDP_FLAGS_SKB_MODE)`


AF_XDP
------

Examples of such use cases are:

- Custom protocol implementations
- DDoS protection
- Application specific optimization


libxdp
------

libxdp is a light eBPF library who add 2 features for XDP programs.

.. _freplace: https://docs.ebpf.io/linux/program-type/BPF_PROG_TYPE_EXT/

- Load multiple programs on single network device using a "dispatcher program" thanks to `freplace`_.
- Configuring `AF_XDP` and functions to read and write on theses sockets

You can check more information on the libxdp readme.


Links
-----

- `A Beginners Guide to eBPF Programming for Networking <https://www.youtube.com/watch?v=0p987hCplbk>`_
- https://en.wikipedia.org/wiki/Express_Data_Path
- https://upload.wikimedia.org/wikipedia/commons/3/37/Netfilter-packet-flow.svg
- https://github.com/xdp-project
    - `xdp-tools <https://github.com/xdp-project/xdp-tools>`_
    - `xdp-tools/libxdp <https://github.com/xdp-project/xdp-tools/tree/master/lib/libxdp>`_
- `AF_XDP <https://docs.ebpf.io/linux/concepts/af_xdp/>`_
- `ebpf-library/libxdp <https://docs.ebpf.io/ebpf-library/libxdp/libxdp/>`_
