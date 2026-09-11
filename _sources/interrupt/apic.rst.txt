APIC - 高级可编程中断控制器
===========================

* apic: Use IO-APIC. Default
* noapic: Don’t use the IO-APIC.
* disableapic: Don’t use the local APIC


LAPIC - Local APIC
------------------

* 每个 CPU 都有一个 LAPIC，在 CPU 内部;
* 另一个是用来链接设备的 I/O APIC, 系统中可以有多个 I/O APIC;


Links
-----

- 内核命令行参数 apics: https://www.kernel.org/doc/html/latest/x86/x86_64/boot-options.html#apics
