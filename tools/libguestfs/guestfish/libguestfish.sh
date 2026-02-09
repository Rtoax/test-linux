#!/bin/bash
#
# ref: coreos-assembler
#

set -euo pipefail

export LIBGUESTFS_BACKEND=direct

GUESTFISH_PID=
gf_launch()
{
	if [ -n "$GUESTFISH_PID" ]; then
		return
	fi

	eval "$(guestfish --listen -a "$@")"
	if [ -z "$GUESTFISH_PID" ]; then
		echo "guestfish didn't start up, see error messages above" && exit 1
	fi
}

_gf_cleanup()
{
	guestfish --remote -- exit >/dev/null 2>&1 ||:
}
trap _gf_cleanup EXIT

gf_shutdown()
{
	gf umount-all
	gf exit
	GUESTFISH_RUNNING=
	GUESTFISH_PID=
}

gf()
{
	guestfish --remote -- "$@"
}

GUESTFISH_RUNNING=
gf_run()
{
	if [ -n "$GUESTFISH_RUNNING" ]; then
		return
	fi

	gf_launch "$@"
	gf run

	GUESTFISH_RUNNING=1
}

gf_run_mount()
{
	local mntarg=mount

	if [ "$1" = ro ]; then
		mntarg=mount-ro
		shift
	fi

	gf_run "$@"

	local root=$(gf findfs-label root)
	gf ${mntarg} "${root}" /

	local boot=$(gf findfs-label boot)
	gf ${mntarg} "${boot}" /boot

	local partitions
	local label
	partitions="$(gf list-partitions)"
	for partition in $partitions
	do
		label="$(gf vfs-label "${partition}")"
		if [ "$label" == "EFI-SYSTEM" ]; then
			gf ${mntarg} "${partition}" /boot/efi
		fi
	done

	# more if coreos
}
