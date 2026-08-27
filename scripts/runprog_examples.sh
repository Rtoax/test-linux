#!/bin/bash
set -e

readonly EXAMPLES_ROOT=$(dirname $(realpath $0))

. ${EXAMPLES_ROOT}/liblog.sh

runprog() {
	echo -e "\033[1;32m$ ./runprog.sh ${@}\033[m"
	./runprog.sh "${@}"
}

cleanup() {
	rm -f ls
}
trap cleanup EXIT

runprog -h
runprog -- runprog.sh -h
runprog -- /usr/bin/ls

# test execution under the current directory, and has the same name of system
# command
{
	touch ls
	runprog -- ls

	chmod +x ls
	for ret in $(seq 0 17 255)
	do
		echo "exit ${ret}" > ls
		runprog --expect-return ${ret} -- ls
	done
	rm ls

	runprog -- findelf.sh
}

runprog --env ENV_EXPECT=THISISAEXPECTENV -- tests/expect_env.sh
runprog --maybe-sudo -- du -sh /boot

# test expect return error
{
	for ret in $(seq 0 17 255)
	do
		runprog --expect-return ${ret} -- bash -c \"exit ${ret}\"
	done
}

# test log
{
	# Test 1
	runprog --log ls.log -- ls
	if [[ ! -e ls.log ]] || [[ ! -e ls.stderr.log ]]; then
		error "Generate log failed."
	fi
	rm -f ls.log ls.stderr.log

	# Test 2
	runprog --log ls.log --tty -- ls
	if [[ $(stat -c '%s' ls.log) -ne 0 ]]; then
		error "test --log with --tty failed"
	fi
	rm -rf ls.log
}

runprog --tty -- ls
