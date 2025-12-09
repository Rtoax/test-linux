#!/bin/bash
#
# GDSIO benchmark
#

set -e

[[ -z ${GDSIO} ]] && GDSIO=gdsio
[[ ${VERIFY} ]] && VERIFY=-V
[[ -z ${SIZE} ]] && SIZE=1G
[[ ${DIR} ]] && DIR="-D ${DIR}"

drop_cache() {
	echo 3 > /proc/sys/vm/drop_caches
}

drop_cache

# GPU->Storage
./${GDSIO} ${DIR} -f a.out -s ${SIZE} -x 0 -I 1
drop_cache
# Storage->GPU
./${GDSIO} ${DIR} -f a.out -s ${SIZE} -x 0 -I 0 ${VERIFY}
drop_cache

# CPU->Storage
./${GDSIO} ${DIR} -f b.out -s ${SIZE} -x 1 -I 1
drop_cache
# Storage->CPU
./${GDSIO} ${DIR} -f b.out -s ${SIZE} -x 1 -I 0 ${VERIFY}
drop_cache

# GPU->CPU->Storage
./${GDSIO} ${DIR} -f c.out -s ${SIZE} -x 2 -I 1
drop_cache
# Storage->CPU->GPU
./${GDSIO} ${DIR} -f c.out -s ${SIZE} -x 2 -I 0 ${VERIFY}
drop_cache
