#!/bin/bash
# Tracing CUDA liked kernel launching.

set -e

declare -a UPROBES URETPROBES

readonly TRACING_TYPE_LATENCY=latency
readonly TRACING_TYPE_LAUNCH=launch
readonly TRACING_TYPES=( ${TRACING_TYPE_LATENCY} ${TRACING_TYPE_LAUNCH} )
TRACING_TYPE=${TRACING_TYPE_LAUNCH}

__usage__()
{
	echo -e "
${BOLD}NAME${RST}
	Kernellaunch.bt.sh - Tracing CUDA kernel Launch

${BOLD}ARGUMENT${RST}
	-T, --trace-type [T]     tracing type: ${TRACING_TYPES[@]}

	-h, --help               show this help information
	-v, --verbose            show detail during running

" | more
	exit ${1-0}
}

error() {
	echo -e >&2 "${RED}ERROR: ${@}${RST}"
	exit 1
}

TEMP_ARGS=$(getopt \
	--options T:vh \
	--long trace-type: \
	--long verbose \
	--long help \
	-n patchset -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$TEMP_ARGS"

while true; do
	case $1 in
	-T|--trace-type)
		shift
		TRACING_TYPE=$1
		if ! [[ " ${TRACING_TYPES[@]} " =~ " ${TRACING_TYPE} " ]]; then
			error "Not support ${TRACING_TYPE}, only: ${TRACING_TYPES[@]}"
		fi
		shift
		;;
	-h|--help)
		shift
		__usage__
		;;
	-v|--verbose)
		shift
		export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
		set -x
		;;
	--)
		shift
		break
		;;
	esac
done

# HPCC
if [[ -e /opt/hpcc/lib/libhcruntime.so ]]; then
	UPROBES+=( uprobe:/opt/hpcc/lib/libhcruntime.so:hcLaunchKernel )
	URETPROBES+=( uretprobe:/opt/hpcc/lib/libhcruntime.so:hcLaunchKernel )
fi

# LUCA
if [[ -e /opt/luca/lib/libhcruntime.so ]]; then
	UPROBES+=( uprobe:/opt/luca/lib/libhcruntime.so:hcLaunchKernel )
	URETPROBES+=( uretprobe:/opt/luca/lib/libhcruntime.so:hcLaunchKernel )
fi
if [[ -e /opt/luca/lib/liblcruntime.so ]]; then
	UPROBES+=( uprobe:/opt/luca/lib/liblcruntime.so:lcLaunchKernel )
	URETPROBES+=( uretprobe:/opt/luca/lib/liblcruntime.so:lcLaunchKernel )
fi

# ROCm
if [[ -e /lib64/libamdhip64.so.6 ]]; then
	UPROBES+=( uprobe:/lib64/libamdhip64.so.6:hipLaunchKernel )
	URETPROBES+=( uretprobe:/lib64/libamdhip64.so.6:hipLaunchKernel )
fi

# CUDA
if [[ -e /lib64/libcuda.so ]]; then
	UPROBES+=( uprobe:/lib64/libcuda.so:cuLaunchKernel )
	URETPROBES+=( uretprobe:/lib64/libcuda.so:cuLaunchKernel )
fi

# FakeCUDA
if [[ -e ../fakeCUDA/libhcruntime.so ]]; then
	UPROBES+=( uprobe:../fakeCUDA/libhcruntime.so:hcLaunchKernel )
	URETPROBES+=( uretprobe:../fakeCUDA/libhcruntime.so:hcLaunchKernel )
fi
if [[ -e ../fakeCUDA/libamdhip64.so.6 ]]; then
	UPROBES+=( uprobe:../fakeCUDA/libamdhip64.so.6:hipLaunchKernel )
	URETPROBES+=( uretprobe:../fakeCUDA/libamdhip64.so.6:hipLaunchKernel )
fi

probes() {
	local arr=( ${@} )
	old_IFS=$IFS
	IFS=","
	echo "${arr[*]}"
	IFS=$old_IFS
}


case ${TRACING_TYPE} in
${TRACING_TYPE_LAUNCH})
	sudo tee tmp-klaunch.bt <<-EOF
	#!/bin/env bpftrace
	BEGIN {
		printf("Tracing CUDA Kernel Launch, hit ctrl-c to end.\n");
		printf("%-8s %-8s %-16s %s\n", "TIME", "PID", "COMM", "PROBE");
	}
	EOF
	sudo tee --append tmp-klaunch.bt <<-EOF
	$(probes ${UPROBES[@]}) {
		time("%H:%M:%S ");
		printf("%-8d %-16s %s\n", pid, comm, probe);
	}
	$(probes ${URETPROBES[@]}) {
		time("%H:%M:%S ");
		printf("%-8d %-16s %s %d\n", pid, comm, probe, retval);
	}
	EOF

	sudo tee --append tmp-klaunch.bt <<-EOF
	END {
		printf("Bye.\n");
	}
	EOF
	;;
${TRACING_TYPE_LATENCY})
	error TODO
	;;
esac

sudo bpftrace tmp-klaunch.bt
