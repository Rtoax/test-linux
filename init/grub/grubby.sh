#!/bin/bash

add_arg_all() {
	sudo grubby --update-kernel=ALL --args=intel_iommu=on
}
add_arg() {
	sudo grubby --update-kernel=/boot/vmlinuz-$(uname -r) --args=intel_iommu=on
}

remove_arg_all() {
	sudo grubby --update-kernel=ALL --remove-args=intel_iommu=on
}
remove_arg() {
	sudo grubby --update-kernel=/boot/vmlinuz-$(uname -r) --remove-args=intel_iommu=on
}

set_default() {
	sudo grubby --set-default /boot/vmlinuz-$(uname -r)
}

info() {
	sudo grubby --info=/boot/vmlinuz-$(uname -r)
	sudo grubby --info=ALL
}

info
