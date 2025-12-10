#!/bin/bash
#
# GDSIO benchmark
#

set -e

[[ -z ${GDSIO} ]] && GDSIO=gdsio
[[ -z ${SIZE} ]] && SIZE=4G
[[ ${DIR} ]] && DIR="-D ${DIR}"

runprog() {
	# drop cache for each test
	echo 3 > /proc/sys/vm/drop_caches
	eval ${@}
}

for thread in 1 2 4 8 16
do
	# GPU write to Storage
	runprog ./${GDSIO} ${DIR} -f a.out -s ${SIZE} -x 0 -I 1 -w ${thread}
	# GPU read from Storage
	runprog ./${GDSIO} ${DIR} -f a.out -s ${SIZE} -x 0 -I 0 -w ${thread}
done

for thread in 1 2 4 8 16
do
	# CPU write to Storage
	runprog ./${GDSIO} ${DIR} -f b.out -s ${SIZE} -x 1 -I 1 -w ${thread}
	# CPU read from Storage
	runprog ./${GDSIO} ${DIR} -f b.out -s ${SIZE} -x 1 -I 0 -w ${thread}
done

for thread in 1 2 4 8 16
do
	# GPU->CPU->Storage
	runprog ./${GDSIO} ${DIR} -f c.out -s ${SIZE} -x 2 -I 1 -w ${thread}
	# Storage->CPU->GPU
	runprog ./${GDSIO} ${DIR} -f c.out -s ${SIZE} -x 2 -I 0 -w ${thread}
done
