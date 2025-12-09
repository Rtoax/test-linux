#!/bin/bash
set -e

SIZE=1G

drop_cache() {
	echo 3 | tee /proc/sys/vm/drop_caches
}

drop_cache

# GPU->Storage
./gdsio -f a.out -s ${SIZE} -x 0 -I 1
drop_cache
# Storage->GPU
./gdsio -f a.out -s ${SIZE} -x 0 -I 0
drop_cache

# CPU->Storage
./gdsio -f b.out -s ${SIZE} -x 1 -I 1
drop_cache
# Storage->CPU
./gdsio -f b.out -s ${SIZE} -x 1 -I 0
drop_cache

# GPU->CPU->Storage
./gdsio -f c.out -s ${SIZE} -x 2 -I 1
drop_cache
# Storage->CPU->GPU
./gdsio -f c.out -s ${SIZE} -x 2 -I 0
drop_cache
