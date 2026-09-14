#!/bin/bash
# utility for controlling IPMI-enabled devices
#
set -e

ip=10.32.161.216
user=root
password=root

_ipmitool() {
	sudo ipmitool -I lanplus -H $ip -U $user -P $password "${@}"
}

# reboot BMC
_ipmitool mc reset cold

# check BMC IP address
_ipmitool lan print

# Boot from bios
_ipmitool chassis bootdev bios
# Reboot machine
_ipmitool power reset

# Rediect bmc console
_ipmitool sol activate
_ipmitool sol deactivate

# Check FRU (Field Replace Unit 现场可更换单元)
_ipmitool fru

# Check SDR, Sensor
_ipmitool sensor list

ipmitool_boot() {
	_ipmitool chassis bootparam set bootflag force_pxe
	_ipmitool chassis bootdev pxe
	_ipmitool raw 0x00 0x08 0x05 0x80 0x04 0x00 0x00 0x00

	# 0x00：网络功能码（NetFn），表示 chassis（机箱）相关的命令.
	# 0x08：命令码（CMD），表示设置系统启动选项（Set System Boot Options）.
	# 0x05：参数类型，表示设置启动设备.
	# 0xa0：设置启动有效期的标志位，二进制为 1010 0000：
	# Bit 7：启动设置有效性的标志位，1 表示有效.
	# Bit 6：一次性启动或者永久启动，0 表示一次性启动，启动设备的设置只在
	#        下一次启动时生效，然后恢复为默认值.
	# 0x04：设置服务器的启动设备，二进制为 0000 0100，其中 Bit 5～Bit 2 为
	#       0100，表示 PXE 启动.
	# 0x00 0x00 0x00：后续的三个字节通常用于设置其他启动相关的参数，但在这
	#                 个命令中，它们被设置为 0x00，表示不进行其他额外的设置
	#                 或配置.
	_ipmitool raw 0x00 0x08 0x05 0xa0 0x04 0x00 0x00 0x00

	# raw 0x00 0x08 0x05 0xc0 0x04 0x00 0x00 (To boot from PXE first)
	# raw 0x00 0x08 0x05 0xc0 0x14 0x00 0x00 (To boot from CD/DVD first)
	# raw 0x00 0x08 0x05 0xc0 0x3C 0x00 0x00 (To boot from floppy or any removable media)
	# raw 0x00 0x08 0x05 0xc0 0x08 0x00 0x00 (To boot from the hard drive)
}

# Print System Event Log (SEL)
_ipmitool sel list
