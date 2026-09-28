===========
File System
===========

.. toctree::
   :maxdepth: 1

   abbrev


Linux Kernel
------------

.. toctree::
   :maxdepth: 1

   9p
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


User space
----------

.. toctree::
   :maxdepth: 1

   sshfs


Tools
-----

.. toctree::
   :maxdepth: 1

   ../tools/util-linux/wipefs


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


Container Storage Drivers
-------------------------

- xfs,ext4 support overlay, overlay2 and aufs;
- devicemapper driver is backed by direct-lvm;
