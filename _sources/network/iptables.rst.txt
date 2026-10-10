iptables
=========

Kernel Sysctl
-------------

- whether packets crossing a bridge are sent to iptables for processing

.. code-block:: text

    net.bridge.bridge-nf-call-iptables=1
    net.bridge.bridge-nf-call-ip6tables=1
