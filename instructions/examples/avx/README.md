Advanced Vector Extensions (AVX)
================================


- `AVX2`扩充到了支持`256bit`的整数运算指令
- `AVX-512`通过使用新的`EVEX prefix`编码方式，将`AVX`扩充到了支持`512-bit`运算


# Headers

- /usr/lib/gcc/x86_64-redhat-linux/11/include/avx512fintrin.h


# 禁用虚拟机的`avx2`特性

```xml
<domain type='kvm' xmlns:qemu='http://libvirt.org/schemas/domain/qemu/1.0'>
  <qemu:commandline>
    <qemu:arg value='-cpu'/>
    <qemu:arg value='host,-avx2'/>
  </qemu:commandline>
</domain>
```


# Links

- https://en.wikipedia.org/wiki/Advanced_Vector_Extensions#Advanced_Vector_Extensions_2

