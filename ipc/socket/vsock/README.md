VM Sockets(vsock)
==================

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


# Device

- /dev/vsock: vsock.ko


# Links

- https://www.man7.org/linux/man-pages/man7/vsock.7.html
