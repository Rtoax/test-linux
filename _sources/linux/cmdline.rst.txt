Kernel cmdline
==============

console
-------

earlycon
--------

- `earlycon=pl011,<addr>`: ARM PL011
- `earlycon=uart8250,mmio32,<addr>`: 8250 兼容 MMIO 串口
- `earlycon=uart8250,io,<port>`: x86 IO 端口
- `earlycon=sbi`: RISC-V SBI 控制台
- `earlycon=efifb`: EFI 帧缓冲（极少数情况）


rootdelay
---------

- `rootdelay=<N>`
