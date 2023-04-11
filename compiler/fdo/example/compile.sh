#!/bin/bash

set -e

prog_name=test

# For clang
profdata=${prog_name}.profdata

compiler=

gcc cachelinesize.c -o cachelinesize
CACHE_LINE_SIZE=$(./cachelinesize)
cflags="-O3 -DTEST_BRANCH -DCACHE_LINE_SIZE=${CACHE_LINE_SIZE}"
sort_srcs="sort.c common.c"
loc_srcs="loc.c common.c"
branch_srcs="branch.c common.c"
loop_srcs="loop.c common.c"


set_test()
{
	local t=$1

	case $t in
	sort)
		prog_name+="-sort"
		srcs="$sort_srcs"
		;;
	loc)
		prog_name+="-loc"
		srcs="$loc_srcs"
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
		echo "Support test list: sort loc branch loop"
		exit 1
		;;
	esac
}

# $1 - input elf file
__common_llvm_bolt_heatmap()
{
	local elf=$1

	perf record -e cycles:u -j any,u -o ${elf}.perf.data -- ./${elf}

	llvm-bolt-heatmap \
		--ignore-build-id \
		-p ${elf}.perf.data \
		${elf} \
		--line-size ${CACHE_LINE_SIZE} \
		-o ${elf}.heatmap

	aha -b -f ${elf}.heatmap > ${elf}.heatmap.html
}

__common_bolt()
{
	local _prog_bolt=${prog_name}-bolt.out

	rm -f ${prog_name}-orig.perf.data ${prog_name}-orig.perf.fdata

	__record() {
		perf record -e cycles:u -j any,u \
			-o ${prog_name}-orig.perf.data -- ./${prog_name}-orig.out
	}

	__record

	set +e

	# Make sure perf2bolt running successfully
	while ! perf2bolt \
		--ignore-build-id \
		-p ${prog_name}-orig.perf.data \
		-o ${prog_name}-orig.perf.fdata \
		${prog_name}-orig.out
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
		-dyno-stats
}

# 普通编译
gcc_ordinary()
{
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

# 使用AutoFDO
gcc_autofdo()
{
	gcc_ordinary

	perf record -b -e br_inst_retired.near_taken:pp -- ./${prog_name}-orig.out

	create_gcov \
		--binary=./${prog_name}-orig.out \
		--profile=perf.data \
		--gcov=sort.gcov \
		-gcov_version=1 >/dev/null

	gcc ${cflags} -fauto-profile=sort.gcov ${srcs} -o ${prog_name}-autofdo.out
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
	clang ${cflags} ${srcs} -o ${prog_name}-orig.out
}

clang_gen_prof()
{
	local _prog=${prog_name}-genprof.out

	clang ${cflags} ${srcs} -o ${_prog} \
		-fexperimental-new-pass-manager \
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
		-fexperimental-new-pass-manager \
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
		cachelinesize \
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

 -t, --test                test: sort, loc, branch, loop

 --noclean                 do not clean anything before compile

 -v, --verbose             show detail.
 -h, --help                show this help information

" | more

	exit ${1-0}
}

__main__()
{
	local noclean

	TEMP=$(getopt \
		--options c:t:vh \
		--long compiler: \
		--long test: \
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
		-t | --test)
			shift
			set_test $1
			shift
			;;
		--noclean)
			shift
			noclean=YES
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
	[[ -z "$srcs" ]] && echo "ERROR: Must specify -t, --test" && exit 1

	[[ -z ${noclean} ]] && clean

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
#	gcc_autofdo
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

size ${prog_name}*.out
md5sum ${prog_name}*.out
