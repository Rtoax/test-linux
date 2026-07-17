===========
File System
===========

.. toctree::
   :maxdepth: 1

   abbrev

.. toctree::
   :maxdepth: 1

   aufs
   btrfs
   cephfs
   cifs
   configfs
   debugfs
   devtmpfs
   erofs
   ext
   ext2
   ext3
   ext4
   f2fs
   fat
   glusterfs
   ksmbd
   lustre
   nfs
   ocfs2
   overlayfs
   procfs
   squashfs
   sysfs
   unionfs
   vfs
   xfs


Write
-----

.. code-block:: text

                                         User Data
                                            |
                                            |
                                    stdio library calls
                                    printf(),fputs(),etc.--------+
                To force buffer             |                    |
                 flush fflush()             |                    | Make flush automatic
                        |                   |                    +  on each IO call
                        |               stdio buffer            /    setbuf(stream, NULL)
                        +--------------+    |           +------+
    user space                          \   |          /
    ----------------------------------IO system calls------------------
    kernel space                         write(), etc.\
                                            |          +---------+
                                            |                    |
                                        Kernel buffer            |
                                            cache                | open(path, flags|O_SYNC, mode);
                fsync(),                    |                    |
                fdatasync(),                |                    |
                sync(),.                    |                    |
                    |                       |                    |
                    *----------------->kernel-initiated----------+
                                            write
                                            |
                                            |
                                            DISK

wipe
----

wipefs
~~~~~~

这会擦除块设备，谨慎执行

.. code-block:: shell

    $ sudo wipefs -af /dev/sdxxx


Container Storage Drivers
-------------------------

- xfs,ext4 support overlay, overlay2 and aufs;
- devicemapper driver is backed by direct-lvm;
