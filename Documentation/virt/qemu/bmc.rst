Qemu IPMI BMC
=============

Internal Emulation (Built-in Simulator)
---------------------------------------

ISA-Based Configuration (Standard x86 PC)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: shell

  qemu-system-x86_64 -m 2G -smp 2 -cdrom ubuntu.iso \
    -device ipmi-bmc-sim,id=bmc0 \
    -device isa-ipmi-kcs,bmc=bmc0


PCI-Based Configuration
~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: shell

  qemu-system-x86_64 -m 2G -smp 2 -cdrom ubuntu.iso \
    -device ipmi-bmc-sim,id=bmc0 \
    -device pci-ipmi-kcs,bmc=bmc0


libvirt XML Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: xml

  <devices>
    <!-- Define the IPMI controller device interface -->
    <controller type='ipmi' index='0' model='kcs'>
      <backend model='sim'/>
    </controller>
  </devices>


External Emulation (Full Featured)
----------------------------------

.. code-block:: text

                       +------------------------+
                       |    External Daemon     |
                       |       (ipmi_sim)       |
                       +-----------+------------+
                                   | (Unix Socket / TCP)
                                   v
  +--------------------------------+------------+
  | QEMU VM                                     |
  |  +---------------+      +----------------+  |
  |  | Guest OS      | ===> | ipmi-bmc-extern|  |
  |  | (ipmitool)    |      | Device Model   |  |
  |  +---------------+      +----------------+  |
  +---------------------------------------------+


.. code-block:: shell

   $ ipmi_sim -c /etc/ipmi/lan.conf -f /etc/ipmi/ipmisim.emu


.. code-block:: shell

  $ qemu-system-x86_64 -m 2G -smp 2 -cdrom ubuntu.iso \
    -chardev socket,id=ipmichr,path=/tmp/ipmisim-sock,reconnect=10 \
    -device ipmi-bmc-extern,id=bmc0,chardev=ipmichr \
    -device isa-ipmi-kcs,bmc=bmc0


Links
-----

- OpenIPMI: https://github.com/cminyard/openipmi
- Aspeed family boards: https://www.qemu.org/docs/master/system/arm/aspeed.html
- Nuvoton iBMC boards: https://www.qemu.org/docs/master/system/arm/nuvoton.html
