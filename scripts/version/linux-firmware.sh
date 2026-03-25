#!/bin/bash
# ref: https://www.kernel.org/pub/linux/kernel/firmware/
set -e

debver() {
	dpkg-query -W -f='${Version}\n' firmware-linux-free 2>/dev/null | \
		grep -v 'no packages found'
}

rpmver() {
	rpm -q --queryformat='%{version}-%{release}\n' linux-firmware 2>/dev/null | \
		grep -v 'is not installed'
}

debver || rpmver
