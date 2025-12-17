# interrupt-modules

This is a set of Linux kernel modules that, with the help of pseudo-files in
procfs, allow to view hardware and internal kernel data, that can be helpful in
researching and debugging interrupts-related issues.

All modules work for both: x86 and x86_64 architectures. They were tested on
Linux kernel version 4.4.5.

## mp

GitHub: https://github.com/nebaruzdin/interrupt-modules

Creates /proc/mp file that shows the contents of the Intel Multiprocessor
Specification data structures.

Particularly, it can be used to determine the number of IO-APICs in the system
and their base addresses. (Note that you can also use ACPI tables for the same
purpose.) For instance:

		$ cat /proc/mp
		...
		Base MP Configuration Table:
		...
		0x104: 02 00 20 01 00 00 C0 FE
		0x10C: 02 02 20 01 00 10 C0 FE
		...

Here the first "02" byte identifies the IO-APIC entry. Last 4 bytes contain the
IO-APIC base address in little-endian. So in this case the system has two
IO-APICs with base addresses 0xFEC00000 and 0xFEC01000.

For details see:
- [Intel Multiprocessor Specification. Version 1.4][1]
- http://wiki.osdev.org/SMP#Finding_information_using_MP_Table

[1]: http://download.intel.com/design/archives/processors/pro/docs/24201606.pdf
[2]: http://download.intel.com/design/chipsets/datashts/29056601.pdf
[3]: http://download.intel.com/design/processor/manuals/253668.pdf
