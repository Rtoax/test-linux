#!/bin/bash

set -e

. clean.sh

prog_name=sort

# For clang
profdata=${prog_name}.profdata

compiler=

gcc cachelinesize.c -o cachelinesize
cflags="-O3 -DCACHE_LINE_SIZE=$(./cachelinesize)"
srcs="sort.c common.c"


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

clang_orig()
{
	clang ${cflags} ${srcs} -o ${prog_name}.out
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

compile-gcc [args]

 -c, --compiler            specify compiler, gcc or clang

 -a, --cacheline-align     cacheline align

 -h, --help                show this help information

" | more

	exit ${1-0}
}

__main__()
{
	TEMP=$(getopt \
		--options c:ah \
		--long compiler: \
		--long cacheline-align \
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
		-a | --cacheline-align)
			shift
			cflags+=" -DCACHELINE_ALIGN"
			prog_name+="-cacheline-align"
			profdata=${prog_name}.profdata
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

	return 0
}

__main__ "$@"


case $compiler in
gcc)
	gcc_ordinary
	gcc_fdo
	gcc_autofdo
	;;
clang)
	clang_orig
	clang_fdo
	;;
esac

size ${prog_name}*.out
md5sum ${prog_name}*.out
