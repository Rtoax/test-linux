iSCSI - Internet Small Computer Systems Interface
=================================================

iSCSI 是一种协议，它通过 IP 提供对存储设备的块级访问。这允许应用程序将远程存储
设备视为本地磁盘。iSCSI 处理来自客户端的请求并在远程 SCSI 设备上执行它们。

- iSCSI is a `client-server` architecture;
- `Clients` of an iSCSI interface are known as `initiators`;
- `Server` that shares the storage area is known as the `targets`;
  * iSCSI `target` is the storage device;

```
    iSCSI Initiator               iSCSI Target
    +-----------+  cmd and data   +-----------+
    |    SCSI   | <-------------> |    SCSI   |
    +-----------+ Login+Discovery +-----------+
    |   iSCSI   | <-------------> |   iSCSI   |
    +-----------+                 +-----------+
    |TCP(or UDP)|                 |TCP(or UDP)|
    +-----------+                 +-----------+
    |     IP    |                 |     IP    |
    +-----------+                 +-----------+
    |   Ether   |                 |   Ether   |
    +-----------+                 +-----------+
    | Fiber...  |                 | Fiber...  |
    +-----------+                 +-----------+
          ^                             ^
          |                             |
          +-----------------------------+
```
