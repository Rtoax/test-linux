AES - Advanced Encryption Standard
==================================


# Instruction

- AESENC
- AESENCLAST
- AESDEC
- AESDECLAST
- AESKEYGENASSIST
- AESIMC


# Headers

```c
#include <vaesintrin.h>
#include <wmmintrin.h>
```

# 关闭虚拟机`sse`特性:

```xml
<domain type='kvm' xmlns:qemu='http://libvirt.org/schemas/domain/qemu/1.0'>
  ...
  <qemu:commandline>
    <qemu:arg value='-cpu'/>
    <qemu:arg value='host,-aes'/>
  </qemu:commandline>
</domain>
```

或者

```xml
<domain type='kvm' xmlns:qemu='http://libvirt.org/schemas/domain/qemu/1.0'>
  ...
  <cpu mode='host-model' check='none'>
    <feature policy='disable' name='vmx'/>
  </cpu>
  ...
  <qemu:commandline>
    <qemu:arg value='-cpu'/>
    <qemu:arg value='host,-aes'/>
  </qemu:commandline>
</domain>
```


# Links

- https://en.wikipedia.org/wiki/AES_instruction_set
- https://medium.com/coccoc-engineering-blog/kvm-guests-cpu-flags-5d3ac9525421
- https://www.felixcloutier.com/x86/aesenc
- https://github.com/wolfmuel/aesenc
