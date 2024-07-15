SPDK - Storage Performance Development Kit
===========================================

# SPDK Block Diagram

```
+---------------------+
|  Storage Protocols  |
+----------+----------+
           |
+----------+----------+
|  Storage Services   |
+----------+----------+
           |
+----------+----------+
|      Drivers        |
+---------------------+
```

## Storage Protocols

- NVMe-oF Target (RDMA)
- iSCSI Target
- vhost-scsi Target
- vhost-blk Target
- Linux nbd


## Storage Services

> Block Device Abstraction (bdev)

- NVMe
- Linux AIO
- Ceph RBD
- PMDK blk
- virtio-scsi
- virtio-blk


## Drivers

- NVMe-oF Initiator
- NVMe PCIe Driver


# Links

- https://github.com/spdk/spdk

