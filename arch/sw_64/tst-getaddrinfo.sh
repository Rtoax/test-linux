#!/bin/bash

set -x

gcc_args=( tst-getaddrinfo.c )
gcc_args+=( -o tst-getaddrinfo )

gcc_args+=( -O2 )
gcc_args+=( -fpie )
gcc_args+=( -fmerge-all-constants )
# Try to fix compile error on sw_64
gcc_args+=( -Wl,-mgprel-size=32 )

gcc ${gcc_args[@]}

gcc_args+=( -DHAVE_PRINTF )

gcc ${gcc_args[@]}
