SPDK - Storage Performance Development Kit
===========================================

# SPDK Block Diagram

```
  +---------------+   +--------------+
  | Block Storage |   | File Storage |
  |    Protocols  |   |   Services   |
  +---------------+   +--------------+

  +----------------------------------+
  |      Block Storage Services      |
  +----------------------------------+

  +----------------------------------+
  |      Block Storage Providers     |
  +----------------------------------+

  +----------------------------------+
  |             Drivers              |
  +----------------------------------+
```

## Block Storage Protocols

- Network
	- NVMe-oF Target (RDMA, TCP, FC)
	- iSCSI Target
- Virtualization
	- vhost-scsi Target
	- vhost-blk Target
	- vfio-user
- Linux nbd


## File Storage Services

- Filesystems: BlobFS


## Block Storage Services

- Partitioning: lvm, gpt
- Caching: OCF
- Host FTL: Open Channel
- Pooling: RAID-0
- Transforms: Crypto, Compression


## Block Storage Providers

> Block Device Abstraction (bdev)

- NVMe
- Linux AIO
- `io_uring`
- Ceph RBD
- PMDK blk
- iSCSI
- virtio-scsi
- virtio-blk


## Drivers

- NVMe(PCIe, RDMA, TCP)
- virtio(scsi, blk)


# Links

- https://github.com/spdk/spdk

