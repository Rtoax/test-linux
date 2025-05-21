VM Sockets(vsock)
==================

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
