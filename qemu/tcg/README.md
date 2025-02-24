Tiny Code Generator (TCG)
=========================

The Tiny Code Generator (TCG) exists to transform target insns (the processor
being emulated) via the TCG frontend to TCG ops which are then transformed into
host insns (the processor executing QEMU itself) via the TCG backend.

- [frontend-ops](https://wiki.qemu.org/Documentation/TCG/frontend-ops)
- [backend-ops](https://wiki.qemu.org/Documentation/TCG/backend-ops)


# Qemu thread

`CPU x/TCG` like:

```
    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
 195836 root      20   0   10.0g 755456  20864 S  48.8   0.2   0:06.18 CPU 1/TCG
 195837 root      20   0   10.0g 755456  20864 R  30.6   0.2   0:05.51 CPU 2/TCG
 195838 root      20   0   10.0g 755456  20864 S  20.6   0.2   0:10.34 CPU 3/TCG
 195835 root      20   0   10.0g 755456  20864 S   7.3   0.2   0:16.83 CPU 0/TCG
```


# TCG IR 大致分为以下几类

> IR: Intermediate Representation (中间表示)

- 移动指令: mov, movi, ...
- 逻辑指令: and, or, xor, shl, shr, ...
- 算术指令: add, sub, mul, div, ...
- 条件移动指令: jmp, br, brcond
- 跳转指令: call
- 加载/存储指令: ld, st
- QEMU特殊指令: `tb_exit, goto_tb, qemu_ld/qemu_st`


# Features

## x86_64

- TCG not support avx512 yet (qemu 8.2.2 on fedora40).


# MTTCG (Multithread TCG)


# Links

- https://wiki.qemu.org/Documentation/TCG

