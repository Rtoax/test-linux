Livepatch
=========

Disable a livepatch module
--------------------------

.. code-block:: shell

    echo 0 | sudo tee /sys/kernel/livepatch/buffer_IO_error/enabled
