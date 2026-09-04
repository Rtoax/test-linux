=================
Net Naming Scheme
=================

net.ifnames cmdline
-------------------

- `eth`: Original Simple Scheme
- `en`: Ethernet
    - `o`: o:Onboard (板载网卡)
    - `P`: P:Domain
    - `p`: p:PCIe Bus
    - `s`: s:Slot, 可热插拔的网卡
    - `f`: f:Function
    - `x`: x:MAC address
- `ib`: InfiniBand
- `sl`: 串列线路互联网协议(slip：Serial line IP)
- `wl`: Wireless Lan (WLAN, WiFi)
    - wlx: 使用MAC地址命名的网卡
- `ww`: Wild Wireless (WWAN)


biosdevname cmdline
-------------------

- `em[1234...]`: Embedded Network Interface (LOM)
- `p<slot><ethernet port>`: PCI card network Interface
    - `p3p4`
- `p<slot><ethernet port>_<virtual interface>`: Virtual Function
    - `p3p4_1`


.. code-block:: sh

    sudo dnf install biosdevname
    sudo apt install biosdevname


net.ifnames .vs. biosdevname
----------------------------

.. list-table::
   :widths: 15 15 15
   :header-rows: 1

   * - net.ifnames
     - biosdevname
     - example
   * - default
     - default
     - enp5s2
   * - default
     - 0
     - enp5s2
   * - 0
     - default
     - em1
   * - 0
     - 0 eth1
     - 


示例
----

PCIe
~~~~

- enp129s0f0np0

.. code-block:: text

	81:00.0 Ethernet controller: xxx
	        ^^^^^^^^   en
	^^                 p129 (bus)
	   ^^              s0   (slot)
	      ^            f0   (function)

- enp129s0f1np1

.. code-block:: text

	81:00.1 Ethernet controller: xxx
	        ^^^^^^^^   en
	^^                 p129 (bus)
	   ^^              s0   (slot)
	      ^            f1   (function)

- enP6p9s93f0

.. code-block:: text

	0006:09:5d.0 Ethernet controller: xxx
	             ^^^^^^^^  en
	^^^^                   P6  (Domain)
	     ^^                p9  (Bus)
	        ^^             s93 (Slot)
	           ^           f0  (Function)

- Q: What is np0/np1?
- A: Different net driver version support different feature, such as devlink.
  You need to check:

.. code-block:: sh

    $ lspci -k -s 21:00.1
    $ modinfo mlx5_core


MAC
~~~

- enx08c0eb8efbd9

.. code-block:: text

	ether 08:c0:eb:8e:fb:d9


Onboard
~~~~~~~

- eno1


systemd-udev
------------

- `/usr/lib/systemd/network/99-default.link`
- `/etc/udev/rules.d/`


udevadm
-------

.. code-block:: sh

    $ udevadm info /sys/class/net/${name}
    $ udevadm test /sys/class/net/${name}


systemd.net-naming-scheme(7)
----------------------------
