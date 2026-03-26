#!/bin/bash
# ref: https://www.kernel.org/pub/linux/kernel/firmware/
set -e

debver() {
	for fw in firmware-linux-free linux-firmware END; do
		if dpkg-query -W -f='${Version}\n' ${fw} 2>/dev/null | \
			grep -v 'no packages found'; then
			break
		fi
	done
	[[ ${fw} == END ]] && return 1
}

rpmver() {
	rpm -q --queryformat='%{version}-%{release}\n' linux-firmware 2>/dev/null | \
		grep -v 'is not installed'
}

debver || rpmver
