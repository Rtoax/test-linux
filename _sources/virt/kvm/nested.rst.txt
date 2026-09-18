KVM Nested
==========

基本步骤
--------

1. 使能

修改 `options kvm_intel nested=1`

.. code-block:: shell

  $ sudo vim /etc/modprobe.d/kvm.conf

2. 查看

.. code-block:: shell

  $ cat /sys/module/kvm_intel/parameters/nested
  Y

3. 修改第一层虚拟机`CPU mode`为`host-passthrough`

.. code-block:: xml

  <cpu mode='host-passthrough' check='none' migratable='on'>
