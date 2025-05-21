VM Sockets(vsock)
==================

# Background

VM Sockets(vsock) is a fast and efficient communication mechanism between guest virtual machines and their host. It was added by VMware in commit [VSOCK: Introduce VM Sockets](https://github.com/torvalds/linux/commit/d021c344051af91f42c5ba9fdedc176740cbd238). The commit added a new socket address family named vsock and its vmci transport.

VM Sockets can be used in a lot of situation such as the VMware Tools inside the guest. As vsock is very useful the community has development vsock supporting other hypervisor such as **qemu&&kvm** and **HyperV**. Redhat added the virtio transport for vsock in [VSOCK: Introduce virtio_transport.ko](https://github.com/torvalds/linux/commit/0ea9e1d3a9e3ef7d2a1462d3de6b95131dc7d872), for vhost transport in host was added in comit [VSOCK: Introduce vhost_vsock.ko](https://github.com/torvalds/linux/commit/433fc58e6bf2c8bd97e57153ed28e64fd78207b8). Microsoft added the HyperV transport in commit [hv_sock: implements Hyper-V transport for Virtual Sockets (AF_VSOCK)](https://github.com/torvalds/linux/commit/ae0078fcf0a5eb3a8623bfb5f988262e0911fdb9), Of course this host transport is in Windows kernel and no open sourced.


# Overview

```
┌───────┐ ┌───────┐           ┌────────┐
│ Guest │ │ Guest │           │ Guest  │
│ CID=3 │ │ CID=5 │           │ CID=135│
└───▲───┘ └───▲───┘           └────▲───┘
    │         │                    │
    │         │                    │
┌───▼─────────▼────────────────────▼───┐
│                 Host                 │
│          VMADDR_CID_HOST(2)          │
└──────────────────────────────────────┘
```

- POSIX Socket API

```
┌────────────┐
│      ┌───┐ │
│Guest │APP│ │
│      └─▲─┘ │
├────────┼───┤
│┌───────▼──┐│
││  Socket  ││
│├──────────┤│
││ AF_VSOCK ││
│└────▲─────┘│
└─────┼──────┘
      │
┌─────┼────────────────────────────────┐
│     │                         ┌─────┐│
│     │                         │ APP ││
│     │                         └──▲──┘│
├─────┼────────────────────────────┼───┤
│     │                    ┌───────▼──┐│
│     │                    │  Socket  ││
│     │                    ├──────────┤│
│     └────────────────────▶ AF_VSOCK ││
│ Host                     └──────────┘│
└──────────────────────────────────────┘
```

- loopback: need module `vsock_loopback`

```
┌──────────┐                ┌──────────┐
│  Server  │                │  Client  │
└─────▲────┘                └────▲─────┘
      │                          │
      │     VMADDR_CID_LOCAL     │
      │                          │
┌─────▼──────────────────────────▼─────┐
│           vsock_loopback.ko          │
└──────────────────────────────────────┘
```


# Qemu

```shell
(host)# qemu-system-x86_64 -device vhost-vsock-pci,guest-cid=3 ...
```


# Libvirt

```xml
<domain type='kvm'>
  <devices>
    <vsock model='virtio'>
      <!-- start from 3 -->
      <cid auto='no' address='3'/>
      <!-- or auto -->
      <cid auto='yes'/>
    </vsock>
  </devices>
</domain>
```


# Device

- /dev/vsock: vsock.ko


# Links

- https://www.man7.org/linux/man-pages/man7/vsock.7.html
- https://wiki.qemu.org/Features/VirtioVsock
