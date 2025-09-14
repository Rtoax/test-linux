SSE (Streaming SIMD Extensions)
===============================


# 介绍

- ssse3 是 sse3 的扩充

关闭虚拟机`sse`特性:

```xml
<domain type='kvm' xmlns:qemu='http://libvirt.org/schemas/domain/qemu/1.0'>
  ...
  <qemu:commandline>
    <qemu:arg value='-cpu'/>
    <qemu:arg value='host,-sse4.1,-sse4.2'/>
  </qemu:commandline>
</domain>
```

添加`sse`特性：

`host-passthrough`改为`custom`

```xml
<domain type='kvm' xmlns:qemu='http://libvirt.org/schemas/domain/qemu/1.0'>
  ...
  <cpu mode='custom' match='exact' check='partial'>
    <model fallback='allow'>qemu64</model>
    <feature policy='require' name='sse4.2'/>
    <feature policy='disable' name='svm'/>
  </cpu>
  ...
  <qemu:commandline>
    <qemu:arg value='-cpu'/>
    <qemu:arg value='qemu64,+ssse3,+sse4.1,+sse4.2'/>
  </qemu:commandline>
</domain>
```


# Headers

## SSE2


```c
#include <emmintrin.h>
#include <mmintrin.h>
```


## SSE3

```c
#include <pmmintrin.h>
#include <immintrin.h>   // (Meta-header)
```


## SSE4

```c
#include <smmintrin.h>
#include <nmmintrin.h>
```


# Links

- https://en.wikipedia.org/wiki/SSE4
- https://superuser.com/questions/1467225/how-to-make-the-kvm-enable-cpu-flags-sse4-2-to-the-guest
