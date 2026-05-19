============
Cloud Native
============

.. toctree::
   :maxdepth: 1

   abbrev
   cncf
   pod
   kubernetes
   microservices
   service-mesh


Metrics and Observability
-------------------------

.. toctree::
   :maxdepth: 1

   prometheus
   grafana
   node-exporter


Tracing
-------

.. toctree::
   :maxdepth: 1

   jaeger


Cloud Infrastructure Technologies
---------------------------------

- `IaaS`: IaaS uses hypervisors, such as Xen, KVM, VMware ESXi, Hyper-V, or
  Nitro.
- `PaaS`: PaaS can be deployed on top of IaaS or independently on VMs,
  bare-metal servers, and containers.


Storage Drivers
---------------

Docker Storage Drivers
~~~~~~~~~~~~~~~~~~~~~~

- `BtrFS`: Supports snapshots.
- `Device Mapper`: For earlier CentOS and RHEL releases.
- `Fuse-Overlay`: Preferred for rootless mode.
- `Overlay2`: Preferred for all supported Linux distributions (Ubuntu, Debian,
  CentOS, Fedora, RHEL, SLES 15).
- `VFS` (Virtual File System): For testing only, not for production.
- `ZFS`: Supports snapshots.


Podman Storage Drivers
~~~~~~~~~~~~~~~~~~~~~~

- `AUFS` (Another Union File System)
- `BtrFS`
- `Thinpool` (Device Mapper)
- `Overlay`
- `VFS` (Virtual File System)
- `ZFS`


Links
-----

- `Cloud Native System Overview <https://swiftorial.com/archview/cloud-native/cloud-native-system-overview>`_
- GitHub markdown: `Reference Architecture for a Cloud Native Digital Enterprise <https://github.com/wso2/reference-architecture/blob/master/reference-cloud-native-architecture-digital-enterprise.md>`_
- GitHub: `Docker Container Network Model (CNM) <https://github.com/moby/libnetwork/blob/master/docs/design.md>`_
- GitHub: https://github.com/containernetworking/cni
    - GitHub: `Container Network Interface (CNI) Specification <https://github.com/containernetworking/cni/blob/main/SPEC.md>`_
- https://opencontainers.org/
    - https://github.com/opencontainers
    - `OCI Runtime Spec v1.2 <https://opencontainers.org/posts/blog/2024-02-18-oci-runtime-spec-v1-2/>`_
