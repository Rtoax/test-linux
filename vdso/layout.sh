#!/bin/bash
set -e

layout_x86()
{
	local VDSO_DATA

	if [[ $(grep 'D _vdso_data' /proc/kallsyms) ]]; then
		VDSO_DATA="_vdso_data"
	# kernel commit 7175126a6d45 ("x86/vdso: Allocate vvar page from C code")
	# v6.12-rc2-27-g7175126a6d45, rename _vdso_data to vdso_data.
	elif [[ $(grep 'D vdso_data' /proc/kallsyms) ]]; then
		VDSO_DATA="vdso_data"
	else
		# linux v6.14 is 'T vdso_data' (fedora 42)
		if [[ $(grep 'T vdso_data' /proc/kallsyms) ]]; then
			VDSO_DATA="vdso_data"
		else
			return 0
		fi
	fi

	echo "Display vDSO/vvar layout!!!!!!!"

	cat>a.bt.out <<-EOF
	BEGIN {
		\$data = (struct vdso_data *)kaddr("${VDSO_DATA}");

		printf("${VDSO_DATA} = %p, size of vdso_data %ld\n",
			\$data, sizeof(struct vdso_data));
		printf("${VDSO_DATA}.seq = %d\n", \$data->seq);
		printf("${VDSO_DATA}.clock_mode = %d\n", \$data->clock_mode);
		printf("${VDSO_DATA}.cycle_last = %ld\n", \$data->cycle_last);

		exit();
	}
	EOF

	sudo bpftrace a.bt.out
	sudo bpftrace scripts/vdso_image_64.bt
}

case $(uname -m) in
x86_64)
	layout_x86
	;;
*)
	echo >&2 "WARNING: Not support $(uname -m) yet"
	exit 0
	;;
esac
