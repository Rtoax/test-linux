#!/bin/bash
set -e

[[ -z ${GDSIO} ]] && GDSIO=gdsio
[[ ${VERIFY} ]] && VERIFY=-V
SIZE=1G

drop_cache() {
	echo 3 > /proc/sys/vm/drop_caches
}

drop_cache

# GPU->Storage
./${GDSIO} -f a.out -s ${SIZE} -x 0 -I 1
drop_cache
# Storage->GPU
./${GDSIO} -f a.out -s ${SIZE} -x 0 -I 0 ${VERIFY}
drop_cache

# CPU->Storage
./${GDSIO} -f b.out -s ${SIZE} -x 1 -I 1
drop_cache
# Storage->CPU
./${GDSIO} -f b.out -s ${SIZE} -x 1 -I 0 ${VERIFY}
drop_cache

# GPU->CPU->Storage
./${GDSIO} -f c.out -s ${SIZE} -x 2 -I 1
drop_cache
# Storage->CPU->GPU
./${GDSIO} -f c.out -s ${SIZE} -x 2 -I 0 ${VERIFY}
drop_cache
