Cloud Native
============

# Cloud Infrastructure Technologies

- `IaaS`: IaaS uses hypervisors, such as Xen, KVM, VMware ESXi, Hyper-V, or Nitro.
- `PaaS`: PaaS can be deployed on top of IaaS or independently on VMs, bare-metal servers, and containers.


# Storage Drivers

## Docker Storage Drivers

- `BtrFS`: Supports snapshots.
- `Device Mapper`: For earlier CentOS and RHEL releases.
- `Fuse-Overlay`: Preferred for rootless mode.
- `Overlay2`: Preferred for all supported Linux distributions (Ubuntu, Debian, CentOS, Fedora, RHEL, SLES 15).
- `VFS` (Virtual File System): For testing only, not for production.
- `ZFS`: Supports snapshots.


## Podman Storage Drivers

- `AUFS` (Another Union File System)
- `BtrFS`
- `Thinpool` (Device Mapper)
- `Overlay`
- `VFS` (Virtual File System)
- `ZFS`


# Links

- GitHub: [Container Network Model (CNM)](https://github.com/moby/libnetwork/blob/master/docs/design.md)
- GitHub: [https://github.com/containernetworking/cni](https://github.com/containernetworking/cni)
	- GitHub: [Container Network Interface (CNI) Specification](https://github.com/containernetworking/cni/blob/main/SPEC.md)


