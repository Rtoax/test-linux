#!/bin/bash
set -e

features=(sse sse2 ssse3 sse4_1 sse4_2)

../sh/cpu_feature_check ${features[@]}

gcc -msse2 -dM -E - < /dev/null | grep SSE
gcc -msse3 -dM -E - < /dev/null | grep SSE3
gcc -msse4 -dM -E - < /dev/null | grep SSE4
