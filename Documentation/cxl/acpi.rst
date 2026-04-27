========
CXL ACPI
========

ACPI: /sys/firmware/acpi/
-------------------------

ACPI0017: CXL Root Object, CEDT
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: text

    { "ACPI0017", (unsigned long) &native_acpi0017 },

.. code-block:: text

    $ sudo dmesg | grep ACPI0017

.. code-block:: text

    /sys/bus/acpi/devices/ACPI0017:00/


ACPI0016: CXL Host Bridge Object, CXL root complex
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
