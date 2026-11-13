======
SR-IOV
======

NIC
---

- Create virtual NIC

.. code-block:: bash

    echo '4' > /sys/class/net/[Interface]/device/sriov_numvfs
