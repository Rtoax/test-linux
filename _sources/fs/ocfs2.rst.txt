OCFS2 - Oracle Cluster File System Version 2
============================================

`OCFS2` 是 `Oracle Cluster File System Version 2` 的缩写，是 `Oracle` 公司内部开发的共享磁盘文件系统，于2011年开源，使用GNU GPL协议。

- 磁盘文件系统
- 共享文件系统: NFS, samba 等
- 共享磁盘文件系统: OCFS2


CONFIG
------

- `CONFIG_OCFS2_FS`


命令
---

mkfs.ocfs2
~~~~~~~~~~

.. code-block:: shell

    $ sudo mkfs.ocfs2 -L OCFS2_LABEL -T vmstore --fs-feature-level=max-compat /dev/vdd -N 2
