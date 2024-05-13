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

