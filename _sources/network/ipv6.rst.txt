IPv6
====

NDP (Neighbor Discovery Protocol)
---------------------------------

NDP（Neighbor Discovery Protocol，邻居发现协议）是IPv6的一个关键协议，它组合了IPv4中的 `ARP` 、 `ICMP` 路由器发现和ICMP重定向等协议，并对它们作了改进。作为IPv6的基础性协议，NDP还提供了前缀发现、邻居不可达检测、重复地址监测、地址自动配置等功能。


ndptool
~~~~~~~

.. code-block:: shell

  $ sudo ndptool monitor


Disable IPv6
------------

1. 修改 cmdline

.. code-block:: text

  $ sudo vi /etc/default/grub
  GRUB_CMDLINE_LINUX="xxxxx ipv6.disable=1"

2. 临时修改 sysctl

.. code-block:: shell

  sudo sysctl -a | grep -w disable_ipv6

3. NetworkManager

.. code-block:: shell

  $ sudo nmcli connection modify [InterfaceName] ipv6.method "disabled"
  $ sudo nmcli connection down [InterfaceName]
  $ sudo nmcli connection up [InterfaceName]
