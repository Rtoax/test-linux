KSM - Kernel SamePage Merging
=============================

KSM sysfs
---------

* Enable ksm

.. code-block:: shell

  echo 1 > /sys/kernel/mm/ksm/run

* Check ksm info

.. code-block:: shell

  cat /sys/kernel/mm/ksm/pages_sharing
  cat /sys/kernel/mm/ksm/pages_shared
  cat /sys/kernel/mm/ksm/pages_unshared


ksmtuned
--------

.. code-block:: shell

  # cat /etc/ksmtuned.conf
