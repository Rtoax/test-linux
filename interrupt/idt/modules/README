# interrupt-modules

This is a set of Linux kernel modules that, with the help of pseudo-files in
procfs, allow to view hardware and internal kernel data, that can be helpful in
researching and debugging interrupts-related issues.

All modules work for both: x86 and x86_64 architectures. They were tested on
Linux kernel version 4.4.5.

## idt

GitHub: https://github.com/nebaruzdin/interrupt-modules

Creates /proc/idt file that shows the contents of the Interrupt Descriptor
Table (IDT).

Each rule from the IO-APIC's routing table can contain a number, known as an
interrupt vector (IV), that refers to a specific entry in IDT. IDT entry, in
turn, contains the location of an interrupt service routine (ISR) that will be
executed for the given interrupt.

For details see:
- [Intel 64 and IA-32 Architectures Software Developer’s Manual.
Volume 3A: System Programming Guide, Part 1][3]
- http://wiki.osdev.org/Interrupt_Descriptor_Table

[1]: http://download.intel.com/design/archives/processors/pro/docs/24201606.pdf
[2]: http://download.intel.com/design/chipsets/datashts/29056601.pdf
[3]: http://download.intel.com/design/processor/manuals/253668.pdf
