LVM - Logical Volume Manager
============================

In Linux, Logical Volume Manager (LVM)  is  a device mapper framework that
provides logical volume management for the Linux kernel. Most modern Linux
distributions are LVM-aware to the point of  being able to have their root
file systems on a logical volume.


- PP: Physical Partition
- PV: Physical Volumes
- VG: Volume Groups
- LV: Logical Volumes
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


# Links

- https://en.wikipedia.org/wiki/Logical_Volume_Manager_(Linux)

