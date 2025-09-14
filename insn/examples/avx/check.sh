#!/bin/bash
set -e

features=(avx avx2 avx512f)

../sh/cpu_feature_check ${features[@]}

gcc -mavx2 -dM -E - < /dev/null | grep AVX2
gcc -mavx512f -dM -E - < /dev/null | grep AVX512F

for i in 4fmaps 4vnniw ifma vbmi vpopcntdq
do
	echo "==== $i ===="
	gcc -mavx512$i -dM -E - < /dev/null | egrep "AVX512" | sort
done
