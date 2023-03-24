#!/bin/bash

set -e

. config
. clean.sh

prog_name=gcc-sort

cflags="${CONFIG_CFLAGS}"
srcs="${CONFIG_SRC}"


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



gcc_ordinary
gcc_fdo
gcc_autofdo

size ${prog_name}*.out
md5sum ${prog_name}*.out
