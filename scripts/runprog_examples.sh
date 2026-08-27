#!/bin/bash
set -e

readonly EXAMPLES_ROOT=$(dirname $(realpath $0))

. ${EXAMPLES_ROOT}/liblog.sh

runprog() {
	./runprog.sh "${@}"
}

runprog -h
runprog -- runprog.sh -h
runprog -- /usr/bin/ls

{
	touch ls
	runprog -- ls
	rm ls
}

runprog -- findelf.sh
runprog --env ENV_EXPECT=THISISAEXPECTENV -- tests/expect_env.sh
runprog --maybe-sudo -- du -sh /boot

for ret in $(seq 0 17 255)
do
	runprog --expect-return ${ret} -- bash  -c \"exit ${ret}\"
done

runprog --log ls.log -- ls
if [[ ! -e ls.log ]] || [[ ! -e ls.stderr.log ]]; then
	error "Generate log failed."
fi
