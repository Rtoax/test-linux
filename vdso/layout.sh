#!/bin/bash
set -e

layout_x86()
{
	echo "Display vDSO/vvar layout!!!!!!!"
	sudo bpftrace -e '
	BEGIN {
		$_vdso_data = (struct vdso_data *)kaddr("_vdso_data");

		printf("_vdso_data = %p, size of vdso_data %ld\n",
			$_vdso_data, sizeof(struct vdso_data));
		printf("_vdso_data.seq = %d\n", $_vdso_data->seq);
		printf("_vdso_data.clock_mode = %d\n", $_vdso_data->clock_mode);
		printf("_vdso_data.cycle_last = %ld\n", $_vdso_data->cycle_last);

		exit();
	}'

	sudo bpftrace scripts/vdso_image_64.bt
}

case $(uname -m) in
x86_64)
	layout_x86
	;;
*)
	echo >&2 "ERROR: Not support $(uname -m) yet"
	;;
esac
