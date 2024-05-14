Tiny Code Generator (TCG)
=========================

The Tiny Code Generator (TCG) exists to transform target insns (the processor
being emulated) via the TCG frontend to TCG ops which are then transformed into
host insns (the processor executing QEMU itself) via the TCG backend.

- [frontend-ops](https://wiki.qemu.org/Documentation/TCG/frontend-ops)
- [backend-ops](https://wiki.qemu.org/Documentation/TCG/backend-ops)


# TCG IR 大致分为以下几类

> IR: Intermediate Representation (中间表示)

- 移动指令: mov, movi, ...
- 逻辑指令: and, or, xor, shl, shr, ...
- 算术指令: add, sub, mul, div, ...
- 条件移动指令: jmp, br, brcond
- 跳转指令: call
- 加载/存储指令: ld, st
- QEMU特殊指令: `tb_exit, goto_tb, qemu_ld/qemu_st`


# Links

- https://wiki.qemu.org/Documentation/TCG

