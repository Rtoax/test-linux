#!/bin/bash
set -e

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
runprog --maybe-sudo -- du -sh /boot/efi/EFI/BOOT/fbaa64.efi

for ret in $(seq 0 17 255)
do
	runprog --expect-return ${ret} -- bash  -c \"exit ${ret}\"
done
