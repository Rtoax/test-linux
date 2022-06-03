'fw_cfg' - Firmware Configuration
=================================

很多时候 Qemu 需要将一些数据传递给虚拟机，比如虚拟机的启动引导顺序、ACPI 和 SMBIOS 表、SMP 和 NUMA 信息等。
虚拟机的 Firmware(如 SeaBIOS) 可以根据这些数据进行相应的配置。Qemu 提供了所谓 Firmware Configuration(`fw_cfg`)
Device 机制来完成这项工作。

# /sys/firmware/qemu_fw_cfg/

In GuestOS `/sys/firmware/qemu_fw_cfg` has `fw_cfg` informations.

