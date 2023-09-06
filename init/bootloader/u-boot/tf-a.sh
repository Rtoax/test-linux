#!/bin/bash

. config

cross_qemu() {
	pushd ${TURST_FIRMWARE_A_DIR}
	make PLAT=qemu DEBUG=1 CROSS_COMPILE=aarch64-linux-gnu- -j8 all
	popd
}

cross_rk3328() {
	pushd ${TURST_FIRMWARE_A_DIR}
	make PLAT=rk3328 CROSS_COMPILE=aarch64-linux-gnu- fip all -j8
	popd
}

usage()
{
	cat <<-EOF

	compile [type]

	type: cross-qemu cross-rk3328

		-v, --verbose
		-h, --help

	EOF
}

while true
do
case $1 in
-v | --verbose)
	shift
	export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
	set -x
	;;
-h | --help)
	shift
	usage
	exit 0
	;;
*)
	break
	;;
esac
done

case $1 in
cross-qemu)
	cross_qemu
	;;
cross-rk3328)
	cross_rk3328
	;;
*)
	usage
	echo "ERROR: Unsupport '$1'"
	exit 1
	;;
esac
