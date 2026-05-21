#!/bin/bash
set -e

./runprog.sh -h
./runprog.sh -- runprog.sh -h
./runprog.sh -- /usr/bin/ls

{
	touch ls
	./runprog.sh -- ls
	rm ls
}

./runprog.sh -- findelf.sh
./runprog.sh --env ENV_EXPECT=THISISAEXPECTENV -- tests/expect_env.sh
