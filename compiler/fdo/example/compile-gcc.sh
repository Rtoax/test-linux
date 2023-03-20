#!/bin/bash

set -e

# 普通编译
gcc_ordinary()
{
	gcc sort.c -o sort.out
}

# 优化编译
gcc_optimized()
{
	gcc -O3 sort.c -o sort_optimized-O3.out
}

# 生成profile，并使用
gcc_fdo()
{
	gcc sort.c -o sort_fdo.out -fprofile-generate

	./sort_fdo.out

	gcc -O3 sort.c -o sort_fdo.out \
		-fprofile-use=sort.gcda
}

# 使用AutoFDO
gcc_autofdo()
{
	gcc_ordinary

	perf record -b -e br_inst_retired.near_taken:pp -- ./sort.out

	create_gcov --binary=./sort.out --profile=perf.data \
		    --gcov=sort.gcov -gcov_version=1 >/dev/null

	gcc -O3 -fauto-profile=sort.gcov sort.c -o sort_autofdo.out
}


. clean.sh

gcc_ordinary
gcc_optimized
gcc_fdo
gcc_autofdo

