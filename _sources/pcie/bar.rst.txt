===========================
BAR (Base Address Register)
===========================

/sys/bus/pci/devices/0000:0d:00.0/resource
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Format: `start_address   end_address   flags`

.. code-block:: shell

    sudo dd if=/dev/mem bs=1 count=4 skip=<start_address> 2>/dev/null | hexdump -C


.. code-block:: c

    void __iomem *bar_addr;
    bar_addr = ioremap(BAR_PHYS_ADDR, BAR_SIZE);
    u32 value = readl(bar_addr + 0);


/sys/bus/pci/devices/0000:0d:00.0/resourceN
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c

    int fd = open("/sys/bus/pci/devices/0000:0d:00.0/resource2", O_RDWR | O_SYNC);
    void *map_base = mmap(0, map_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
