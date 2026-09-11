Ether
=====

.. code-block:: text

    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |  Dst_Mac  |  Src_Mac  |  Type |  Data(46-15000) |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

.. code-block:: shell

  tcpdump -i eth0 -e
