# interrupt-modules

This is a set of Linux kernel modules that, with the help of pseudo-files in
procfs, allow to view hardware and internal kernel data, that can be helpful in
researching and debugging interrupts-related issues.

All modules work for both: x86 and x86_64 architectures. They were tested on
Linux kernel version 4.4.5.


## ioapic

GitHub: https://github.com/nebaruzdin/interrupt-modules

By default creates /proc/ioapic0 file that shows the contents of the IO-APIC
interrupt routing table. Supports an optional second IO-APIC: if the second
IO-APIC's base address is provided, the /proc/ioapic1 file is also created.
IO-APICs' base addresses are set through module parameters:

		# insmod ioapic.ko ioapic0_base=0xFEC00000 ioapic1_base=0xFEC01000

Thus you can simultaneously view the contents of any two of the system IO-APICs.

For details see:
- [82093AA I/O Advanced Programmable Interrupt Controller (IOAPIC)][2]
- http://wiki.osdev.org/IOAPIC

[1]: http://download.intel.com/design/archives/processors/pro/docs/24201606.pdf
[2]: http://download.intel.com/design/chipsets/datashts/29056601.pdf
[3]: http://download.intel.com/design/processor/manuals/253668.pdf
