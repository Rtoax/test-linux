#!/bin/bash

get_qemu_kvm_emulator()
{
	qemu_kvm=""

	qemu_kvm_possible_emulators=(
		/usr/libexec/qemu-kvm
		/usr/libexec/qemu-system-$(uname -m)
		/usr/bin/qemu-system-$(uname -m)
		/usr/local/bin/qemu-system-$(uname -m)
	)

	for b in ${qemu_kvm_possible_emulators[@]}
	do
		if [[ -e ${b} ]]; then
			qemu_kvm=${b}
			break
		fi
	done

	if [[ -z $qemu_kvm ]]; then
		echo "ERROR: Not found qemu-kvm emulator" >&2
		exit 1
	else
		echo $qemu_kvm
	fi

	return 0
}

