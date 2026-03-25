======
VirtIO
======

virtio
------

- virtio frontend
- virt queue
    - virtqueue: vring
- virtio backend
    - vhost


Virtio Architecture
-------------------

1. Descriptor Table
2. Available Vring
3. Used Vring

- :ref:`virtio_architecture`

.. _virtio_architecture:

.. code-block:: text
   :caption: Virtio Architecture

           +------------------------------------+
           |       virtio  guest driver         |
           +-----------------+------------------+
             /               |              ^
            /                |               \
           put            update             get
          /                  |                 \
         V                   V                  \
    +----------+      +------------+        +----------+
    |          |      |            |        |          |
    +----------+      +------------+        +----------+
    | available|      | descriptor |        |   used   |
    |   ring   |      |   table    |        |   ring   |
    +----------+      +------------+        +----------+
    |          |      |            |        |          |
    +----------+      +------------+        +----------+
    |          |      |            |        |          |
    +----------+      +------------+        +----------+
         \                   ^                   ^
          \                  |                  /
          get             update              put
            \                |                /
             V               |               /
            +----------------+-------------------+
            |       virtio host backend          |
            +------------------------------------+


VirtIO 9P
---------


VirtIO Balloon
--------------

内存气球是通过半虚拟化机制的 ballooning 方式实现的内存过载分配. 内存气球是在虚
拟机内部引入气球的概念，气球内的内存不能被虚拟机使用。当 hypervisor 请求扩大内
存时，虚拟机内部的气球就会膨胀，内存页就会释放。当虚拟机需要扩大内存时，虚拟机
内部的气球就会缩小，可用的内存增多。引入内存气球的机制可以动态调整虚拟机的内存.


内存气球的工作流程
~~~~~~~~~~~~~~~~~~

* 1) hypervisor 发送请求给虚拟机，请求虚拟机释放内存。
* 2) 虚拟机的 virtio-pci 驱动接收到该请求，并且使虚拟机内部的内存气球膨胀。
* 3) 内存气球膨胀之后，虚拟机可用的内存减少，虚拟机通知 hypervisor 内存已释放。
* 4) hypervisor 将释放的内存分配到需要内存的地方。

- :ref:`virtio_balloon`

.. _virtio_balloon:

.. code-block:: text
   :caption: Virtio Balloon

     +-------------------+
     |                   |
     |   virtio-pci      |
     |                   |
     +--+----------^-----+
        |          |
        |          |
        |          |           GuestOS
        |          |
    +-----------------------------------+
        |          |
        |          |   HostOS/Hypervisor
        |          |
        |          |
     +--v----------+-----+
     |                   |
     |   virtio_balloon  |
     |                   |
     +-------------------+


VirtIO FS
---------

- on hostos

.. code-block:: xml

    <domain type='kvm'>
      <memoryBacking>
        <source type="memfd"/>
        <access mode="shared"/>
      </memoryBacking>
      <devices>
        <filesystem type="mount" accessmode="passthrough">
          <driver type="virtiofs"/>
          <binary path="/usr/libexec/virtiofsd"/>
          <source dir="/home/rongtao/Pictures"/>
          <target dir="rongtao_Pictures"/>
          <alias name="fs0"/>
          <address type="pci" domain="0x0000" bus="0x08" slot="0x00" function="0x0"/>
        </filesystem>
      </devices>
    </domain>

- in guestos

.. code-block:: bash

    $ mkdir pic
    $ sudo mount -t virtiofs rongtao_Pictures pic


Links
-----

- https://kernelgo.org/virtio-overview.html
- PDF: `Virtual I/O Device (VIRTIO) Version 1.2 <https://docs.oasis-open.org/virtio/virtio/v1.2/virtio-v1.2.pdf>`_
- https://gitlab.com/virtio-fs/virtiofsd
