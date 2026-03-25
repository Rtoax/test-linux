#!/bin/bash
# ref: https://www.kernel.org/pub/linux/kernel/firmware/
set -e

debver() {
	dpkg-query -W -f='${Version}\n' firmware-linux-free
}

rpmver() {
	rpm -q --queryformat='%{version}-%{release}\n' linux-firmware 2>/dev/null
}

debver || rpmver
