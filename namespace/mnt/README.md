Namespace MNT
=============


# flags MS_SHARED

- **rshared** 或 **shared**
  - 可以保证当`$PWD`下存在mount点时，在host下umount后，容器内也被umount.
  - 对应`mount(2)`参数`MS_SHARED`.

```
$ sudo podman run --rm -ti --privileged -v $PWD:/root:rshared [IMAGE] bash
```

可以使用**bcc:tools/mountsnoop.py**进行跟踪。

