#!/bin/bash

set -x

gcc_args=( tst-getaddrinfo.c )
gcc_args+=( -o tst-getaddrinfo )

gcc_args+=( -O2 )
gcc_args+=( -fpie )
gcc_args+=( -fmerge-all-constants )

gcc ${gcc_args[@]}

gcc_args+=( -DHAVE_PRINTF )

gcc ${gcc_args[@]}
