virtio
======

# virtio 组成

1. virtio frontend
2. virt queue
	* virtqueue: vring
3. virtio backend
	* vhost


# vring

## vring 组成

1. Descriptor Table
2. Available Vring
3. Used Vring


```
 *          +------------------------------------+
 *          |       virtio  guest driver         |
 *          +-----------------+------------------+
 *            /               |              ^
 *           /                |               \
 *          put            update             get
 *         /                  |                 \
 *        V                   V                  \
 *   +----------+      +------------+        +----------+
 *   |          |      |            |        |          |
 *   +----------+      +------------+        +----------+
 *   | available|      | descriptor |        |   used   |
 *   |   ring   |      |   table    |        |   ring   |
 *   +----------+      +------------+        +----------+
 *   |          |      |            |        |          |
 *   +----------+      +------------+        +----------+
 *   |          |      |            |        |          |
 *   +----------+      +------------+        +----------+
 *        \                   ^                   ^
 *         \                  |                  /
 *         get             update              put
 *           \                |                /
 *            V               |               /
 *           +----------------+-------------------+
 *           |       virtio host backend          |
 *           +------------------------------------+
```


# Links

- https://kernelgo.org/virtio-overview.html
- PDF: [Virtual I/O Device (VIRTIO) Version 1.2](https://docs.oasis-open.org/virtio/virtio/v1.2/virtio-v1.2.pdf)

