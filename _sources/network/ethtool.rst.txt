=======
ETHTool
=======


- 查看网卡固件版本

.. code-block:: sh

  $ sudo ethtool -i [Interface]


- 关闭发送 checksum

.. code-block:: sh

  $ sudo ethtool -K [Interface] tx off


- Checksum

.. code-block:: sh

  # check supportted features
  sudo ethtool -k eth0

  # Turn off Checksum
  sudo ethtool -K eth0 rx off tx off
