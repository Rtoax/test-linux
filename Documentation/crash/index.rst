============
Kernel Crash
============

Trigger crash
-------------

.. code-block:: text

   $ echo c | sudo tee /proc/sysrq-Trigger


Start crash
-----------

.. code-block:: text

   $ sudo crash /usr/lib/debug/lib/modules/$(uname -r)/vmlinux vmcore


Commands
--------

.. toctree::
   :maxdepth: 3

   commands/index


Links
-----

- https://github.com/crash-utility/crash
