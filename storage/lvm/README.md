LVM - Logical Volume Manager
============================

In Linux, Logical Volume Manager (LVM)  is  a device mapper framework that
provides logical volume management for the Linux kernel. Most modern Linux
distributions are LVM-aware to the point of  being able to have their root
file systems on a logical volume.


- VG: Volume Groups      (sudo vgs)
- PV: Physical Volumes   (sudo pvs)
- PP: Physical Partition
- LV: Logical Volumes    (sudo lvs)
- FS: Filesystem
- MP: Mounting Point

```
+----------------------------------------------------------------------------------+
|  VG: myvg                                                                        |
|  +----------------------------+    +--------------------+  +------------------+  |
|  | PV hdisk1                  |    |PV hdisk2           |  | PP hdisk3        |  |
|  |   +-------+    +-------+   |    |  +--+       +--+   |  |  +--+     +--+   |  |
|  |   |PP(32M)|    |PP(32M)|   |    |  |PP|       |PP|   |  |  |PP|     |PP|   |  |
|  |   +-------+    +-------+   |    |  +--+       +--+   |  |  +--+     +--+   |  |
|  | +---------------------------------------+            |  |        +-------+ |  |
|  | | +-------+    +-------+   |    |  +--+ |     +--+   |  |  +--+  |  +--+ | |  |
|  | | |PP(32M)|    |PP(32M)|   |    |  |PP| |     |PP|   |  |  |PP|  |  |PP| | |  |
|  | | +-------+    +-------+   |    |  +--+ |     +--+   |  |  +--+  |  +--+ | |  |
|  | |                        +--------------+   +------+ |  |        |       | |  |
|  | | +-------+    +-------+ | |    |  +--+     | +--+ | |  |  +--+  |  +--+ | |  |
|  | | |PP(32M)|    |PP(32M)| | |    |  |PP|     | |PP| | |  |  |PP|  |  |PP| | |  |
|  | | +-------+    +-------+ | |    |  +--+     | +--+ | |  |  +--+  |  +--+ | |  |
|  | |                        | |    |           |      | |  |        |       | |  |
|  +-|------------------------|-+    +-----------|------|-+  +--------|-------|-+  |
|    |                        |                  |      |             |       |    |
+----|------------------------|------------------|------|-------------|-------|----+
     |                        |                  |      |             |       |
     |                        |        +---------+      |      +------+       |
     |  LV: /dev/hlv          |        | LV:/dev/srv    |      | LV:/dev/data |
     +------------------------+        +----------------+      +--------------+
     |  FS: xfs               |        | FS: ext3       |      | FS: ext4     |
     +------------------------+        +----------------+      +--------------+
     |  MP: /home/            |        | MP: /var/www   |      | MP: /data/   |
     +------------------------+        +----------------+      +--------------+
```


# Q&A

## mount: unknown filesystem type 'LVM2_member'

- vgs
  lvchange -ay cl (-a: activate)
- mount /dev/mapper/


# Links

- https://en.wikipedia.org/wiki/Logical_Volume_Manager_(Linux)

