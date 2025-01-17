Scalable Vector Extension (SVE)
================================

Scalable Vector Extension (SVE) is a vector extension the A64 instruction set of
the Armv8-A architecture. Armv9-A builds on SVE with the SVE2 extension.

可伸缩向量扩展(SVE)是 Armv8-A 架构的 A64指令集的向量扩展。Armv9-A 构建在 SVE 和 SVE2 扩展的基础上。与其他 SIMD 架构不同，SVE 和 SVE2 并不定义向量寄存器的大小，而是将其限制在一个可能的值范围内，从**最小128位**到**最大2048位**(128位宽单元)。因此，任何 CPU 供应商都可以通过选择更适合 CPU 目标工作负载的向量寄存器大小来实现扩展。

SVE 和 SVE2 的设计保证了同一个程序可以在不同的指令集架构实现上运行，而无需重新编译代码。


# 在 qemu virsh xml 中使能 SVE

> qemu 命令行`-cpu max,sve=on,sve256=on`，同 ostools

```
<domain type='qemu' xmlns:qemu='http://libvirt.org/schemas/domain/qemu/1.0'>
  <qemu:commandline>
    <qemu:arg value='-cpu'/>
    <qemu:arg value='max,sve=on,sve256=on'/>
  </qemu:commandline>
</domain>
```


# Links

- https://developer.arm.com/Architectures/Scalable%20Vector%20Extensions

