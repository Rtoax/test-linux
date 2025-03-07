#!/bin/bash
set -e

prog_name=test

# For clang
profdata=${prog_name}.profdata

compiler=

CACHE_LINE_SIZE=$(getconf LEVEL3_CACHE_LINESIZE)
cflags_orig="-DCACHE_LINE_SIZE=${CACHE_LINE_SIZE} -g"
cflags_opt="-O3"
cflags+="${cflags_opt} ${cflags_orig}"

sort_srcs="sort.c common.c"
branch_srcs="branch.c common.c"
loop_srcs="loop.c common.c"

# autofdo: Test all branches_retired
af_br_all=

log_file=/dev/null

test_type=
set_test()
{
	local t=$1

	case $t in
	sort)
		prog_name+="-sort"
		srcs="$sort_srcs"
		;;
	branch)
		prog_name+="-branch"
		srcs="$branch_srcs"
		;;
	loop)
		prog_name+="-loop"
		srcs="$loop_srcs"
		;;
	*)
		echo "Support test list: sort branch loop"
		exit 1
		;;
	esac

	test_type=$t
}

# Do something after compile
test_test()
{
	case $test_type in
	sort)
		;;
	branch)
		echo "Branch of statement"
		dump_branch() {
			local bin=$1
			local fun=$2
			echo -e "\033[1;32m>>> $bin:$fun <<<\033[0m"
			gdb -batch \
				-ex "file $bin" \
				-ex "disassemble $fun" \
				| grep branch_f_ \
				| sed "s|^|\t$fun|g"
		}
		dump_branch ${prog_name}-orig-pure.out branch_A
		dump_branch ${prog_name}-orig-pure.out branch_B
		dump_branch ${prog_name}-orig.out branch_A
		dump_branch ${prog_name}-orig.out branch_B
		dump_branch ${prog_name}-fdo.out branch_A
		dump_branch ${prog_name}-fdo.out branch_B
		if [[ $compiler == gcc ]]; then
			for p in $(ls ${prog_name}-autofdo*.out)
			do
				dump_branch ${p} branch_A
				dump_branch ${p} branch_B
			done
		fi
		dump_branch ${prog_name}-bolt.out branch_A
		dump_branch ${prog_name}-bolt.out branch_B
		;;
	loop)
		;;
	*)
		echo "Support test list: sort branch loop"
		exit 1
		;;
	esac
}

# $1 - input elf file
__common_llvm_bolt_heatmap()
{
	local elf=$1

	perf record -e cycles:u -j any,u -o ${elf}.perf.data -- ./${elf} \
		2>&1 >>${log_file}

	llvm-bolt-heatmap \
		--ignore-build-id \
		-p ${elf}.perf.data \
		${elf} \
		--line-size ${CACHE_LINE_SIZE} \
		-o ${elf}.heatmap \
	2>&1 >>${log_file}

	# Convert terminal output to HTML
	aha -b -f ${elf}.heatmap > ${elf}.heatmap.html
}

__common_bolt()
{
	local _prog_bolt=${prog_name}-bolt.out

	rm -f ${prog_name}-orig.perf.data ${prog_name}-orig.perf.fdata

	__record() {
		perf record -e cycles:u -j any,u \
			-o ${prog_name}-orig.perf.data -- ./${prog_name}-orig.out \
		2>&1 >>${log_file}
	}

	__record

	set +e

	# Make sure perf2bolt running successfully
	while ! perf2bolt \
		--ignore-build-id \
		-p ${prog_name}-orig.perf.data \
		-o ${prog_name}-orig.perf.fdata \
		${prog_name}-orig.out \
	2>&1 >>${log_file}
	do
		__record
	done

	set -e

		#-reorder-functions=hfsort \
	llvm-bolt ${prog_name}-orig.out -o ${_prog_bolt} \
		-data=${prog_name}-orig.perf.fdata \
		-reorder-blocks=ext-tsp \
		-split-functions \
		-split-all-cold \
		-split-eh \
		-dyno-stats \
	2>&1 >>${log_file}

}

# 普通编译
gcc_ordinary()
{
	gcc ${cflags_orig} ${srcs} -o ${prog_name}-orig-pure.out
	gcc ${cflags} ${srcs} -o ${prog_name}-orig.out
}

# 生成profile，并使用
gcc_fdo()
{
	gcc ${cflags} ${srcs} -o ${prog_name}-fdo.out -fprofile-generate

	./${prog_name}-fdo.out

	# -fprofile-use will use default gcda profile
	gcc ${cflags} ${srcs} -o ${prog_name}-fdo.out -fprofile-use
}

dump_all_gcov()
{
	for g in `ls *.gcov`
	do
		echo
		echo -e "\033[1;32m>>> $g <<<\033[0m"
		dump_gcov $g
	done
}

# 使用AutoFDO
gcc_autofdo_1()
{
	# Default
	local br_retired=br_inst_retired.near_taken

	if [[ ! -z $1 ]]; then
		br_retired=$1
	fi

	gcc_ordinary

	echo "=== ${br_retired}"
	perf record -b -e ${br_retired} -o ${prog_name}-afdo-${br_retired}.perf.data \
		-- ./${prog_name}-orig.out \
		2>&1 >>${log_file}


	# true: skip 0 samples error
	create_gcov \
		--binary=./${prog_name}-orig.out \
		--profile=${prog_name}-afdo-${br_retired}.perf.data \
		--gcov=${prog_name}-afdo-${br_retired}.gcov \
		-gcov_version=1 >/dev/null \
	2>&1 >>${log_file} \
	|| true

	if [[ ! -e ${prog_name}-afdo-${br_retired}.gcov ]]; then
		return 0
	fi

	gcc ${cflags} -fauto-profile=${prog_name}-afdo-${br_retired}.gcov \
		${srcs} -o ${prog_name}-autofdo-${br_retired}.out
}

gcc_autofdo()
{
	# perf list : pipeline
	branches_retired=( $(perf list | grep -e ' br_') )

	for br in ${branches_retired[@]}
	do
		gcc_autofdo_1 $br
	done

	dump_all_gcov
}

gcc_bolt()
{
	gcc_ordinary

	__common_bolt
}

gcc_heatmap()
{
	__common_llvm_bolt_heatmap ${prog_name}-orig.out
	__common_llvm_bolt_heatmap ${prog_name}-fdo.out
	__common_llvm_bolt_heatmap ${prog_name}-bolt.out
}

clang_orig()
{
	clang ${cflags_orig} ${srcs} -o ${prog_name}-orig-pure.out
	clang ${cflags} ${srcs} -o ${prog_name}-orig.out
}

clang_gen_prof()
{
	local _prog=${prog_name}-genprof.out

	clang ${cflags} ${srcs} -o ${_prog} \
		-fprofile-generate

	# Generate default.profraw
	./${_prog}

	llvm-profdata merge --output ${profdata} default*.profraw
}

clang_fdo()
{
	local _prog_pgo=${prog_name}-pgo.out
	local _prog_fdo=${prog_name}-fdo.out


	clang_gen_prof

	clang ${cflags} ${srcs} -o ${_prog_pgo} \
		-fprofile-use=${profdata}

	# FIXME: How to FDO?
	ln -s ${_prog_pgo} ${_prog_fdo}
}

clang_bolt()
{
	clang_orig

	__common_bolt
}

clang_heatmap()
{
	__common_llvm_bolt_heatmap ${prog_name}-orig.out
	__common_llvm_bolt_heatmap ${prog_name}-fdo.out
	__common_llvm_bolt_heatmap ${prog_name}-bolt.out
}

clean()
{
	rm -f *.out *.gcda *.profraw *.profdata \
		*perf.data* \
		*perf.fdata* \
		*.gcov  \
		*.heatmap*
}

set_compiler()
{
	case $1 in
	gcc | clang)
		compiler=$1
		prog_name=$compiler-$prog_name
		profdata=${prog_name}.profdata
		;;
	*)
		echo "Unknown compiler, only support gcc, clang"
		exit 1
		;;
	esac
}

__usage__()
{
	echo -e "

compile-gcc [clean] [args]

 clean                     clean and return

 -c, --compiler            specify compiler, gcc or clang

 -t, --type                test type: sort, branch, loop

 -a, --af-all              test all branches retired for autofdo

 -l, --log                 specify log file, default: $log_file
 --test-only               only running test_test()
 --noclean                 do not clean anything before compile

 -v, --verbose             show detail.
 -h, --help                show this help information

" | more

	exit ${1-0}
}

__main__()
{
	local noclean testonly

	TEMP=$(getopt \
		--options c:t:al:vh \
		--long compiler: \
		--long type: \
		--long test-only \
		--long af-all \
		--long log: \
		--long noclean \
		--long verbose \
		--long help \
		-n compile-gcc -- "$@")

	test $? != 0 && __usage__ 1

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-c | --compiler)
			shift
			set_compiler $1
			shift
			;;
		-t | --type)
			shift
			set_test $1
			shift
			;;
		-a | --af-all)
			shift
			af_br_all=YES
			;;
		-l | --log)
			shift
			log_file=$1
			shift
			;;
		--noclean)
			shift
			noclean=YES
			;;
		--test-only)
			shift
			noclean=YES
			testonly=YES
			;;
		-v | --verbose)
			shift
			export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
			set -x
			;;
		-h | --help)
			shift
			__usage__
			;;
		--)
			shift
			break
			;;
		esac
	done

	[[ -z $compiler ]] && echo "ERROR: Must specify -c, --compiler" && exit 1
	[[ -z "$srcs" ]] && echo "ERROR: Must specify -t, --type" && exit 1

	[[ -z ${noclean} ]] && clean

	if [[ ! -z $testonly ]]; then
		[[ -z $compiler ]] && echo "ERROR: Must specify -c" && exit 1
		[[ -z $test_type ]] && echo "ERROR: Must specify -t" && exit 1
		test_test

		exit 0
	fi

	return 0
}

case $1 in
clean)
	clean
	exit 0
	;;
esac

__main__ "$@"

case $compiler in
gcc)
	gcc_ordinary
	gcc_fdo
	if [[ ! -z $af_br_all ]]; then
		gcc_autofdo
	else
		gcc_autofdo_1
	fi
	gcc_bolt
	gcc_heatmap
	;;
clang)
	clang_orig
	clang_fdo
	clang_bolt
	clang_heatmap
	;;
esac

size ${prog_name}*.out 2>&1 >>${log_file}
md5sum ${prog_name}*.out 2>&1 >>${log_file}

test_test

