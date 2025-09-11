#!/bin/bash

set -e
HEATMAP_ROOT_DIRECTORY=$(dirname `realpath $0`)

program_name=hmctl
heatmap_prog=${HEATMAP_ROOT_DIRECTORY}/build/src/heatmap

binary=


###############################################################################
## record
record_kernel_flag=
record_secs=10

perf_record()
{
	perf record -e cycles:u -j any,u -o perf.data -- "$@"
}

perf_record_kernel()
{
	if [[ $(id -g) != 0 ]]; then
		echo "ERROR: Only running with root(sudo)"
		exit 1
	fi

	sudo timeout ${record_secs} perf record -F 99 --all-kernel -o perf.data

	sudo chown root:root perf.data
}

__record_usage__()
{
	echo -e "

 ${program_name}-record     - record perf.data

   -k, --kernel       record kernel, default: user space
       --secs         record seconds, default: ${record_secs}

   -h, --help         show this help information
   -v, --verbose      show detail during running

  examples:

  # Record ls
  $ ${program_name} record -- /usr/bin/ls -l

  # Record kernel for 20 seconds
  $ sudo ${program_name} record --kernel --secs 20

"

	exit ${1-0}
}

__record_main__()
{
	TEMP=$(getopt \
		--options ks:vh \
		--long kernel \
		--long secs: \
		--long verbose \
		--long help \
		-n ${program_name} -- "$@")

	test $? != 0 && __record_usage__ 1

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-k|--kernel)
			shift
			record_kernel_flag=YES
			;;
		-s|--secs)
			shift
			record_secs=$1
			shift
			;;
		-h|--help)
			shift
			__record_usage__
			;;
		-v|--verbose)
			shift
			set -x
			;;
		--)
			shift
			break
			;;
		esac
	done

	if [[ ! -z ${record_kernel_flag} ]]; then
		perf_record_kernel
	else
		[[ -z "$@" ]] && echo "ERROR: Need specify what to run?" && exit 1

		perf_record "$@"
	fi
}

###############################################################################
## bolt
output_binary=
perf_data=

llvm_bolt()
{
	[[ ! -e perf.data ]] && echo "ERROR: not found perf.data" && exit 1
	[[ -z ${binary} ]] && echo "ERROR: Must specify binary" && exit 1
	[[ ! -e ${binary} ]] && echo "ERROR: ${binary} is not exist" && exit 1
	[[ -z ${output_binary} ]] && echo "ERROR: Must specify output binary" && exit 1

	[[ -z ${perf_data} ]] && echo "WARNING: Need perf.data" && perf_data=perf.data
	[[ ! -e ${perf_data} ]] && echo "ERROR: ${perf_data} is not exist" && exit 1


	perf2bolt -p perf.data -o perf.fdata ${binary}

	llvm-bolt ${binary} -o ${output_binary} \
		-data=perf.fdata \
		-reorder-blocks=ext-tsp \
		-split-functions \
		-split-all-cold \
		-split-eh \
		-dyno-stats
}

__bolt_usage__()
{
	echo -e "

 bolt       - generate new binary with perf.data

            ${program_name} bolt -b /usr/bin/ls -o ./ls-bolt

   -b, --bin          specify binary

   -p, --perf-data    specify perf.data

   -o, --output       specify output binary

   -h, --help         show this help information
   -v, --verbose      show detail during running

"

	exit ${1-0}
}

__bolt_main__()
{
	TEMP=$(getopt \
		--options b:p:o:vh \
		--long bin: \
		--long perf-data: \
		--long output: \
		--long verbose \
		--long help \
		-n ${program_name}-bolt -- "$@")

	test $? != 0 && __bolt_usage__ 1

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-b|--bin)
			shift
			binary=$1
			shift
			;;
		-p|--perf-data)
			shift
			perf_data=$1
			shift
			;;
		-o|--output)
			shift
			output_binary=$1
			shift
			;;
		-h|--help)
			shift
			__bolt_usage__
			;;
		-v|--verbose)
			shift
			set -x
			;;
		--)
			shift
			break
			;;
		esac
	done

	llvm_bolt "$@"
}

###############################################################################
## report
output_txt=
report_kernel=

perf_report()
{
	local txt=$output_txt

	if [[ ! -z $binary ]]; then
		perf report --stdio -n -v -i perf.data \
			| grep ${binary} \
			| awk '{print $5" "$2}' \
			| grep ^0x > ${txt}
	elif [[ ! -z ${report_kernel} ]]; then
		perf report --stdio -n -v -i perf.data \
			| grep '\[k\]' \
			| awk '{print $5" "$2}' \
			| grep ^0x > ${txt}
	else
		perf report --stdio -n -v -i perf.data \
			| awk '{print $5" "$2}' \
			| grep ^0x > ${txt}
	fi
}

__report_usage__()
{
	echo -e "

 report     - report heatmap text file

            ${program_name} report -b /usr/bin/ls

   -b, --bin          specify binary

   -k, --kernel       filter out kernel samples only([k])

   -o, --output       specify output file, default: ${output_txt}

   -h, --help         show this help information
   -v, --verbose      show detail during running

"

	exit ${1-0}
}

__report_main__()
{
	output_txt=heatmap.txt

	TEMP=$(getopt \
		--options b:ko:vh \
		--long bin: \
		--long kernel \
		--long output: \
		--long verbose \
		--long help \
		-n ${program_name}-report -- "$@")

	test $? != 0 && __report_usage__ 1

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-b|--bin)
			shift
			binary=$1
			shift
			;;
		-k|--kernel)
			shift
			report_kernel=YES
			;;
		-o|--output)
			shift
			output_txt=$1
			shift
			;;
		-h|--help)
			shift
			__report_usage__
			;;
		-v|--verbose)
			shift
			set -x
			;;
		--)
			shift
			break
			;;
		esac
	done

	perf_report "$@"

	echo "SAVE: save to ${output_txt}"
}

###############################################################################
## sampleip
sample_kern=
sample_user=
sample_freq=
sample_secs=

__sampleip__()
{
	[[ -z ${output_txt} ]] && echo "ERROR: Must specify output txt" && exit 1
	[[ -e ${output_txt} ]] && echo "ERROR: ${output_txt} is already exist" && exit 1

	make -C $HEATMAP_ROOT_DIRECTORY/src/sampleip/ 2>&1 >/dev/null

	echo "Start sampling... (freq ${sample_freq}Hz, ${sample_secs}s)"

	sudo $HEATMAP_ROOT_DIRECTORY/src/sampleip/sampleip \
		${sample_user:+-u} \
		${sample_kern:+-k} \
		${sample_freq:+-F ${sample_freq}} \
		${sample_secs} \
		| grep ^0x \
		| awk '{print $1" "$3}' > ${output_txt}

	echo "Done to sampling."
}

__sampleip_usage__()
{
	echo -e "

 sampleip     - get heatmap text file

            ${program_name} sampleip -k -o kernel-sampleip.txt

   -k, --kernel       get kernel space samples only
   -u, --user         get user space samples only

   -s, --secs         sample seconds, default 5s
   -F, --freq         sample frequency (Hz)

   -o, --output       specify output file, default: heatmap.txt

   -h, --help         show this help information
   -v, --verbose      show detail during running

"

	exit ${1-0}
}

__sampleip_main__()
{
	output_txt=

	TEMP=$(getopt \
		--options kus:F:o:vh \
		--long kernel \
		--long user \
		--long secs: \
		--long freq: \
		--long output: \
		--long verbose \
		--long help \
		-n ${program_name}-sampleip -- "$@")

	test $? != 0 && __sampleip_usage__ 1

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-k|--kernel)
			shift
			sample_kern=YES
			;;
		-u|--user)
			shift
			sample_user=YES
			;;
		-s|--secs)
			shift
			sample_secs=$1
			shift
			;;
		-F|--freq)
			shift
			sample_freq=$1
			shift
			;;
		-o|--output)
			shift
			output_txt=$1
			shift
			;;
		-h|--help)
			shift
			__sampleip_usage__
			;;
		-v|--verbose)
			shift
			set -x
			;;
		--)
			shift
			break
			;;
		esac
	done

	__sampleip__ "$@"
}

###############################################################################
# compile
compile_src()
{
	local oldpwd=$PWD

	pushd $HEATMAP_ROOT_DIRECTORY
	mkdir -p build
	pushd build
	cmake .. >/dev/null
	make >/dev/null
	popd
	popd
}

###############################################################################
## main
__usage__()
{
	echo -e "
${program_name} [-v|-h] [command]

 -h,--help
 -v,--verbose

 record     - record perf.data
 bolt       - generate new binary with perf.data
 report     - report heatmap text file
 heatmap    - plot heatmap

 sampleip   - new record+report method (use perf_event and ebpf)

"

	exit ${1-0}
}

while :;
do
	case $1 in
	-h|--help)
		shift
		__usage__
		;;
	-v|--verbose)
		shift
		export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
		set -x
		;;
	*)
		break
		;;
	esac
done

case $1 in
heatmap)
	shift
	# Compile for each time
	compile_src
	${heatmap_prog} "$@"
	;;
record)
	shift
	__record_main__ "$@"
	;;
bolt)
	shift
	__bolt_main__ "$@"
	;;
report)
	shift
	__report_main__ "$@"
	;;
sampleip)
	shift
	__sampleip_main__ "$@"
	;;
*)
	__usage__
	;;
esac

