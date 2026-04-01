=======
ETHTool
=======


- 查看网卡固件版本

.. code-block:: sh

    $ sudo ethtool -i [Interface]


- 关闭发送 checksum

.. code-block:: sh

    $ sudo ethtool -K [Interface] tx off
