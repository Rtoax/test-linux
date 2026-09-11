Netlink
=======

用户态和内核态交互数据的方式


Kernel Connector
----------------

* Kernel connector: https://www.kernel.org/doc/html/latest/driver-api/connector.html

Kernel connector - new netlink based userspace <-> kernel space easy to use communication module.

From the userspace point of view it’s quite straightforward:

.. code-block:: c

  socket();
  bind();
  send();
  recv();
