=======================
XDP - eXpress Data Path
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
