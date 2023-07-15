Kernel Connector
=========

* [Kernel connector](https://www.kernel.org/doc/html/latest/driver-api/connector.html)

Kernel connector - new netlink based userspace <-> kernel space easy to use communication module.

From the userspace point of view it’s quite straightforward:

```
socket();
bind();
send();
recv();
```
